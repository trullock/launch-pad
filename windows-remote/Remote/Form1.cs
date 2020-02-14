using System;
using System.ComponentModel;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;

namespace Remote
{
	public partial class Form1 : Form
	{
		SerialPort port;
		IPEndPoint broadcastAddress;
		UdpClient udpClient;
		TcpClient tcpClient;
		byte[] tcpBuffer = new byte[256];

		public Form1()
		{
			InitializeComponent();
			this.Closing += Form1_Closing;
		}

		void Form1_Closing(object sender, CancelEventArgs e)
		{
			if (port != null && port.IsOpen)
				port.Close();
		}

		void Form1_Load(object sender, EventArgs e)
		{
			var portNames = SerialPort.GetPortNames().Distinct();
			foreach (var portName in portNames)
				cbCOMPort.Items.Add(portName);

			cbCOMPort.SelectedItem = cbCOMPort.Items[cbCOMPort.Items.Count - 1];
		}

		void btnConnect_Click(object sender, EventArgs e)
		{
			port = new SerialPort((string)cbCOMPort.SelectedItem, 4800);
			port.Open();
			port.DataReceived += Port_DataReceived;
		}

		void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
		{
			var txt = port.ReadExisting();
			SetText(txt);
		}

		delegate void SetTextCallback(string text);

		void SetText(string text)
		{
			// InvokeRequired required compares the thread ID of the
			// calling thread to the thread ID of the creating thread.
			// If these threads are different, it returns true.
			if (this.txtConsole.InvokeRequired)
			{
				SetTextCallback d = new SetTextCallback(SetText);
				this.Invoke(d, new object[] { text });
			}
			else
			{
				this.txtConsole.AppendText(text);
			}
		}

		void btnArm_Click(object sender, EventArgs e)
		{
			sendTCP("Arm");
		}

		void btnTestContinuity_Click(object sender, EventArgs e)
		{
			sendTCP("TestContinuity");
		}

		void btnDisarm_Click(object sender, EventArgs e)
		{
			sendTCP("Disarm");
		}

		void btnFire_Click(object sender, EventArgs e)
		{
			sendTCP("Fire");
		}

		void btnDisconnect_Click(object sender, EventArgs e)
		{
			if(port != null && port.IsOpen)
				port.Close();
		}

		private void btnClear_Click(object sender, EventArgs e)
		{
			txtConsole.Text = string.Empty;
		}

		private IPAddress LocalIPAddress()
		{
			if (!System.Net.NetworkInformation.NetworkInterface.GetIsNetworkAvailable())
			{
				return null;
			}

			IPHostEntry host = Dns.GetHostEntry(Dns.GetHostName());

			return host
				.AddressList
				.FirstOrDefault(ip => ip.AddressFamily == AddressFamily.InterNetwork);
		}

		void btnUdpListen_Click(object sender, EventArgs e)
		{
			this.broadcastAddress = new IPEndPoint(IPAddress.Any, 4321);
			this.udpClient = new UdpClient();
			this.udpClient.EnableBroadcast = true;
			this.udpClient.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, true);
			//this.udpClient.ExclusiveAddressUse = true;
			this.udpClient.Client.Bind(this.broadcastAddress);

			this.udpClient.BeginReceive(this.ReceiveUdp, null);
		}

		void ConnectTCP(string hostname)
		{
			try
			{
				tcpClient = new TcpClient();
				SetText("Connecting.....\r\n");

				tcpClient.Connect(hostname, 4321);
				// use the ipaddress as in the server program
				//tcpClient.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.KeepAlive, true);
				
				SetText("Connected\r\n");
				Stream stm = tcpClient.GetStream();

				stm.BeginRead(tcpBuffer, 0, tcpBuffer.Length, HandleTcpResponse, stm);
				
			}

			catch (Exception e)
			{
				SetText("Error..... " + e.StackTrace);
			}
		}

		void HandleTcpResponse(IAsyncResult ar)
		{
			if (tcpClient == null)
				return;

			var stm = ar.AsyncState as Stream;

			if (!stm.CanRead)
				return;

			var bytesRead = stm.EndRead(ar);
			if(bytesRead > 0)
				SetText(Encoding.ASCII.GetString(tcpBuffer, 0, bytesRead));

			stm.BeginRead(this.tcpBuffer, 0, tcpBuffer.Length, HandleTcpResponse, stm);
		}


		void sendTCP(string message)
		{
			try
			{
				Stream stm = tcpClient.GetStream();

				ASCIIEncoding asen = new ASCIIEncoding();
				byte[] ba = asen.GetBytes(message + '\0');
				SetText("Transmitting: " + message + "\r\n");

				stm.Write(ba, 0, ba.Length);
				//stm.Flush();
			}
			catch (Exception e)
			{
				SetText("Error..... " + e.StackTrace);
			}
		}
		void ReceiveUdp(IAsyncResult ar)
		{
			var from = new IPEndPoint(IPAddress.Any, 4321);
			var buffer = this.udpClient.EndReceive(ar, ref from);
			var data = Encoding.ASCII.GetString(buffer);

			if (data == "hello")
			{
				//ConnectTCP(from.Address.ToString());
			}

			SetText("UDP: " + from.ToString() + ": " + data + "\r\n");

			this.udpClient.BeginReceive(this.ReceiveUdp, null);
		}

		private void button1_Click(object sender, EventArgs e)
		{
			ConnectTCP("192.168.2.251");
		}

		protected override void Dispose(bool disposing)
		{
			if(tcpClient != null)
				tcpClient.Close();

			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		private void btnTcpDisconnect_Click(object sender, EventArgs e)
		{

			if (tcpClient != null)
			{
				tcpClient.Close();
				tcpClient.Dispose();
				tcpClient = null;
			}
		}
	}
}

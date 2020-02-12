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
			sendTCP("Arm\n");
		}

		void btnTestContinuity_Click(object sender, EventArgs e)
		{
			port.Write(":C");
		}

		void btnDisarm_Click(object sender, EventArgs e)
		{
			port.Write(":D");
		}

		void btnFire_Click(object sender, EventArgs e)
		{
			port.Write(":F");
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

			this.udpClient.BeginReceive(this.ReceiveCallback, null);
		}

		void ConnectTCP(string hostname)
		{
			try
			{
				tcpClient = new TcpClient();
				SetText("Connecting.....");

				tcpClient.Connect(hostname, 4321);
				// use the ipaddress as in the server program
				//tcpClient.Client.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.KeepAlive, true);
				
				SetText("Connected");
				SetText("Enter the string to be transmitted : ");

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
				byte[] ba = asen.GetBytes(message);
				SetText("Transmitting.....");

				stm.Write(ba, 0, ba.Length);
				//stm.Flush();
			}
			catch (Exception e)
			{
				SetText("Error..... " + e.StackTrace);
			}
		}
		void ReceiveCallback(IAsyncResult ar)
		{
			var from = new IPEndPoint(IPAddress.Any, 4321);
			var buffer = this.udpClient.EndReceive(ar, ref from);
			var data = Encoding.ASCII.GetString(buffer);

			if (data == "helloo")
			{
				IPAddress ipAd = IPAddress.Parse("192.168.2.114");

				/* Initializes the Listener */
				// TcpListener myList=new TcpListener(IPAddress.Any,8001);
				TcpListener myList = new TcpListener(ipAd, 4321);

				/* Start Listeneting at the specified port */
				myList.Start();

				Console.WriteLine("The server is running at port 8001...");
				Console.WriteLine("The local End point is  :" +				                  myList.LocalEndpoint);
				Console.WriteLine("Waiting for a connection.....");

				Socket s = myList.AcceptSocket();
				Console.WriteLine("Connection accepted from " + s.RemoteEndPoint);

				byte[] b = new byte[100];
				int k = s.Receive(b);
				Console.WriteLine("Recieved...");
				for (int i = 0; i < k; i++)
					Console.Write(Convert.ToChar(b[i]));

				ASCIIEncoding asen = new ASCIIEncoding();
				s.Send(asen.GetBytes("The string was recieved by the server."));
				Console.WriteLine("\nSent Acknowledgement");
				/* clean up */
				s.Close();
				myList.Stop();
			}

			SetText(from.ToString() + ": " + data + "\n");

			this.udpClient.BeginReceive(this.ReceiveCallback, null);
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

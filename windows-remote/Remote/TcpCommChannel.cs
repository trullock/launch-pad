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
	public partial class TcpCommChannel : Form
	{
		IPEndPoint broadcastAddress;
		UdpClient udpClient;
		TcpClient tcpClient;
		byte[] tcpBuffer = new byte[256];

		public TcpCommChannel()
		{
			InitializeComponent();
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

		void btnTcpConnect_Click(object sender, EventArgs e)
		{
			ConnectTCP(txtManualIP.Text);
		}

		void btnTcpDisconnect_Click(object sender, EventArgs e)
		{
			Disconnect();
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
			if (bytesRead > 0)
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
			if (this.udpClient == null)
				return;

			var from = new IPEndPoint(IPAddress.Any, 4321);
			var buffer = this.udpClient.EndReceive(ar, ref from);
			var data = Encoding.ASCII.GetString(buffer);

			if (data == "LaunchPad:Hello")
			{
				//ConnectTCP(from.Address.ToString());
			}

			SetText("UDP: " + from.ToString() + ": " + data + "\r\n");

			this.udpClient.BeginReceive(this.ReceiveUdp, null);
		}

		void Disconnect()
		{
			if (tcpClient != null)
			{
				tcpClient.Close();
				tcpClient.Dispose();
				tcpClient = null;
			}
		}

		void btnClear_Click(object sender, EventArgs e)
		{
			txtConsole.Text = string.Empty;
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

		IPAddress LocalIPAddress()
		{
			if (!System.Net.NetworkInformation.NetworkInterface.GetIsNetworkAvailable())
				return null;

			IPHostEntry host = Dns.GetHostEntry(Dns.GetHostName());

			return host
				.AddressList
				.FirstOrDefault(ip => ip.AddressFamily == AddressFamily.InterNetwork);
		}

		void TcpCommChannel_Load(object sender, EventArgs e)
		{

		}

		void btnUdpDisconnect_Click(object sender, EventArgs e)
		{
			if(udpClient != null)
			{
				udpClient.Close();
				udpClient.Dispose();
				udpClient = null;
			}
		}
	}
}

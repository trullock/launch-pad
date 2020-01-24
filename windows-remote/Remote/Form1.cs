using System;
using System.ComponentModel;
using System.IO.Ports;
using System.Linq;
using System.Windows.Forms;

namespace Remote
{
	public partial class Form1 : Form
	{
		SerialPort port;
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
			port.Write(":A");
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
	}
}

namespace Remote
{
	partial class TcpCommChannel
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.btnTcpDisconnect = new System.Windows.Forms.Button();
			this.btnUdpListen = new System.Windows.Forms.Button();
			this.btnClear = new System.Windows.Forms.Button();
			this.txtConsole = new System.Windows.Forms.TextBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.btnTcpConnect = new System.Windows.Forms.Button();
			this.txtManualIP = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.btnFire = new System.Windows.Forms.Button();
			this.btnDisarm = new System.Windows.Forms.Button();
			this.btnTestContinuity = new System.Windows.Forms.Button();
			this.btnArm = new System.Windows.Forms.Button();
			this.btnUdpDisconnect = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// btnTcpDisconnect
			// 
			this.btnTcpDisconnect.Location = new System.Drawing.Point(9, 100);
			this.btnTcpDisconnect.Name = "btnTcpDisconnect";
			this.btnTcpDisconnect.Size = new System.Drawing.Size(204, 29);
			this.btnTcpDisconnect.TabIndex = 21;
			this.btnTcpDisconnect.Text = "Manual TCP Disonnect";
			this.btnTcpDisconnect.UseVisualStyleBackColor = true;
			this.btnTcpDisconnect.Click += new System.EventHandler(this.btnTcpDisconnect_Click);
			// 
			// btnUdpListen
			// 
			this.btnUdpListen.Location = new System.Drawing.Point(12, 12);
			this.btnUdpListen.Name = "btnUdpListen";
			this.btnUdpListen.Size = new System.Drawing.Size(152, 30);
			this.btnUdpListen.TabIndex = 19;
			this.btnUdpListen.Text = "UDP Listen";
			this.btnUdpListen.UseVisualStyleBackColor = true;
			this.btnUdpListen.Click += new System.EventHandler(this.btnUdpListen_Click);
			// 
			// btnClear
			// 
			this.btnClear.Location = new System.Drawing.Point(240, 439);
			this.btnClear.Name = "btnClear";
			this.btnClear.Size = new System.Drawing.Size(120, 27);
			this.btnClear.TabIndex = 18;
			this.btnClear.Text = "Clear";
			this.btnClear.UseVisualStyleBackColor = true;
			this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
			// 
			// txtConsole
			// 
			this.txtConsole.Location = new System.Drawing.Point(12, 48);
			this.txtConsole.Multiline = true;
			this.txtConsole.Name = "txtConsole";
			this.txtConsole.ReadOnly = true;
			this.txtConsole.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.txtConsole.Size = new System.Drawing.Size(348, 385);
			this.txtConsole.TabIndex = 13;
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.btnTcpConnect);
			this.groupBox1.Controls.Add(this.btnTcpDisconnect);
			this.groupBox1.Controls.Add(this.txtManualIP);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Location = new System.Drawing.Point(366, 48);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(224, 140);
			this.groupBox1.TabIndex = 22;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Manual Connection Test";
			// 
			// btnTcpConnect
			// 
			this.btnTcpConnect.Location = new System.Drawing.Point(9, 65);
			this.btnTcpConnect.Name = "btnTcpConnect";
			this.btnTcpConnect.Size = new System.Drawing.Size(204, 29);
			this.btnTcpConnect.TabIndex = 21;
			this.btnTcpConnect.Text = "Manual TCP Connect";
			this.btnTcpConnect.UseVisualStyleBackColor = true;
			this.btnTcpConnect.Click += new System.EventHandler(this.btnTcpConnect_Click);
			// 
			// txtManualIP
			// 
			this.txtManualIP.Location = new System.Drawing.Point(92, 26);
			this.txtManualIP.Name = "txtManualIP";
			this.txtManualIP.Size = new System.Drawing.Size(121, 22);
			this.txtManualIP.TabIndex = 1;
			this.txtManualIP.Text = "192.168.2.251";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(6, 29);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(80, 17);
			this.label1.TabIndex = 0;
			this.label1.Text = "IP Address:";
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.btnFire);
			this.groupBox2.Controls.Add(this.btnDisarm);
			this.groupBox2.Controls.Add(this.btnTestContinuity);
			this.groupBox2.Controls.Add(this.btnArm);
			this.groupBox2.Location = new System.Drawing.Point(366, 194);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(224, 146);
			this.groupBox2.TabIndex = 22;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Controls";
			// 
			// btnFire
			// 
			this.btnFire.Location = new System.Drawing.Point(110, 82);
			this.btnFire.Name = "btnFire";
			this.btnFire.Size = new System.Drawing.Size(98, 55);
			this.btnFire.TabIndex = 21;
			this.btnFire.Text = "Fire";
			this.btnFire.UseVisualStyleBackColor = true;
			this.btnFire.Click += new System.EventHandler(this.btnFire_Click);
			// 
			// btnDisarm
			// 
			this.btnDisarm.Location = new System.Drawing.Point(6, 82);
			this.btnDisarm.Name = "btnDisarm";
			this.btnDisarm.Size = new System.Drawing.Size(98, 55);
			this.btnDisarm.TabIndex = 20;
			this.btnDisarm.Text = "Disarm";
			this.btnDisarm.UseVisualStyleBackColor = true;
			this.btnDisarm.Click += new System.EventHandler(this.btnDisarm_Click);
			// 
			// btnTestContinuity
			// 
			this.btnTestContinuity.Location = new System.Drawing.Point(110, 21);
			this.btnTestContinuity.Name = "btnTestContinuity";
			this.btnTestContinuity.Size = new System.Drawing.Size(98, 55);
			this.btnTestContinuity.TabIndex = 19;
			this.btnTestContinuity.Text = "Test Continuity";
			this.btnTestContinuity.UseVisualStyleBackColor = true;
			this.btnTestContinuity.Click += new System.EventHandler(this.btnTestContinuity_Click);
			// 
			// btnArm
			// 
			this.btnArm.Location = new System.Drawing.Point(6, 21);
			this.btnArm.Name = "btnArm";
			this.btnArm.Size = new System.Drawing.Size(98, 55);
			this.btnArm.TabIndex = 18;
			this.btnArm.Text = "Arm";
			this.btnArm.UseVisualStyleBackColor = true;
			this.btnArm.Click += new System.EventHandler(this.btnArm_Click);
			// 
			// btnUdpDisconnect
			// 
			this.btnUdpDisconnect.Location = new System.Drawing.Point(170, 12);
			this.btnUdpDisconnect.Name = "btnUdpDisconnect";
			this.btnUdpDisconnect.Size = new System.Drawing.Size(152, 30);
			this.btnUdpDisconnect.TabIndex = 23;
			this.btnUdpDisconnect.Text = "UDP Listen";
			this.btnUdpDisconnect.UseVisualStyleBackColor = true;
			this.btnUdpDisconnect.Click += new System.EventHandler(this.btnUdpDisconnect_Click);
			// 
			// TcpCommChannel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(606, 480);
			this.Controls.Add(this.btnUdpDisconnect);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.btnUdpListen);
			this.Controls.Add(this.btnClear);
			this.Controls.Add(this.txtConsole);
			this.Name = "TcpCommChannel";
			this.Text = "TcpCommChannel";
			this.Load += new System.EventHandler(this.TcpCommChannel_Load);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnTcpDisconnect;
		private System.Windows.Forms.Button btnUdpListen;
		private System.Windows.Forms.Button btnClear;
		private System.Windows.Forms.TextBox txtConsole;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Button btnTcpConnect;
		private System.Windows.Forms.TextBox txtManualIP;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Button btnFire;
		private System.Windows.Forms.Button btnDisarm;
		private System.Windows.Forms.Button btnTestContinuity;
		private System.Windows.Forms.Button btnArm;
		private System.Windows.Forms.Button btnUdpDisconnect;
	}
}
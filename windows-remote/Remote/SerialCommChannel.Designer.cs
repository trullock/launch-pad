namespace Remote
{
	partial class SerialCommChannel
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
			this.btnClear = new System.Windows.Forms.Button();
			this.btnDisconnect = new System.Windows.Forms.Button();
			this.txtConsole = new System.Windows.Forms.TextBox();
			this.btnConnect = new System.Windows.Forms.Button();
			this.cbCOMPort = new System.Windows.Forms.ComboBox();
			this.label1 = new System.Windows.Forms.Label();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.btnFire = new System.Windows.Forms.Button();
			this.btnDisarm = new System.Windows.Forms.Button();
			this.btnTestContinuity = new System.Windows.Forms.Button();
			this.btnArm = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.SuspendLayout();
			// 
			// btnClear
			// 
			this.btnClear.Location = new System.Drawing.Point(257, 444);
			this.btnClear.Name = "btnClear";
			this.btnClear.Size = new System.Drawing.Size(140, 25);
			this.btnClear.TabIndex = 19;
			this.btnClear.Text = "Clear";
			this.btnClear.UseVisualStyleBackColor = true;
			this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
			// 
			// btnDisconnect
			// 
			this.btnDisconnect.Location = new System.Drawing.Point(305, 9);
			this.btnDisconnect.Name = "btnDisconnect";
			this.btnDisconnect.Size = new System.Drawing.Size(92, 38);
			this.btnDisconnect.TabIndex = 18;
			this.btnDisconnect.Text = "Disconnect";
			this.btnDisconnect.UseVisualStyleBackColor = true;
			this.btnDisconnect.Click += new System.EventHandler(this.btnDisconnect_Click);
			// 
			// txtConsole
			// 
			this.txtConsole.Location = new System.Drawing.Point(12, 53);
			this.txtConsole.Multiline = true;
			this.txtConsole.Name = "txtConsole";
			this.txtConsole.ReadOnly = true;
			this.txtConsole.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.txtConsole.Size = new System.Drawing.Size(385, 385);
			this.txtConsole.TabIndex = 13;
			// 
			// btnConnect
			// 
			this.btnConnect.Location = new System.Drawing.Point(224, 9);
			this.btnConnect.Name = "btnConnect";
			this.btnConnect.Size = new System.Drawing.Size(75, 38);
			this.btnConnect.TabIndex = 12;
			this.btnConnect.Text = "Connect";
			this.btnConnect.UseVisualStyleBackColor = true;
			this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
			// 
			// cbCOMPort
			// 
			this.cbCOMPort.FormattingEnabled = true;
			this.cbCOMPort.Location = new System.Drawing.Point(97, 17);
			this.cbCOMPort.Name = "cbCOMPort";
			this.cbCOMPort.Size = new System.Drawing.Size(121, 24);
			this.cbCOMPort.TabIndex = 11;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(18, 20);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(73, 17);
			this.label1.TabIndex = 10;
			this.label1.Text = "COM Port:";
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.btnFire);
			this.groupBox1.Controls.Add(this.btnDisarm);
			this.groupBox1.Controls.Add(this.btnTestContinuity);
			this.groupBox1.Controls.Add(this.btnArm);
			this.groupBox1.Location = new System.Drawing.Point(403, 53);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(215, 146);
			this.groupBox1.TabIndex = 20;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Controls";
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
			// SerialCommChannel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(635, 484);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.btnClear);
			this.Controls.Add(this.btnDisconnect);
			this.Controls.Add(this.txtConsole);
			this.Controls.Add(this.btnConnect);
			this.Controls.Add(this.cbCOMPort);
			this.Controls.Add(this.label1);
			this.Name = "SerialCommChannel";
			this.Text = "SerialCommChannel";
			this.Load += new System.EventHandler(this.SerialCommChannel_Load);
			this.groupBox1.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnClear;
		private System.Windows.Forms.Button btnDisconnect;
		private System.Windows.Forms.TextBox txtConsole;
		private System.Windows.Forms.Button btnConnect;
		private System.Windows.Forms.ComboBox cbCOMPort;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Button btnFire;
		private System.Windows.Forms.Button btnDisarm;
		private System.Windows.Forms.Button btnTestContinuity;
		private System.Windows.Forms.Button btnArm;
	}
}
namespace Remote
{
	partial class Form1
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
			this.label1 = new System.Windows.Forms.Label();
			this.cbCOMPort = new System.Windows.Forms.ComboBox();
			this.btnConnect = new System.Windows.Forms.Button();
			this.txtConsole = new System.Windows.Forms.TextBox();
			this.btnArm = new System.Windows.Forms.Button();
			this.btnTestContinuity = new System.Windows.Forms.Button();
			this.btnDisarm = new System.Windows.Forms.Button();
			this.btnFire = new System.Windows.Forms.Button();
			this.btnDisconnect = new System.Windows.Forms.Button();
			this.btnClear = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(12, 9);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(73, 17);
			this.label1.TabIndex = 0;
			this.label1.Text = "COM Port:";
			// 
			// cbCOMPort
			// 
			this.cbCOMPort.FormattingEnabled = true;
			this.cbCOMPort.Location = new System.Drawing.Point(91, 6);
			this.cbCOMPort.Name = "cbCOMPort";
			this.cbCOMPort.Size = new System.Drawing.Size(121, 24);
			this.cbCOMPort.TabIndex = 1;
			// 
			// btnConnect
			// 
			this.btnConnect.Location = new System.Drawing.Point(218, 6);
			this.btnConnect.Name = "btnConnect";
			this.btnConnect.Size = new System.Drawing.Size(75, 23);
			this.btnConnect.TabIndex = 2;
			this.btnConnect.Text = "Connect";
			this.btnConnect.UseVisualStyleBackColor = true;
			this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
			// 
			// txtConsole
			// 
			this.txtConsole.Location = new System.Drawing.Point(24, 50);
			this.txtConsole.Multiline = true;
			this.txtConsole.Name = "txtConsole";
			this.txtConsole.ReadOnly = true;
			this.txtConsole.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.txtConsole.Size = new System.Drawing.Size(348, 385);
			this.txtConsole.TabIndex = 3;
			// 
			// btnArm
			// 
			this.btnArm.Location = new System.Drawing.Point(402, 67);
			this.btnArm.Name = "btnArm";
			this.btnArm.Size = new System.Drawing.Size(98, 55);
			this.btnArm.TabIndex = 4;
			this.btnArm.Text = "Arm";
			this.btnArm.UseVisualStyleBackColor = true;
			this.btnArm.Click += new System.EventHandler(this.btnArm_Click);
			// 
			// btnTestContinuity
			// 
			this.btnTestContinuity.Location = new System.Drawing.Point(506, 67);
			this.btnTestContinuity.Name = "btnTestContinuity";
			this.btnTestContinuity.Size = new System.Drawing.Size(98, 55);
			this.btnTestContinuity.TabIndex = 5;
			this.btnTestContinuity.Text = "Test Continuity";
			this.btnTestContinuity.UseVisualStyleBackColor = true;
			this.btnTestContinuity.Click += new System.EventHandler(this.btnTestContinuity_Click);
			// 
			// btnDisarm
			// 
			this.btnDisarm.Location = new System.Drawing.Point(402, 128);
			this.btnDisarm.Name = "btnDisarm";
			this.btnDisarm.Size = new System.Drawing.Size(98, 55);
			this.btnDisarm.TabIndex = 6;
			this.btnDisarm.Text = "Disarm";
			this.btnDisarm.UseVisualStyleBackColor = true;
			this.btnDisarm.Click += new System.EventHandler(this.btnDisarm_Click);
			// 
			// btnFire
			// 
			this.btnFire.Location = new System.Drawing.Point(506, 128);
			this.btnFire.Name = "btnFire";
			this.btnFire.Size = new System.Drawing.Size(98, 55);
			this.btnFire.TabIndex = 7;
			this.btnFire.Text = "Fire";
			this.btnFire.UseVisualStyleBackColor = true;
			this.btnFire.Click += new System.EventHandler(this.btnFire_Click);
			// 
			// btnDisconnect
			// 
			this.btnDisconnect.Location = new System.Drawing.Point(299, 6);
			this.btnDisconnect.Name = "btnDisconnect";
			this.btnDisconnect.Size = new System.Drawing.Size(110, 23);
			this.btnDisconnect.TabIndex = 8;
			this.btnDisconnect.Text = "Disconnect";
			this.btnDisconnect.UseVisualStyleBackColor = true;
			this.btnDisconnect.Click += new System.EventHandler(this.btnDisconnect_Click);
			// 
			// btnClear
			// 
			this.btnClear.Location = new System.Drawing.Point(402, 384);
			this.btnClear.Name = "btnClear";
			this.btnClear.Size = new System.Drawing.Size(98, 51);
			this.btnClear.TabIndex = 9;
			this.btnClear.Text = "Clear";
			this.btnClear.UseVisualStyleBackColor = true;
			this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.btnClear);
			this.Controls.Add(this.btnDisconnect);
			this.Controls.Add(this.btnFire);
			this.Controls.Add(this.btnDisarm);
			this.Controls.Add(this.btnTestContinuity);
			this.Controls.Add(this.btnArm);
			this.Controls.Add(this.txtConsole);
			this.Controls.Add(this.btnConnect);
			this.Controls.Add(this.cbCOMPort);
			this.Controls.Add(this.label1);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ComboBox cbCOMPort;
		private System.Windows.Forms.Button btnConnect;
		private System.Windows.Forms.TextBox txtConsole;
		private System.Windows.Forms.Button btnArm;
		private System.Windows.Forms.Button btnTestContinuity;
		private System.Windows.Forms.Button btnDisarm;
		private System.Windows.Forms.Button btnFire;
		private System.Windows.Forms.Button btnDisconnect;
		private System.Windows.Forms.Button btnClear;
	}
}


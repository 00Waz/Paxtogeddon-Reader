namespace Companion
{
    partial class FrmSettings
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmSettings));
            this.lblPM3EXE = new System.Windows.Forms.Label();
            this.txtPM3EXE = new System.Windows.Forms.TextBox();
            this.btnLocate = new System.Windows.Forms.Button();
            this.lblPM3ComPort = new System.Windows.Forms.Label();
            this.cbPM3ComPort = new System.Windows.Forms.ComboBox();
            this.cbPages67 = new System.Windows.Forms.CheckBox();
            this.lblPages67 = new System.Windows.Forms.Label();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnRefresh = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // lblPM3EXE
            // 
            this.lblPM3EXE.AutoSize = true;
            this.lblPM3EXE.Location = new System.Drawing.Point(15, 15);
            this.lblPM3EXE.Name = "lblPM3EXE";
            this.lblPM3EXE.Size = new System.Drawing.Size(123, 13);
            this.lblPM3EXE.TabIndex = 1;
            this.lblPM3EXE.Text = "Proxmark3.exe Location";
            // 
            // txtPM3EXE
            // 
            this.txtPM3EXE.BackColor = System.Drawing.Color.White;
            this.txtPM3EXE.Location = new System.Drawing.Point(18, 36);
            this.txtPM3EXE.Name = "txtPM3EXE";
            this.txtPM3EXE.Size = new System.Drawing.Size(320, 21);
            this.txtPM3EXE.TabIndex = 2;
            this.txtPM3EXE.TabStop = false;
            // 
            // btnLocate
            // 
            this.btnLocate.Location = new System.Drawing.Point(344, 35);
            this.btnLocate.Name = "btnLocate";
            this.btnLocate.Size = new System.Drawing.Size(75, 23);
            this.btnLocate.TabIndex = 3;
            this.btnLocate.TabStop = false;
            this.btnLocate.Text = "Locate";
            this.btnLocate.UseVisualStyleBackColor = true;
            this.btnLocate.Click += new System.EventHandler(this.btnLocate_Click);
            // 
            // lblPM3ComPort
            // 
            this.lblPM3ComPort.AutoSize = true;
            this.lblPM3ComPort.Location = new System.Drawing.Point(15, 75);
            this.lblPM3ComPort.Name = "lblPM3ComPort";
            this.lblPM3ComPort.Size = new System.Drawing.Size(107, 13);
            this.lblPM3ComPort.TabIndex = 4;
            this.lblPM3ComPort.Text = "Proxmark3 COM Port";
            // 
            // cbPM3ComPort
            // 
            this.cbPM3ComPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbPM3ComPort.FormattingEnabled = true;
            this.cbPM3ComPort.Location = new System.Drawing.Point(18, 96);
            this.cbPM3ComPort.Name = "cbPM3ComPort";
            this.cbPM3ComPort.Size = new System.Drawing.Size(320, 21);
            this.cbPM3ComPort.TabIndex = 5;
            this.cbPM3ComPort.TabStop = false;
            // 
            // cbPages67
            // 
            this.cbPages67.AutoSize = true;
            this.cbPages67.Checked = true;
            this.cbPages67.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbPages67.Location = new System.Drawing.Point(18, 156);
            this.cbPages67.Name = "cbPages67";
            this.cbPages67.Size = new System.Drawing.Size(123, 17);
            this.cbPages67.TabIndex = 7;
            this.cbPages67.TabStop = false;
            this.cbPages67.Text = "Write Pages 6 and 7";
            this.cbPages67.UseVisualStyleBackColor = true;
            // 
            // lblPages67
            // 
            this.lblPages67.AutoSize = true;
            this.lblPages67.Location = new System.Drawing.Point(15, 135);
            this.lblPages67.Name = "lblPages67";
            this.lblPages67.Size = new System.Drawing.Size(256, 13);
            this.lblPages67.TabIndex = 6;
            this.lblPages67.Text = "When cloning a card by clicking the clone action icon";
            // 
            // btnSave
            // 
            this.btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSave.Location = new System.Drawing.Point(351, 205);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(75, 23);
            this.btnSave.TabIndex = 0;
            this.btnSave.TabStop = false;
            this.btnSave.Text = "Save";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnRefresh
            // 
            this.btnRefresh.Location = new System.Drawing.Point(344, 95);
            this.btnRefresh.Name = "btnRefresh";
            this.btnRefresh.Size = new System.Drawing.Size(75, 23);
            this.btnRefresh.TabIndex = 8;
            this.btnRefresh.TabStop = false;
            this.btnRefresh.Text = "Refresh";
            this.btnRefresh.UseVisualStyleBackColor = true;
            this.btnRefresh.Click += new System.EventHandler(this.btnRefresh_Click);
            // 
            // FrmSettings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(438, 240);
            this.Controls.Add(this.btnRefresh);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.lblPages67);
            this.Controls.Add(this.cbPages67);
            this.Controls.Add(this.cbPM3ComPort);
            this.Controls.Add(this.lblPM3ComPort);
            this.Controls.Add(this.btnLocate);
            this.Controls.Add(this.txtPM3EXE);
            this.Controls.Add(this.lblPM3EXE);
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.Color.Black;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmSettings";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Settings";
            this.Load += new System.EventHandler(this.FrmSettings_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblPM3EXE;
        private System.Windows.Forms.TextBox txtPM3EXE;
        private System.Windows.Forms.Button btnLocate;
        private System.Windows.Forms.Label lblPM3ComPort;
        private System.Windows.Forms.ComboBox cbPM3ComPort;
        private System.Windows.Forms.CheckBox cbPages67;
        private System.Windows.Forms.Label lblPages67;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Button btnRefresh;
    }
}
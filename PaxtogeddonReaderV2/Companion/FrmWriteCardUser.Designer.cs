namespace Companion
{
    partial class FrmWriteCardUser
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmWriteCardUser));
            this.gbPrepareBlankCard = new System.Windows.Forms.GroupBox();
            this.btnPrepareBlankCard = new System.Windows.Forms.Button();
            this.lblPrepareBlankCard = new System.Windows.Forms.Label();
            this.gbWriteCardNumber = new System.Windows.Forms.GroupBox();
            this.lblCardNumber = new System.Windows.Forms.Label();
            this.txtWriteCardNumber = new System.Windows.Forms.TextBox();
            this.cbPages67 = new System.Windows.Forms.CheckBox();
            this.btnWriteCardNumber = new System.Windows.Forms.Button();
            this.lblWriteCardNumber = new System.Windows.Forms.Label();
            this.gbWritePaxtonFunctionCard = new System.Windows.Forms.GroupBox();
            this.cbPAXFC = new System.Windows.Forms.ComboBox();
            this.btnWritePaxtonFunctionCard = new System.Windows.Forms.Button();
            this.lblWritePaxtonFunctionCard = new System.Windows.Forms.Label();
            this.gbWritePaxtogeddonReaderFunctionCard = new System.Windows.Forms.GroupBox();
            this.cbPRFC = new System.Windows.Forms.ComboBox();
            this.btnWritePaxtogeddonReaderFunctionCard = new System.Windows.Forms.Button();
            this.lblWritePaxtogeddonReaderFunctionCard = new System.Windows.Forms.Label();
            this.gbPrepareBlankCard.SuspendLayout();
            this.gbWriteCardNumber.SuspendLayout();
            this.gbWritePaxtonFunctionCard.SuspendLayout();
            this.gbWritePaxtogeddonReaderFunctionCard.SuspendLayout();
            this.SuspendLayout();
            // 
            // gbPrepareBlankCard
            // 
            this.gbPrepareBlankCard.Controls.Add(this.btnPrepareBlankCard);
            this.gbPrepareBlankCard.Controls.Add(this.lblPrepareBlankCard);
            this.gbPrepareBlankCard.Location = new System.Drawing.Point(15, 15);
            this.gbPrepareBlankCard.Name = "gbPrepareBlankCard";
            this.gbPrepareBlankCard.Size = new System.Drawing.Size(300, 150);
            this.gbPrepareBlankCard.TabIndex = 0;
            this.gbPrepareBlankCard.TabStop = false;
            this.gbPrepareBlankCard.Text = "Prepare Blank Card";
            // 
            // btnPrepareBlankCard
            // 
            this.btnPrepareBlankCard.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnPrepareBlankCard.Location = new System.Drawing.Point(214, 116);
            this.btnPrepareBlankCard.Name = "btnPrepareBlankCard";
            this.btnPrepareBlankCard.Size = new System.Drawing.Size(75, 23);
            this.btnPrepareBlankCard.TabIndex = 1;
            this.btnPrepareBlankCard.TabStop = false;
            this.btnPrepareBlankCard.Text = "Write Card";
            this.btnPrepareBlankCard.UseVisualStyleBackColor = true;
            this.btnPrepareBlankCard.Click += new System.EventHandler(this.btnPrepareBlankCard_Click);
            // 
            // lblPrepareBlankCard
            // 
            this.lblPrepareBlankCard.ForeColor = System.Drawing.Color.Navy;
            this.lblPrepareBlankCard.Location = new System.Drawing.Point(10, 20);
            this.lblPrepareBlankCard.Name = "lblPrepareBlankCard";
            this.lblPrepareBlankCard.Size = new System.Drawing.Size(279, 60);
            this.lblPrepareBlankCard.TabIndex = 0;
            this.lblPrepareBlankCard.Text = "This will write page 1 using the default transport password, change page 1 to the" +
    " Net2 transport password, then configure pages 2 - 7 with a card number of 12345" +
    "678.";
            // 
            // gbWriteCardNumber
            // 
            this.gbWriteCardNumber.Controls.Add(this.lblCardNumber);
            this.gbWriteCardNumber.Controls.Add(this.txtWriteCardNumber);
            this.gbWriteCardNumber.Controls.Add(this.cbPages67);
            this.gbWriteCardNumber.Controls.Add(this.btnWriteCardNumber);
            this.gbWriteCardNumber.Controls.Add(this.lblWriteCardNumber);
            this.gbWriteCardNumber.Location = new System.Drawing.Point(331, 15);
            this.gbWriteCardNumber.Name = "gbWriteCardNumber";
            this.gbWriteCardNumber.Size = new System.Drawing.Size(300, 150);
            this.gbWriteCardNumber.TabIndex = 2;
            this.gbWriteCardNumber.TabStop = false;
            this.gbWriteCardNumber.Text = "Write Net2 Card Number";
            // 
            // lblCardNumber
            // 
            this.lblCardNumber.AutoSize = true;
            this.lblCardNumber.Location = new System.Drawing.Point(10, 77);
            this.lblCardNumber.Name = "lblCardNumber";
            this.lblCardNumber.Size = new System.Drawing.Size(74, 13);
            this.lblCardNumber.TabIndex = 4;
            this.lblCardNumber.Text = "Card Number:";
            // 
            // txtWriteCardNumber
            // 
            this.txtWriteCardNumber.Location = new System.Drawing.Point(90, 74);
            this.txtWriteCardNumber.Name = "txtWriteCardNumber";
            this.txtWriteCardNumber.ShortcutsEnabled = false;
            this.txtWriteCardNumber.Size = new System.Drawing.Size(199, 21);
            this.txtWriteCardNumber.TabIndex = 3;
            this.txtWriteCardNumber.TabStop = false;
            this.txtWriteCardNumber.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtWriteCardNumber_KeyPress);
            // 
            // cbPages67
            // 
            this.cbPages67.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cbPages67.AutoSize = true;
            this.cbPages67.Checked = true;
            this.cbPages67.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbPages67.Location = new System.Drawing.Point(13, 120);
            this.cbPages67.Name = "cbPages67";
            this.cbPages67.Size = new System.Drawing.Size(123, 17);
            this.cbPages67.TabIndex = 2;
            this.cbPages67.TabStop = false;
            this.cbPages67.Text = "Write Pages 6 and 7";
            this.cbPages67.UseVisualStyleBackColor = true;
            // 
            // btnWriteCardNumber
            // 
            this.btnWriteCardNumber.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnWriteCardNumber.Location = new System.Drawing.Point(214, 116);
            this.btnWriteCardNumber.Name = "btnWriteCardNumber";
            this.btnWriteCardNumber.Size = new System.Drawing.Size(75, 23);
            this.btnWriteCardNumber.TabIndex = 1;
            this.btnWriteCardNumber.TabStop = false;
            this.btnWriteCardNumber.Text = "Write Card";
            this.btnWriteCardNumber.UseVisualStyleBackColor = true;
            this.btnWriteCardNumber.Click += new System.EventHandler(this.btnWriteCardNumber_Click);
            // 
            // lblWriteCardNumber
            // 
            this.lblWriteCardNumber.ForeColor = System.Drawing.Color.Navy;
            this.lblWriteCardNumber.Location = new System.Drawing.Point(10, 20);
            this.lblWriteCardNumber.Name = "lblWriteCardNumber";
            this.lblWriteCardNumber.Size = new System.Drawing.Size(279, 35);
            this.lblWriteCardNumber.TabIndex = 0;
            this.lblWriteCardNumber.Text = "This will write pages 4 and 5 and optionally pages 6 and 7 using the Net2 transpo" +
    "rt password.";
            // 
            // gbWritePaxtonFunctionCard
            // 
            this.gbWritePaxtonFunctionCard.Controls.Add(this.cbPAXFC);
            this.gbWritePaxtonFunctionCard.Controls.Add(this.btnWritePaxtonFunctionCard);
            this.gbWritePaxtonFunctionCard.Controls.Add(this.lblWritePaxtonFunctionCard);
            this.gbWritePaxtonFunctionCard.Location = new System.Drawing.Point(15, 181);
            this.gbWritePaxtonFunctionCard.Name = "gbWritePaxtonFunctionCard";
            this.gbWritePaxtonFunctionCard.Size = new System.Drawing.Size(300, 150);
            this.gbWritePaxtonFunctionCard.TabIndex = 5;
            this.gbWritePaxtonFunctionCard.TabStop = false;
            this.gbWritePaxtonFunctionCard.Text = "Write Paxton Function Card";
            // 
            // cbPAXFC
            // 
            this.cbPAXFC.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbPAXFC.FormattingEnabled = true;
            this.cbPAXFC.Items.AddRange(new object[] {
            "Silent Operation Card",
            "Backlight Dimmer Card"});
            this.cbPAXFC.Location = new System.Drawing.Point(13, 75);
            this.cbPAXFC.Name = "cbPAXFC";
            this.cbPAXFC.Size = new System.Drawing.Size(276, 21);
            this.cbPAXFC.TabIndex = 2;
            this.cbPAXFC.TabStop = false;
            // 
            // btnWritePaxtonFunctionCard
            // 
            this.btnWritePaxtonFunctionCard.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnWritePaxtonFunctionCard.Location = new System.Drawing.Point(214, 116);
            this.btnWritePaxtonFunctionCard.Name = "btnWritePaxtonFunctionCard";
            this.btnWritePaxtonFunctionCard.Size = new System.Drawing.Size(75, 23);
            this.btnWritePaxtonFunctionCard.TabIndex = 1;
            this.btnWritePaxtonFunctionCard.TabStop = false;
            this.btnWritePaxtonFunctionCard.Text = "Write Card";
            this.btnWritePaxtonFunctionCard.UseVisualStyleBackColor = true;
            this.btnWritePaxtonFunctionCard.Click += new System.EventHandler(this.btnWritePaxtonFunctionCard_Click);
            // 
            // lblWritePaxtonFunctionCard
            // 
            this.lblWritePaxtonFunctionCard.ForeColor = System.Drawing.Color.Navy;
            this.lblWritePaxtonFunctionCard.Location = new System.Drawing.Point(10, 20);
            this.lblWritePaxtonFunctionCard.Name = "lblWritePaxtonFunctionCard";
            this.lblWritePaxtonFunctionCard.Size = new System.Drawing.Size(279, 35);
            this.lblWritePaxtonFunctionCard.TabIndex = 0;
            this.lblWritePaxtonFunctionCard.Text = "This will write pages 4 - 7 for a Paxton function card for use on Paxton Readers." +
    "";
            // 
            // gbWritePaxtogeddonReaderFunctionCard
            // 
            this.gbWritePaxtogeddonReaderFunctionCard.Controls.Add(this.cbPRFC);
            this.gbWritePaxtogeddonReaderFunctionCard.Controls.Add(this.btnWritePaxtogeddonReaderFunctionCard);
            this.gbWritePaxtogeddonReaderFunctionCard.Controls.Add(this.lblWritePaxtogeddonReaderFunctionCard);
            this.gbWritePaxtogeddonReaderFunctionCard.Location = new System.Drawing.Point(331, 181);
            this.gbWritePaxtogeddonReaderFunctionCard.Name = "gbWritePaxtogeddonReaderFunctionCard";
            this.gbWritePaxtogeddonReaderFunctionCard.Size = new System.Drawing.Size(300, 150);
            this.gbWritePaxtogeddonReaderFunctionCard.TabIndex = 6;
            this.gbWritePaxtogeddonReaderFunctionCard.TabStop = false;
            this.gbWritePaxtogeddonReaderFunctionCard.Text = "Write Paxtogeddon Reader Function Card";
            // 
            // cbPRFC
            // 
            this.cbPRFC.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbPRFC.FormattingEnabled = true;
            this.cbPRFC.Items.AddRange(new object[] {
            "Test Card",
            "Default Settings",
            "Connect to AP",
            "Show AP info on OLED"});
            this.cbPRFC.Location = new System.Drawing.Point(13, 75);
            this.cbPRFC.Name = "cbPRFC";
            this.cbPRFC.Size = new System.Drawing.Size(276, 21);
            this.cbPRFC.TabIndex = 3;
            this.cbPRFC.TabStop = false;
            // 
            // btnWritePaxtogeddonReaderFunctionCard
            // 
            this.btnWritePaxtogeddonReaderFunctionCard.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnWritePaxtogeddonReaderFunctionCard.Location = new System.Drawing.Point(214, 116);
            this.btnWritePaxtogeddonReaderFunctionCard.Name = "btnWritePaxtogeddonReaderFunctionCard";
            this.btnWritePaxtogeddonReaderFunctionCard.Size = new System.Drawing.Size(75, 23);
            this.btnWritePaxtogeddonReaderFunctionCard.TabIndex = 1;
            this.btnWritePaxtogeddonReaderFunctionCard.TabStop = false;
            this.btnWritePaxtogeddonReaderFunctionCard.Text = "Write Card";
            this.btnWritePaxtogeddonReaderFunctionCard.UseVisualStyleBackColor = true;
            this.btnWritePaxtogeddonReaderFunctionCard.Click += new System.EventHandler(this.btnWritePaxtogeddonReaderFunctionCard_Click);
            // 
            // lblWritePaxtogeddonReaderFunctionCard
            // 
            this.lblWritePaxtogeddonReaderFunctionCard.ForeColor = System.Drawing.Color.Navy;
            this.lblWritePaxtogeddonReaderFunctionCard.Location = new System.Drawing.Point(10, 20);
            this.lblWritePaxtogeddonReaderFunctionCard.Name = "lblWritePaxtogeddonReaderFunctionCard";
            this.lblWritePaxtogeddonReaderFunctionCard.Size = new System.Drawing.Size(279, 42);
            this.lblWritePaxtogeddonReaderFunctionCard.TabIndex = 0;
            this.lblWritePaxtogeddonReaderFunctionCard.Text = "This will write pages 4 - 7 for a Paxtogeddon Reader function card for use on the" +
    " reader connected to the Paxtogeddon Reader hardware.\r\n\r\n";
            // 
            // FrmWriteCardUser
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(648, 347);
            this.Controls.Add(this.gbWritePaxtogeddonReaderFunctionCard);
            this.Controls.Add(this.gbWritePaxtonFunctionCard);
            this.Controls.Add(this.gbWriteCardNumber);
            this.Controls.Add(this.gbPrepareBlankCard);
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.Color.Black;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmWriteCardUser";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Write Card (User Controlled)";
            this.Load += new System.EventHandler(this.FrmWriteCardUser_Load);
            this.gbPrepareBlankCard.ResumeLayout(false);
            this.gbWriteCardNumber.ResumeLayout(false);
            this.gbWriteCardNumber.PerformLayout();
            this.gbWritePaxtonFunctionCard.ResumeLayout(false);
            this.gbWritePaxtogeddonReaderFunctionCard.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gbPrepareBlankCard;
        private System.Windows.Forms.Label lblPrepareBlankCard;
        private System.Windows.Forms.Button btnPrepareBlankCard;
        private System.Windows.Forms.GroupBox gbWriteCardNumber;
        private System.Windows.Forms.Button btnWriteCardNumber;
        private System.Windows.Forms.Label lblWriteCardNumber;
        private System.Windows.Forms.TextBox txtWriteCardNumber;
        private System.Windows.Forms.CheckBox cbPages67;
        private System.Windows.Forms.Label lblCardNumber;
        private System.Windows.Forms.GroupBox gbWritePaxtonFunctionCard;
        private System.Windows.Forms.Button btnWritePaxtonFunctionCard;
        private System.Windows.Forms.Label lblWritePaxtonFunctionCard;
        private System.Windows.Forms.GroupBox gbWritePaxtogeddonReaderFunctionCard;
        private System.Windows.Forms.Button btnWritePaxtogeddonReaderFunctionCard;
        private System.Windows.Forms.Label lblWritePaxtogeddonReaderFunctionCard;
        private System.Windows.Forms.ComboBox cbPAXFC;
        private System.Windows.Forms.ComboBox cbPRFC;
    }
}
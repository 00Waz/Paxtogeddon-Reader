namespace Companion
{
    partial class FrmWriteCard
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmWriteCard));
            this.txtConsoleOutput = new System.Windows.Forms.TextBox();
            this.tsWriteCard = new System.Windows.Forms.ToolStrip();
            this.btnClose = new System.Windows.Forms.ToolStripButton();
            this.sep1 = new System.Windows.Forms.ToolStripSeparator();
            this.btnWriteCardAgain = new System.Windows.Forms.ToolStripButton();
            this.tsWriteCard.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtConsoleOutput
            // 
            this.txtConsoleOutput.BackColor = System.Drawing.Color.White;
            this.txtConsoleOutput.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.txtConsoleOutput.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtConsoleOutput.ForeColor = System.Drawing.Color.Black;
            this.txtConsoleOutput.Location = new System.Drawing.Point(0, 33);
            this.txtConsoleOutput.Multiline = true;
            this.txtConsoleOutput.Name = "txtConsoleOutput";
            this.txtConsoleOutput.ReadOnly = true;
            this.txtConsoleOutput.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtConsoleOutput.Size = new System.Drawing.Size(784, 428);
            this.txtConsoleOutput.TabIndex = 0;
            this.txtConsoleOutput.TabStop = false;
            // 
            // tsWriteCard
            // 
            this.tsWriteCard.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tsWriteCard.AutoSize = false;
            this.tsWriteCard.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(251)))), ((int)(((byte)(251)))), ((int)(((byte)(251)))));
            this.tsWriteCard.Dock = System.Windows.Forms.DockStyle.None;
            this.tsWriteCard.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tsWriteCard.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.tsWriteCard.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.tsWriteCard.ImeMode = System.Windows.Forms.ImeMode.On;
            this.tsWriteCard.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.btnClose,
            this.sep1,
            this.btnWriteCardAgain});
            this.tsWriteCard.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.tsWriteCard.Location = new System.Drawing.Point(0, 0);
            this.tsWriteCard.Name = "tsWriteCard";
            this.tsWriteCard.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.tsWriteCard.ShowItemToolTips = false;
            this.tsWriteCard.Size = new System.Drawing.Size(810, 32);
            this.tsWriteCard.TabIndex = 176;
            this.tsWriteCard.Text = "Users Menu";
            // 
            // btnClose
            // 
            this.btnClose.Image = ((System.Drawing.Image)(resources.GetObject("btnClose.Image")));
            this.btnClose.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new System.Drawing.Size(61, 29);
            this.btnClose.Text = "Close";
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            // 
            // sep1
            // 
            this.sep1.Name = "sep1";
            this.sep1.Size = new System.Drawing.Size(6, 32);
            // 
            // btnWriteCardAgain
            // 
            this.btnWriteCardAgain.Image = ((System.Drawing.Image)(resources.GetObject("btnWriteCardAgain.Image")));
            this.btnWriteCardAgain.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnWriteCardAgain.Name = "btnWriteCardAgain";
            this.btnWriteCardAgain.Size = new System.Drawing.Size(117, 29);
            this.btnWriteCardAgain.Text = "Write Card Again";
            this.btnWriteCardAgain.Click += new System.EventHandler(this.btnWriteCardAgain_Click);
            // 
            // FrmWriteCard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(784, 461);
            this.Controls.Add(this.tsWriteCard);
            this.Controls.Add(this.txtConsoleOutput);
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.Color.Black;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmWriteCard";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Write Card";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FrmWriteCard_FormClosing);
            this.Load += new System.EventHandler(this.FrmWriteCard_Load);
            this.tsWriteCard.ResumeLayout(false);
            this.tsWriteCard.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtConsoleOutput;
        private System.Windows.Forms.ToolStrip tsWriteCard;
        private System.Windows.Forms.ToolStripButton btnClose;
        private System.Windows.Forms.ToolStripSeparator sep1;
        private System.Windows.Forms.ToolStripButton btnWriteCardAgain;
    }
}
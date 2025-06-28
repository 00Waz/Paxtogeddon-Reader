namespace Companion
{
    partial class FrmRawLog
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FrmRawLog));
            this.txtRawLog = new System.Windows.Forms.TextBox();
            this.tsRawLog = new System.Windows.Forms.ToolStrip();
            this.btnClose = new System.Windows.Forms.ToolStripButton();
            this.tsRawLog.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtRawLog
            // 
            this.txtRawLog.BackColor = System.Drawing.Color.White;
            this.txtRawLog.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.txtRawLog.Font = new System.Drawing.Font("Tahoma", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtRawLog.ForeColor = System.Drawing.Color.Black;
            this.txtRawLog.Location = new System.Drawing.Point(0, 33);
            this.txtRawLog.Multiline = true;
            this.txtRawLog.Name = "txtRawLog";
            this.txtRawLog.ReadOnly = true;
            this.txtRawLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtRawLog.Size = new System.Drawing.Size(784, 428);
            this.txtRawLog.TabIndex = 0;
            this.txtRawLog.TabStop = false;
            // 
            // tsRawLog
            // 
            this.tsRawLog.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tsRawLog.AutoSize = false;
            this.tsRawLog.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(251)))), ((int)(((byte)(251)))), ((int)(((byte)(251)))));
            this.tsRawLog.Dock = System.Windows.Forms.DockStyle.None;
            this.tsRawLog.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tsRawLog.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.tsRawLog.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.tsRawLog.ImeMode = System.Windows.Forms.ImeMode.On;
            this.tsRawLog.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.btnClose});
            this.tsRawLog.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.tsRawLog.Location = new System.Drawing.Point(0, 0);
            this.tsRawLog.Name = "tsRawLog";
            this.tsRawLog.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.tsRawLog.ShowItemToolTips = false;
            this.tsRawLog.Size = new System.Drawing.Size(810, 32);
            this.tsRawLog.TabIndex = 176;
            this.tsRawLog.Text = "Users Menu";
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
            // FrmRawLog
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(784, 461);
            this.Controls.Add(this.tsRawLog);
            this.Controls.Add(this.txtRawLog);
            this.DoubleBuffered = true;
            this.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ForeColor = System.Drawing.Color.Black;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "FrmRawLog";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Raw Log";
            this.Load += new System.EventHandler(this.FrmRawLog_Load);
            this.tsRawLog.ResumeLayout(false);
            this.tsRawLog.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtRawLog;
        private System.Windows.Forms.ToolStrip tsRawLog;
        private System.Windows.Forms.ToolStripButton btnClose;
    }
}
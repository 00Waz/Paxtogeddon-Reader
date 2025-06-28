using System;
using System.Windows.Forms;

namespace Companion
{
    public partial class FrmRawLog : Form
    {
        public FrmRawLog()
        {
            InitializeComponent();
        }

        private async void FrmRawLog_Load(object sender, EventArgs e)
        {
            string response = await ESP32Connect.Get(Settings.prIpAddress, "/exportLog?d=0", 5000);
            if (response.Contains("<!DOCTYPE html>"))
            {
                txtRawLog.Text = "Log is empty";
                return;
            }

            txtRawLog.Text = response;
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}

using System;
using System.Text;
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

            StringBuilder header = new StringBuilder();
            header.AppendLine("--------------------------------------------------------------------------");
            header.AppendLine("Number, Bits, Bin, Type, Colour, Page 4, Page 5, Page 6, Page 7");
            header.AppendLine("--------------------------------------------------------------------------");
            header.AppendLine("");
            txtRawLog.Text = header + response;
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}

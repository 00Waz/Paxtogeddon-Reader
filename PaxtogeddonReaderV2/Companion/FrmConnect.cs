using System;
using System.Windows.Forms;

namespace Companion
{
    public partial class FrmConnect : Form
    {
        internal bool userCancel { get; private set; }
        private bool systemBusy = false;

        public FrmConnect()
        {
            InitializeComponent();
        }

        #region FrmConnect - Load
        private void FrmConnect_Load(object sender, EventArgs e)
        {
            userCancel = true;
            Settings.LoadIpAddress();
            txtIpAddress.Text = Settings.prIpAddress;
            if (!string.IsNullOrEmpty(Settings.prIpAddress))
            {
                btnConnect.Select();
                btnConnect.Focus();
            }
        }
        #endregion

        #region FrmConnect - From Closing
        private void FrmConnect_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (systemBusy)
            {
                e.Cancel = true;
            }
        }
        #endregion

        #region Process Connect
        private async void ProcessConnect()
        {
            bool connected = false;
            systemBusy = true;
            txtIpAddress.Enabled = false;
            btnConnect.Enabled = false;

            try
            {
                string response = await ESP32Connect.Get(txtIpAddress.Text, "/companionDetect", 5000);
                if (response == "paxtogeddon-reader")
                {
                    await ESP32Connect.Get(txtIpAddress.Text, "/enableCloneAction", 5000);
                    response = await ESP32Connect.Get(txtIpAddress.Text, "/getSpecialCards", 5000);
                    if (!string.IsNullOrEmpty(response) && response.Contains(","))
                    {
                        string[] data = response.Split(',');
                        if (data.Length == 4)
                        {
                            Settings.testCard = data[0];
                            Settings.fcDefault = data[1];
                            Settings.fcConnectToAp = data[2];
                            Settings.fcShowApInfo = data[3];
                            connected = true;
                        }
                    }
                }
            }
            catch { }

            systemBusy = false;

            if (connected)
            {
                Settings.prIpAddress = txtIpAddress.Text;
                Settings.SaveIpAddress();
                Settings.LoadSettings();
                userCancel = false;
                this.Close();
                return;
            }

            MessageBox.Show(this, "Could not connect to Paxtogeddon Reader.", "Paxtogeddon Reader Companion",
                MessageBoxButtons.OK, MessageBoxIcon.Error);
            txtIpAddress.Enabled = true;
            btnConnect.Enabled = true;
        }
        #endregion

        #region Button - Connect
        private void btnConnect_Click(object sender, EventArgs e)
        {
            txtIpAddress.Text = txtIpAddress.Text.Trim();
            if (txtIpAddress.Text == "")
            {
                txtIpAddress.Select();
                txtIpAddress.Focus();
                return;
            }

            ProcessConnect();
        }
        #endregion

        #region txtIpAddress - Key Press
        private void txtIpAddress_KeyPress(object sender, KeyPressEventArgs e)
        {
            switch (e.KeyChar)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '.':
                case '\b':
                    {
                        e.Handled = false;
                        break;
                    }

                default:
                    {
                        e.Handled = true;
                        break;
                    }
            }
        }
        #endregion

    }
}

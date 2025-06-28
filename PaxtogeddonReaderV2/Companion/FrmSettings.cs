using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Companion
{
    public partial class FrmSettings : Form
    {
        public FrmSettings()
        {
            InitializeComponent();
        }

        #region FrmSettings - Load
        private void FrmSettings_Load(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(Settings.pm3exePath))
            {
                txtPM3EXE.Text = $@"{Settings.pm3exePath}\proxmark3.exe";
            }

            PopulateComPorts();
            cbPages67.Checked = Settings.whenCloningWritePages67;
        }
        #endregion

        #region Populate Com Ports
        private void PopulateComPorts()
        {
            cbPM3ComPort.Items.Clear();

            List<string> comPorts = Util.GetComPorts();
            foreach (string comPort in comPorts)
            {
                cbPM3ComPort.Items.Add(comPort);
            }

            if (cbPM3ComPort.Items.Count > 0)
            {
                if (!string.IsNullOrEmpty(Settings.comPort))
                {
                    if (cbPM3ComPort.Items.Contains(Settings.comPort))
                    {
                        cbPM3ComPort.Text = Settings.comPort;
                    }
                }
            }
        }
        #endregion

        #region Button - Locate
        private void btnLocate_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog()
            {
                InitialDirectory = @"c:\",
                Filter = "Proxmark3 exe (*.exe)|*.exe",
                RestoreDirectory = true,
            };

            if (openFileDialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            txtPM3EXE.Text = openFileDialog.FileName;
        }
        #endregion

        #region Button - Refresh
        private void btnRefresh_Click(object sender, EventArgs e)
        {
            PopulateComPorts();
        }
        #endregion

        #region Button - Save
        private void btnSave_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(txtPM3EXE.Text))
            {
                MessageBox.Show(this, "proxmark3.exe location cannot be empty!", 
                    "Paxtogeddon Reader Companion", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (!txtPM3EXE.Text.Contains(@"\proxmark3.exe"))
            {
                MessageBox.Show(this, "Path must contain proxmark3.exe!",
                    "Paxtogeddon Reader Companion", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (string.IsNullOrEmpty(cbPM3ComPort.Text))
            {
                MessageBox.Show(this, "No com port has been selected!",
                    "Paxtogeddon Reader Companion", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            btnSave.Enabled = false;
            Settings.pm3exePath = txtPM3EXE.Text.Replace(@"\proxmark3.exe", "");
            Settings.comPort = cbPM3ComPort.Text;
            Settings.whenCloningWritePages67 = cbPages67.Checked;
            Settings.SaveSettings();
            this.Close();
        }
        #endregion

    }
}

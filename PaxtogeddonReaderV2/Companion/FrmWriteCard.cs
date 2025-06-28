using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Companion
{
    public partial class FrmWriteCard : Form
    {
        private string cardNo = string.Empty;
        private bool systemBusy = false;

        #region FrmWriteCard - Constructor
        public FrmWriteCard(string cardNumber, CardData pages, bool cardIsNet2, bool writePages123, bool writePages67)
        {
            InitializeComponent();
            cardNo = cardNumber;
            string transportPassword = Settings.net2CardTransportPassword;

            if (!cardIsNet2)
            {
                transportPassword = Settings.blankCardTransportPassword;
                sep1.Visible = false;
                btnWriteCardAgain.Visible = false;
                btnWriteCardAgain.Enabled = false;
            }

            StringBuilder sb = new StringBuilder();
            sb.AppendLine("@echo off");
            sb.AppendLine($@"set ""HOME={Settings.pm3exePath}""");
            sb.AppendLine(@"set ""QT_PLUGIN_PATH=%HOME%\libs\""");
            sb.AppendLine(@"set ""QT_QPA_PLATFORM_PLUGIN_PATH=%QT_PLUGIN_PATH%""");
            sb.AppendLine(@"set ""PATH=%QT_PLUGIN_PATH%;%QT_PLUGIN_PATH%shell\;%PATH%""");
            sb.AppendLine("set MSYSTEM=MINGW64");
            sb.Append($@"""{Settings.pm3exePath}\proxmark3.exe"" {Settings.comPort} -c """);

            if (writePages123)
            {
                sb.Append($"lf hitag wrbl --ht2 -k {transportPassword} -p 1 -d {pages.Page1}; ");
                transportPassword = Settings.net2CardTransportPassword;
                sb.Append($"lf hitag wrbl --ht2 -k {transportPassword} -p 2 -d {pages.Page2}; ");
                sb.Append($"lf hitag wrbl --ht2 -k {transportPassword} -p 3 -d {pages.Page3}; ");
            }

            sb.Append($"lf hitag wrbl --ht2 -k {transportPassword} -p 4 -d {pages.Page4}; ");
            sb.Append($"lf hitag wrbl --ht2 -k {transportPassword} -p 5 -d {pages.Page5}; ");

            if (writePages67)
            {
                sb.Append($"lf hitag wrbl --ht2 -k {transportPassword} -p 6 -d {pages.Page6}; ");
                sb.Append($"lf hitag wrbl --ht2 -k {transportPassword} -p 7 -d {pages.Page7}; ");
            }

            sb.Append(@"""");

            try
            {
                File.WriteAllText(Settings.batchFile, sb.ToString());
            }
            catch (Exception ex)
            {
                txtConsoleOutput.Text = ex.Message;
            }
        }
        #endregion

        #region FrmWriteCard - Load
        private void FrmWriteCard_Load(object sender, EventArgs e)
        {
            WriteCardData();
        }
        #endregion

        #region FrmWriteCard - Form Closing
        private void FrmWriteCard_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (systemBusy)
            {
                e.Cancel = true;
                return;
            }

            try
            {
                if (File.Exists(Settings.batchFile))
                {
                    File.Delete(Settings.batchFile);
                }
            }
            catch { }
        }
        #endregion

        #region Write Card Data
        private async void WriteCardData()
        {
            if (systemBusy)
            {
                return;
            }

            if (!File.Exists(Settings.batchFile))
            {
                txtConsoleOutput.Text = "\r\nBatch file does not exist!\r\n";
                return;
            }

            systemBusy = true;
            string result = string.Empty;
            txtConsoleOutput.Clear();
            txtConsoleOutput.AppendText($"Writing card number {cardNo} via PM3...");
            txtConsoleOutput.AppendText(Environment.NewLine);
            txtConsoleOutput.AppendText(Environment.NewLine);
            txtConsoleOutput.AppendText("If the process takes too long, the card is incorrectly aligned on the reader.");
            txtConsoleOutput.AppendText(Environment.NewLine);
            txtConsoleOutput.AppendText("Pressing the button on the PM3 which cancel each stage of the write cycle.");
            txtConsoleOutput.AppendText(Environment.NewLine);
            txtConsoleOutput.AppendText(Environment.NewLine);

            await Task.Run(() =>
            {
                try
                {
                    using (Process p = new Process())
                    {
                        p.StartInfo.FileName = Settings.batchFile;
                        p.StartInfo.UseShellExecute = false;
                        p.StartInfo.RedirectStandardOutput = true;
                        p.StartInfo.CreateNoWindow = true;
                        p.Start();
                        result = p.StandardOutput.ReadToEnd();
                        p.WaitForExit();
                    }
                }
                catch (Exception ex)
                {
                    result = ex.Message;
                }
            });

            txtConsoleOutput.AppendText(result);
            systemBusy = false;
        }
        #endregion

        #region Button - Close
        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        #endregion

        #region Button - Write Card Again
        private void btnWriteCardAgain_Click(object sender, EventArgs e)
        {
            WriteCardData();
        }

        #endregion
     
    }
}

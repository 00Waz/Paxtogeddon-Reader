using Microsoft.Web.WebView2.Core;
using System;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Companion
{
    public partial class FrmMain : Form
    {
        public FrmMain()
        {
            InitializeComponent();
        }

        #region FrmMain - Load
        private void FrmMain_Load(object sender, EventArgs e)
        {
            FrmConnect frmConnect = new FrmConnect();
            frmConnect.ShowDialog();

            if (frmConnect.userCancel)
            {
                this.Top = -10000;
                this.Left = -10000;
                Application.Exit();
                return;
            }

            WebView2Init(Settings.prIpAddress);
        }
        #endregion

        #region FrmMain - Form Closing
        private void FrmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            DisableCloneAction();

            try
            {
                var webViewProcessId = Convert.ToInt32(gcWV2.CoreWebView2.BrowserProcessId);
                var webViewProcess = Process.GetProcessById(webViewProcessId);
                gcWV2.Dispose();
                webViewProcess.WaitForExit(3000);

                if (Directory.Exists(Settings.wvTempFolder))
                {
                    Directory.Delete(Settings.wvTempFolder, true);
                }
            }
            catch { }
        }
        #endregion

        #region Disable Clone Action
        private async void DisableCloneAction()
        {
            await ESP32Connect.Get(Settings.prIpAddress, "/disableCloneAction", 5000);
        }
        #endregion

        #region Check Settings
        private bool CheckSettings()
        {
            bool ret = true;

            if (string.IsNullOrEmpty(Settings.pm3exePath)) { ret = false; }
            if (string.IsNullOrEmpty(Settings.comPort)) { ret = false; }

            if (ret == false)
            {
                this.InvokeIfRequired(c =>
                {
                    MessageBox.Show(this, "Please configure settings in the companion menu to use this option.",
                        "Paxtogeddon Reader Companion", MessageBoxButtons.OK, MessageBoxIcon.Error);
                });
            }

            return ret;
        }
        #endregion

        #region Process Message
        private void ProcessMessage(string message)
        {
            if (message == "PAX_VIEW_RAW_LOG")
            {
                this.InvokeIfRequired(c =>
                {
                    FrmRawLog frmRawLog = new FrmRawLog();
                    frmRawLog.ShowDialog(this);
                });
            }

            if (message == "PAX_WRITE_CARD")
            {
                if (!CheckSettings()) { return; }
                this.InvokeIfRequired(c =>
                {
                    FrmWriteCardUser frmWriteCardUser = new FrmWriteCardUser();
                    frmWriteCardUser.ShowDialog(this);
                });
            }

            if (message == "PAX_SETTINGS")
            {
                this.InvokeIfRequired(c =>
                {
                    FrmSettings frmSettings = new FrmSettings();
                    frmSettings.ShowDialog(this);
                });
            }

            if (message.Contains("CLONE_CARD,"))
            {
                if (!CheckSettings()) { return; }
                string[] data = message.Split(',');
                if (data.Length != 5) { return; }
                string header = data[0];
                string cardNumber = data[1];
                string cardType = data[2];
                string cardColour = data[3];
                string cardBinary = data[4];

                if (Util.PagesByTokenNumber(cardNumber, out CardData pages))
                {
                    this.InvokeIfRequired(c =>
                    {
                        FrmWriteCard frmWriteCard = new FrmWriteCard(cardNumber, pages, 
                            true, false, Settings.whenCloningWritePages67);
                        frmWriteCard.ShowDialog(this);
                    });
                }
            }

            if (message.Contains("CLONE_CARD_PAGES,"))
            {
                if (!CheckSettings()) { return; }
                string[] data = message.Split(',');
                if (data.Length != 6) { return; }
                string header = data[0];
                string cardNumber = data[1];
                CardData pages = new CardData()
                {
                    Page0 = "UID",
                    Page1 = "BDF5E846",
                    Page2 = "20F04F4E",
                    Page3 = "06F907C2",
                    Page4 = data[2],
                    Page5 = data[3],
                    Page6 = data[4],
                    Page7 = data[5]
                };

                this.InvokeIfRequired(c =>
                {
                    FrmWriteCard frmWriteCard = new FrmWriteCard(cardNumber, pages, true, false, true);
                    frmWriteCard.ShowDialog(this);
                });
            }
        }
        #endregion

        #region WebView2 Init
        private async void WebView2Init(string ip)
        {
            CoreWebView2Environment cwv2Environment = await CoreWebView2Environment.CreateAsync(
                null, Settings.wvTempFolder, new CoreWebView2EnvironmentOptions());
            await gcWV2.EnsureCoreWebView2Async(cwv2Environment);
            gcWV2.Source = new Uri($"http://{ip}");
        }
        #endregion

        #region WebView2 - Init Complete
        private void gcWV2_CoreWebView2InitializationCompleted(object sender, CoreWebView2InitializationCompletedEventArgs e)
        {
            try
            {
                gcWV2.CoreWebView2.Profile.DefaultDownloadFolderPath = Environment.GetFolderPath(Environment.SpecialFolder.Desktop) + @"\";
                gcWV2.CoreWebView2.Settings.AreBrowserAcceleratorKeysEnabled = true;
                gcWV2.CoreWebView2.Settings.AreDefaultContextMenusEnabled = false;
                gcWV2.CoreWebView2.Settings.AreDefaultScriptDialogsEnabled = false;
                gcWV2.CoreWebView2.Settings.AreDevToolsEnabled = false;
                gcWV2.CoreWebView2.Settings.AreHostObjectsAllowed = false;
                gcWV2.CoreWebView2.Settings.IsBuiltInErrorPageEnabled = false;
                gcWV2.CoreWebView2.Settings.IsGeneralAutofillEnabled = false;
                gcWV2.CoreWebView2.Settings.IsNonClientRegionSupportEnabled = false;
                gcWV2.CoreWebView2.Settings.IsPasswordAutosaveEnabled = false;
                gcWV2.CoreWebView2.Settings.IsPinchZoomEnabled = false;
                gcWV2.CoreWebView2.Settings.IsReputationCheckingRequired = false;
                gcWV2.CoreWebView2.Settings.IsScriptEnabled = true;
                gcWV2.CoreWebView2.Settings.IsStatusBarEnabled = false;
                gcWV2.CoreWebView2.Settings.IsSwipeNavigationEnabled = false;
                gcWV2.CoreWebView2.Settings.IsWebMessageEnabled = true;
                gcWV2.CoreWebView2.Settings.IsZoomControlEnabled = false;
            }
            catch { }

        }
        #endregion

        #region WebView2 - Navigation Completed
        private void gcWV2_NavigationCompleted(object sender, CoreWebView2NavigationCompletedEventArgs e)
        {
            gcWV2.ExecuteScriptAsync("EnableCompanion();");
        }
        #endregion

        #region WebView2 - Web Message Received
        private void gcWV2_WebMessageReceived(object sender, CoreWebView2WebMessageReceivedEventArgs e)
        {
            try
            {
                string message = e.WebMessageAsJson;

                if (string.IsNullOrEmpty(message))
                {
                    return;
                }

                message = message.Replace("\"", "").Trim();
                Task.Run(() => { ProcessMessage(message); });
            }
            catch { }
        }
        #endregion

        #region WebView2 - Navigation Starting
        private void gcWV2_NavigationStarting(object sender, CoreWebView2NavigationStartingEventArgs e)
        {
            try
            {
                if (e.Uri.ToString() == $"http://{Settings.prIpAddress}/exportLog?d=0")
                {
                    e.Cancel = true;
                    Task.Run(() => { ProcessMessage("PAX_VIEW_RAW_LOG"); });
                }
            }
            catch { }
        }
        #endregion

    }
}

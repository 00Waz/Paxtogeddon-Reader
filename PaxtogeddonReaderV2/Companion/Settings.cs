using System;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace Companion
{
    internal sealed class Settings
    {
        internal static readonly string wvTempFolder = $"{Path.GetTempPath()}WebView2-{Guid.NewGuid().ToString().ToUpper()}";
        internal static readonly string batchFile = $"{Path.GetTempPath()}pm3-card-data.bat";
        internal static readonly string ipAddressFile = Application.StartupPath + @"\ipAddress.dat";
        internal static readonly string settingsFile = Application.StartupPath + @"\settings.dat";
        internal static readonly string blankCardTransportPassword = "4D494B52";
        internal static readonly string net2CardTransportPassword = "BDF5E846";
        internal static string prIpAddress = string.Empty;
        internal static string pm3exePath = string.Empty;
        internal static string comPort = string.Empty;
        internal static bool whenCloningWritePages67 = true;
        internal static string testCard = string.Empty;
        internal static string fcDefault = string.Empty;
        internal static string fcConnectToAp = string.Empty;
        internal static string fcShowApInfo = string.Empty;

        #region Load IP Address
        internal static void LoadIpAddress()
        {
            try
            {
                if (File.Exists(ipAddressFile))
                {
                    string ipAddr = File.ReadAllText(ipAddressFile);
                    prIpAddress = ipAddr;
                }
            }
            catch { }
        }
        #endregion

        #region Save IP Address
        internal static void SaveIpAddress()
        {
            try
            {
                File.WriteAllText(ipAddressFile, prIpAddress);
            }
            catch { }
        }
        #endregion

        #region Load Settings
        internal static void LoadSettings()
        {
            try
            {
                if (File.Exists(settingsFile))
                {
                    string[] settings = File.ReadAllLines(settingsFile);
                    if (settings.Length == 3)
                    {
                        pm3exePath = settings[0];
                        comPort = settings[1];
                        whenCloningWritePages67 = settings[2] == "true" ? true : false;
                    }
                }
            }
            catch { }
        }
        #endregion

        #region Save Settings
        internal static void SaveSettings()
        {
            try
            {
                StringBuilder sb = new StringBuilder();
                sb.AppendLine(pm3exePath);
                sb.AppendLine(comPort);
                sb.AppendLine(whenCloningWritePages67.ToString().ToLower());
                File.WriteAllText(settingsFile, sb.ToString());
            }
            catch { }   
        }
        #endregion

    }
}

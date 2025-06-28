using System;
using System.Collections.Generic;
using System.Management;

namespace Companion
{
    internal sealed class Util
    {
        #region Pages by Token Number
        internal static bool PagesByTokenNumber(string tokenNumber, out CardData pages)
        {
            pages = new CardData()
            {
                Page0 = "UID",
                Page1 = "BDF5E846",
                Page2 = "20F04F4E",
                Page3 = "06F907C2",
                Page4 = "",
                Page5 = "",
                Page6 = "00600F8E",
                Page7 = "C6000010"
            };

            if (!int.TryParse(tokenNumber, out _))
            {
                return false;
            }

            try
            {
                ulong result = 0;
                tokenNumber = tokenNumber.PadLeft(8, '0');

                for (int i = 0; i < 8; i++)
                {
                    ulong dec = Convert.ToUInt32(tokenNumber[i].ToString());
                    dec = ((~(((dec * 0x0101010101010101) & 0x8040201008040201) % 0x1FF) & 1) << 4) + dec;
                    result = (result << 5) + dec;
                    if (i == 5) { result <<= 2; }
                }

                result = (result << 22) + 4128774;
                string hex = string.Format("{0:X}", result).PadLeft(16, '0');
                pages.Page4 = hex.Substring(0, 8);
                pages.Page5 = hex.Substring(8, 8);
                return true;
            }
            catch { }

            return false;
        }
        #endregion

        #region Paxton Silent Operation Card
        internal static CardData PaxtonSilentOperationCard()
        {
            CardData pages = new CardData()
            {
                Page0 = "UID",
                Page1 = "BDF5E846",
                Page2 = "20F04F4E",
                Page3 = "06F907C2",
                Page4 = "84030810",
                Page5 = "AE441204",
                Page6 = "ADAB0840",
                Page7 = "08610084"
            };

            return pages;
        }
        #endregion

        #region Paxton Backlight Dimmer Card
        internal static CardData PaxtonBacklightDimmerCard()
        {
            CardData pages = new CardData()
            {
                Page0 = "UID",
                Page1 = "BDF5E846",
                Page2 = "20F04F4E",
                Page3 = "06F907C2",
                Page4 = "840309C0",
                Page5 = "B06A7A88",
                Page6 = "3CF27840",
                Page7 = "09216084"
            };

            return pages;
        }
        #endregion

        #region Get Com Ports
        internal static List<string> GetComPorts()
        {
            List<string> ret = new List<string>();
            
            try
            {
                ManagementObjectSearcher mos = new ManagementObjectSearcher("root\\CIMV2",
                    "SELECT * FROM Win32_PnPEntity WHERE ClassGuid=\"{4d36e978-e325-11ce-bfc1-08002be10318}\"");

                foreach (ManagementBaseObject mbo in mos.Get())
                {
                    string comPort = mbo["Name"].ToString().ToLower();
                    if (comPort.Contains("("))
                    {
                        comPort = comPort.Split('(')[1].Replace(")", "");
                        ret.Add(comPort.Trim());
                    }
                }
            }
            catch { }

            if (ret.Count > 0)
            {
                ret.Sort();
            }

            return ret;
        }

        #endregion
    }
}

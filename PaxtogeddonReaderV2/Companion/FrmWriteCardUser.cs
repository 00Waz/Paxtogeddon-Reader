using System;
using System.Windows.Forms;

namespace Companion
{
    public partial class FrmWriteCardUser : Form
    {
        public FrmWriteCardUser()
        {
            InitializeComponent();
        }

        private void FrmWriteCardUser_Load(object sender, EventArgs e)
        {
            cbPRFC.SelectedIndex = 0;   
            cbPAXFC.SelectedIndex = 0;
        }

        #region Button - Prepare Blank Card
        private void btnPrepareBlankCard_Click(object sender, EventArgs e)
        {
            string cardNumber = "12345678";
            if (Util.PagesByTokenNumber(cardNumber, out CardData pages))
            {
                FrmWriteCard frmWriteCard = new FrmWriteCard(cardNumber, pages, false, true, true);
                frmWriteCard.ShowDialog(this);
            }
        }
        #endregion

        #region Button - Write Card Number
        private void btnWriteCardNumber_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(txtWriteCardNumber.Text)) { return; }

            if (int.TryParse(txtWriteCardNumber.Text, out _))
            {
                if (Util.PagesByTokenNumber(txtWriteCardNumber.Text, out CardData pages))
                {
                    FrmWriteCard frmWriteCard = new FrmWriteCard(txtWriteCardNumber.Text, pages, true, false, cbPages67.Checked);
                    frmWriteCard.ShowDialog(this);
                }
            }
        }
        #endregion

        #region Button - Write Paxton Function Card
        private void btnWritePaxtonFunctionCard_Click(object sender, EventArgs e)
        {
            if (cbPAXFC.Text == "Silent Operation Card")
            {
                CardData pages = Util.PaxtonSilentOperationCard();
                FrmWriteCard frmWriteCard = new FrmWriteCard("Paxton Silent Operation Card", pages, true, false, true);
                frmWriteCard.ShowDialog(this);
            }

            if (cbPAXFC.Text == "Backlight Dimmer Card")
            {
                CardData pages = Util.PaxtonBacklightDimmerCard();
                FrmWriteCard frmWriteCard = new FrmWriteCard("Paxton Backlight Dimmer Card", pages, true, false, true);
                frmWriteCard.ShowDialog(this);
            }
        }
        #endregion

        #region Button - Write Paxtogeddon Reader Function Card
        private void btnWritePaxtogeddonReaderFunctionCard_Click(object sender, EventArgs e)
        {

            if (cbPRFC.Text == "Test Card")
            {
                if (Util.PagesByTokenNumber(Settings.testCard, out CardData pages))
                {
                    FrmWriteCard frmWriteCard = new FrmWriteCard(Settings.testCard, pages, true, false, true);
                    frmWriteCard.ShowDialog(this);
                }
            }

            if (cbPRFC.Text == "Default Settings")
            {
                if (Util.PagesByTokenNumber(Settings.fcDefault, out CardData pages))
                {
                    FrmWriteCard frmWriteCard = new FrmWriteCard(Settings.fcDefault, pages, true, false, true);
                    frmWriteCard.ShowDialog(this);
                }
            }

            if (cbPRFC.Text == "Connect to AP")
            {
                if (Util.PagesByTokenNumber(Settings.fcConnectToAp, out CardData pages))
                {
                    FrmWriteCard frmWriteCard = new FrmWriteCard(Settings.fcConnectToAp, pages, true, false, true);
                    frmWriteCard.ShowDialog(this);
                }
            }

            if (cbPRFC.Text == "Show AP info on OLED")
            {
                if (Util.PagesByTokenNumber(Settings.fcShowApInfo, out CardData pages))
                {
                    FrmWriteCard frmWriteCard = new FrmWriteCard(Settings.fcShowApInfo, pages, true, false, true);
                    frmWriteCard.ShowDialog(this);
                }
            }
        }
        #endregion

        #region txtWriteCardNumber - Key Press
        private void txtWriteCardNumber_KeyPress(object sender, KeyPressEventArgs e)
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

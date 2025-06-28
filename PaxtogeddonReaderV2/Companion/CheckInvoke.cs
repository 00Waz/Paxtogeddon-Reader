using System;
using System.Windows.Forms;

namespace Companion
{
    internal static class CheckInvoke
    {
        internal static void InvokeIfRequired(this Control c, Action<Control> action)
        {
            if (c.InvokeRequired)
            {
                c.Invoke(new Action(() => action(c)));
            }
            else
            {
                action(c);
            }
        }
    }
}

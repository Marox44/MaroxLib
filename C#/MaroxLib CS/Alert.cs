using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Marox
{
    public static class Alert
    {
        public static void Error(string text)
        {
            MessageBox.Show(text,
       "Error",
       MessageBoxButtons.OK,
       MessageBoxIcon.Error,
       MessageBoxDefaultButton.Button1);
        }
        public static void Warning(string text)
        {
            MessageBox.Show(text,
       "Warning",
       MessageBoxButtons.OK,
       MessageBoxIcon.Warning,
       MessageBoxDefaultButton.Button1);
        }
        public static void Info(string text)
        {
            MessageBox.Show(text,
       "Info",
       MessageBoxButtons.OK,
       MessageBoxIcon.Information,
       MessageBoxDefaultButton.Button1);
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;
using System.Diagnostics;
using Microsoft.VisualBasic.Devices;
using Microsoft.VisualBasic;

namespace PataponController
{
    
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void walkButton_Click(object sender, RoutedEventArgs e)
        {
            //My.Computer.Keyboard.SendKeys("q", true);

            //SendKeys.SendWait("q");
        }

        private void launchButton_Click(object sender, RoutedEventArgs e)
        {
            /*ProcID = Shell("NOTEPAD.EXE", AppWinStyle.NormalFocus);
            AppActivate(ProcID);*/
            Process.Start("C:\\Program Files\\PPSSPP\\PPSSPPWindows64.exe");
        }
    }
}

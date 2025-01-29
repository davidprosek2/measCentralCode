using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TempMeasControl
{
    public partial class SetupForm : Form
    {
        public SerialPort Port { get; set; }
        public SetupForm(SerialPort sp)
        {
            InitializeComponent();
            Port = sp;
            if (Port == null)
                throw new Exception("Port not initialized");
            Port.WriteLine("SETUP");
        }

        private void OnClosing(object sender, FormClosingEventArgs e)
        {
            if (Port == null)
                throw new Exception("Port not initialized");
            Port.WriteLine("EXIT");
        }
    }
}

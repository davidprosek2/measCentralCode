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
    public partial class COMPortSelect : Form
    {

        public string SelectedPort { get; private set; }
        public COMPortSelect()
        {
            InitializeComponent();
            var ports = SerialPort.GetPortNames().AsEnumerable();
            foreach (var port in ports)
            {
                comboBox1.Items.Add(port);
            }

        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.SelectedPort = string.Empty;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            this.SelectedPort = (comboBox1.Items[comboBox1.SelectedIndex] as string) ?? "NA";
            this.Close();
        }
    }
}

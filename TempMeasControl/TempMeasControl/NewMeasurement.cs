using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TempMeasControl
{
    public partial class NewMeasurement : Form
    {

        public string MeasurementName {  get; private set; }
        public NewMeasurement()
        {
            InitializeComponent();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.Cancel;
            this.Close();   
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            this.MeasurementName = this.tbName.Text;    
            this.DialogResult = DialogResult.OK;
            Close();
        }
    }
}

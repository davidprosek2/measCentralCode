
using System;
using System.Diagnostics;
using System.IO.Ports;
using System.Windows.Forms;
using TempMeasControl.Commands;

namespace TempMeasControl
{
    public partial class Form1 : Form
    {
        
        private string _portName;   
        private string MeasurementName = "default";
        MessageProcessor _messageProcessor; 

        public Form1()
        {
            InitializeComponent();
            _messageProcessor = new MessageProcessor( this, UpdateTemperatureData);
      
            //   InitCom();
        }

      

        private void StartButton_Click(object sender, EventArgs e)
        {
            InitCom();
        }

        private void InitCom()
        {
            _messageProcessor.InitCom(_portName);
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            _messageProcessor.CloseCom();
        }

        

        private void UpdateTemperatureData(string data)
        {
            Debug.WriteLine(data);
            // Assume the data is in the format "temp1;temp2;temp3;...;temp8"
            string[] temperatures = data.Split(';');
            if (temperatures.Length == 8)
            {
                textBox1.Text = temperatures[0];
                textBox2.Text = temperatures[1];
                textBox3.Text = temperatures[2];
                textBox4.Text = temperatures[3];
                textBox5.Text = temperatures[4];
                textBox6.Text = temperatures[5];
                textBox7.Text = temperatures[6];
                textBox8.Text = temperatures[7];
            }
            WriteTemperatures(data);
        }

        

        private void WriteTemperatures(string data)
        {

            string datats = $"{DateTime.Now.ToString()};{data.Replace(".", ",")}";
            Debug.WriteLine(datats);
            File.AppendAllText($"{MeasurementName}.csv", datats);

        }

        private void button1_Click(object sender, EventArgs e)
        {
            NewMeasurement dlg = new NewMeasurement();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                MeasurementName = dlg.MeasurementName;
                this.Text = dlg.MeasurementName;
                InitCom();
            }

        }

        private void btnStopMeasurement_Click(object sender, EventArgs e)
        {
            MeasurementName = "default";
            this.Text = MeasurementName;
        }

        private void btnSensorsSettings_Click(object sender, EventArgs e)
        {
            SetupForm setupForm = new SetupForm(_serialPort);

            setupForm.ShowDialog();
        }

        private void portToolStripMenuItem_Click(object sender, EventArgs e)
        {
            COMPortSelect cOMPortSelect = new COMPortSelect();
            if (cOMPortSelect.ShowDialog() == DialogResult.OK)
            { 
                _portName = cOMPortSelect.SelectedPort;
                InitCom() ; 
            }
        }
    }
}

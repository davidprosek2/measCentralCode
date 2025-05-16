
using System;
using System.Diagnostics;
using System.IO.Ports;
using System.Windows.Forms;
using TempMeasControl.Commands;

namespace TempMeasControl
{
    public partial class Form1 : Form
    {

        private string _portName = "COM5";
        private string MeasurementName = "default";
        private double initC = 0;
        MessageProcessor _messageProcessor;

        public Form1()
        {
            InitializeComponent();
            _messageProcessor = new MessageProcessor(this, UpdateTemperatureData);

            InitCom();
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
            if (temperatures.Length > 8)
            {
                int.TryParse(temperatures[0], out int time);
                time = time / 1000;
                double v = 0;
                if (!double.TryParse(temperatures[10], out v))
                    double.TryParse(temperatures[10].Replace(".", ","), out v);

                double p = 0;
                if (!double.TryParse(temperatures[11], out p))
                    double.TryParse(temperatures[11].Replace(".", ","), out p);

                toolStripStatusLabel1.Text = time.ToString();
                textBox1.Text = temperatures[1] + " °C";
                textBox2.Text = temperatures[2] + " °C";
                textBox3.Text = temperatures[3] + " °C";
                textBox4.Text = temperatures[4] + " °C";
                textBox5.Text = temperatures[5] + " °C";
                textBox6.Text = temperatures[6] + " °C";
                textBox7.Text = temperatures[7] + " °C";
                textBox8.Text = temperatures[8] + " °C";//t8
                textBox9.Text = temperatures[9];//nic
                textBox10.Text = v.ToString("0.0") + " l"; //objem
                textBoxVt.Text = p.ToString("0") + "l/h";//orutok
                textBoxP.Text = v.ToString("0") + " l";

                tbVolume.Text = (v - initC).ToString("0") + " l";
                LastV = v;
                if (Math.Abs(initC) < 0.001)
                    initC = v;
            }
            WriteTemperatures(data);
        }
        private double LastV;


        private void WriteTemperatures(string data)
        {

            string datats = $"{DateTime.Now.ToString()};{data.Replace(".", ",").Replace(Environment.NewLine, "")}";
            if (this._notesForm != null && !_notesForm.IsDisposed)
            {
                lock (_notesForm.lck)
                {
                    datats += ";" + (this._notesForm.Volume.HasValue ? this._notesForm.Volume.Value.ToString("0000") : "") + ";";
                    datats += (this._notesForm.Energy.HasValue ? this._notesForm.Energy.Value.ToString("00.00") : "") + ";";
                    datats += (this._notesForm.Note ?? "").Replace(Environment.NewLine, " ") + ";";
                }
                _notesForm.Clear();
            }
            else
            {
                datats += ";;;";
            }
            Debug.WriteLine(datats);
            datats = datats.Replace(Environment.NewLine, "").Replace("\r", "").Replace("\n", "");
            File.AppendAllText($"{MeasurementName}.csv", datats + Environment.NewLine);
            //gitpokus
        }

        private void button1_Click(object sender, EventArgs e)
        {
            NewMeasurement dlg = new NewMeasurement();
            if (dlg.ShowDialog() == DialogResult.OK)
            {
                MeasurementName = dlg.MeasurementName;
                this.Text = dlg.MeasurementName;
                initC = LastV;
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
            SetupForm setupForm = new SetupForm(_messageProcessor.GetPort());

            setupForm.ShowDialog();
        }

        private void portToolStripMenuItem_Click(object sender, EventArgs e)
        {
            COMPortSelect cOMPortSelect = new COMPortSelect();
            if (cOMPortSelect.ShowDialog() == DialogResult.OK)
            {
                _portName = cOMPortSelect.SelectedPort;
                InitCom();
            }
        }

        private NotesForm _notesForm;

        private void btnNote_Click(object sender, EventArgs e)
        {
            if (_notesForm == null)
                _notesForm = new NotesForm();
            if (_notesForm.IsDisposed)
                _notesForm = new NotesForm();
            _notesForm.Show();
        }

        private void label13_Click(object sender, EventArgs e)
        {

        }
    }
}

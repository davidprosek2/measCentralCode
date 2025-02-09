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
    public partial class NotesForm : Form
    {
        public NotesForm()
        {
            InitializeComponent();
        }

        private void NotesForm_Load(object sender, EventArgs e)
        {

        }

        public object lck = new();

        public double? Volume { get; set; }
        public double? Energy { get; set; }

        public string Note { get; set; }

        public void Clear()
        {
            lock (lck)
            {
                this.Volume = null;
                this.Energy = null;
                this.Note = null!;
            }
        }



        private void btnWriteValues_Click(object sender, EventArgs e)
        {

            if (!string.IsNullOrWhiteSpace(tbEnergy.Text))
            {
                if (double.TryParse(tbEnergy.Text.Replace(".",","), out double value))
                {
                    lock (lck)
                    {
                        this.Energy = value;
                    }
                    this.tbEnergyOld.Text = value.ToString("0");
                    this.tbEnergy.Text = string.Empty;
                }
                else
                {
                    MessageBox.Show("Neplatný formát energie");
                }
            }

            if (!string.IsNullOrWhiteSpace(tbVolume.Text))
            {
                if (double.TryParse(tbVolume.Text.Replace(".", ","), out double value))
                {
                    lock (lck)
                    {
                        this.Volume = value;
                    }
                    this.tbVolumeOld.Text = value.ToString("0.0");
                    this.tbVolume.Text = string.Empty;
                }
                else
                {
                    MessageBox.Show("Neplatný formát objemu");
                }
            }

        }

        private void btnWriteNote_Click(object sender, EventArgs e)
        {
            lock (this.lck)
            {
                this.Note = this.tbNote.Text;

            }
            this.tbNote.BackColor = Color.LightGreen;

        }

        private void tbNote_TextChanged(object sender, EventArgs e)
        {
            this.tbNote.BackColor = SystemColors.Control;
        }
    }
}

namespace TempMeasControl
{
    partial class NotesForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            tbVolume = new TextBox();
            tbEnergy = new TextBox();
            tbNote = new RichTextBox();
            tbEnergyOld = new TextBox();
            tbVolumeOld = new TextBox();
            btnWriteValues = new Button();
            btnWriteNote = new Button();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(35, 32);
            label1.Name = "label1";
            label1.Size = new Size(94, 21);
            label1.TabIndex = 0;
            label1.Text = "Objem (m3)";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(35, 86);
            label2.Name = "label2";
            label2.Size = new Size(110, 21);
            label2.TabIndex = 1;
            label2.Text = "Energie(MWh)";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(35, 140);
            label3.Name = "label3";
            label3.Size = new Size(81, 21);
            label3.TabIndex = 2;
            label3.Text = "Poznámka";
            // 
            // tbVolume
            // 
            tbVolume.Location = new Point(198, 29);
            tbVolume.Name = "tbVolume";
            tbVolume.Size = new Size(100, 29);
            tbVolume.TabIndex = 3;
            // 
            // tbEnergy
            // 
            tbEnergy.Location = new Point(198, 83);
            tbEnergy.Name = "tbEnergy";
            tbEnergy.Size = new Size(100, 29);
            tbEnergy.TabIndex = 4;
            // 
            // tbNote
            // 
            tbNote.Location = new Point(198, 147);
            tbNote.Name = "tbNote";
            tbNote.Size = new Size(206, 96);
            tbNote.TabIndex = 5;
            tbNote.Text = "";
            tbNote.TextChanged += tbNote_TextChanged;
            // 
            // tbEnergyOld
            // 
            tbEnergyOld.Location = new Point(304, 83);
            tbEnergyOld.Name = "tbEnergyOld";
            tbEnergyOld.ReadOnly = true;
            tbEnergyOld.Size = new Size(100, 29);
            tbEnergyOld.TabIndex = 7;
            // 
            // tbVolumeOld
            // 
            tbVolumeOld.Location = new Point(304, 29);
            tbVolumeOld.Name = "tbVolumeOld";
            tbVolumeOld.ReadOnly = true;
            tbVolumeOld.Size = new Size(100, 29);
            tbVolumeOld.TabIndex = 6;
            // 
            // btnWriteValues
            // 
            btnWriteValues.Location = new Point(440, 29);
            btnWriteValues.Name = "btnWriteValues";
            btnWriteValues.Size = new Size(113, 83);
            btnWriteValues.TabIndex = 8;
            btnWriteValues.Text = "Zapsat hodnoty";
            btnWriteValues.UseVisualStyleBackColor = true;
            btnWriteValues.Click += btnWriteValues_Click;
            // 
            // btnWriteNote
            // 
            btnWriteNote.Location = new Point(440, 156);
            btnWriteNote.Name = "btnWriteNote";
            btnWriteNote.Size = new Size(113, 83);
            btnWriteNote.TabIndex = 9;
            btnWriteNote.Text = "Zapsat poznámku";
            btnWriteNote.UseVisualStyleBackColor = true;
            btnWriteNote.Click += btnWriteNote_Click;
            // 
            // NotesForm
            // 
            AutoScaleDimensions = new SizeF(9F, 21F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(585, 274);
            Controls.Add(btnWriteNote);
            Controls.Add(btnWriteValues);
            Controls.Add(tbEnergyOld);
            Controls.Add(tbVolumeOld);
            Controls.Add(tbNote);
            Controls.Add(tbEnergy);
            Controls.Add(tbVolume);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 238);
            Margin = new Padding(4);
            Name = "NotesForm";
            Text = "NotesForm";
            Load += NotesForm_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private Label label3;
        private TextBox tbVolume;
        private TextBox tbEnergy;
        private RichTextBox tbNote;
        private TextBox tbEnergyOld;
        private TextBox tbVolumeOld;
        private Button btnWriteValues;
        private Button btnWriteNote;
    }
}
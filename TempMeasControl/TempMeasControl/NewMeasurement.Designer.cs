namespace TempMeasControl
{
    partial class NewMeasurement
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
            tbName = new TextBox();
            btnOK = new Button();
            btnCancel = new Button();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(15, 47);
            label1.Margin = new Padding(6, 0, 6, 0);
            label1.Name = "label1";
            label1.Size = new Size(80, 32);
            label1.TabIndex = 0;
            label1.Text = "Název";
            // 
            // tbName
            // 
            tbName.Location = new Point(119, 44);
            tbName.Margin = new Padding(6, 6, 6, 6);
            tbName.Name = "tbName";
            tbName.Size = new Size(394, 39);
            tbName.TabIndex = 1;
            // 
            // btnOK
            // 
            btnOK.Location = new Point(272, 117);
            btnOK.Name = "btnOK";
            btnOK.Size = new Size(241, 70);
            btnOK.TabIndex = 2;
            btnOK.Text = "Start";
            btnOK.UseVisualStyleBackColor = true;
            btnOK.Click += btnOK_Click;
            // 
            // btnCancel
            // 
            btnCancel.Location = new Point(15, 117);
            btnCancel.Name = "btnCancel";
            btnCancel.Size = new Size(241, 70);
            btnCancel.TabIndex = 3;
            btnCancel.Text = "Zpět";
            btnCancel.UseVisualStyleBackColor = true;
            btnCancel.Click += btnCancel_Click;
            // 
            // NewMeasurement
            // 
            AutoScaleDimensions = new SizeF(13F, 32F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(542, 223);
            Controls.Add(btnCancel);
            Controls.Add(btnOK);
            Controls.Add(tbName);
            Controls.Add(label1);
            Font = new Font("Segoe UI", 18F, FontStyle.Regular, GraphicsUnit.Point, 238);
            FormBorderStyle = FormBorderStyle.FixedToolWindow;
            Margin = new Padding(6, 6, 6, 6);
            Name = "NewMeasurement";
            Text = "Nové měření";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private TextBox tbName;
        private Button btnOK;
        private Button btnCancel;
    }
}
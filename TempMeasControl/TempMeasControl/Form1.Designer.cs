namespace TempMeasControl
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label label5;
        private Label label6;
        private Label label7;
        private Label label8;
        private TextBox textBox1;
        private TextBox textBox2;
        private TextBox textBox3;
        private TextBox textBox4;
        private TextBox textBox5;
        private TextBox textBox6;
        private TextBox textBox7;
        private TextBox textBox8;
        private Button startButton;
        private Button stopButton;

        private void InitializeComponent()
        {
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            label4 = new Label();
            label5 = new Label();
            label6 = new Label();
            label7 = new Label();
            label8 = new Label();
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            textBox3 = new TextBox();
            textBox4 = new TextBox();
            textBox5 = new TextBox();
            textBox6 = new TextBox();
            textBox7 = new TextBox();
            textBox8 = new TextBox();
            startButton = new Button();
            stopButton = new Button();
            button1 = new Button();
            btnStopMeasurement = new Button();
            btnSensorsSettings = new Button();
            menuStrip1 = new MenuStrip();
            nastaveníToolStripMenuItem = new ToolStripMenuItem();
            portToolStripMenuItem = new ToolStripMenuItem();
            nastaveníČidelToolStripMenuItem = new ToolStripMenuItem();
            statusStrip1 = new StatusStrip();
            statusStripPort = new ToolStripStatusLabel();
            menuStrip1.SuspendLayout();
            statusStrip1.SuspendLayout();
            SuspendLayout();
            // 
            // label1
            // 
            label1.Location = new Point(11, 51);
            label1.Name = "label1";
            label1.Size = new Size(50, 20);
            label1.TabIndex = 0;
            label1.Text = "Temp 1:";
            // 
            // label2
            // 
            label2.Location = new Point(11, 81);
            label2.Name = "label2";
            label2.Size = new Size(50, 20);
            label2.TabIndex = 1;
            label2.Text = "Temp 2:";
            // 
            // label3
            // 
            label3.Location = new Point(11, 111);
            label3.Name = "label3";
            label3.Size = new Size(50, 20);
            label3.TabIndex = 2;
            label3.Text = "Temp 3:";
            // 
            // label4
            // 
            label4.Location = new Point(11, 141);
            label4.Name = "label4";
            label4.Size = new Size(50, 20);
            label4.TabIndex = 3;
            label4.Text = "Temp 4:";
            // 
            // label5
            // 
            label5.Location = new Point(201, 51);
            label5.Name = "label5";
            label5.Size = new Size(50, 20);
            label5.TabIndex = 4;
            label5.Text = "Temp 5:";
            // 
            // label6
            // 
            label6.Location = new Point(201, 81);
            label6.Name = "label6";
            label6.Size = new Size(50, 20);
            label6.TabIndex = 5;
            label6.Text = "Temp 6:";
            // 
            // label7
            // 
            label7.Location = new Point(201, 111);
            label7.Name = "label7";
            label7.Size = new Size(50, 20);
            label7.TabIndex = 6;
            label7.Text = "Temp 7:";
            // 
            // label8
            // 
            label8.Location = new Point(201, 141);
            label8.Name = "label8";
            label8.Size = new Size(50, 20);
            label8.TabIndex = 7;
            label8.Text = "Temp 8:";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(71, 51);
            textBox1.Name = "textBox1";
            textBox1.ReadOnly = true;
            textBox1.Size = new Size(100, 23);
            textBox1.TabIndex = 8;
            // 
            // textBox2
            // 
            textBox2.Location = new Point(71, 81);
            textBox2.Name = "textBox2";
            textBox2.ReadOnly = true;
            textBox2.Size = new Size(100, 23);
            textBox2.TabIndex = 9;
            // 
            // textBox3
            // 
            textBox3.Location = new Point(71, 111);
            textBox3.Name = "textBox3";
            textBox3.ReadOnly = true;
            textBox3.Size = new Size(100, 23);
            textBox3.TabIndex = 10;
            // 
            // textBox4
            // 
            textBox4.Location = new Point(71, 141);
            textBox4.Name = "textBox4";
            textBox4.ReadOnly = true;
            textBox4.Size = new Size(100, 23);
            textBox4.TabIndex = 11;
            // 
            // textBox5
            // 
            textBox5.Location = new Point(261, 51);
            textBox5.Name = "textBox5";
            textBox5.ReadOnly = true;
            textBox5.Size = new Size(100, 23);
            textBox5.TabIndex = 12;
            // 
            // textBox6
            // 
            textBox6.Location = new Point(261, 81);
            textBox6.Name = "textBox6";
            textBox6.ReadOnly = true;
            textBox6.Size = new Size(100, 23);
            textBox6.TabIndex = 13;
            // 
            // textBox7
            // 
            textBox7.Location = new Point(261, 111);
            textBox7.Name = "textBox7";
            textBox7.ReadOnly = true;
            textBox7.Size = new Size(100, 23);
            textBox7.TabIndex = 14;
            // 
            // textBox8
            // 
            textBox8.Location = new Point(261, 141);
            textBox8.Name = "textBox8";
            textBox8.ReadOnly = true;
            textBox8.Size = new Size(100, 23);
            textBox8.TabIndex = 15;
            // 
            // startButton
            // 
            startButton.Location = new Point(13, 191);
            startButton.Name = "startButton";
            startButton.Size = new Size(75, 23);
            startButton.TabIndex = 16;
            startButton.Text = "Start";
            startButton.Click += StartButton_Click;
            // 
            // stopButton
            // 
            stopButton.Location = new Point(96, 191);
            stopButton.Name = "stopButton";
            stopButton.Size = new Size(75, 23);
            stopButton.TabIndex = 17;
            stopButton.Text = "Stop";
            stopButton.Click += StopButton_Click;
            // 
            // button1
            // 
            button1.Location = new Point(439, 53);
            button1.Name = "button1";
            button1.Size = new Size(122, 23);
            button1.TabIndex = 18;
            button1.Text = "Nové měření";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // btnStopMeasurement
            // 
            btnStopMeasurement.Location = new Point(587, 53);
            btnStopMeasurement.Name = "btnStopMeasurement";
            btnStopMeasurement.Size = new Size(140, 23);
            btnStopMeasurement.TabIndex = 19;
            btnStopMeasurement.Text = "Zastavit měření";
            btnStopMeasurement.UseVisualStyleBackColor = true;
            btnStopMeasurement.Click += btnStopMeasurement_Click;
            // 
            // btnSensorsSettings
            // 
            btnSensorsSettings.Location = new Point(13, 236);
            btnSensorsSettings.Name = "btnSensorsSettings";
            btnSensorsSettings.Size = new Size(171, 23);
            btnSensorsSettings.TabIndex = 20;
            btnSensorsSettings.Text = "Nastavení čidel";
            btnSensorsSettings.UseVisualStyleBackColor = true;
            btnSensorsSettings.Click += btnSensorsSettings_Click;
            // 
            // menuStrip1
            // 
            menuStrip1.Items.AddRange(new ToolStripItem[] { nastaveníToolStripMenuItem });
            menuStrip1.Location = new Point(0, 0);
            menuStrip1.Name = "menuStrip1";
            menuStrip1.Size = new Size(755, 24);
            menuStrip1.TabIndex = 21;
            menuStrip1.Text = "menuStrip1";
            // 
            // nastaveníToolStripMenuItem
            // 
            nastaveníToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { portToolStripMenuItem, nastaveníČidelToolStripMenuItem });
            nastaveníToolStripMenuItem.Name = "nastaveníToolStripMenuItem";
            nastaveníToolStripMenuItem.Size = new Size(71, 20);
            nastaveníToolStripMenuItem.Text = "Nastavení";
            // 
            // portToolStripMenuItem
            // 
            portToolStripMenuItem.Name = "portToolStripMenuItem";
            portToolStripMenuItem.Size = new Size(180, 22);
            portToolStripMenuItem.Text = "Port";
            portToolStripMenuItem.Click += portToolStripMenuItem_Click;
            // 
            // nastaveníČidelToolStripMenuItem
            // 
            nastaveníČidelToolStripMenuItem.Name = "nastaveníČidelToolStripMenuItem";
            nastaveníČidelToolStripMenuItem.Size = new Size(180, 22);
            nastaveníČidelToolStripMenuItem.Text = "Nastavení čidel";
            // 
            // statusStrip1
            // 
            statusStrip1.Items.AddRange(new ToolStripItem[] { statusStripPort });
            statusStrip1.Location = new Point(0, 280);
            statusStrip1.Name = "statusStrip1";
            statusStrip1.Size = new Size(755, 22);
            statusStrip1.TabIndex = 22;
            statusStrip1.Text = "statusStrip1";
            // 
            // statusStripPort
            // 
            statusStripPort.Name = "statusStripPort";
            statusStripPort.Size = new Size(84, 17);
            statusStripPort.Text = "statusStripPort";
            // 
            // Form1
            // 
            ClientSize = new Size(755, 302);
            Controls.Add(statusStrip1);
            Controls.Add(btnSensorsSettings);
            Controls.Add(btnStopMeasurement);
            Controls.Add(button1);
            Controls.Add(label1);
            Controls.Add(label2);
            Controls.Add(label3);
            Controls.Add(label4);
            Controls.Add(label5);
            Controls.Add(label6);
            Controls.Add(label7);
            Controls.Add(label8);
            Controls.Add(textBox1);
            Controls.Add(textBox2);
            Controls.Add(textBox3);
            Controls.Add(textBox4);
            Controls.Add(textBox5);
            Controls.Add(textBox6);
            Controls.Add(textBox7);
            Controls.Add(textBox8);
            Controls.Add(startButton);
            Controls.Add(stopButton);
            Controls.Add(menuStrip1);
            MainMenuStrip = menuStrip1;
            Name = "Form1";
            menuStrip1.ResumeLayout(false);
            menuStrip1.PerformLayout();
            statusStrip1.ResumeLayout(false);
            statusStrip1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }


        #endregion

        private Button button1;
        private Button btnStopMeasurement;
        private Button btnSensorsSettings;
        private MenuStrip menuStrip1;
        private ToolStripMenuItem nastaveníToolStripMenuItem;
        private ToolStripMenuItem portToolStripMenuItem;
        private ToolStripMenuItem nastaveníČidelToolStripMenuItem;
        private StatusStrip statusStrip1;
        private ToolStripStatusLabel statusStripPort;
    }
}

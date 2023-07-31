namespace GUI
{
    partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.A1 = new System.Windows.Forms.CheckBox();
            this.A2 = new System.Windows.Forms.CheckBox();
            this.A3 = new System.Windows.Forms.CheckBox();
            this.A4 = new System.Windows.Forms.CheckBox();
            this.A5 = new System.Windows.Forms.CheckBox();
            this.A6 = new System.Windows.Forms.CheckBox();
            this.A7 = new System.Windows.Forms.CheckBox();
            this.A8 = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // A1
            // 
            this.A1.AutoSize = true;
            this.A1.Location = new System.Drawing.Point(212, 83);
            this.A1.Name = "A1";
            this.A1.Size = new System.Drawing.Size(47, 21);
            this.A1.TabIndex = 0;
            this.A1.Text = "A1";
            this.A1.UseVisualStyleBackColor = true;
            this.A1.CheckedChanged += new System.EventHandler(this.A1_CheckedChanged);
            // 
            // A2
            // 
            this.A2.AutoSize = true;
            this.A2.Location = new System.Drawing.Point(212, 110);
            this.A2.Name = "A2";
            this.A2.Size = new System.Drawing.Size(47, 21);
            this.A2.TabIndex = 1;
            this.A2.Text = "A2";
            this.A2.UseVisualStyleBackColor = true;
            this.A2.CheckedChanged += new System.EventHandler(this.A2_CheckedChanged);
            // 
            // A3
            // 
            this.A3.AutoSize = true;
            this.A3.Location = new System.Drawing.Point(212, 137);
            this.A3.Name = "A3";
            this.A3.Size = new System.Drawing.Size(47, 21);
            this.A3.TabIndex = 1;
            this.A3.Text = "A3";
            this.A3.UseVisualStyleBackColor = true;
            this.A3.CheckedChanged += new System.EventHandler(this.A3_CheckedChanged);
            // 
            // A4
            // 
            this.A4.AutoSize = true;
            this.A4.Location = new System.Drawing.Point(212, 164);
            this.A4.Name = "A4";
            this.A4.Size = new System.Drawing.Size(47, 21);
            this.A4.TabIndex = 1;
            this.A4.Text = "A4";
            this.A4.UseVisualStyleBackColor = true;
            this.A4.CheckedChanged += new System.EventHandler(this.A4_CheckedChanged);
            // 
            // A5
            // 
            this.A5.AutoSize = true;
            this.A5.Location = new System.Drawing.Point(212, 191);
            this.A5.Name = "A5";
            this.A5.Size = new System.Drawing.Size(47, 21);
            this.A5.TabIndex = 1;
            this.A5.Text = "A5";
            this.A5.UseVisualStyleBackColor = true;
            this.A5.CheckedChanged += new System.EventHandler(this.A5_CheckedChanged);
            // 
            // A6
            // 
            this.A6.AutoSize = true;
            this.A6.Location = new System.Drawing.Point(212, 218);
            this.A6.Name = "A6";
            this.A6.Size = new System.Drawing.Size(47, 21);
            this.A6.TabIndex = 1;
            this.A6.Text = "A6";
            this.A6.UseVisualStyleBackColor = true;
            this.A6.CheckedChanged += new System.EventHandler(this.A6_CheckedChanged);
            // 
            // A7
            // 
            this.A7.AutoSize = true;
            this.A7.Location = new System.Drawing.Point(212, 245);
            this.A7.Name = "A7";
            this.A7.Size = new System.Drawing.Size(47, 21);
            this.A7.TabIndex = 1;
            this.A7.Text = "A7";
            this.A7.UseVisualStyleBackColor = true;
            this.A7.CheckedChanged += new System.EventHandler(this.A7_CheckedChanged);
            // 
            // A8
            // 
            this.A8.AutoSize = true;
            this.A8.Location = new System.Drawing.Point(212, 272);
            this.A8.Name = "A8";
            this.A8.Size = new System.Drawing.Size(47, 21);
            this.A8.TabIndex = 1;
            this.A8.Text = "A8";
            this.A8.UseVisualStyleBackColor = true;
            this.A8.CheckedChanged += new System.EventHandler(this.A8_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(208, 390);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(90, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "Rate 115200";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(12, 29);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(195, 471);
            this.pictureBox1.TabIndex = 4;
            this.pictureBox1.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(412, 512);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.A8);
            this.Controls.Add(this.A7);
            this.Controls.Add(this.A6);
            this.Controls.Add(this.A5);
            this.Controls.Add(this.A4);
            this.Controls.Add(this.A3);
            this.Controls.Add(this.A2);
            this.Controls.Add(this.A1);
            this.Name = "Form1";
            this.Text = "GPIO Extender";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox A1;
        private System.Windows.Forms.CheckBox A2;
        private System.Windows.Forms.CheckBox A3;
        private System.Windows.Forms.CheckBox A4;
        private System.Windows.Forms.CheckBox A5;
        private System.Windows.Forms.CheckBox A6;
        private System.Windows.Forms.CheckBox A7;
        private System.Windows.Forms.CheckBox A8;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}


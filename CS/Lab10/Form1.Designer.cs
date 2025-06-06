namespace Lab10
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.saveButton = new System.Windows.Forms.Button();
            this.executeButton = new System.Windows.Forms.Button();
            this.loadButton = new System.Windows.Forms.Button();
            this.mozaicLabel = new System.Windows.Forms.Label();
            this.mozaicBar = new System.Windows.Forms.TrackBar();
            this.pictureBox = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.mozaicBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).BeginInit();
            this.SuspendLayout();
            // 
            // saveButton
            // 
            this.saveButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
            this.saveButton.Location = new System.Drawing.Point(218, 12);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(97, 26);
            this.saveButton.TabIndex = 0;
            this.saveButton.Text = "Сохранить";
            this.saveButton.UseVisualStyleBackColor = true;
            // 
            // executeButton
            // 
            this.executeButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
            this.executeButton.Location = new System.Drawing.Point(115, 12);
            this.executeButton.Name = "executeButton";
            this.executeButton.Size = new System.Drawing.Size(97, 26);
            this.executeButton.TabIndex = 0;
            this.executeButton.Text = "Применить";
            this.executeButton.UseVisualStyleBackColor = true;
            // 
            // loadButton
            // 
            this.loadButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
            this.loadButton.Location = new System.Drawing.Point(12, 12);
            this.loadButton.Name = "loadButton";
            this.loadButton.Size = new System.Drawing.Size(97, 26);
            this.loadButton.TabIndex = 0;
            this.loadButton.Text = "Загрузить";
            this.loadButton.UseVisualStyleBackColor = true;
            // 
            // mozaicLabel
            // 
            this.mozaicLabel.AutoSize = true;
            this.mozaicLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F);
            this.mozaicLabel.Location = new System.Drawing.Point(321, 17);
            this.mozaicLabel.Name = "mozaicLabel";
            this.mozaicLabel.Size = new System.Drawing.Size(145, 17);
            this.mozaicLabel.TabIndex = 1;
            this.mozaicLabel.Text = "Количество мозайки";
            // 
            // mozaicBar
            // 
            this.mozaicBar.Location = new System.Drawing.Point(482, 12);
            this.mozaicBar.Name = "mozaicBar";
            this.mozaicBar.Size = new System.Drawing.Size(230, 45);
            this.mozaicBar.TabIndex = 2;
            this.mozaicBar.TickFrequency = 10;
            // 
            // pictureBox
            // 
            this.pictureBox.Location = new System.Drawing.Point(13, 45);
            this.pictureBox.Name = "pictureBox";
            this.pictureBox.Size = new System.Drawing.Size(702, 500);
            this.pictureBox.TabIndex = 3;
            this.pictureBox.TabStop = false;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(727, 557);
            this.Controls.Add(this.pictureBox);
            this.Controls.Add(this.mozaicBar);
            this.Controls.Add(this.mozaicLabel);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.executeButton);
            this.Controls.Add(this.loadButton);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.mozaicBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.Button executeButton;
        private System.Windows.Forms.Button loadButton;
        private System.Windows.Forms.Label mozaicLabel;
        private System.Windows.Forms.TrackBar mozaicBar;
        private System.Windows.Forms.PictureBox pictureBox;
    }
}


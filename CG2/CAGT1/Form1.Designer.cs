namespace CAGT1
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
            this.buttonLoad = new System.Windows.Forms.Button();
            this.labelFile = new System.Windows.Forms.Label();
            this.labelMoveY = new System.Windows.Forms.Label();
            this.trackBarMoveY = new System.Windows.Forms.TrackBar();
            this.labelMoveX = new System.Windows.Forms.Label();
            this.trackBarMoveX = new System.Windows.Forms.TrackBar();
            this.labelRotateY = new System.Windows.Forms.Label();
            this.trackBarRotateY = new System.Windows.Forms.TrackBar();
            this.labelRotateX = new System.Windows.Forms.Label();
            this.trackBarRotateX = new System.Windows.Forms.TrackBar();
            this.labelScale = new System.Windows.Forms.Label();
            this.trackBarScale = new System.Windows.Forms.TrackBar();
            this.labelRotateZ = new System.Windows.Forms.Label();
            this.trackBarRotateZ = new System.Windows.Forms.TrackBar();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarMoveY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarMoveX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRotateY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRotateX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarScale)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRotateZ)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonLoad
            // 
            this.buttonLoad.Font = new System.Drawing.Font("Playtime Cyrillic", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonLoad.Location = new System.Drawing.Point(627, 18);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(200, 51);
            this.buttonLoad.TabIndex = 48;
            this.buttonLoad.Text = "Загрузить";
            this.buttonLoad.UseVisualStyleBackColor = true;
            // 
            // labelFile
            // 
            this.labelFile.AutoSize = true;
            this.labelFile.Font = new System.Drawing.Font("Playtime Cyrillic", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelFile.Location = new System.Drawing.Point(571, 32);
            this.labelFile.Name = "labelFile";
            this.labelFile.Size = new System.Drawing.Size(43, 17);
            this.labelFile.TabIndex = 47;
            this.labelFile.Text = "Файл";
            // 
            // labelMoveY
            // 
            this.labelMoveY.AutoSize = true;
            this.labelMoveY.Font = new System.Drawing.Font("Playtime Cyrillic", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelMoveY.Location = new System.Drawing.Point(571, 436);
            this.labelMoveY.Name = "labelMoveY";
            this.labelMoveY.Size = new System.Drawing.Size(106, 17);
            this.labelMoveY.TabIndex = 57;
            this.labelMoveY.Text = "Перемещение Y";
            // 
            // trackBarMoveY
            // 
            this.trackBarMoveY.Location = new System.Drawing.Point(574, 456);
            this.trackBarMoveY.Name = "trackBarMoveY";
            this.trackBarMoveY.Size = new System.Drawing.Size(271, 45);
            this.trackBarMoveY.TabIndex = 51;
            this.trackBarMoveY.TickFrequency = 20;
            // 
            // labelMoveX
            // 
            this.labelMoveX.AutoSize = true;
            this.labelMoveX.Font = new System.Drawing.Font("Playtime Cyrillic", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelMoveX.Location = new System.Drawing.Point(571, 368);
            this.labelMoveX.Name = "labelMoveX";
            this.labelMoveX.Size = new System.Drawing.Size(106, 17);
            this.labelMoveX.TabIndex = 58;
            this.labelMoveX.Text = "Перемещение X";
            // 
            // trackBarMoveX
            // 
            this.trackBarMoveX.Location = new System.Drawing.Point(574, 388);
            this.trackBarMoveX.Name = "trackBarMoveX";
            this.trackBarMoveX.Size = new System.Drawing.Size(271, 45);
            this.trackBarMoveX.TabIndex = 52;
            this.trackBarMoveX.TickFrequency = 20;
            // 
            // labelRotateY
            // 
            this.labelRotateY.AutoSize = true;
            this.labelRotateY.Font = new System.Drawing.Font("Playtime Cyrillic", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelRotateY.Location = new System.Drawing.Point(571, 232);
            this.labelRotateY.Name = "labelRotateY";
            this.labelRotateY.Size = new System.Drawing.Size(73, 17);
            this.labelRotateY.TabIndex = 56;
            this.labelRotateY.Text = "Поворот Y";
            // 
            // trackBarRotateY
            // 
            this.trackBarRotateY.Location = new System.Drawing.Point(575, 252);
            this.trackBarRotateY.Name = "trackBarRotateY";
            this.trackBarRotateY.Size = new System.Drawing.Size(271, 45);
            this.trackBarRotateY.TabIndex = 53;
            this.trackBarRotateY.TickFrequency = 30;
            // 
            // labelRotateX
            // 
            this.labelRotateX.AutoSize = true;
            this.labelRotateX.Font = new System.Drawing.Font("Playtime Cyrillic", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelRotateX.Location = new System.Drawing.Point(571, 164);
            this.labelRotateX.Name = "labelRotateX";
            this.labelRotateX.Size = new System.Drawing.Size(73, 17);
            this.labelRotateX.TabIndex = 55;
            this.labelRotateX.Text = "Поворот X";
            // 
            // trackBarRotateX
            // 
            this.trackBarRotateX.Location = new System.Drawing.Point(574, 184);
            this.trackBarRotateX.Name = "trackBarRotateX";
            this.trackBarRotateX.Size = new System.Drawing.Size(271, 45);
            this.trackBarRotateX.TabIndex = 50;
            this.trackBarRotateX.TickFrequency = 30;
            // 
            // labelScale
            // 
            this.labelScale.AutoSize = true;
            this.labelScale.Font = new System.Drawing.Font("Playtime Cyrillic", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelScale.Location = new System.Drawing.Point(571, 84);
            this.labelScale.Name = "labelScale";
            this.labelScale.Size = new System.Drawing.Size(58, 17);
            this.labelScale.TabIndex = 54;
            this.labelScale.Text = "Маштаб";
            // 
            // trackBarScale
            // 
            this.trackBarScale.Location = new System.Drawing.Point(574, 105);
            this.trackBarScale.Name = "trackBarScale";
            this.trackBarScale.Size = new System.Drawing.Size(271, 45);
            this.trackBarScale.TabIndex = 49;
            this.trackBarScale.TickFrequency = 10;
            // 
            // labelRotateZ
            // 
            this.labelRotateZ.AutoSize = true;
            this.labelRotateZ.Font = new System.Drawing.Font("Playtime Cyrillic", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelRotateZ.Location = new System.Drawing.Point(571, 300);
            this.labelRotateZ.Name = "labelRotateZ";
            this.labelRotateZ.Size = new System.Drawing.Size(74, 17);
            this.labelRotateZ.TabIndex = 60;
            this.labelRotateZ.Text = "Поворот Z";
            // 
            // trackBarRotateZ
            // 
            this.trackBarRotateZ.Location = new System.Drawing.Point(574, 320);
            this.trackBarRotateZ.Name = "trackBarRotateZ";
            this.trackBarRotateZ.Size = new System.Drawing.Size(271, 45);
            this.trackBarRotateZ.TabIndex = 59;
            this.trackBarRotateZ.TickFrequency = 30;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(864, 582);
            this.Controls.Add(this.labelRotateZ);
            this.Controls.Add(this.trackBarRotateZ);
            this.Controls.Add(this.labelMoveY);
            this.Controls.Add(this.trackBarMoveY);
            this.Controls.Add(this.labelMoveX);
            this.Controls.Add(this.trackBarMoveX);
            this.Controls.Add(this.labelRotateY);
            this.Controls.Add(this.trackBarRotateY);
            this.Controls.Add(this.labelRotateX);
            this.Controls.Add(this.trackBarRotateX);
            this.Controls.Add(this.labelScale);
            this.Controls.Add(this.trackBarScale);
            this.Controls.Add(this.buttonLoad);
            this.Controls.Add(this.labelFile);
            this.Name = "Form1";
            this.Text = "Дайте автомат(!)";
            ((System.ComponentModel.ISupportInitialize)(this.trackBarMoveY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarMoveX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRotateY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRotateX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarScale)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBarRotateZ)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.Label labelFile;
        private System.Windows.Forms.Label labelMoveY;
        private System.Windows.Forms.TrackBar trackBarMoveY;
        private System.Windows.Forms.Label labelMoveX;
        private System.Windows.Forms.TrackBar trackBarMoveX;
        private System.Windows.Forms.Label labelRotateY;
        private System.Windows.Forms.TrackBar trackBarRotateY;
        private System.Windows.Forms.Label labelRotateX;
        private System.Windows.Forms.TrackBar trackBarRotateX;
        private System.Windows.Forms.Label labelScale;
        private System.Windows.Forms.TrackBar trackBarScale;
        private System.Windows.Forms.Label labelRotateZ;
        private System.Windows.Forms.TrackBar trackBarRotateZ;
    }
}


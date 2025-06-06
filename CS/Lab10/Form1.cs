using System;
using System.Drawing;
using System.Windows.Forms;

namespace Lab10
{
    public partial class Form1 : Form
    {
        private Bitmap bmp;

        public Form1()
        {
            InitializeComponent();
            mozaicBar.Minimum = 0; mozaicBar.Maximum = 100;
            loadButton.Click += buttonOpen;
            saveButton.Click += buttonSave;
            mozaicBar.ValueChanged += barUpdate;
            executeButton.Click += exc;
        }

        private void barUpdate(object sender, EventArgs e)
        {
            if (bmp != null)
                mozaicLabel.Text = $"Мозайка {(int)(bmp.Width * (double)(mozaicBar.Value) / 100)}x{(int)(bmp.Height * (double)(mozaicBar.Value) / 100)}";
        }

        private void exc(object sender, EventArgs e)
        {
            if (bmp != null)
            {
                int blockWidth = (int)((double)(mozaicBar.Value) / 100 * bmp.Width);
                int blockHeight = (int)((double)(mozaicBar.Value) / 100 * bmp.Height);
                applyMosaic(blockWidth, blockHeight);
            }
        }

        private void buttonOpen(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Image files (*.BMP, *.JPG, *.PNG, *.ICO)| *.bmp; *.jpg; *.png; *.ico;";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                Image image = Image.FromFile(dialog.FileName);
                //int width = pictureBox.Width;
                //int height = pictureBox.Height;
                int width = image.Width;
                int height = image.Height;
                pictureBox.Width = width;
                pictureBox.Height = height;
                bmp = new Bitmap(image, width, height);
                pictureBox.Image = bmp;
                mozaicLabel.Text = $"Мозайка {(int)(bmp.Width * (double)(mozaicBar.Value) / 100)}x{(int)(bmp.Height * (double)(mozaicBar.Value) / 100)}";
            }
        }

        private void buttonSave(object sender, EventArgs e)
        {
            if (bmp != null)
            {
                bmp = pictureBox.Image as Bitmap;
                SaveFileDialog savedialog = new SaveFileDialog();
                savedialog.Title = "Сохранить картинку как ...";
                savedialog.OverwritePrompt = true;
                savedialog.CheckPathExists = true;
                savedialog.Filter =
                "Bitmap File(*.bmp)|*.bmp|" +
                "JPEG File(*.jpg)|*.jpg|" +
                "PNG File(*.png)|*.png";
                savedialog.ShowHelp = true;
                if (savedialog.ShowDialog() == DialogResult.OK)
                {
                    string fileName = savedialog.FileName;
                    string strFilExtn =
                    fileName.Remove(0, fileName.Length - 3);
                    switch (strFilExtn)
                    {
                        case "bmp":
                            bmp.Save(fileName, System.Drawing.Imaging.ImageFormat.Bmp);
                            break;
                        case "jpg":
                            bmp.Save(fileName, System.Drawing.Imaging.ImageFormat.Jpeg);
                            break;
                        case "png":
                            bmp.Save(fileName, System.Drawing.Imaging.ImageFormat.Png);
                            break;
                        default:
                            break;
                    }
                }
            }
        }

        private void applyMosaic(int blockWidth, int blockHeight)
        {
            if (bmp == null) return;
            if (blockWidth <= 0 || blockHeight <= 0) return;
            Bitmap mosaicBmp = new Bitmap(bmp.Width, bmp.Height);

            for (int y = 0; y < bmp.Height; y += blockHeight)
            {
                for (int x = 0; x < bmp.Width; x += blockWidth)
                {
                    int centerX = x + blockWidth / 2;
                    int centerY = y + blockHeight / 2;
                    if (centerX >= bmp.Width) centerX = bmp.Width - 1;
                    if (centerY >= bmp.Height) centerY = bmp.Height - 1;

                    Color centerColor = bmp.GetPixel(centerX, centerY);

                    for (int j = y; j < y + blockHeight && j < bmp.Height; j++)
                        for (int i = x; i < x + blockWidth && i < bmp.Width; i++)
                            mosaicBmp.SetPixel(i, j, centerColor);
                }
            }

            pictureBox.Image = mosaicBmp;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection.Emit;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.Button;

namespace temp
{
    public partial class Form1 : Form
    {
        float scale = 1.0f;
        float rotateX = 0.0f;
        float rotateY = 0.0f;
        float translateX = 0.0f;
        float translateY = 0.0f;
        float[,] outBuff;
        float[,] inBuff;


        public Form1()
        {
            InitializeComponent();
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);

            trackBar1.Minimum = 10; trackBar1.Maximum = 300; trackBar1.Value = 100; // Масштаб
            trackBar2.Minimum = -180; trackBar2.Maximum = 180; // Поворот X
            trackBar3.Minimum = -180; trackBar3.Maximum = 180; // Поворот Y
            trackBar4.Minimum = -100; trackBar4.Maximum = 100; // Перемещение X
            trackBar5.Minimum = -100; trackBar5.Maximum = 100; // Перемещение Y

            trackBar1.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar2.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar3.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar4.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar5.ValueChanged += (s, e) => { UpdateTransform(); };
            label1.Click += label1_Click;
            label2.Click += label2_Click;
            label3.Click += label3_Click;
            label4.Click += label4_Click;
            label5.Click += label5_Click;
            label6.Click += label6_Click;
            button1.Click += Button1_Click;

            pictureBox1.BackColor = Color.White;
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "BMP Image (*.bmp)|*.bmp";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                LoadBMP(ofd.FileName);
                UpdateTransform();
            }
        }

        private void LoadBMP(string path)
        {
            Bitmap bmp = new Bitmap(path);
            inBuff = new float[bmp.Width, bmp.Height];

            for (int y = 0; y < bmp.Height; y++) for (int x = 0; x < bmp.Width; x++)
            {
                Color pixel = bmp.GetPixel(x, y);
                float height = (pixel.R + pixel.G + pixel.B) / 3f;
                inBuff[x, y] = height;
            }

            int screen = (int)Math.Sqrt(bmp.Width * bmp.Width + bmp.Height * bmp.Height);
            outBuff = new float[screen, screen];
            int offsetX = (screen - bmp.Width) / 2;
            int offsetY = (screen - bmp.Height) / 2;

            for (int y = 0; y < bmp.Height; y++)
                for (int x = 0; x < bmp.Width; x++)
                    outBuff[x + offsetX, y + offsetY] = inBuff[x, y];
            //outBuff = inBuff;
        }

        private void UpdateTransform()
        {
            scale = trackBar1.Value / 100f;
            rotateX = DegreesToRadians(trackBar2.Value);
            rotateY = DegreesToRadians(trackBar3.Value);
            translateX = trackBar4.Value;
            translateY = trackBar5.Value;

            using (Graphics g = Graphics.FromImage(pictureBox1.Image))
            {
                g.Clear(Color.White);
                Draw(g);
            }
            pictureBox1.Invalidate();
        }

        private void Draw(Graphics g)
        {
            if (inBuff == null) return;
            int pW = pictureBox1.Width; int pH = pictureBox1.Height;
            int W = outBuff.GetLength(0); int H = outBuff.GetLength(1);
            float pScale = (float)pW / (float)W;

            int centerX = pW / 2; int centerY = pH / 2;
            int[] topH = new int[pW];
            int [] bottomH = new int[pW];

            for (int i = 0; i < pW; i++) { topH[i] = int.MinValue; bottomH[i] = int.MaxValue; }

            int zs = 0;
            int ze = H;
            int stepZ = 2;
            float angleY = RadiansToDegrees(rotateY);
            if (angleY > 90 || angleY < -90)
            {
                zs = H - 1;
                ze = -1;
                stepZ = -stepZ;
            }

            int xs = 0;
            int xe = W;
            int stepX = 2;
            float angleX = RadiansToDegrees(rotateX);
            if (angleX > 90 || angleX < -90)
            {
                xs = W - 1;
                xe = -1;
                stepX = -1;
            }

            for (int z = zs; z != ze; z += stepZ)
            {
                PointF? last = null;

                int[] topHtemp = (int[])topH.Clone();
                int[] bottomHtemp = (int[])bottomH.Clone();

                for (int x = xs; x != xe; x += stepX)
                {
                    
                    float dx = (x - W / 2.0f) * pScale;
                    float dy = outBuff[x, z] * (float)0.5;
                    float dz = (z - H / 2.0f) * pScale;

                    Vector3 dV = new Vector3(dx, dy, dz) * 
                        Matrix4x4.CreateScale(scale) * 
                        Matrix4x4.CreateRotationY(rotateY) *
                        Matrix4x4.CreateRotationX(rotateX) * 
                        Matrix4x4.CreateTranslation(translateX, translateY, 0);

                    int sX = centerX + (int)dV.X;
                    int sY = centerY - (int)dV.Y;

                    if (sX < 0 || sX >= pW) continue;

                    if (sY <= topH[sX] && sY >= bottomH[sX])
                    {
                        last = null;
                        continue;
                    }

                    if (last != null)
                    {
                        int x0 = (int)last.Value.X;
                        int y0 = (int)last.Value.Y;
                        int x1 = sX;
                        int y1 = sY;

                        if (Math.Abs(x1 - x0) > 1)
                        {
                            int steps = Math.Abs(x1 - x0);
                            for (int i = 1; i < steps; i++)
                            {
                                int xi = x0 + i * (x1 - x0) / steps;
                                int yi = y0 + i * (y1 - y0) / steps;
                                topHtemp[xi] = Math.Max(topHtemp[xi], yi);
                                bottomHtemp[xi] = Math.Min(bottomHtemp[xi], yi);
                            }
                        }
                        g.DrawLine(Pens.Black, x0, y0, x1, y1);
                        //g.FillRectangle(Brushes.Black, x0, y0, 2, 2);
                    }
                    topHtemp[sX] = Math.Max(topHtemp[sX], sY);
                    bottomHtemp[sX] = Math.Min(bottomHtemp[sX], sY);
                    last = new PointF(sX, sY);
                }
                topH = (int[])topHtemp.Clone();
                bottomH = (int[])bottomHtemp.Clone();
            }
        }

        private float DegreesToRadians(float degrees)
        {
            return (float)(Math.PI / 180.0) * degrees;
        }

        private float RadiansToDegrees(float radians)
        {
            return (float)(180.0 / Math.PI) * radians;
        }

        private void label3_Click(object sender, EventArgs e)
        {
            trackBar2.Value = 0;
        }

        private void label4_Click(object sender, EventArgs e)
        {
            trackBar3.Value = 0;
        }

        private void label2_Click(object sender, EventArgs e)
        {
            trackBar1.Value = 100;
        }

        private void label1_Click(object sender, EventArgs e)
        {
            trackBar1.Value = 100;
            trackBar2.Value = 0;
            trackBar3.Value = 0;
            trackBar4.Value = 0;
            trackBar5.Value = 0;
        }

        private void label5_Click(object sender, EventArgs e)
        {
            trackBar4.Value = 0;
        }

        private void label6_Click(object sender, EventArgs e)
        {
            trackBar5.Value = 0;
        }
    }

    public struct Vector3
    {
        public float X, Y, Z;
        public Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }

        public static Vector3 operator *(Vector3 v, Matrix4x4 m)
        {
            float x = m.M[0, 0] * v.X + m.M[0, 1] * v.Y + m.M[0, 2] * v.Z + m.M[0, 3] * 1;
            float y = m.M[1, 0] * v.X + m.M[1, 1] * v.Y + m.M[1, 2] * v.Z + m.M[1, 3] * 1;
            float z = m.M[2, 0] * v.X + m.M[2, 1] * v.Y + m.M[2, 2] * v.Z + m.M[2, 3] * 1;
            return new Vector3(x, y, z);
        }
    }

    public class Matrix4x4
    {
        public float[,] M = new float[4, 4];

        public Matrix4x4()
        {
            for (int i = 0; i < 4; i++)
                M[i, i] = 1;
        }

        public static Matrix4x4 CreateScale(float s)
        {
            var m = new Matrix4x4();
            m.M[0, 0] = m.M[1, 1] = m.M[2, 2] = s;
            return m;
        }
        public static Matrix4x4 CreateTranslation(float dx, float dy, float dz)
        {
            var m = new Matrix4x4();
            m.M[0, 3] = dx;
            m.M[1, 3] = dy;
            m.M[2, 3] = dz;
            return m;
        }

        public static Matrix4x4 CreateRotationX(float angle)
        {
            var m = new Matrix4x4();
            float c = (float)Math.Cos(angle);
            float s = (float)Math.Sin(angle);
            m.M[1, 1] = c;
            m.M[1, 2] = -s;
            m.M[2, 1] = s;
            m.M[2, 2] = c;
            return m;
        }

        public static Matrix4x4 CreateRotationY(float angle)
        {
            var m = new Matrix4x4();
            float c = (float)Math.Cos(angle);
            float s = (float)Math.Sin(angle);
            m.M[0, 0] = c;
            m.M[0, 2] = s;
            m.M[2, 0] = -s;
            m.M[2, 2] = c;
            return m;
        }
    }
}

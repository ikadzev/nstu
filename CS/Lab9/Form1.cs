using System;
using System.Drawing;
using System.Windows.Forms;

namespace Lab9
{
    public partial class Form1: Form
    {
        private float angleMercury = 0;
        private float angleVenus = 0;
        private float angleEarth = 0;
        private float angleMars = 0;

        public Form1()
        {
            InitializeComponent();
            timer1.Start();
        }

        private void Timer1_Tick(object sender, EventArgs e)
        {
            angleMercury += 4;
            angleVenus += 2;
            angleEarth += 1;
            angleMars += 0.5f;

            pictureBox1.Invalidate();
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            int centerX = this.ClientSize.Width / 2;
            int centerY = this.ClientSize.Height / 2;

            int sunSize = 40;
            g.FillEllipse(Brushes.Yellow, centerX - sunSize / 2, centerY - sunSize / 2, sunSize, sunSize);

            DrawPlanet(g, Brushes.Gray, centerX, centerY, 60, 6, angleMercury);
            DrawPlanet(g, Brushes.Orange, centerX, centerY, 90, 8, angleVenus);
            DrawPlanet(g, Brushes.Blue, centerX, centerY, 130, 10, angleEarth); 
            DrawPlanet(g, Brushes.Red, centerX, centerY, 170, 9, angleMars);
        }

        private void DrawPlanet(Graphics g, Brush brush, int centerX, int centerY, int orbitRadius, int size, float angle)
        {
            double radians = angle * Math.PI / 180;
            int x = centerX + (int)(orbitRadius * Math.Cos(radians)) - size / 2;
            int y = centerY + (int)(orbitRadius * Math.Sin(radians)) - size / 2;

            g.DrawEllipse(Pens.DarkGray, centerX - orbitRadius, centerY - orbitRadius, orbitRadius * 2, orbitRadius * 2);
            g.FillEllipse(brush, x, y, size, size);
        }
    }
}

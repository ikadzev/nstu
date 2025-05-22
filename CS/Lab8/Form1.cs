using System.Drawing;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace Lab8
{
    public partial class Form1: Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            //g.SmoothingMode = SmoothingMode.AntiAlias;

            Pen mypen = new Pen(Color.Red, 2);
            mypen.DashStyle = DashStyle.DashDotDot;

            Rectangle rect = new Rectangle(50, 50, 200, 100);
            g.FillRectangle(Brushes.Blue, rect);

            Rectangle ellipseRect = new Rectangle(300, 50, 200, 100);
            g.DrawEllipse(mypen, ellipseRect);

            Pen pen = new Pen(Color.Green, 5);
            g.DrawLine(pen, new Point(50, 200), new Point(250, 200));

            mypen.DashStyle = DashStyle.Dot;
            Point[] points = { new Point(300, 200), new Point(350, 300), new Point(250, 300) };
            g.DrawPolygon(mypen, points);
        }
    }
}

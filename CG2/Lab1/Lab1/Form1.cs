using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Lab1
{
    public partial class Form1 : Form
    {
        ObjModel model = new ObjModel();
        Matrix4x4 transform = new Matrix4x4();
        float scale = 1.0f;
        float rotateX = 0.0f;
        float rotateY = 0.0f;
        float translateX = 0.0f;
        float translateY = 0.0f;
        float translateZ = 0.0f;

        public Form1()
        {
            InitializeComponent();

            // Настроить TrackBar'ы
            trackBar1.Minimum = 1; trackBar1.Maximum = 200; trackBar1.Value = 100; // Масштаб
            trackBar2.Minimum = -180; trackBar2.Maximum = 180; // Поворот X
            trackBar3.Minimum = -180; trackBar3.Maximum = 180; // Поворот Y
            trackBar4.Minimum = -100; trackBar4.Maximum = 100; // Перемещение X
            trackBar5.Minimum = -100; trackBar5.Maximum = 100; // Перемещение Y
            trackBar6.Minimum = -100; trackBar6.Maximum = 100; // Перемещение Z

            // Подключаем обработчики событий
            trackBar1.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar2.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar3.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar4.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar5.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar6.ValueChanged += (s, e) => { UpdateTransform(); };
            button1.Click += Button1_Click;

            pictureBox1.Paint += PictureBox1_Paint;
            pictureBox1.BackColor = Color.White;
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "OBJ Files (*.obj)|*.obj";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                model = LoadObj(ofd.FileName);
                UpdateTransform();
            }
        }

        private void UpdateTransform()
        {
            scale = trackBar1.Value / 100f;
            rotateX = DegreesToRadians(trackBar2.Value);
            rotateY = DegreesToRadians(trackBar3.Value);
            translateX = trackBar4.Value;
            translateY = trackBar5.Value;
            translateZ = trackBar6.Value;
            label8.Text = transform.M[0, 0].ToString();
            label9.Text = transform.M[0, 1].ToString();
            label11.Text = transform.M[0, 2].ToString();
            label10.Text = transform.M[0, 3].ToString();
            label15.Text = transform.M[1, 0].ToString();
            label14.Text = transform.M[1, 1].ToString();
            label13.Text = transform.M[1, 2].ToString();
            label12.Text = transform.M[1, 3].ToString();
            label23.Text = transform.M[2, 0].ToString();
            label22.Text = transform.M[2, 1].ToString();
            label21.Text = transform.M[2, 2].ToString();
            label20.Text = transform.M[2, 3].ToString();
            label19.Text = transform.M[3, 0].ToString();
            label18.Text = transform.M[3, 1].ToString();
            label17.Text = transform.M[3, 2].ToString();
            label16.Text = transform.M[3, 3].ToString();

            pictureBox1.Invalidate(); // Перерисовать PictureBox
        }

        private Vector3 CenterFig()
        {
            float cX = model.Vertices.Average(v => v.X);
            float cY = model.Vertices.Average(v => v.Y);
            float cZ = model.Vertices.Average(v => v.Z);
            return new Vector3(cX, cY, cZ);
        }

        private void PictureBox1_Paint(object sender, PaintEventArgs e)
        {
            if (model == null || model.Vertices.Count == 0) return;

            Graphics g = e.Graphics;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            int w = pictureBox1.Width;
            int h = pictureBox1.Height;
            Vector3 c = CenterFig();

            transform =
                Matrix4x4.CreateTranslation(-translateX, -translateY, -translateZ) *
                Matrix4x4.CreateScale(scale) *
                Matrix4x4.CreateRotationX(rotateX) *
                Matrix4x4.CreateRotationY(rotateY) *
                Matrix4x4.CreateTranslation(translateX, translateY, translateZ);
                //Matrix4x4.CreateTranslation(c.X, c.Y, c.Z);

            var points = model.Vertices.Select(v =>
            {
                var t = transform.Transform(v);
                return new PointF(t.X * scale + w / 2, -t.Y * scale + h / 2); // Отразить Y
            }).ToList();

            foreach (var face in model.Faces)
            {
                g.DrawLine(Pens.Black, points[face.Item1], points[face.Item2]);
                g.DrawLine(Pens.Black, points[face.Item2], points[face.Item3]);
                g.DrawLine(Pens.Black, points[face.Item3], points[face.Item1]);
            }

            //DrawAxes(g, transform, w, h);
        }
        private void DrawAxes(Graphics g, Matrix4x4 transform, int w, int h)
        {
            float axisLength = 100.0f;

            var origin = transform.Transform(new Vector3(0, 0, 0));
            var xAxis = transform.Transform(new Vector3(axisLength, 0, 0));
            var yAxis = transform.Transform(new Vector3(0, axisLength, 0));
            var zAxis = transform.Transform(new Vector3(0, 0, axisLength));

            PointF pOrigin = new PointF(origin.X + w / 2, -origin.Y + h / 2);
            PointF pX = new PointF(xAxis.X + w / 2, -xAxis.Y + h / 2);
            PointF pY = new PointF(yAxis.X + w / 2, -yAxis.Y + h / 2);
            PointF pZ = new PointF(zAxis.X + w / 2, -zAxis.Y + h / 2);

            using (var redPen = new Pen(Color.Red, 2))
            using (var greenPen = new Pen(Color.Green, 2))
            using (var bluePen = new Pen(Color.Blue, 2))
            {
                g.DrawLine(redPen, pOrigin, pX);   // X - Красная
                g.DrawLine(greenPen, pOrigin, pY); // Y - Зелёная
                g.DrawLine(bluePen, pOrigin, pZ);  // Z - Синяя
            }
        }

        private ObjModel LoadObj(string path)
        {
            var model = new ObjModel();
            foreach (var line in File.ReadAllLines(path))
            {
                if (line.StartsWith("v "))
                {
                    var parts = line.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    float x = float.Parse(parts[1]);
                    float y = float.Parse(parts[2]);
                    float z = float.Parse(parts[3]);
                    model.Vertices.Add(new Vector3(x, y, z));
                }
                else if (line.StartsWith("f "))
                {
                    var parts = line.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    int v1 = int.Parse(parts[1].Split('/')[0]) - 1;
                    int v2 = int.Parse(parts[2].Split('/')[0]) - 1;
                    int v3 = int.Parse(parts[3].Split('/')[0]) - 1;
                    model.Faces.Add((v1, v2, v3));
                }
            }
            return model;
        }

        private float DegreesToRadians(float degrees)
        {
            return (float)(Math.PI / 180.0) * degrees;
        }
    }

    // Модель и математика

    public class ObjModel
    {
        public List<Vector3> Vertices = new List<Vector3>();
        public List<(int, int, int)> Faces = new List<(int, int, int)>();
    }

    public struct Vector3
    {
        public float X, Y, Z;
        public Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }

    }

    public class Matrix4x4
    {
        public float[,] M = new float[4, 4];

        public Matrix4x4()
        {
            for (int i = 0; i < 4; i++)
                M[i, i] = 1;
        }

        public static Matrix4x4 operator *(Matrix4x4 a, Matrix4x4 b)
        {
            var result = new Matrix4x4();
            for (int row = 0; row < 4; row++)
                for (int col = 0; col < 4; col++)
                    for (int k = 0; k < 4; k++)
                        result.M[row, col] += a.M[row, k] * b.M[k, col];
            return result;
        }

        public Vector3 Transform(Vector3 v)
        {
            float x = v.X * M[0, 0] + v.Y * M[0, 1] + v.Z * M[0, 2] + M[0, 3];
            float y = v.X * M[1, 0] + v.Y * M[1, 1] + v.Z * M[1, 2] + M[1, 3];
            float z = v.X * M[2, 0] + v.Y * M[2, 1] + v.Z * M[2, 2] + M[2, 3];
            return new Vector3(x, y, z);
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

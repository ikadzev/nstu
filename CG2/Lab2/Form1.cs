using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace Lab2
{
    public partial class Form1 : Form
    {
        ObjModel model = new ObjModel();
        float scale = 1.0f;
        float rotateX = 0.0f;
        float rotateY = 0.0f;
        float rotateZ = 0.0f;
        float translateX = 0.0f;
        float translateY = 0.0f;
        bool invisible = false;
        public Form1()
        {
            InitializeComponent();

            trackBar1.Minimum = 10; trackBar1.Maximum = 300; trackBar1.Value = 100; // Масштаб
            trackBar2.Minimum = -180; trackBar2.Maximum = 180; // Поворот X
            trackBar3.Minimum = -180; trackBar3.Maximum = 180; // Поворот Y
            trackBar7.Minimum = -180; trackBar7.Maximum = 180; // Поворот Y
            trackBar4.Minimum = -100; trackBar4.Maximum = 100; // Перемещение X
            trackBar5.Minimum = -100; trackBar5.Maximum = 100; // Перемещение Y

            trackBar1.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar2.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar3.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar4.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar5.ValueChanged += (s, e) => { UpdateTransform(); };
            trackBar7.ValueChanged += (s, e) => { UpdateTransform(); };
            checkBox1.CheckedChanged += (s, e) => { UpdateTransform(); };
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
            scale = trackBar1.Value / 10f;
            rotateX = DegreesToRadians(trackBar2.Value);
            rotateY = DegreesToRadians(trackBar3.Value);
            rotateZ = DegreesToRadians(trackBar7.Value);
            translateX = trackBar4.Value;
            translateY = trackBar5.Value;
            invisible = checkBox1.Checked;

            pictureBox1.Invalidate();
        }

        private Vector3 CenterFig()
        {
            float cX = model.Vertices.Average(v => v.X);
            float cY = model.Vertices.Average(v => v.Y);
            float cZ = model.Vertices.Average(v => v.Z);
            return new Vector3(cX, cY, cZ);
        }

        private Vector3 Normal((int, int, int) face, List<Vector3> points)
        {
            Vector3 v1 = points[face.Item1];
            Vector3 v2 = points[face.Item2];
            Vector3 v3 = points[face.Item3];

            Vector3 u = new Vector3(v2.X - v1.X, v2.Y - v1.Y, v2.Z - v1.Z);
            Vector3 v = new Vector3(v3.X - v1.X, v3.Y - v1.Y, v3.Z - v1.Z);

            float nx = u.Y * v.Z - u.Z * v.Y;
            float ny = u.Z * v.X - u.X * v.Z;
            float nz = u.X * v.Y - u.Y * v.X;

            float length = (float)Math.Sqrt(nx * nx + ny * ny + nz * nz);
            if (length > 0)
            {
                nx /= length;
                ny /= length;
                nz /= length;
            }

            return new Vector3(nx, ny, nz);
        }

        private void PictureBox1_Paint(object sender, PaintEventArgs e)
        {
            if (model == null || model.Vertices.Count == 0) return;

            Graphics g = e.Graphics;
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

            int w = pictureBox1.Width;
            int h = pictureBox1.Height;
            Vector3 c = CenterFig();

            var transform = model.Vertices.Select(v =>
            {
                var t = v *
                    Matrix4x4.CreateTranslation(-c.X, -c.Y, -c.Z) *
                    Matrix4x4.CreateScale(scale) *
                    Matrix4x4.CreateRotationX(rotateX) *
                    Matrix4x4.CreateRotationY(rotateY) *
                    Matrix4x4.CreateRotationZ(rotateZ) *
                    Matrix4x4.CreateTranslation(translateX, translateY, 0) *
                    Matrix4x4.CreateTranslation(c.X, c.Y, c.Z);
                return t;
            }).ToList();
            var points = transform.Select(v => new PointF(v.X + w / 2, -v.Y + h / 2)).ToList();

            foreach (var face in model.Faces)
            {
                var view = new Vector3(0, 0, -1);
                if ((Normal(face, transform).Z * view.Z > 0) | !invisible)
                {
                    g.DrawLine(Pens.Black, points[face.Item1], points[face.Item2]);
                    g.DrawLine(Pens.Black, points[face.Item2], points[face.Item3]);
                    g.DrawLine(Pens.Black, points[face.Item3], points[face.Item1]);
                }
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

        private void label5_Click(object sender, EventArgs e)
        {
            trackBar4.Value = 0;
        }

        private void label6_Click(object sender, EventArgs e)
        {
            trackBar5.Value = 0;
        }

        private void label3_Click(object sender, EventArgs e)
        {
            trackBar2.Value = 0;
        }

        private void label4_Click(object sender, EventArgs e)
        {
            trackBar3.Value = 0;
        }

        private void label8_Click(object sender, EventArgs e)
        {
            trackBar7.Value = 0;
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
            trackBar7.Value = 0;
        }
    }

    public class ObjModel
    {
        public List<Vector3> Vertices = new List<Vector3>();
        public List<(int, int, int)> Faces = new List<(int, int, int)>();
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

        public static Matrix4x4 operator *(Matrix4x4 a, Matrix4x4 b)
        {
            var result = new Matrix4x4();
            for (int row = 0; row < 4; row++)
                for (int col = 0; col < 4; col++)
                    for (int k = 0; k < 4; k++)
                        result.M[row, col] += a.M[row, k] * b.M[k, col];
            return result;
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
        public static Matrix4x4 CreateRotationZ(float angle)
        {
            var m = new Matrix4x4();
            float c = (float)Math.Cos(angle);
            float s = (float)Math.Sin(angle);
            m.M[0, 0] = c;
            m.M[0, 1] = -s;
            m.M[1, 0] = s;
            m.M[1, 1] = c;
            return m;
        }
    }
}

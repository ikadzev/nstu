using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace CAGT1
{
    public partial class Form1 : Form
    {
        private GLControl glControl;
        ObjModel model = new ObjModel();
        float scale = 1.0f;
        float rotateX = 0.0f;
        float rotateY = 0.0f;
        float rotateZ = 0.0f;
        float translateX = 0.0f;
        float translateY = 0.0f;

        private Bitmap loadedImage;
        private List<Dot> dots = new List<Dot>();
        private Dot selectedDot = null;
        private const int DotRadius = 4;
        //private Size canvasSize = new Size(600, 600);

        public Form1()
        {
            InitializeComponent();
            InitializeGLControl();
            elementsDefault();
        }

        private void InitializeGLControl()
        {
            glControl = new GLControl(new GraphicsMode(32, 24, 0, 4));
            glControl.Location = new Point(292, 12);
            glControl.Name = "glControl";
            glControl.Size = new Size(600, 600);
            glControl.VSync = true;
            glControl.Paint += GLControl_Paint;
            glControl.Resize += GLControl_Resize;

            this.Controls.Add(glControl);
        }

        private void GLControl_Resize(object sender, EventArgs e)
        {
            if (glControl == null || glControl.ClientSize.Height == 0)
                return;

            SetupViewport();
        }

        private void SetupViewport()
        {
            GL.Viewport(0, 0, glControl.ClientSize.Width, glControl.ClientSize.Height);

            float aspectRatio = (float)glControl.Width / glControl.Height;
            Matrix4 perspective = Matrix4.CreatePerspectiveFieldOfView(
                MathHelper.PiOver4, aspectRatio, 0.1f, 100.0f);
            GL.MatrixMode(MatrixMode.Projection);
            GL.LoadIdentity();
            GL.LoadMatrix(ref perspective);
            GL.Enable(EnableCap.DepthTest);
            GL.Enable(EnableCap.CullFace);
            GL.CullFace(CullFaceMode.Back);
        }

        private void GLControl_Paint(object sender, PaintEventArgs e)
        {
            if (model.Vertices.Count == 0) return;
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);

            GL.MatrixMode(MatrixMode.Modelview);
            Matrix4 modelview = Matrix4.LookAt(
                new Vector3(0, 0, 5),  // Позиция камеры
                Vector3.Zero,             // Точка, на которую смотрим
                Vector3.UnitY);           // Вектор "вверх"
            GL.LoadMatrix(ref modelview);

            Vector3 cent = CenterFig();
            // Применяем преобразования
            GL.Translate(-cent.X, -cent.Y, -cent.Z); // Центрируем модель
            GL.Scale(scale, scale, scale);
            GL.Rotate(rotateX, 1.0f, 0.0f, 0.0f);
            GL.Rotate(rotateY, 0.0f, 1.0f, 0.0f);
            GL.Rotate(rotateZ, 0.0f, 0.0f, 1.0f);
            GL.Translate(cent.X, cent.Y, cent.Z);
            GL.Translate(translateX, translateY, 0);

            // Отрисовка модели
            Draw_Figure();

            glControl.SwapBuffers();
        }
        private Vector3 CenterFig()
        {
            float cX = model.Vertices.Average(v => v.X);
            float cY = model.Vertices.Average(v => v.Y);
            float cZ = model.Vertices.Average(v => v.Z);
            return new Vector3(cX, cY, cZ);
        }

        private void Draw_Figure()
        {
            if (model == null || model.Vertices.Count == 0) return;
            GL.Begin(PrimitiveType.Lines);
            GL.Color3(Color.BlueViolet);
            GL.LineWidth(0.1f);
            foreach (var face in model.Faces)
            {
                var v1 = model.Vertices[face.Item1];
                var v2 = model.Vertices[face.Item2];
                var v3 = model.Vertices[face.Item3];
                GL.Vertex3(v1.X, v1.Y, v1.Z);
                GL.Vertex3(v2.X, v2.Y, v2.Z);
                GL.Vertex3(v3.X, v3.Y, v3.Z);
                GL.Vertex3(v1.X, v1.Y, v1.Z);
            }
            GL.End();
        }

        private void elementsDefault()
        {
            trackBarScale.Minimum = 1; trackBarScale.Maximum = 200; trackBarScale.Value = 100;
            trackBarRotateX.Minimum = -180; trackBarRotateX.Maximum = 180;
            trackBarRotateY.Minimum = -180; trackBarRotateY.Maximum = 180;
            trackBarRotateZ.Minimum = -180; trackBarRotateZ.Maximum = 180;
            trackBarMoveX.Minimum = -100; trackBarMoveX.Maximum = 100;
            trackBarMoveY.Minimum = -100; trackBarMoveY.Maximum = 100;

            trackBarDotHeight.Minimum = 0; trackBarDotHeight.Maximum = 100; trackBarDotHeight.Value = 0;
            trackBarDotHeight.ValueChanged += TrackBarDotHeight_ValueChanged;
            pictureBoxIMG.Paint += pictireBoxIMG_Paint;
            pictureBoxIMG.MouseClick += pictireBoxIMG_MouseDown;
            buttonLoadIMG.Click += buttonLoadIMG_Click;
            buttonBuildOBJ.Click += ButtonBuildOBJ_Click;


            trackBarScale.ValueChanged += (s, e) => { updateTransform(); };
            trackBarRotateX.ValueChanged += (s, e) => { updateTransform(); };
            trackBarRotateY.ValueChanged += (s, e) => { updateTransform(); };
            trackBarMoveX.ValueChanged += (s, e) => { updateTransform(); };
            trackBarMoveY.ValueChanged += (s, e) => { updateTransform(); };
            trackBarRotateZ.ValueChanged += (s, e) => { updateTransform(); };
            buttonLoad.Click += buttonLoadClick;
            labelRotateX.Click += (s, e) => { trackBarRotateX.Value = 0; };
            labelRotateY.Click += (s, e) => { trackBarRotateY.Value = 0; };
            labelRotateZ.Click += (s, e) => { trackBarRotateZ.Value = 0; };
            labelMoveX.Click += (s, e) => { trackBarMoveX.Value = 0; };
            labelMoveY.Click += (s, e) => { trackBarMoveY.Value = 0; };
            labelScale.Click += (s, e) => { trackBarScale.Value = 100; };
            labelFile.Click += (s, e) =>
            {
                trackBarScale.Value = 100;
                trackBarRotateX.Value = 0;
                trackBarRotateY.Value = 0;
                trackBarMoveX.Value = 0;
                trackBarMoveY.Value = 0;
                trackBarRotateZ.Value = 0;
            };
        }

        private void TrackBarDotHeight_ValueChanged(object sender, EventArgs e)
        {
            if (selectedDot != null)
            {
                selectedDot.Height = trackBarDotHeight.Value;
                pictureBoxIMG.Invalidate();
            }
        }

        private void buttonLoadIMG_Click(object sender, EventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Filter = "Image files (*.BMP, *.JPG, *.PNG, *.ICO)| *.bmp; *.jpg; *.png; *.ico;";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                Bitmap original = new Bitmap(dialog.FileName);
                int size = Math.Min(original.Width, original.Height);
                Rectangle cropRect = new Rectangle((original.Width - size) / 2, (original.Height - size) / 2, size, size);
                loadedImage = new Bitmap(size, size);
                using (Graphics g = Graphics.FromImage(loadedImage))
                    g.DrawImage(original, new Rectangle(0, 0, size, size), cropRect, GraphicsUnit.Pixel);

                Bitmap resized = new Bitmap(loadedImage, new Size(pictureBoxIMG.Width, pictureBoxIMG.Height));
                loadedImage.Dispose();
                loadedImage = resized;
                dots.Clear();
                selectedDot = null;
                pictureBoxIMG.Invalidate();
            }
        }

        private void pictireBoxIMG_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            if (loadedImage != null)
                g.DrawImage(loadedImage, 0, 0, pictureBoxIMG.Width, pictureBoxIMG.Height);

            DrawDelaunayTriangles(g);

            foreach (var dot in dots)
            {
                Brush b = dot == selectedDot ? Brushes.Red : Brushes.Blue;
                g.FillEllipse(b, dot.Position.X - DotRadius, dot.Position.Y - DotRadius, DotRadius * 2, DotRadius * 2);
            }
        }

        private void pictireBoxIMG_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                dots.Add(new Dot { Position = e.Location, Height = 0 });
                selectedDot = dots.FirstOrDefault(d => IsNear(e.Location, d.Position));
                labelDotHeight.Enabled = true;
                trackBarDotHeight.Enabled = true;
                trackBarDotHeight.Value = selectedDot.Height;
            }
            else if (e.Button == MouseButtons.Right)
            {
                var target = dots.FirstOrDefault(d => IsNear(e.Location, d.Position));
                if (target != null) dots.Remove(target);
            }
            else if (e.Button == MouseButtons.Middle)
            {
                selectedDot = dots.FirstOrDefault(d => IsNear(e.Location, d.Position));
                labelDotHeight.Enabled = false;
                trackBarDotHeight.Enabled = false;
                if (selectedDot != null)
                {
                    labelDotHeight.Enabled = true;
                    trackBarDotHeight.Enabled = true;
                    trackBarDotHeight.Value = selectedDot.Height;
                }
            }
            pictureBoxIMG.Invalidate();
        }

        private void DrawDelaunayTriangles(Graphics g)
        {
            if (dots.Count < 3) { buttonBuildOBJ.Enabled = false; return; }
            buttonBuildOBJ.Enabled = true;

            var triangles = new List<Triangle>();

            for (int i = 0; i < dots.Count; i++)
            {
                for (int j = i + 1; j < dots.Count; j++)
                {
                    for (int k = j + 1; k < dots.Count; k++)
                    {
                        var a = dots[i].Position;
                        var b = dots[j].Position;
                        var c = dots[k].Position;

                        if (IsDelaunayTriangle(a, b, c, dots.Select(d => d.Position).ToList()))
                        {
                            g.DrawLine(Pens.Green, a, b);
                            g.DrawLine(Pens.Green, b, c);
                            g.DrawLine(Pens.Green, c, a);
                        }
                    }
                }
            }
        }

        private bool IsDelaunayTriangle(Point a, Point b, Point c, List<Point> points)
        {
            float ax = a.X, ay = a.Y;
            float bx = b.X, by = b.Y;
            float cx = c.X, cy = c.Y;

            float A = bx - ax;
            float B = by - ay;
            float C = cx - ax;
            float D = cy - ay;

            float E = A * (ax + bx) + B * (ay + by);
            float F = C * (ax + cx) + D * (ay + cy);
            float G = 2 * (A * (cy - by) - B * (cx - bx));

            if (Math.Abs(G) < 1e-6) return false; // Точки лежат на одной прямой

            float cxCirc = (D * E - B * F) / G;
            float cyCirc = (A * F - C * E) / G;
            float radiusSq = (ax - cxCirc) * (ax - cxCirc) + (ay - cyCirc) * (ay - cyCirc);

            foreach (var p in points)
            {
                if (p == a || p == b || p == c) continue;
                float dx = p.X - cxCirc;
                float dy = p.Y - cyCirc;
                if ((dx * dx + dy * dy) < radiusSq)
                    return false;
            }
            return true;
        }

        private bool IsNear(Point p1, Point p2)
        {
            return Math.Sqrt(Math.Pow(p1.X - p2.X, 2) + Math.Pow(p1.Y - p2.Y, 2)) <= DotRadius * 2;
        }

        private void ButtonBuildOBJ_Click(object sender, EventArgs e)
        {
            model.Vertices.Clear();
            model.Faces.Clear();

            Dictionary<Point, int> pointToIndex = new Dictionary<Point, int>();
            for (int i = 0; i < dots.Count; i++)
            {
                var d = dots[i];
                Vector3 v = new Vector3(d.Position.X, d.Position.Y, d.Height);
                model.Vertices.Add(v);
                pointToIndex[d.Position] = i;
            }

            for (int i = 0; i < dots.Count; i++)
            {
                for (int j = i + 1; j < dots.Count; j++)
                {
                    for (int k = j + 1; k < dots.Count; k++)
                    {
                        var a = dots[i].Position;
                        var b = dots[j].Position;
                        var c = dots[k].Position;

                        if (IsDelaunayTriangle(a, b, c, dots.Select(d => d.Position).ToList()))
                        {
                            model.Faces.Add((pointToIndex[a], pointToIndex[b], pointToIndex[c]));
                        }
                    }
                }
            }

            MessageBox.Show($"OBJ создан: {model.Vertices.Count} вершин, {model.Faces.Count} граней.", "Готово");
            glControl.Invalidate();
        }

        private void buttonLoadClick(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "OBJ Files (*.obj)|*.obj";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                model = loadOBJ(ofd.FileName);
                updateTransform();
                glControl.Invalidate();
            }
        }

        private ObjModel loadOBJ(string path)
        {
            var model = new ObjModel();
            foreach (var line in File.ReadAllLines(path))
            {
                if (line.StartsWith("v "))
                {
                    var parts = line.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
                    float x = float.Parse(parts[1].Replace('.', ','));
                    float y = float.Parse(parts[2].Replace('.', ','));
                    float z = float.Parse(parts[3].Replace('.', ','));
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

        private void updateTransform()
        {
            scale = trackBarScale.Value / 100f;
            rotateX = trackBarRotateX.Value;
            rotateY = trackBarRotateY.Value;
            rotateZ = trackBarRotateZ.Value;
            translateX = trackBarMoveX.Value;
            translateY = trackBarMoveY.Value;

            glControl.Invalidate();
        }
    }

    public class ObjModel
    {
        public List<Vector3> Vertices = new List<Vector3>();
        public List<(int, int, int)> Faces = new List<(int, int, int)>();
    }
    public class Dot
    {
        public Point Position { get; set; }
        public int Height { get; set; }
    }

    public class Triangle
    {
        public Point A, B, C;
        public Triangle(Point a, Point b, Point c)
        {
            A = a;
            B = b;
            C = c;
        }
    }
}

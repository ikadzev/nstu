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

        public Form1()
        {
            InitializeComponent();
            InitializeGLControl();
            elementsDefault();
        }

        private Vector3 CenterFig()
        {
            float cX = model.Vertices.Average(v => v.X);
            float cY = model.Vertices.Average(v => v.Y);
            float cZ = model.Vertices.Average(v => v.Z);
            return new Vector3(cX, cY, cZ);
        }

        private void InitializeGLControl()
        {
            glControl = new GLControl(new GraphicsMode(32, 24, 0, 4));
            glControl.Location = new Point(20, 13);
            glControl.Name = "glControl";
            glControl.Size = new Size(536, 557);
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
            GL.LoadMatrix(ref perspective);
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
}

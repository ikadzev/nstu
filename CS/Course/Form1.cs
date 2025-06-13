using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace Course
{
    public partial class Form1 : Form
    {
        private Rectangle selectedRegion;
        private Process ffmpegProcess;
        private int scrnCnt = 0;
        private int cptrCnt = 0;
        private int fps = 30;
        private int crf = 25;
        private bool toggle = false;
        private bool recording = false;
        private Keys screenshotKey = Keys.F9;
        private Keys recordKey = Keys.F10;
        private bool waitingForScreenshotKey = false;
        private bool waitingForRecordKey = false;
        private string saveDirectory = "./"; // Default save directory

        public Form1()
        {
            InitializeComponent();
            button1.Text = $"{screenshotKey}";
            button2.Text = $"{recordKey}";
            textBox1.Text = $"{fps}";
            textBox2.Text = $"{crf}";
        }

        private void lockButtons()
        {
            label1.Enabled = false;
            label3.Enabled = false;
            label4.Enabled = false;
            label5.Enabled = false;
            checkBox1.Enabled = false;
            button1.Enabled = false;
            button2.Enabled = false;
            textBox1.Enabled = false;
            textBox2.Enabled = false;
            button3.Enabled = false;
        }

        private void unlockButtons()
        {
            label1.Enabled = true;
            label3.Enabled = true;
            label4.Enabled = true;
            label5.Enabled = true;
            checkBox1.Enabled = true;
            button1.Enabled = true;
            button2.Enabled = true;
            textBox1.Enabled = true;
            textBox2.Enabled = true;
            button3.Enabled = true;
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (waitingForScreenshotKey)
            {
                waitingForScreenshotKey = false;
                if (keyData == recordKey)
                {
                    MessageBox.Show("Нельзя использовать одну клавишу для двух функций!");
                }
                else
                {
                    screenshotKey = keyData;
                }
                button1.Text = $"{screenshotKey}";
                return true;
            }
            else if (waitingForRecordKey)
            {
                waitingForRecordKey = false;
                if (keyData == screenshotKey)
                {
                    MessageBox.Show("Нельзя использовать одну клавишу для двух функций!");
                }
                else
                {
                    recordKey = keyData;
                }
                button2.Text = $"{recordKey}";
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        private void checkBoxUpdate(object sender, EventArgs e)
        {
            toggle = checkBox1.Checked;
        }

        private void buttonScreenshotKey_Click(object sender, EventArgs e)
        {
            waitingForScreenshotKey = true;
            button1.Text = "Клавиша...";
            this.Focus();
        }

        private void buttonRecordKey_Click(object sender, EventArgs e)
        {
            waitingForRecordKey = true;
            button2.Text = "Клавиша...";
            this.Focus();
        }

        private void buttonSaveDirectory_Click(object sender, EventArgs e)
        {
            using (var dialog = new FolderBrowserDialog())
            {
                dialog.Description = "Выберите папку для сохранения скриншотов и записей";
                if (dialog.ShowDialog() == DialogResult.OK)
                {
                    saveDirectory = dialog.SelectedPath;
                    MessageBox.Show($"Папка сохранения установлена: {saveDirectory}");
                }
            }
        }

        private void UpdateFPS(object sender, EventArgs e)
        {
            if (int.TryParse(textBox1.Text, out int newFps) && newFps > 0)
            {
                fps = newFps;
            }
            else
            {
                MessageBox.Show("Введите корректное значение FPS (целое число больше 0).");
                return;
            }
            if (int.TryParse(textBox2.Text, out int newCrf) && newCrf > 0)
            {
                crf = newCrf;
            }
            else
            {
                MessageBox.Show("Введите корректное значение CRF (целое число больше 0).");
                return;
            }
        }

        private void MainForm_KeyDown(object sender, KeyEventArgs e)
        {
            if (toggle)
            {
                if (e.KeyCode == screenshotKey)
                {
                    using (var selector = new RegionSelector())
                    {
                        if (selector.ShowDialog() == DialogResult.OK)
                        {
                            selectedRegion = selector.SelectedRegion;
                            var screenshot = CaptureRegion(selectedRegion);
                            screenshot.Save($"{saveDirectory}/screenshot{scrnCnt}.png");
                            MessageBox.Show($"Скриншот сохранён как screenshot{scrnCnt++}.png");
                        }
                    }
                }
                else if (e.KeyCode == recordKey && !recording)
                {
                    using (var selector = new RegionSelector())
                    {
                        if (selector.ShowDialog() == DialogResult.OK)
                        {
                            selectedRegion = selector.SelectedRegion;
                            recording = true;
                            StartRecording(selectedRegion, fps, crf);
                            lockButtons();
                        }
                    }
                }
                else if (e.KeyCode == recordKey && recording)
                {
                    recording = false;
                    StopRecording();
                    MessageBox.Show("Запись завершена.");
                    unlockButtons();
                }
            }
        }

        private Bitmap CaptureRegion(Rectangle region)
        {
            Bitmap bmp = new Bitmap(region.Width, region.Height);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                g.CopyFromScreen(region.Location, Point.Empty, region.Size);
            }
            return bmp;
        }

        private void StartRecording(Rectangle region, int fps, int crf)
        {
            string args = $"-f gdigrab " +
                          $"-framerate {fps} " +
                          $"-offset_x {region.X} -offset_y {region.Y} " +
                          $"-video_size {region.Width}x{region.Height} " +
                          $"-i desktop " +
                          $"-vcodec libx264 " +
                          $" -crf {crf} " +
                          $"-preset ultrafast " + 
                          $"{saveDirectory}/capture{cptrCnt++}.mp4";

            ffmpegProcess = new Process 
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = "ffmpeg.exe",
                    Arguments = args,
                    RedirectStandardInput = true,
                    RedirectStandardError = true,
                    UseShellExecute = false,
                    CreateNoWindow = true
                }
            };
            ffmpegProcess.ErrorDataReceived += (s, e) =>
            {
                if (textBox3.InvokeRequired)
                {
                    textBox3.Invoke(new Action(() => textBox3.AppendText(e.Data + Environment.NewLine)));
                }
                else
                {
                    textBox3.AppendText(e.Data + Environment.NewLine);
                }
            };

            if (!ffmpegProcess.Start()) 
            {
                MessageBox.Show("Произошла ошибка");
                recording = false;
            }
            ffmpegProcess.StandardInput.WriteLine("y");
            ffmpegProcess.BeginErrorReadLine();
        }

        private void StopRecording()
        {
            if (ffmpegProcess != null && !ffmpegProcess.HasExited)
            {
                ffmpegProcess.StandardInput.WriteLine("q");
                ffmpegProcess.CloseMainWindow();
                ffmpegProcess.Dispose();
            }
        }
    }
}

public class RegionSelector : Form
{
    public Rectangle SelectedRegion { get; private set; }
    private Point startPoint;
    private Point endPoint;
    private bool selecting = false;

    public RegionSelector()
    {
        this.FormBorderStyle = FormBorderStyle.None;
        this.BackColor = Color.LightGray;
        this.Opacity = 0.5;
        this.WindowState = FormWindowState.Maximized;
        this.DoubleBuffered = true;
        this.Cursor = Cursors.Cross;
        this.TopMost = true;

        this.MouseDown += (s, e) => { startPoint = e.Location; selecting = true; };
        this.MouseMove += (s, e) => { if (selecting) { endPoint = e.Location; Invalidate(); } };
        this.MouseUp += (s, e) =>
        {
            selecting = false;
            SelectedRegion = GetRectangle(startPoint, endPoint);
            DialogResult = DialogResult.OK;
            Close();
        };
    }

    protected override void OnPaint(PaintEventArgs e)
    {
        if (selecting)
        {
            var rect = GetRectangle(startPoint, endPoint);
            e.Graphics.DrawRectangle(Pens.Red, rect);
        }
    }

    private Rectangle GetRectangle(Point p1, Point p2)
    {
        int x = Math.Min(p1.X, p2.X);
        int y = Math.Min(p1.Y, p2.Y);
        int width = Math.Abs(p1.X - p2.X);
        int height = Math.Abs(p1.Y - p2.Y);
        return new Rectangle(x, y, width, height);
    }
}


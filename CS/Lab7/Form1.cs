using System;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace Lab7
{
    public partial class Form1: Form
    {
        private double XMin = -5;
        private double XMax = 5;
        private double Step = 0.1;

        public Form1()
        {
            InitializeComponent();
            chart1.ChartAreas[0].AxisX.Minimum = -5;
            chart1.ChartAreas[0].AxisX.Maximum = 5;
            chart1.ChartAreas[0].AxisX.Title = "x";
            chart1.ChartAreas[0].AxisY.Title = "h(x)";

            chart1.Series.Clear();
            chart1.Series.Add("h(x)");
            chart1.Series["h(x)"].ChartType = SeriesChartType.Line;
            chart1.Series["h(x)"].BorderWidth = 2;

            CalcFunction();
        }

        private void Update(object sender, EventArgs e)
        {
            CalcFunction();
        }

        private void CalcFunction()
        {
            //double y = trackBar1.Value;
            //double z = trackBar2.Value;
            double y = 2;
            double z = 1;
            chart1.Series["h(x)"].Points.Clear();

            for (double x = XMin; x <= XMax; x += Step)
            {
                if (x * Math.Abs(y - Math.Tan(z)) == -1) continue;
                double result = Calculate(x, y, z);
                chart1.Series["h(x)"].Points.AddXY(x, result);
            }
        }
        
        public static double Calculate(double x, double y, double z)
        {
            double delta = Math.Abs(y - x);
            double numerator = (Math.Pow(x, y + 1) + Math.Exp(y - 1)) * (1 + delta);
            double denominator = 1 + x * Math.Abs(y - Math.Tan(z));

            double result = (numerator / denominator) + (Math.Pow(delta, 2) / 2) - (Math.Pow(delta, 3) / 3);

            return result;
        }
    }
}

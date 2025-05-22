using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Lab4
{
    public partial class Form1: Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!int.TryParse(textBox1.Text, out int rows) || !int.TryParse(textBox2.Text, out int cols))
            {
                MessageBox.Show("Введите корректные размеры таблицы.");
                return;
            }

            double[,] matrix = GenerateRandomMatrix(rows, cols);
            DisplayMatrix(matrix);

            double[][] steppedMatrix = TransformToSteppedMatrix(matrix);
            DisplayJaggedMatrix(steppedMatrix);
        }

        private double[,] GenerateRandomMatrix(int rows, int cols)
        {
            Random rand = new Random();
            double[,] matrix = new double[rows, cols];

            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    matrix[i, j] = Math.Round(rand.NextDouble() * 100, 2);

            return matrix;
        }

        private void DisplayMatrix(double[,] matrix)
        {
            dataGridView1.Columns.Clear();
            dataGridView1.Rows.Clear();

            int rows = matrix.GetLength(0);
            int cols = matrix.GetLength(1);

            dataGridView1.RowCount = rows;
            dataGridView1.ColumnCount = cols;

            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++) dataGridView1.Rows[i].Cells[j].Value = matrix[i, j];
        }

        private double[][] TransformToSteppedMatrix(double[,] matrix)
        {
            int rows = matrix.GetLength(0);
            int cols = matrix.GetLength(1);

            double[][] result = new double[cols][];
            for (int j = 0; j < cols; j++)
            {
                double sum = 0;
                for (int i = 0; i < rows; i++)
                    sum += matrix[i, j];

                double average = sum / rows;

                double[] values = new double[rows];
                int c = 0;

                for (int i = 0; i < rows; i++)
                {
                    if (matrix[i, j] >= average)
                    {
                        values[c] = matrix[i, j];
                        c++;
                    }
                }

                result[j] = values;
            }

            return result;
        }

        private void DisplayJaggedMatrix(double[][] matrix)
        {
            dataGridView2.Columns.Clear();
            dataGridView2.Rows.Clear();

            int cols = matrix.Length;
            int maxRows = 0;
            foreach (var column in matrix)
                if (column.Length > maxRows)
                    maxRows = column.Length;

            dataGridView2.RowCount = maxRows;
            dataGridView2.ColumnCount = cols;

            for (int i = 0; i < maxRows; i++) for (int j = 0; j < cols; j++)
            {
                if (matrix[j][i] != 0)
                    dataGridView2.Rows[i].Cells[j].Value = matrix[j][i];
            }
        }
    }
}

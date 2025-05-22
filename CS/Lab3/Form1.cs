using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab3
{
    public partial class Form1: Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int[] A = new int[30];
            Random rand = new Random();

            listBox1.Items.Clear();
            listBox2.Items.Clear();

            for (int i = 0; i < A.Length; i++)
            {
                A[i] = rand.Next(-100, 101);
                listBox1.Items.Add(A[i]);
            }

            int count = 0;
            int sum = 0;

            foreach (int num in A)
            {
                if (num % 5 == 0 && num % 7 != 0)
                {
                    listBox2.Items.Add(num);
                    count++;
                    sum += num;
                }
            }

            label3.Text = count.ToString();
            label5.Text = sum.ToString();
        }
    }
}

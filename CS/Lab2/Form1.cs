using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab2
{
    public partial class Form1: Form
    {
        static bool IsPalindrome(string str)
        {
            var clear = new string(str.Where(char.IsLetterOrDigit).ToArray()).ToLower();
            return clear.SequenceEqual(clear.Reverse());
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_MouseClick(object sender, MouseEventArgs e)
        {
            //label1.Text = listBox1.SelectedIndex.ToString();
            int selectedInt = listBox1.SelectedIndex;
            if (selectedInt == -1) { return; }
            string selectedItem = (string)listBox1.SelectedItem;
            if (IsPalindrome(selectedItem)) {
                label1.Text = "Выделенная строка - палиндром";
            } else
            {
                label1.Text = "Выделенная строка - не палиндром";
            }
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            label1.Text = "";
        }
    }
}

using System;
using System.Text.RegularExpressions;
using System.Linq;
using System.Windows.Forms;

namespace Lab5
{
    public partial class Form1 : Form
    {
        static bool IsPalindrome(string str)
        {
            //var clear = new string(str.Where(char.IsLetterOrDigit).ToArray()).ToLower();
            //return clear.SequenceEqual(clear.Reverse());
            string cleaned = Regex.Replace(str.ToLower(), "[^a-zа-я0-9]", "");
            string reversed = new string(cleaned.Reverse().ToArray());
            return cleaned == reversed;
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_MouseClick(object sender, EventArgs e)
        {
            int selectedInt = listBox1.SelectedIndex;
            if (selectedInt == -1) { return; }
            string selectedItem = (string)listBox1.SelectedItem;
            if (IsPalindrome(selectedItem))
            {
                label1.Text = "Выделенная строка - палиндром";
            }
            else
            {
                label1.Text = "Выделенная строка - не палиндром";
            }
        }
    }
}

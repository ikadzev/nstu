using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1: Form
    {
        enum Operat
        {
            Mult, Div, Plus, Minus
        }
        double first, second, result;
        Operat oper;
        bool fl = false, perv = false;

        void operation(Operat op)
        {
            if (!string.IsNullOrEmpty(textBox1.Text))
            {
                if (!perv)
                {
                    first = Double.Parse(textBox1.Text);
                    oper = op;
                    textBox1.Text = "";
                    perv = !perv;
                }
                else
                {
                    second = Double.Parse(textBox1.Text);
                    switch (oper)
                    {
                        case Operat.Div: first = (first / second);
                            break;
                        case Operat.Mult: first = (first * second);
                            break;
                        case Operat.Plus: first = (first + second);
                            break;
                        case Operat.Minus: first = (first - second);
                            break;
                    }
                    oper = op;
                    textBox1.Text = "";
                }
            }
        }

        private void equalButtonClick(object sender, MouseEventArgs e)
        {
            if (!string.IsNullOrEmpty(textBox1.Text))
            {
                fl = false;
                second = Double.Parse(textBox1.Text);
                switch (oper)
                {
                    case Operat.Div:
                        result = (first / second);
                        break;
                    case Operat.Mult:
                        result = (first * second);
                        break;
                    case Operat.Plus:
                        result = (first + second);
                        break;
                    case Operat.Minus:
                        result = (first - second);
                        break;
                }
                textBox1.Text = result.ToString();
                perv = !perv;
            }
        }

        private void plusButtonClick(object sender, MouseEventArgs e)
        {
            operation(Operat.Plus);
        }

        private void minusButtonClick(object sender, MouseEventArgs e)
        {
            operation(Operat.Minus);
        }

        private void multButtonClick(object sender, MouseEventArgs e)
        {
            operation(Operat.Mult);
        }

        private void divButtonClick(object sender, MouseEventArgs e)
        {
            operation(Operat.Div);
        }

        private void deleteButtonClick(object sender, MouseEventArgs e)
        {
            if (!string.IsNullOrEmpty(textBox1.Text))
            {
                textBox1.Text = textBox1.Text.Substring(0, textBox1.Text.Length - 1);
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void numberButtonClick(object sender, MouseEventArgs e)
        {
            if (textBox1.Text != result.ToString() || fl)
            {
                fl = true;
                textBox1.Text += (sender as Button).Text;
            }
            else
            {
                textBox1.Text = (sender as Button).Text;
            }
        }
    }
}

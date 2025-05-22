using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab6
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!int.TryParse(textBox8.Text, out int length1) ||
                !int.TryParse(textBox7.Text, out int length2) ||
                !int.TryParse(textBox6.Text, out int length3) ||
                !int.TryParse(textBox5.Text, out int length4) ||
                !int.TryParse(textBox11.Text, out int power)  ||
                !int.TryParse(textBox10.Text, out int sail1)  ||
                !int.TryParse(textBox9.Text, out int sail2)   ||
                !int.TryParse(textBox12.Text, out int gun))
            {
                MessageBox.Show("Введите корректные характеристики");
                return;
            }

            Ship genericShip = new Ship(textBox2.Text, length1);
            Steamship steamship = new Steamship(textBox1.Text, length2, power);
            SailingShip sailboat = new SailingShip(textBox3.Text, length3, sail1);
            Corvette corvette = new Corvette(textBox4.Text, length4, sail2, gun);

            genericShip.Sail();
            steamship.Sail();
            sailboat.Sail();
            corvette.Sail();
        }
    }

    public class Ship
    {
        public string Name { get; set; }
        public double Length { get; set; }
        public Ship(string name, double length)
        {
            Name = name;
            Length = length;
        }
        public virtual void Sail()
        {
            MessageBox.Show($"{Name} длиной {Length} м выходит в море.");
        }
    }

    public class Steamship : Ship
    {
        public double EnginePower { get; set; }
        public Steamship(string name, double length, double enginePower)
            : base(name, length)
        {
            EnginePower = enginePower;
        }
        public override void Sail()
        {
            MessageBox.Show($"{Name} (Пароход) длиной {Length} м движется с помощью парового двигателя ({EnginePower} кВт).");
        }
    }

    public class SailingShip : Ship
    {
        public int SailCount { get; set; }
        public SailingShip(string name, double length, int sailCount)
            : base(name, length)
        {
            SailCount = sailCount;
        }
        public override void Sail()
        {
            MessageBox.Show($"{Name} (Парусник) длиной {Length} м плывёт под парусами ({SailCount} парусов).");
        }
    }

    public class Corvette : SailingShip
    {
        public int GunCount { get; set; }
        public Corvette(string name, double length, int sailCount, int gunCount)
            : base(name, length, sailCount)
        {
            GunCount = gunCount;
        }
        public override void Sail()
        {
            MessageBox.Show($"{Name} (Корвет) длиной {Length} м плывёт под парусами с {GunCount} пушками ({SailCount} парусов).");
        }
    }


}

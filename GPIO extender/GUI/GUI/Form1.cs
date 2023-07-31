using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
namespace GUI
{
    public partial class Form1 : Form
    {
        static private SerialPort myCOM;
        public Form1()
        {
            InitializeComponent();
           
        }
        static private char sendChar='2';

        private void Form1_Load(object sender, EventArgs e)
        {
            
            string[] ports = SerialPort.GetPortNames();
            myCOM = new SerialPort(ports[0], 115200);
            myCOM.Open();
            myCOM.Write(sendChar.ToString());
     
        }
        ~Form1()
        {
            myCOM.Close();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {

        }

   



        private void A1_CheckedChanged(object sender, EventArgs e)
        {
            if (A1.Checked)
            { myCOM.Write('1'.ToString()); }
            else
            { myCOM.Write('q'.ToString()); }
        }

        private void A2_CheckedChanged(object sender, EventArgs e)
        {
            if (A2.Checked)
            { myCOM.Write('2'.ToString()); }
            else
            { myCOM.Write('w'.ToString()); }
        }
        private void A3_CheckedChanged(object sender, EventArgs e)
        {
            if (A3.Checked)
            { myCOM.Write('3'.ToString()); }
            else
            { myCOM.Write('e'.ToString()); }
        }
        private void A4_CheckedChanged(object sender, EventArgs e)
        {
            if (A4.Checked)
            { myCOM.Write('4'.ToString()); }
            else
            { myCOM.Write('r'.ToString()); }
        }
        private void A5_CheckedChanged(object sender, EventArgs e)
        {
            if (A5.Checked)
            { myCOM.Write('5'.ToString()); }
            else
            { myCOM.Write('t'.ToString()); }
        }
        private void A6_CheckedChanged(object sender, EventArgs e)
        {
            if (A6.Checked)
            { myCOM.Write('6'.ToString()); }
            else
            { myCOM.Write('y'.ToString()); }
        }
        private void A7_CheckedChanged(object sender, EventArgs e)
        {
            if (A7.Checked)
            { myCOM.Write('7'.ToString()); }
            else
            { myCOM.Write('u'.ToString()); }
        }
        private void A8_CheckedChanged(object sender, EventArgs e)
        {
            if (A8.Checked)
            { myCOM.Write('8'.ToString()); }
            else
            { myCOM.Write('i'.ToString()); }
        }
    }
}

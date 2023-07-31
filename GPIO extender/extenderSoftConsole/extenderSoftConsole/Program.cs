using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

namespace extenderSoftConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            char sendChar;
            string[] ports = SerialPort.GetPortNames();
            if(args.Count()==0)
            {
                sendChar = '1';
            }
            else
            {
                sendChar = args[0][0];

            }
            SerialPort myCOM = new SerialPort(ports[0], 115200);
            myCOM.Open();
            myCOM.Write(sendChar.ToString());
            myCOM.Close();
        }
    }
}

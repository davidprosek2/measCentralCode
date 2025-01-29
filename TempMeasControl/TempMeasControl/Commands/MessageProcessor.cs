using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace TempMeasControl.Commands
{
    internal class MessageProcessor
    {

        SerialPort _serialPort;
        Form _parent;
        UpdatetemperatureDataDelagate _showDataMethod;

        private Queue<string> Commands = new Queue<string>();

        public delegate void UpdatetemperatureDataDelagate(string data);

        public MessageProcessor(Form parent, UpdatetemperatureDataDelagate showDataMethod)
        {
            _serialPort = new SerialPort();
            InitializeSerialPort();
            _parent = parent;
            _showDataMethod = showDataMethod;
        }




        private void InitializeSerialPort()
        {
            _serialPort = new SerialPort();
            _serialPort.DataReceived += SerialPort_DataReceived;
            _serialPort.BaudRate = 115200;
            _serialPort.Parity = Parity.None;
            _serialPort.StopBits = StopBits.One;
            _serialPort.DataBits = 8;
        }


        public void InitCom(string portName)
        {
            if (!_serialPort.IsOpen)
            {
                _serialPort.PortName = portName; // Replace with your COM port
                _serialPort.Open();
            }
        }

        public void CloseCom()
        {
            if (_serialPort.IsOpen)
            {
                _serialPort.Close();
            }
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string data = _serialPort.ReadLine();
            ProcessMessage(data);
        }



        public bool ProcessMessage(string message)
        {
            char prefix = message.FirstOrDefault();
            switch (prefix)
            {
                case 'P':
                    return false;
                default:
                    _parent.Invoke(new MethodInvoker(delegate { _showDataMethod(message); }));
                    return true;
            }

        }


        public void Ping()
        {

            if (_serialPort.IsOpen)
            {
                if (_serialPort.BaseStream.CanWrite)
                {

                    _serialPort.WriteLine("P");
                    Commands.Enqueue("P");
                }
            }
        }

    }
}

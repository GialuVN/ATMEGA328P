using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Threading;
using System.IO.Ports;
using System.Timers;
using RS485_protocol;
namespace RS485
{

    delegate void SetTextCallback(string text);

    public partial class Form1 : Form
    {

        System.Timers.Timer timer;
        SerialPort serialport;

        RS485_protocol.RS485 rs485;

        byte[] data;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            rs485 = new RS485_protocol.RS485("COM5", 250000);
            rs485.Myaddr = 100;
            rs485.RS485_listen();
            rs485.RS485_start();
            

            Thread thread = new Thread(new ThreadStart(threat_run));
            thread.Start();
          
        }


        void threat_run()
        {
            while (true)
            {

                if (rs485.RS485_isNew() == true && (rs485.RS485_isData() == true))
                {
                    SetText(rs485.Buff[0].ToString());

                    rs485.RS485_listen();
                }


            }

        }

        private void SetText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.textBox1.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.textBox1.Text += text+",";
            }
        }
   
        private void button1_Click(object sender, EventArgs e)
        {
            rs485.RS485_start();
        }
        
        private void button2_Click(object sender, EventArgs e)
        {
            rs485.RS485_stop();
           
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            byte[] dt = new byte[10];
            dt[0] = Convert.ToByte(textBox2.Text);
            dt[1] = Convert.ToByte(textBox2.Text);

            rs485.RS485_send_data(100, dt, 2);

        }
    }
}

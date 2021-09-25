using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading;
using System.IO.Ports;
using System.Drawing;
using System.Windows.Forms;
using System.Timers;
namespace RS485_protocol
{
    class RS485
    {

        private string comport;
        public string Comport
        {
            get { return comport; }
            set { comport = value; }
        }
        
        private int baudrate;
        public int Baudrate
        {
            get { return baudrate; }
            set { baudrate = value; }
        }

        private int datalen;
        public int Datalen
        {
            get { return datalen; }
           private set { datalen = value; }
        }

        private int myaddr;
        public int Myaddr
        {
            get { return myaddr; }
            set { myaddr = value; }
        }


        private byte[] buff;
        public byte[] Buff
        {
            get { return buff; }
           private set { buff = value; }
        }

        
     //   private System.Timers.Timer timer;

        private Thread thread;
        private SerialPort serialport;
        private byte[] temp;
        private bool isData = false;
        private bool isError = false;
        private byte stage;
        private byte counter;

        public RS485(string _comport, int _baudrate)
        {
            comport = _comport;
            baudrate = _baudrate;
            serialport = new SerialPort(_comport, _baudrate);
            serialport.Parity = Parity.None;
            serialport.StopBits = StopBits.Two;
            serialport.DataBits = 8;
            buff = new byte[256];
            temp = new byte[256];
        }


        
public bool RS485_send_data(byte _addr,byte[] _data_in,byte _data_len)// return _ERR _data_len>250
{
    byte[] _temp= new byte[_data_len+5];
    if (serialport.IsOpen == false) return false;
	if (_data_len>250) return true;
	_temp[0] = 0xAA;
	_temp[1] = _addr;
	_temp[2] = _data_len;
    for (int i = 0; i < _data_len; i++) _temp[3 + i] = _data_in[i];
    _temp[_data_len + 3] = CheckSum(_temp, _data_len + 3);
    _temp[_data_len + 4] = 0x55;
    RS485_send_zero(2);
    while (serialport.BytesToWrite > 0) {};
    serialport.Write(_temp, 0, _temp.Length);
	return false;
}



public void RS485_send_respond(byte _cmd,byte _val)
{
    byte[] _temp = new byte[5];

    if (serialport.IsOpen == false) return;
  
    _temp[0] = 0xCC;
    _temp[1] = _cmd;
    _temp[2] = _val;
    _temp[3] = CheckSum(_temp, 3);
    _temp[4] = 0x55;
    RS485_send_zero(2);
    while (serialport.BytesToWrite > 0) {};
    serialport.Write(_temp, 0, _temp.Length);

}



private void RS485_send_zero(byte n_zero)
{
    byte[] _temp = new byte[n_zero];
    if (serialport.IsOpen == false) return;
    while (serialport.BytesToWrite > 0) {};
    serialport.Write(_temp, 0,n_zero);
}



    public void RS485_start()
    {
        if (serialport.IsOpen == false) serialport.Open();
        if (thread != null) return;
        thread = new Thread(new ThreadStart(rs485_run));
        thread.Start();
    }

    public void RS485_stop()
    {
        thread = null;
        if (serialport.IsOpen == true) serialport.Close();

    }

    private  byte _crc_ibutton_update(byte crc, byte data) //
    {
        crc ^= data;
        for (byte i = 0; i < 8; i++)
        {
            if ((crc & 0x01) != 0)
            {
                crc >>= 1;
                crc ^= 0x8C;
            }
            else crc >>= 1;
        }
        return crc;
    }



      private  byte CheckSum(byte[] _data_in, int _data_len)	// CRC CHECK , 255 if error
        {
            byte crc;
            crc = 0;
            for (int i = 0; i < _data_len; i++)
                crc = _crc_ibutton_update(crc, _data_in[i]);
            return crc;
        }



          public void RS485_listen()
          {
              this.isError = false;
              this.isData = false;
              this.stage = 0;
              this.datalen = 0;
          }


      public bool RS485_isNew()
      {
          if ((this.stage == 255) && (this.datalen != 0)) return true;
          else return false;
      }

      public bool RS485_isError()
      {
          return isError;
      }

      public bool RS485_isData()
      {
          return isData;
      }

      private void rs485_run()
      {

          while (true)
          {
              if (serialport.IsOpen == false) break;
              if (serialport.BytesToRead!=0) rs485_decode((byte)serialport.ReadByte());
          
          }
      }

     private  void rs485_decode(byte _data_in)
      {
          switch (this.stage)
          {
              case 0:
                  if (_data_in == 0xAA) this.stage = 1;
                  else if (_data_in == 0xCC) this.stage = 4;
                  else this.stage = 0;
                  break;
              case 1:
                  if (_data_in == (byte)this.myaddr) this.stage = 2;
                  else this.stage = 0;
                  break;
              case 2:
                  if (_data_in != 0)
                  {
                      this.temp[0] = 0xAA;
                      this.temp[1] = (byte)this.myaddr;
                      this.temp[2] = _data_in;
                      this.counter = 0;
                      this.stage = 3;
                  }
                  else this.stage = 0;
                  break;
              case 3:
                  this.temp[this.counter + 3] = _data_in;
                  this.counter++;
                  if (this.counter >= (this.temp[2] + 2))
                  {
                      if (this.temp[this.temp[2] + 3] != CheckSum(this.temp, (int)this.temp[2] + 3)) this.isError = true;
                      for (int i = 0; i < this.temp[2]; i++) this.buff[i] = this.temp[i + 3];
                      this.isData = true;
                      this.datalen = this.temp[2];
                      this.stage = 255;
                  }
                  break;
              case 4:
                  this.temp[0] = 0xCC;
                  this.temp[1] = _data_in;
                  this.counter = 0;
                  this.stage = 5;
                  break;
              case 5:
                  this.temp[this.counter + 2] = _data_in;
                  this.counter++;
                  if (this.counter >= 2)
                  {
                      if (this.temp[3] != CheckSum(this.temp, 3)) this.isError = true;

                      for (int i = 0; i < 2; i++) this.buff[i] = this.temp[i + 1];
                      this.isData = false;
                      this.datalen = 2;
                      this.stage = 255;
                  }
                  break;
              default:
                  break;
          }

      }


    }
}

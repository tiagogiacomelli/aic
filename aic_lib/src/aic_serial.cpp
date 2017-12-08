#include "aic_serial.h"

#define INVALID_FILE_DESCRIPTOR -1


aic_serial::aic_serial()
  : aic_serial_ok(false), serial_fd(INVALID_FILE_DESCRIPTOR) {}

aic_serial::~aic_serial()
{
  if(aic_serial_ok == true)
  {
    if(tcdrain(this->serial_fd))
    {
      perror("serial control error");
//      return -errno;
    }

    if(close(this->serial_fd))
    {
      perror("serial release error");
//      return -errno;
    }
  }
}

bool aic_serial::init(const char *interfaceName, int *error_code)
{
  if((this->serial_fd=open(interfaceName, O_RDWR | O_NOCTTY))==-1)
  {
    perror("Serial connection error");
    *error_code = -errno;
    aic_serial_ok = false;
    return serial_ok();
  }

  if(tcgetattr(this->serial_fd,&this->tty))
  {
    perror("Serial connection error");
    *error_code = -errno;
    aic_serial_ok = false;
    return serial_ok();
  }

  if(cfsetspeed(&this->tty,B115200))
  {
    perror("Serial speed error");
    *error_code = -errno;
    aic_serial_ok = false;
    return serial_ok();
  }

  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;

  tty.c_cflag &= ~CRTSCTS;

  tty.c_cflag |= CREAD | CLOCAL;

  tty.c_iflag &= ~(IXON | IXOFF | IXANY);

  tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

  tty.c_oflag &= ~OPOST;

  tty.c_cc[VMIN] = 8;
  tty.c_cc[VTIME] = 0;


  if (tcsetattr(this->serial_fd,TCSANOW,&this->tty))
  {
    perror("Serial configuration error");
    *error_code = -errno;
    aic_serial_ok = false;
    return serial_ok();
  }

  usleep(50);

  if (tcflush(serial_fd, TCIFLUSH)){
    perror("Serial flush error");
    *error_code = -errno;
    aic_serial_ok = false;
    return serial_ok();
  }
  aic_serial_ok = true;
  return serial_ok();
}

bool aic_serial::send_serial_char(char *data, int *error_code)
{
  if(write(serial_fd,data,1)==-1)
  {
    perror("serial write error");
    *error_code = -errno;
    return false;
  }
  return true;
}

bool aic_serial::get_serial_chars(int cmd, char *buffer, int count, int *error_code)
{
  int n;
  if((n=read(this->serial_fd,buffer,count))==-1)
  {
    perror("serial read error");
    *error_code = -errno;
    return false;
  }

  return true;

}

bool aic_serial::serial_ok()
{
  return aic_serial_ok;
}

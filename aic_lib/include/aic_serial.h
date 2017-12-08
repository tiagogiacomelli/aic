#ifndef AIC_SERIAL_H
#define AIC_SERIAL_H

#include <string>
#include <cstdio>

extern "C"{
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
}

class aic_serial
{
public:
  aic_serial();
  ~aic_serial();
  bool init(const char *interfaceName, int *error_code);
  bool send_serial_char(char *data, int *error_code);
  bool get_serial_chars(int cmd, char *buffer, int count, int *error_code);

private:
  bool serial_ok();
  bool aic_serial_ok;

  int serial_fd;
  struct termios tty;


};

#endif // AIC_SERIAL_H

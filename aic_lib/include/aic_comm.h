#ifndef AIC_COMM_H
#define AIC_COMM_H

#include <string>
#include <cstdio>
#include <cstdarg>
#include <iostream>

#include "aic_net.h"
#include "aic_can.h"
#include "aic_serial.h"



enum aic_comm_method_t {
  none = 0,
  rs232 = 1,
  socketcan = 2
};

typedef struct aic_comm_config {
  std::string aic_serial_port;
  int aic_can_id_number;  
  std::string aic_can_iface;
  int aic_comm_device;  
  aic_comm_config() :
    aic_serial_port("/dev/ttyUSB0"),
    aic_can_id_number(0),
    aic_can_iface("can0"),
    aic_comm_device(none) {}
} aic_comm_config_t;


class aic_comm
{
public:
  aic_comm(aic_comm_config_t aic_connection_parameters);
  ~aic_comm();
  int send_command(int command,...);
  int get_status(int status,...);
  bool status_ok();
private:
  aic_comm_config_t connection_parameters;

  int init();
  int stop();

  int error_code;

  bool aic_comm_status;  

  aic_can * can_bus;
  aic_serial * serial_bus;
};

#endif // AIC_COMM_H

#include "aic_comm.h"


aic_comm::aic_comm(aic_comm_config_t aic_connection_parameters)  
  : error_code(0), connection_parameters(aic_connection_parameters)
{
  if(this->connection_parameters.aic_comm_device == rs232) serial_bus = new aic_serial();
  else can_bus = new aic_can();

  this->init();
}

aic_comm::~aic_comm()
{
  this->stop();
}

int aic_comm::send_command(int command, ...)
{
  struct can_frame msg_tx;
  if (this->connection_parameters.aic_comm_device == socketcan)
  {
    msg_tx.can_id = can_bus->get_id_number() | (command << 5);
    msg_tx.can_dlc = 0;
    for (int k = 0; k < 8; k++) msg_tx.data[k] = 0;
  }

  int err_code = 0;

  if (this->connection_parameters.aic_comm_device == rs232){
    serial_bus->send_serial_char((char*)(&command),&error_code);
  }

  if (command == AIC_MOTOR_ACT) {
    va_list ap;
    va_start(ap,command);
    double volt=va_arg(ap,double);
    va_end(ap);

    for (int i = 7; i >=0; i--){
      if (connection_parameters.aic_comm_device == rs232){
        serial_bus->send_serial_char((char*) &volt + i,&error_code);

      } else ((unsigned char *)(&msg_tx.data))[7-i] = ((unsigned char *)(&volt))[i];
    }
  }

  if (this->connection_parameters.aic_comm_device == socketcan){
    if (command == AIC_MOTOR_ACT){
      msg_tx.can_dlc = 8;
      can_bus->send_can_msg(msg_tx,command,false, err_code);
    } else if (command == AIC_STATUS){
      can_bus->send_can_msg(msg_tx,command,true, err_code);
    }else {
      can_bus->send_can_msg(msg_tx,command,false, err_code);
    }
  }

  return 0;
}

int aic_comm::get_status(int command, ...)
{
  va_list ap;
  va_start(ap,command);
  double *encoder=va_arg(ap, double *);
  int *index=va_arg(ap,int *);

  *encoder=0.0;
  *index=0;
  int n = 0;

  char buffer[256];

  can_frame msg_rx;

  if(this->connection_parameters.aic_comm_device == rs232){    
    serial_bus->get_serial_chars(command, buffer, 8,&error_code);
  } else {

    bool rtr;
    bool extended;
    bool error;

    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 300;

    can_bus->get_can_msg(msg_rx, &extended, &rtr, &error, this->error_code, timeout);
  }  

  int i = 0;
  int idx = 0; float enc = 0;
  if (this->connection_parameters.aic_comm_device == rs232){
      for(i=0;i<4;i++) ((char *)(&enc))[i]=((char *)(&buffer))[3-i];
      for(i=0;i<4;i++) ((char *)(&idx))[i]=((char *)(&buffer))[7-i];
  } else {
    for(int i=0;i < 4;i++) ((unsigned char *)(&enc))[i]=msg_rx.data[3-i];
    for(int i=0;i < 4;i++) ((unsigned char *)(&idx))[i]=msg_rx.data[7-i];
  }
  *encoder = enc;
//  *encoder = enc;
  *index = idx;
  va_end(ap);

  return command;
}

int aic_comm::init()
{
  if (this->connection_parameters.aic_comm_device == rs232)
    return aic_comm_status = serial_bus->init(connection_parameters.aic_serial_port.c_str(),
                                      &error_code);
   else return aic_comm_status = can_bus->init(connection_parameters.aic_can_iface.c_str(),
                                    connection_parameters.aic_can_id_number,
                                    error_code);
}

int aic_comm::stop()
{
  if (this->connection_parameters.aic_comm_device == rs232) serial_bus->~aic_serial();
  else can_bus->~aic_can();
  return aic_comm_status = false;
}

bool aic_comm::status_ok()
{
  return aic_comm_status;
}

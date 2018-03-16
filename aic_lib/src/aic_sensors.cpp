#include "aic_sensors.h"

aic_sensors::aic_sensors(aic_comm *param_connection)
  : connection(param_connection) {}

aic_sensors::~aic_sensors(void){
}

aic_displacement_msg_t aic_sensors::read_displacement(void)
{
  double displacement = 0;
  int index = 0;
  aic_displacement_msg_t status;

  this->connection->send_command(AIC_STATUS);
  this->connection->get_status(AIC_STATUS, &displacement, &index);
  status.joint_displacement = displacement;
  status.index = index;
  return status;
}

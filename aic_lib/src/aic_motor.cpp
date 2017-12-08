#include "aic_motor.h"


aic_motor::aic_motor(aic_comm *param_connection)
  : connection(param_connection) {}

aic_motor::~aic_motor()
{
}

void aic_motor::on()
{
  this->connection->send_command(AIC_MOTOR_ON);
}

void aic_motor::off()
{
this->connection->send_command(AIC_MOTOR_OFF);
}

double aic_motor::set_motor_voltage(double voltage)
{
  this->connection->send_command(AIC_MOTOR_ACT,voltage);
  return voltage;
}

double aic_motor::set_controller_reference(double reference)
{
  this->connection->send_command(AIC_MOTOR_REF, reference);
  return reference;
}



#include "aic_motor.h"


aic_motor::aic_motor(aic_comm *param_connection)
  : connection(param_connection) {}

aic_motor::~aic_motor(void)
{
}

void aic_motor::on(void)
{
  this->connection->send_command(AIC_MOTOR_ON);
}

void aic_motor::off(void)
{
this->connection->send_command(AIC_MOTOR_OFF);
}

double aic_motor::set_motor_voltage(const double &voltage)
{
  this->connection->send_command(AIC_MOTOR_ACT,voltage);
  return voltage;
}

double aic_motor::set_controller_reference(const double &reference)
{
  this->connection->send_command(AIC_MOTOR_REF, reference);
  return reference;
}



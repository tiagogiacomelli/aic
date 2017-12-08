#include "aic_brake.h"

aic_brake::aic_brake(aic_comm *param_connection)
  : connection(param_connection) {}

aic_brake::~aic_brake(){}

void aic_brake::apply()
{
  this->connection->send_command(AIC_BRAKE_APPLY);
}

void aic_brake::release()
{
  this->connection->send_command(AIC_BRAKE_RELEASE);
}

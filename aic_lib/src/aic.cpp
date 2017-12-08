#include "aic.h"

aic::aic(aic_comm_config_t aic_connection_parameters)
  : connection_parameters(aic_connection_parameters), aic_ok(false)
{
  this->reset();
}

aic::~aic()
{
  if (this->connection->status_ok() == true) this->shutdown();
}

bool aic::shutdown(){
  this->motor->off();
  this->brake->apply();
  return this->release();
}

bool aic::release(){
  this->motor->~aic_motor();
  this->sensors->~aic_sensors();
  this->brake->~aic_brake();
  this->connection->~aic_comm();
  return this->aic_ok = false;
}

void aic::reset()
{
  if (aic_ok == true){
    this->connection->send_command(AIC_RESET);
    usleep(100);
    this->release();
  }
  this->connect();
}

bool aic::connect()
{
  aic_ok = false;
  usleep(10000);
  this->connection = new aic_comm(this->connection_parameters);
  if (this->connection->status_ok() == true){
    this->brake = new aic_brake(this->connection);
    this->sensors = new aic_sensors(this->connection);
    this->motor = new aic_motor(this->connection);
    this->motor->on();
    this->brake->release();
    return aic_ok = true;
  } else return aic_ok = false;
}

void aic::set_controller_reference(double reference)
{  
  this->motor->set_controller_reference(reference);
}

void aic::set_motor_voltage(double voltage)
{  
  this->motor->set_motor_voltage(voltage);
}

void aic::brake_on()
{
  this->brake->apply();
}

void aic::brake_off()
{
  this->brake->release();
}

void aic::ping()
{
  this->connection->send_command(AIC_STATUS);
  this->connection->get_status(AIC_STATUS);
}

aic_displacement_msg_t aic::read_displacement_sensors()
{
  return this->sensors->read_displacement();
}

bool aic::status_ok()
{
  return this->aic_ok;
}


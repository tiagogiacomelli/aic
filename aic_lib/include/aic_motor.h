#ifndef AIC_MOTOR_H
#define AIC_MOTOR_H

#include "aic_comm.h"

class aic_motor
{
public:
  aic_motor(aic_comm * param_connection);
  ~aic_motor();
  void on(void);
  void off(void);
  double set_motor_voltage(double voltage);
  double set_controller_reference(double voltage);

private:
  aic_comm * connection;
};

#endif // AIC_MOTOR_H

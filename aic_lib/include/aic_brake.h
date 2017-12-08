#ifndef AIC_BRAKE_H
#define AIC_BRAKE_H

#include "aic_comm.h"

class aic_brake
{
public:
  aic_brake(aic_comm *param_connection);
  ~aic_brake();
  void apply(void);
  void release(void);
private:
  aic_comm * connection;
};

#endif // AIC_BRAKE_H

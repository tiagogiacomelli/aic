#ifndef AIC_SENSORS_H
#define AIC_SENSORS_H

#include "aic_comm.h"

typedef struct aic_displacement_msg {
  double joint_displacement;
  int32_t index;
  aic_displacement_msg() : joint_displacement(0.0f), index (0){}
} aic_displacement_msg_t;


class aic_sensors
{
public:
  aic_sensors(aic_comm *param_connection);
  ~aic_sensors();
  aic_displacement_msg_t read_displacement(void);
private:
  aic_comm * connection;
};

#endif // aic_sensors_H

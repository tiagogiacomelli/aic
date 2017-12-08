#include "aic.h"

#include <cstdio>
#include <iostream>


int main(int argc, char *argv[])
{
    aic_comm_config_t param;
//    param.aic_can_bus_number = 0;
//    param.aic_can_id_number = 2;
//    param.aic_can_iface = "can0";
//    param.aic_comm_device = socketcan;

    param.aic_comm_device = rs232;
    param.aic_serial_port = "/dev/ttyUSB0";

    aic * board = new aic(param);
    while(board->status_ok() != true);
    if (board->status_ok()){
        board->set_motor_voltage(0);
        while(1){
            aic_displacement_msg dp = board->read_displacement_sensors();
            std::cout << "Encoder: " << dp.joint_displacement << " - Index: " << dp.index << std::endl;
//            sleep(3);
            usleep(1000000);
        }
        board->brake_on();
    }
    board->~aic();

  return 0;
}

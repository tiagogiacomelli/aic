#include "aic.h"

#include <cstdio>
#include <iostream>


int main(int argc, char *argv[])
{
    aic_comm_config_t param;    
    param.aic_can_id_number = 2;
    param.aic_can_iface = "can0";
    param.aic_comm_device = socketcan;

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


//#include "canwrapper.h"

//int main(int argc, char *argv[])
//{
//    int errorCode;
//    CanWrapper * bus = new CanWrapper();
//    std::string param = "can0";

//    int aicid = 2;

//    if(bus->Init(param.c_str(),errorCode)) std::cout << "is initialized\n" << std::endl;
//    else std::cout << "non initialized with error: " << errorCode << "\n" << std::endl;

//    can_frame msg;

//    struct timeval tv;
//    tv.tv_usec = 1000;

//    msg.can_dlc = 2;

//    int msg_id = aicid | (AIC_RESET << 5);
//    msg.can_id = msg_id;
////    bus->SendMsg(msg,false,false,errorCode);

//    msg_id = aicid | (AIC_MOTOR_OFF << 5);
//    msg.can_id = msg_id;
//    bus->SendMsg(msg,false,false,errorCode);

//    /*------------------------------------------------------------*/
//    msg_id = aicid | (AIC_STATUS << 5);
//    msg.can_id = msg_id;
//    bus->SendMsg(msg,false,true,errorCode);

//    bool rtr;
//    bool extended;
//    bool error;

//    can_frame incoming_msg;
//    int ret = bus->GetMsg(incoming_msg, extended, rtr, error, errorCode, tv);
//    if (ret){
//        int cmd = (incoming_msg.can_id & AIC_CMD_MASK) >> 5;
//        int id = (incoming_msg.can_id & AIC_ID_MASK);
//        std::cout << "Error: " << errorCode << " - RTR: " << rtr << " - Ext: " << extended << " - Id: " << id << " - Cmd: " << cmd << " - Dlc: " <<
//                     (unsigned int) incoming_msg.can_dlc << "\n" << std::endl;

//        long index=0;
//        float encoder;

////        for(int i=0;i<4;i++) ((unsigned char *)(&msg))[i]=((unsigned char *)(&encoder))[i];
////        for(int i=4;i<8;i++) ((unsigned char *)(&msg))[i]=((unsigned char *)(&encoder))[i-4]
//        //          for(int i=0;i<4;i++) ((unsigned char *)(&encoder))[i]=((unsigned char *)(&incoming_msg.data))[3-i];
//                  for(int i=0;i < 4;i++) *(((unsigned char *)&encoder)+i)=incoming_msg.data[3-i];
//        //          for(int i=0;i<4;i++) ((unsigned char *)(&index))[i]=((unsigned char *)(&incoming_msg.data))[7-i];
//                  for(int i=0;i < 4;i++) *(((unsigned char *)&index)+i)=incoming_msg.data[7-i];
//          std::cout << "Encoder: " << (double) encoder << " - Index: " << index << std::endl;
//    }
//    /*------------------------------------------------------------*/
//    msg.can_id = aicid;
//    msg_id = aicid | (AIC_MOTOR_ON << 5);
//    msg.can_id = msg_id;
//    bus->SendMsg(msg,false,false,errorCode);

//    msg_id = aicid | (AIC_MOTOR_ACT << 5);
//    double teste, volts = 0.0f;
//    msg.can_dlc = 8;
//    for (int k=0; k<8; k++) {
////        ((unsigned char *)(&msg.data))[7-k] = ((unsigned char *)(&volts))[k];
////        ((unsigned char *)(&teste))[k] = ((unsigned char *)(&msg.data))[7-k];

//        ((unsigned char *)(&msg.data))[7-k] = ((unsigned char *)(&volts))[k];
////        ((unsigned char *)(&teste))[k] = ((unsigned char *)(&msg.data))[k];

//    }
//    msg.can_id = msg_id;
//    bus->SendMsg(msg,false,false,errorCode);


//    sleep(2);
//    msg_id = aicid | (AIC_MOTOR_ACT << 5);
//    msg.can_dlc = 8;
//    volts = 0.0f;
//    for (int k=0; k<8; k++) {
////        ((unsigned char *)(&msg.data))[7-k] = ((unsigned char *)(&volts))[k];
////        ((unsigned char *)(&teste))[k] = ((unsigned char *)(&msg.data))[7-k];

//        ((unsigned char *)(&msg.data))[7-k] = ((unsigned char *)(&volts))[k];
////        ((unsigned char *)(&teste))[k] = ((unsigned char *)(&msg.data))[k];

//    }
//    msg.can_id = msg_id;
//    bus->SendMsg(msg,false,false,errorCode);

//    msg_id = aicid | (AIC_STATUS << 5);
//    msg.can_id = msg_id;
//    bus->SendMsg(msg,false,true,errorCode);

//    incoming_msg;
//    ret = bus->GetMsg(incoming_msg, extended, rtr, error, errorCode, tv);
//        if (ret){
//            int cmd = (incoming_msg.can_id & AIC_CMD_MASK) >> 5;
//            int id = (incoming_msg.can_id & AIC_ID_MASK);
//            std::cout << "Error: " << errorCode << " - RTR: " << rtr << " - Ext: " << extended << " - Id: " << id << " - Cmd: " << cmd << " - Dlc: " <<
//                         (unsigned int) incoming_msg.can_dlc << "\n" << std::endl;

//            long index=0;
//            float encoder;
//    //        for(int i=0;i<4;i++) ((unsigned char *)(&msg))[i]=((unsigned char *)(&encoder))[i];
//    //        for(int i=4;i<8;i++) ((unsigned char *)(&msg))[i]=((unsigned char *)(&encoder))[i-4]
//            //          for(int i=0;i<4;i++) ((unsigned char *)(&encoder))[i]=((unsigned char *)(&incoming_msg.data))[3-i];
//                      for(int i=0;i < 4;i++) *(((unsigned char *)&encoder)+i)=incoming_msg.data[3-i];
//            //          for(int i=0;i<4;i++) ((unsigned char *)(&index))[i]=((unsigned char *)(&incoming_msg.data))[7-i];
//                      for(int i=0;i < 4;i++) *(((unsigned char *)&index)+i)=incoming_msg.data[7-i];
//              std::cout << "Encoder: " << (double) encoder << " - Index: " << index << std::endl;
//        }

//  return 0;
//}


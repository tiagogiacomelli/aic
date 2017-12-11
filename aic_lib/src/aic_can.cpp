#include "aic_can.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/select.h>
#include <net/if.h>

#include <linux/can/raw.h>
#include <linux/can/error.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>

#include <unistd.h>
#include <string.h>
#include <iostream>


#define INVALID_SOCK -1

aic_can::aic_can()
    :  aic_can_ok(false), socket_fd (INVALID_SOCK) {}

aic_can::~aic_can()
{
    if(aic_can_ok)
    {
        // We don't want to read or write anything more
        shutdown(socket_fd, SHUT_RDWR);

        close(socket_fd);

        socket_fd = INVALID_SOCK;

        aic_can_ok = false;
    }
}

bool aic_can::init(const char *interfaceName, const int card_number, int &error_code)
{
    enable_error_messages();
    aic_card_number = card_number;

    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_filter rfilter;

    rfilter.can_id = card_number;
    rfilter.can_mask = 0x1F;


    int ret;

    error_code = 0;

    socket_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    strcpy(ifr.ifr_name, interfaceName);
    ret = ioctl(socket_fd, SIOCGIFINDEX, &ifr);
    if(ret)
    {
        error_code = errno;

        return false;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    ret = bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr));

    setsockopt(socket_fd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));


    if(ret)
    {
        error_code = errno;

        close(socket_fd);
        socket_fd = INVALID_SOCK;

        return false;
    }

    aic_can_ok = true;

    return aic_can_ok;
}

bool aic_can::send_can_msg(struct can_frame msg, int command, bool rtr, int &error_code){

  // only standard socketcan frame

    int res;

    error_code = 0;

    if(!aic_can_ok) return false;


    if(rtr){
        msg.can_id |=  CAN_RTR_FLAG;
    }

    res = write(socket_fd, &msg, sizeof(struct can_frame));

    if(res < 0)
    {
        error_code = errno;
        return false;
    }
    return true;
}

//bool aic_can::get_can_msg(struct can_frame &frame, bool &extended, bool &rtr, bool &error, int *error_code, struct timeval timeout)
bool aic_can::get_can_msg(struct can_frame &frame, bool *extended, bool *rtr, bool *error, int &error_code,
                          struct timeval timeout)
{
//  std::cout << "Reading CAN MSG\n" << std::endl;
  int NumOfBytes;
    int ret;
    fd_set rfds;

    error_code = 0;

    if(!aic_can_ok)
    {
        return false;
    }

    // Set up a file descriptor set only containing one socket
    FD_ZERO(&rfds);
    FD_SET(socket_fd, &rfds);

    // Use select to be able to use a timeout
    ret = select(socket_fd+1, &rfds, NULL, NULL, &timeout);

    if(ret < 0)
    {
        error_code = errno;

        return false;
    }

    if(ret > 0)
    {
        NumOfBytes = read(socket_fd, &frame, sizeof(frame));        

        if(NumOfBytes < 0)
        {
            error_code = errno;

            return false;
        }

        if(NumOfBytes == sizeof(frame))
        {

            *error = frame.can_id & CAN_ERR_FLAG;

            *extended = frame.can_id & CAN_EFF_FLAG;

            *rtr = frame.can_id & CAN_RTR_FLAG;

            if(error)
            {
                frame.can_id  &= CAN_ERR_MASK;
            }

            if(extended)
            {
                frame.can_id  &= CAN_EFF_MASK;
            }
            else
            {
                frame.can_id &= CAN_SFF_MASK;
            }


            int aicid = (frame.can_id) & AIC_ID_MASK;

            if(aicid != this-> aic_card_number){
              std::cout << "ERROR IN AIC_CARD_NUMBER!\n" << std::endl;
                return false;
            }

            return true;
        }
    }

    return false;
}

bool aic_can::set_receive_buffer_size(int size)
{
    int ret;
    int rcvbuf_size = size;

    ret = setsockopt(socket_fd, SOL_SOCKET, SO_RCVBUF, &rcvbuf_size, sizeof(rcvbuf_size));

    if(ret < 0)
    {
        return false;
    }

    return true;
}

void aic_can::enable_error_messages()
{
    int ret;

    can_err_mask_t err_mask = ( CAN_ERR_TX_TIMEOUT | CAN_ERR_BUSOFF );

    ret = setsockopt(socket_fd, SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &err_mask, sizeof(err_mask));
}

bool aic_can::can_ok()
{
    return this->can_ok();
}

int aic_can::get_id_number(){
  return aic_card_number;
}


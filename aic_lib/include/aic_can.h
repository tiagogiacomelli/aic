#ifndef AIC_CAN_H
#define AIC_CAN_H

#include <string>
#include <cstdio>
#include <linux/can.h>

/*
 *
 * ------------------------------------------------------------------------- *
 */

const static int AIC_ID_MASK=0x01f;	///< AIC CAN identification mask

const static int AIC_CMD_MASK=0x7e0;	///< AIC CAN command mask

/*
 *
 * ------------------------------------------------------------------------- *
 */

class aic_can
{
public:  
  aic_can();
  ~aic_can();
  bool init(const char *interfaceName, const int card_number, int &error_code);
  bool send_can_msg(struct can_frame msg, int command, bool rtr, int &error_code);
  bool get_can_msg(struct can_frame &frame, bool *extended, bool *rtr, bool *error, int &error_code,
                   struct timeval timeout);
  bool set_receive_buffer_size(int size);
  void enable_error_messages(void);
  int get_id_number(void);
private:
  bool can_ok();
  bool aic_can_ok;
  int aic_card_number;

  int socket_fd;
};

#endif // AIC_CAN_H

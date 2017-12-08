#ifndef AIC_NET_H
#define AIC_NET_H

extern "C" {

/******************************************************************************

        Actuator Interface Card
        Host Interface Library
    Copyright (C) 2003-2008 Walter Fetter Lages <w.fetter@ieee.org>
            2008	Diego Caberlon Santini <diegos@ece.ufrgs.br>

      This program is free software; you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation; either version 2 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program; if not, write to the Free Software
      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

      You can also obtain a copy of the GNU General Public License
      at <http://www.gnu.org/licenses>.

  *******************************************************************************/

/** AIC command codes
  */

#include <stdlib.h>

typedef enum AIC_COMMAND {
  AIC_INVALID=        0x00,	///< Invalid command
  AIC_RESET=          0x01,	///< Reset AIC
  AIC_MOTOR_OFF=      0x02,	///< Turns motor off
  AIC_BRAKE_APPLY=    0x03,	///< Aplies brake
  AIC_MOTOR_ACT=      0x10,	///< Actuates motor with given voltage
  AIC_MOTOR_REF=      0x15,	///< Sets the reference for the motor PID
  AIC_STATUS=         0x20,	///< Status identification
  AIC_BRAKE_RELEASE= 	0x30,	///< Releases brake
  AIC_MOTOR_ON=       0x31,	///< Turns motor on
  AIC_USER0=          0x3b,	///< User defined command 0
  AIC_USER1=          0x3c,	///< User defined command 1
  AIC_USER2=          0x3d,	///< User defined command 2
  AIC_USER3=          0x3e,	///< User defined command 3
  AIC_NOP=            0x3f	///< No operation
} aic_command_t;

/** AIC status codes */
typedef enum AIC_STATUS {
  AIC_INDEX_ON=		0x01,	///< Index on
} aic_status_t;

}

#endif // AIC_NET_H

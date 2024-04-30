// Copyright 2023 j-w-e (@j-w-e)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MASTER_RIGHT

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U  //if problem check 'U'

/* #define OLED_DC_PIN GP3 */ 
/* #define OLED_CS_PIN GP2 */
#define I2C1_SCL_PIN        GP3
#define I2C1_SDA_PIN        GP2
#define I2C_DRIVER I2CD0


#define ONESHOT_TAP_TOGGLE 2  /* Tap this many times to hold key until pressed again */
#define ONESHOT_TIMEOUT 2000  /* Time in ms before OS releases */

#define TAPPING_TERM 200  /* max allowed time in between taps to call TD key */


#define ENCODERS_PAD_A { GP9 }
#define ENCODERS_PAD_B { GP8 }

#define ENCODERS_PAD_A_RIGHT { GP8 }
#define ENCODERS_PAD_B_RIGHT { GP9 }


#define ENCODER_MAP_KEY_DELAY 20


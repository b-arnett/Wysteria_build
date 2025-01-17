// Copyright 2023 j-w-e (@j-w-e)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MASTER_LEFT

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#ifdef RGB_MATRIX_ENABLE
#    define SPLIT_TRANSPORT_MIRROR
#    define RGB_MATRIX_LED_COUNT 36
#    define RGB_MATRIX_SPLIT { 18, 18 }
/* #    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50 */
#    define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_CENTER { 112, 64 }
#endif

/* #define OLED_DC_PIN GP3 */
/* #define OLED_CS_PIN GP2 */
#define I2C1_SCL_PIN        GP3
#define I2C1_SDA_PIN        GP2
/* #define I2C_DRIVER I2CD0 */

#define ENCODER_A_PINS { GP9 }
#define ENCODER_B_PINS { GP8 }
#define ENCODER_A_PINS_RIGHT { GP8 }
#define ENCODER_B_PINS_RIGHT { GP9 }

#define ENCODER_RESOLUTIONS { 2 }
#define ENCODER_MAP_KEY_DELAY 10
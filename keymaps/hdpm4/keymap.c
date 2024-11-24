// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#define ENCODER_MAP_ENABLE

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_UP, KC_DOWN),        ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  },
    [1] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU),      ENCODER_CCW_CW(KC_PGDN, KC_PGUP)  },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),      ENCODER_CCW_CW(KC_BRIU, KC_BRID)  },
    
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   [0] = LAYOUT_wyst_custom(
        KC_F, KC_P, KC_D, KC_L, KC_X,                                                           KC_SCLN, KC_U, KC_O, KC_Y, KC_Z,
        MT(MOD_LSFT, KC_S), MT(MOD_LCTL, KC_N), KC_T, KC_H, KC_K,                                 KC_DOT, KC_A, KC_E, MT(MOD_LCTL, KC_I), MT(MOD_RSFT, KC_C),        
        MT(MOD_LGUI, KC_V), MT(MOD_LALT, KC_B), KC_G, KC_L, KC_J,                       KC_MINUS, KC_COMMA, KC_QUOTE, MT(MOD_LALT, KC_SLASH), MT(MOD_RGUI, KC_Q),

                                            KC_BSPC, KC_R, TG(1), KC_MPLY,                  KC_MPLY, KC_ENT, KC_SPACE, TG(2)
    ),  

    //  NUMPAD LAYER
    [1] = LAYOUT_wyst_custom(
        KC_ESC, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS,                   KC_PMNS, KC_7, KC_8, KC_9, KC_PSLS,
        KC_TAB, KC_LEFT, KC_DOWN, KC_RIGHT, KC_BSLS,                KC_PPLS, KC_4, KC_5, KC_6, KC_PAST,
        KC_CAPS, KC_TRNS, KC_GRAVE, KC_MPRV, KC_MNXT,               KC_PEQL, KC_1, KC_2, KC_3, KC_DOT,

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                         KC_TRNS, KC_BSPC, KC_TRNS, KC_0  
        ), 
    //  Symbol layer
    [2] = LAYOUT_wyst_custom(
        KC_QUOTE, LSFT(KC_COMMA), LSFT(KC_DOT), LSFT(KC_QUOTE), KC_DOT,     LSFT(KC_7), LSFT(KC_SCLN), KC_LBRC, KC_RBRC, LSFT(KC_5),
        LSFT(KC_1), KC_PMNS, KC_PPLS, KC_PEQL, LSFT(KC_3),                    LSFT(KC_BSLS), KC_SCLN, LSFT(KC_9), LSFT(KC_0), LSFT(KC_SLASH), 
        LSFT(KC_6), KC_PSLS, KC_PAST, KC_BSLS, KC_TRNS,                       KC_GRAVE, LSFT(KC_4), LSFT(KC_LBRC), LSFT(KC_RBRC), LSFT(KC_2),

        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_MCTL, KC_TRNS, KC_TRNS
    )
};


void oneshot_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    println("Oneshot mods SHIFT");
  }
  if (mods & MOD_MASK_CTRL) {
    println("Oneshot mods CTRL");
  }
  if (mods & MOD_MASK_ALT) {
    println("Oneshot mods ALT");
  }
  if (mods & MOD_MASK_GUI) {
    println("Oneshot mods GUI");
  }
  if (!mods) {
    println("Oneshot mods off");
  }
}
void oneshot_locked_mods_changed_user(uint8_t mods) {
  if (mods & MOD_MASK_SHIFT) {
    println("Oneshot locked mods SHIFT");
  }
  if (mods & MOD_MASK_CTRL) {
    println("Oneshot locked mods CTRL");
  }
  if (mods & MOD_MASK_ALT) {
    println("Oneshot locked mods ALT");
  }
  if (mods & MOD_MASK_GUI) {
    println("Oneshot locked mods GUI");
  }
  if (!mods) {
    println("Oneshot locked mods off");
  }
}

void oneshot_layer_changed_user(uint8_t layer) {
  if (layer == 1) {
    println("Oneshot layer 1 on");
  }
  if (!layer) {
    println("Oneshot layer off");
  }
}



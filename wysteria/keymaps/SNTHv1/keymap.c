// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H



/* TAPDANCE */
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,   // double tap and hold
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    SCLN_C,
    SPC_ENT,
    BCSP_WD
};


td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void scln_finished (tap_dance_state_t *state, void *user_data);
void scln_reset (tap_dance_state_t *state, void *user_data);
void spc_finished (tap_dance_state_t *state, void *user_data);
void spc_reset (tap_dance_state_t *state, void *user_data);
void bcsp_finished (tap_dance_state_t *state, void *user_data);
void bcsp_reset (tap_dance_state_t *state, void *user_data);


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(KC_BRIU, KC_BRID)  },
    [1] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT),      ENCODER_CCW_CW(KC_DOWN, KC_UP)  },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),           ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [0] = LAYOUT_wyst_custom(
        KC_X, KC_P, KC_D, KC_M, KC_Q,     KC_EQUAL, KC_Y, KC_O, KC_U, KC_COMMA,
        KC_S, KC_N, KC_T, KC_H, KC_V,     KC_G, KC_C, KC_A, KC_E, KC_I,
        KC_F, KC_B, KC_K, KC_L, KC_J,     KC_Z, KC_W, KC_QUOTE, KC_SLASH, KC_DOT,

        TD(SCLN_C), KC_R, KC_MINUS, KC_MPLY,       OSM(MOD_RCTL), TD(BCSP_WD)/*Ltgl*/, TD(SPC_ENT), OSM(MOD_RGUI) // ONESHOT TO L1,  double t to move to layer
    ),
    //  Encoders @ KC_MUTE

    //  NUMPAD LAYER
    [1] = LAYOUT_wyst_custom(
        KC_Q, KC_W, KC_UP, KC_R, KC_T,              KC_PMNS, KC_7, KC_8, KC_9, KC_PSLS,
        KC_S, KC_LEFT, KC_DOWN, KC_RIGHT, KC_V,     KC_PPLS, KC_4, KC_5, KC_6, KC_PAST,
        KC_F, KC_B, KC_K, KC_L, KC_J,               KC_0, KC_1, KC_2, KC_3, KC_PEQL,

        KC_TRNS, KC_R, KC_BACKSPACE, KC_TRNS,       KC_SPC, KC_TRNS, KC_PMNS, KC_TRNS  // ONESHOT TO L1,  double t to move to layer
        ),
  
    [2] = LAYOUT_wyst_custom(
        KC_Q, KC_W, KC_E, KC_R, KC_T,     KC_Y, KC_U, KC_I, KC_O, KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G,     KC_H, KC_J, KC_K, KC_L, KC_SCLN,
        KC_Z, KC_X, KC_C, KC_V, KC_B,     KC_M, KC_N, KC_COMM, KC_DOT, KC_SLSH,

        KC_LCTL, KC_LSFT, KC_SPC, KC_TRNS,       KC_MUTE, KC_ENT, KC_LGUI, KC_LALT
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
/* TAPDANCE CONT */
/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t sclntap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void scln_finished(tap_dance_state_t *state, void *user_data) {
    sclntap_state.state = cur_dance(state);
    switch (sclntap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SCLN); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: register_code16(LSFT(KC_SCLN)); break;  // if dbl tap doesnt send colon, change
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SCLN); register_code(KC_SCLN); break;
        case TD_TRIPLE_TAP: register_code16(LSG(KC_4)); break;   // L SFT + GUI(CMD) -> 4  (SCREEN CAPTURE)
        default: break;
    }
}

void scln_reset(tap_dance_state_t *state, void *user_data) {
    switch (sclntap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SCLN); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: unregister_code16(LSFT(KC_SCLN)); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_SCLN); break;
        case TD_TRIPLE_TAP: unregister_code16(LSG(KC_4)); break; 
        default: break;
    }
    sclntap_state.state = TD_NONE;
}

static td_tap_t spctap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void spc_finished(tap_dance_state_t *state, void *user_data) {
    spctap_state.state = cur_dance(state);
    switch (spctap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SPC); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: register_code(KC_ENTER); break;  // if dbl tap doesnt send colon, change
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SPC); register_code(KC_SPC); break;
        default: break;
    }
}

void spc_reset(tap_dance_state_t *state, void *user_data) {
    switch (spctap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SCLN); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: unregister_code(KC_ENTER); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_SPC); break;
        default: break;
    }
    spctap_state.state = TD_NONE;
}

static td_tap_t bcsptap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
// Functions that control what our tap dance key does
void bcsp_finished(tap_dance_state_t *state, void *user_data) {
    bcsptap_state.state = cur_dance(state);
    switch (bcsptap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_BACKSPACE);
            break;
        case TD_SINGLE_HOLD:
            layer_on(1);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(1)) {
                // If already set, then switch it off
                layer_off(1);
            } else {
                // If not already set, then switch the layer on
                layer_on(1);
            }
            break;
        case TD_DOUBLE_HOLD:
            register_code16(LALT(KC_BACKSPACE));
            break;
        default:
            break;
    }
}

void bcsp_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (bcsptap_state.state == TD_SINGLE_HOLD) {
        layer_off(1);
    }
    bcsptap_state.state = TD_NONE;
}


tap_dance_action_t tap_dance_actions[] = {
    [SCLN_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_finished, scln_reset),
    [SPC_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, spc_finished, spc_reset),
    [BCSP_WD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bcsp_finished, bcsp_reset)
};


// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}


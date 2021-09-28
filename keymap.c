/*
Copyright 2020 Cole Smith <cole@boadsource.xyz>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// COMBOS

enum combos {
  DF_LPRN,
  JK_RPRN,
  SD_LBRC,
  KL_RBRC,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM df_combo[] = {LALT_T(KC_D), LGUI_T(KC_F), COMBO_END};
const uint16_t PROGMEM jk_combo[] = {RGUI_T(KC_J), RALT_T(KC_K), COMBO_END};
const uint16_t PROGMEM sd_combo[] = {LCTL_T(KC_S), LALT_T(KC_D), COMBO_END};
const uint16_t PROGMEM kl_combo[] = {RALT_T(KC_K), RCTL_T(KC_L), COMBO_END};

combo_t key_combos[] = {
    // D+F = (
    [DF_LPRN] = COMBO(df_combo, KC_LPRN),
    // J+K = )
    [JK_RPRN] = COMBO(jk_combo, KC_RPRN),
    // S+D = [
    [SD_LBRC] = COMBO(sd_combo, KC_LBRC),
    // K+L = ]
    [KL_RBRC] = COMBO(kl_combo, KC_RBRC)
};

// Tap Dance keycodes
enum td_keycodes {
    DOT_EL, // `…` when held, `.` when pressed, `@` when double tapped
    EUR_DOL, // `$` when held, `€` when pressed
    DASH_EM, // `—` (OPT-SHFT -) when held, `-` when pressed
    PI_PASTE, // `SHFT-OPT-CMD v` when held, | when pressed
    ESC_FRC, // `Force quit` when held, ESC when pressed
    QU_LAYR
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void dotel_finished(qk_tap_dance_state_t *state, void *user_data);
void dotel_reset(qk_tap_dance_state_t *state, void *user_data);

void eurdol_finished(qk_tap_dance_state_t *state, void *user_data);
void eurdol_reset(qk_tap_dance_state_t *state, void *user_data);

void dashem_finished(qk_tap_dance_state_t *state, void *user_data);
void dashem_reset(qk_tap_dance_state_t *state, void *user_data);

void pipaste_finished(qk_tap_dance_state_t *state, void *user_data);
void pipaste_reset(qk_tap_dance_state_t *state, void *user_data);

void escfrc_finished(qk_tap_dance_state_t *state, void *user_data);
void escfrc_reset(qk_tap_dance_state_t *state, void *user_data);

void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_split_3x5_3(
  KC_Q,             KC_W,           KC_E,           KC_R,           KC_T,               KC_Y,           KC_U,           KC_I,           KC_O,           KC_BSPC,
  LSFT_T(KC_A),     LCTL_T(KC_S),   LALT_T(KC_D),   LGUI_T(KC_F),   ALL_T(KC_G),        ALL_T(KC_H),    RGUI_T(KC_J),   RALT_T(KC_K),   RCTL_T(KC_L),   RSFT_T(KC_P),
  KC_Z,             KC_X,           KC_C,           KC_V,           KC_B,               KC_N,           KC_M,           KC_COMM,        TD(DOT_EL),     KC_SLSH,
                                    MEH(KC_NO),     KC_SPC,         KC_TAB,             KC_ENT,         OSL(1),         TD(QU_LAYR)
),

// ONE SHOTS
[1] = LAYOUT_split_3x5_3(
  KC_ESC,           KC_HASH,        TD(EUR_DOL),    KC_UNDS,        KC_DQUO,            KC_QUOT,        KC_LCBR,        KC_RCBR,        KC_TILD,        KC_TRNS,
  KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_GRV,         KC_LPRN,        KC_RPRN,        KC_COLN,        KC_EXLM,
  LALT(KC_BSLS),    LSA(KC_BSLS),   LALT(KC_8),     TD(PI_PASTE),   KC_AMPR,            KC_SCLN,        KC_LBRC,        KC_RBRC,        KC_CIRC,        KC_BSLS,
                                    MEH(KC_NO),     TD(DASH_EM),    KC_TRNS,            KC_TRNS,        KC_TRNS,        KC_TRNS
),

// NAVIGATION
[2] = LAYOUT_split_3x5_3(
  KC_TRNS,          KC_BRID,        KC_BRIU,        LGUI(KC_GRV),   LCTL(KC_TAB),       KC_PGUP,        LGUI(KC_LBRC),  KC_UP,          LGUI(KC_RBRC),  KC_TRNS,
  KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RGHT,        KC_NO,
  KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                    TO(0),          KC_SPC,         KC_TRNS,            KC_TRNS,        KC_TRNS,        TT(3)
),

// NUMPAD
[3] = LAYOUT_split_3x5_3(
  TD(ESC_FRC),      KC_NO,          KC_NO,          KC_NO,          KC_PERC,            KC_PMNS,        KC_7,           KC_8,           KC_9,           KC_TRNS,
  KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_COLN,            KC_PPLS,        KC_4,           KC_5,           KC_6,           KC_COMM,
  KC_NO,            KC_NO,          KC_PSLS,        KC_ASTR,        KC_PEQL,            KC_0,           KC_1,           KC_2,           KC_3,           KC_DOT,
                                    TO(0),          KC_TRNS,        KC_TRNS,            KC_TRNS,        KC_TRNS,        KC_NO
)

};

//-----

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a tap dance is "interrupted", that means that another key has been hit
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
td_state_t cur_dance(qk_tap_dance_state_t *state) {
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

// Handle the possible states for each tapdance keycode you define:

// DOTEL

void dotel_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: // .
            register_code16(KC_DOT);
            break;
        case TD_SINGLE_HOLD: // …
            register_code16(LOPT(KC_SCLN));
            break;
        case TD_DOUBLE_TAP:
            register_code16(LSFT(KC_2));
            break;
        default:
            break;
    }
}

void dotel_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_DOT);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(LOPT(KC_SCLN));
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(LSFT(KC_2));
            break;
        default:
            break;
    }
}

// EURDOL

void eurdol_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: // €
            register_code16(LALT(KC_2));
            break;
        case TD_SINGLE_HOLD: // $
            register_code16(LSFT(KC_4));
            break;
        default:
            break;
    }
}

void eurdol_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LALT(KC_2));
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(LSFT(KC_4));
            break;
        default:
            break;
    }
}

// DASHEM

void dashem_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: // - (dash)
            register_code16(KC_MINUS);
            break;
        case TD_SINGLE_HOLD: // — (em dash)
            register_code16(LSA(KC_MINUS));
            break;
        default:
            break;
    }
}

void dashem_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_MINUS);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(LSA(KC_MINUS));
            break;
        default:
            break;
    }
}

// PIPASTE

void pipaste_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: // Paste and match style
            register_code16(LSA(LGUI(KC_V)));
            break;
        case TD_SINGLE_HOLD: // |
            register_code16(LSFT(KC_BSLASH));
            break;
        default:
            break;
    }
}

void pipaste_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSA(LGUI(KC_V)));
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(LSFT(KC_BSLASH));
            break;
        default:
            break;
    }
}

// ESCFORCE

void escfrc_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: // Paste and match style
            register_code16(KC_ESC);
            break;
        case TD_SINGLE_HOLD: // |
            register_code16(LAG(KC_ESC));
            break;
        default:
            break;
    }
}

void escfrc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_ESC);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(LAG(KC_ESC));
            break;
        default:
            break;
    }
}

// --- QUANTUM LAYER

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            layer_on(2);
            break;
        case TD_SINGLE_HOLD:
            layer_on(2);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(3)) {
                // If already set, then switch it off
                layer_off(3);
            } else {
                // If not already set, then switch the layer on
                layer_on(3);
            }
            break;
        default:
            break;
    }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(2);
    }
    ql_tap_state.state = TD_NONE;
}

// ---

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [DOT_EL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dotel_finished, dotel_reset),
    [EUR_DOL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, eurdol_finished, eurdol_reset),
    [DASH_EM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dashem_finished, dashem_reset),
    [PI_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pipaste_finished, pipaste_reset),
    [ESC_FRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, escfrc_finished, escfrc_reset),
    [QU_LAYR] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ql_finished, ql_reset, 275)
};

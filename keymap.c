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

// COMBOS playground

enum combos {
  AB_ESC,
  UI_TAB,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};

combo_t key_combos[] = {
  [AB_ESC] = COMBO(ab_combo, KC_ESC),
  [UI_TAB] = COMBO(ui_combo, KC_TAB)
};

// Tap Dance keycodes
enum td_keycodes {
    M_AT, // `@` when held, `m` when tapped. Use as TD(M_AT)
    DOT_EL, // `…` when held, `.` when pressed
    EUR_DOL, // `$` when held, `€` when pressed
    DASH_EM, // `—` (OPT-SHFT -) when held, `-` when pressed
    PI_PASTE, // `SHFT-OPT-CMD v` when held, | when pressed
    ESC_FRC // `Force quit` when held, ESC when pressed
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void mat_finished(qk_tap_dance_state_t *state, void *user_data);
void mat_reset(qk_tap_dance_state_t *state, void *user_data);

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_split_3x5_3(
  KC_Q,             KC_W,           KC_E,           KC_R,           KC_T,               KC_Y,           KC_U,           KC_I,           KC_O,           KC_BSPC,
  LSFT_T(KC_A),     LCTL_T(KC_S),   LALT_T(KC_D),   LGUI_T(KC_F),   ALL_T(KC_G),        ALL_T(KC_H),    RGUI_T(KC_J),   RALT_T(KC_K),   RCTL_T(KC_L),   RSFT_T(KC_P),
  KC_Z,             KC_X,           KC_C,           KC_V,           KC_B,               KC_N,           TD(M_AT),       KC_COMM,        TD(DOT_EL),     KC_SLSH,
                                    MEH(KC_NO),     KC_SPC,         KC_TAB,             KC_ENT,         OSL(1),         TT(2)
),

[1] = LAYOUT_split_3x5_3(
  KC_ESC,           KC_HASH,        TD(EUR_DOL),    KC_UNDS,        KC_DQUO,            KC_QUOT,        KC_LCBR,        KC_RCBR,        KC_TILD,        KC_TRNS,
  KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_GRV,         KC_LPRN,        KC_RPRN,        KC_COLN,        KC_EXLM,
  LALT(KC_BSLS),    LSA(KC_BSLS),   LALT(KC_8),     TD(PI_PASTE),   KC_AMPR,            KC_SCLN,        KC_LBRC,        KC_RBRC,        KC_CIRC,        KC_BSLS,
                                    MEH(KC_NO),     TD(DASH_EM),        KC_TRNS,            KC_TRNS,        KC_TRNS,        KC_TRNS
),

[2] = LAYOUT_split_3x5_3(
  KC_TRNS,          KC_BRID,        KC_BRIU,        LGUI(KC_GRV),   LCTL(KC_TAB),       KC_PGUP,        LGUI(KC_LBRC),  KC_UP,          LGUI(KC_RBRC),  KC_TRNS,
  KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RGHT,        KC_NO,
  KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
                                    TO(0),          KC_SPC,         KC_TRNS,            KC_TRNS,        KC_TRNS,        TT(3)
),

[3] = LAYOUT_split_3x5_3(
  KC_TRNS,          KC_NO,          KC_NO,          KC_NO,          KC_PERC,            KC_PMNS,        KC_7,           KC_8,           KC_9,           KC_TRNS,
  KC_TRNS,          KC_TRNS,        KC_TRNS,        KC_TRNS,        KC_COLN,            KC_PPLS,        KC_4,           KC_5,           KC_6,           KC_COMM,
  KC_NO,            KC_NO,          KC_PSLS,        KC_ASTR,        KC_PEQL,            KC_0,           KC_1,           KC_2,           KC_3,           KC_DOT,
                                    KC_TRNS,        KC_TRNS,        KC_TRNS,            KC_TRNS,        KC_TRNS,        KC_NO
)

};

// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

// MAT

void mat_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: // M
            register_code16(KC_M);
            break;
        case TD_SINGLE_HOLD: // @
            register_code16(LSFT(KC_2)); // Figure out how to type @ instead of 2
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow 2 m's being typed
            tap_code16(KC_M);
            register_code16(KC_M);
            break;
        case TD_UNKNOWN:
            break;
    }
}

void mat_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_M);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(LSFT(KC_2));
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_M);
            break;
        case TD_UNKNOWN:
            break;
    }
}

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
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_DOT);
            register_code16(KC_DOT);
            break;
        case TD_UNKNOWN:
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
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_DOT);
            break;
        case TD_UNKNOWN:
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
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(LALT(KC_2));
            register_code16(LALT(KC_2));
            break;
        case TD_UNKNOWN:
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
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(LALT(KC_2));
            break;
        case TD_UNKNOWN:
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
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_MINUS);
            register_code16(KC_MINUS);
            break;
        case TD_UNKNOWN:
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
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_MINUS);
            break;
        case TD_UNKNOWN:
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
        case TD_DOUBLE_SINGLE_TAP:
        case TD_UNKNOWN:
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
        case TD_DOUBLE_SINGLE_TAP:
        case TD_UNKNOWN:
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
        case TD_DOUBLE_SINGLE_TAP:
        case TD_UNKNOWN:
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
        case TD_DOUBLE_SINGLE_TAP:
        case TD_UNKNOWN:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [M_AT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mat_finished, mat_reset),
    [DOT_EL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dotel_finished, dotel_reset),
    [EUR_DOL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, eurdol_finished, eurdol_reset),
    [DASH_EM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dashem_finished, dashem_reset),
    [PI_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pipaste_finished, pipaste_reset),
    [ESC_FRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, escfrc_finished, escfrc_reset)
};

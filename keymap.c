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

#include "combos.c"
#include "tapdance.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_split_3x5_3(
    KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,               KC_Y,           KC_U,           KC_I,           KC_O,           KC_BSPC,
    SFT_T(KC_A),    LCTL_T(KC_S),   LALT_T(KC_D),   LGUI_T(KC_F),   KC_G,               KC_H,           RGUI_T(KC_J),   RALT_T(KC_K),   RCTL_T(KC_L),   RSFT_T(KC_P),
    KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,               KC_N,           KC_M,           KC_COMM,        TD(DOT_EL),     KC_SLSH,
                                    MEH(KC_NO),     HYPR_T(KC_SPC), KC_TAB,             LT(1, KC_ENT),  TT(2),          TT(3)
),

// ONE SHOTS
[1] = LAYOUT_split_3x5_3(
    KC_ESC,         KC_NO,          TD(EUR_DOL),    KC_HASH,        KC_UNDS,            KC_DQUO,        LSFT(KC_LBRC),  LSFT(KC_RBRC),  KC_TILD,        KC_BSPC,
    SFT_T(KC_A),    LCTL_T(KC_SCLN),TD(ALT_COLN),   TD(CMD_EXL),    KC_NO,              KC_QUOT,        TD(CMD_LPRN),   TD(ALT_RPRN),   TD(DASH_EM),    RSFT_T(KC_NO),
    LALT(KC_BSLS),  LSA(KC_BSLS),   LALT(KC_8),     TD(PI_PASTE),   KC_AMPR,            KC_GRV,         KC_LBRC,        KC_RBRC,        KC_CIRC,        KC_BSLASH,
                                    MEH(KC_NO),     HYPR_T(KC_SPC), KC_TAB,             LT(1, KC_ENT),  TT(2),          TT(3)
),

// NAVIGATION
[2] = LAYOUT_split_3x5_3(
  KC_ESC,           KC_BRID,        KC_BRIU,        LGUI(KC_GRV),   LCTL(KC_TAB),       KC_PGUP,        LGUI(KC_LBRC),  KC_UP,          LGUI(KC_RBRC),  KC_BSPC,
  KC_LSFT,          KC_LCTL,        KC_LOPT,        KC_LCMD,        KC_NO,              KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RGHT,        KC_NO,
  KC_NO,            KC_NO,          KC_NO,          KC_NO,          KC_NO,              KC_NO,          LGUI(KC_MINUS), LGUI(KC_EQL),   KC_NO,          KC_NO,
                                    TO(0),          HYPR_T(KC_SPC), KC_TAB,             LT(1, KC_ENT),  TT(2),          TT(3)
),

// NUMPAD
[3] = LAYOUT_split_3x5_3(
  TD(ESC_FRC),      KC_DEL,         KC_NO,          KC_NO,          KC_PERC,            KC_PMNS,        KC_7,           KC_8,           KC_9,           KC_BSPC,
  KC_LSFT,          KC_LCTL,        KC_LOPT,        KC_LCMD,        KC_COLN,            KC_PPLS,        KC_4,           KC_5,           KC_6,           KC_COMM,
  KC_NO,            KC_NO,          KC_PSLS,        KC_ASTR,        KC_PEQL,            KC_0,           KC_1,           KC_2,           KC_3,           KC_DOT,
                                    TO(0),          HYPR_T(KC_SPC), KC_TAB,             LT(1, KC_ENT),  TT(2),          TT(3)
)

};


// -- moonlander

// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//     [0] = LAYOUT_moonlander(
//         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,     KC_Y,           KC_U,           KC_I,           KC_O,           KC_BSPC,
//         SFT_T(KC_A),    LCTL_T(KC_S),   LALT_T(KC_D),   LGUI_T(KC_F),   KC_G,      KC_H,           RGUI_T(KC_J),   RALT_T(KC_K),   RCTL_T(KC_L),   RSFT_T(KC_P),
//         KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,       KC_N,           KC_M,           KC_COMM,        TD(DOT_EL),         KC_SLSH,
//         MEH(KC_NO),     KC_SPC,         HYPR_T(KC_TAB),                              LT(1, KC_ENT),         TT(2),          TT(3)
//     ),
//
//     [1] = LAYOUT_moonlander(
// KC_ESC,           KC_HASH,        TD(EUR_DOL),    KC_UNDS,        KC_DQUO,                 KC_QUOT,        KC_NO,          KC_NO,        KC_TILD,        KC_BSPC,
// KC_LSFT,          KC_LCTL,        KC_LOPT,        KC_LCMD,        TD(DASH_EM),         KC_GRV,         KC_EXLM,        KC_COLN,      KC_NO,          KC_NO,
// LALT(KC_BSLS),    LSA(KC_BSLS),   LALT(KC_8),     TD(PI_PASTE),   KC_AMPR,               KC_SCLN,        KC_LBRC,        KC_RBRC,      KC_CIRC,        KC_BSLASH,
//  MEH(KC_NO),     KC_SPC,         HYPR_T(KC_TAB),                              LT(1, KC_ENT),         TT(2),          TT(3),
//     ),
//
//     [2] = LAYOUT_moonlander(
//         KC_ESC,           KC_BRID,        KC_BRIU,        LGUI(KC_GRV),   LCTL(KC_TAB),                 KC_PGUP,        LGUI(KC_LBRC),  KC_UP,          LGUI(KC_RBRC),  KC_BSPC,
//         KC_LSFT,          KC_LCTL,        KC_LOPT,        KC_LCMD,        KC_NO,                          KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RGHT,        KC_NO,
//         KC_NO,            KC_NO,          KC_NO,          KC_NO,          KC_NO,                          KC_NO,          KC_MINUS,       KC_EQL,         KC_NO,          KC_NO,
//                     TO(0),          KC_SPC,         HYPR_T(KC_TAB),                              LT(1, KC_ENT),         TT(2),          TT(3)
//     ),
//
//     [3] = LAYOUT_moonlander(
//         TD(ESC_FRC),      KC_DEL,         KC_NO,          KC_PERC,        KC_TAB,                 KC_PMNS,        KC_7,           KC_8,           KC_9,           KC_BSPC,
//         KC_LSFT,          KC_LCTL,        KC_LOPT,        KC_LCMD,        KC_COLN,                KC_PPLS,        KC_4,           KC_5,           KC_6,           KC_COMM,
//         KC_NO,            KC_NO,          KC_PSLS,        KC_ASTR,        KC_PEQL,                KC_0,           KC_1,           KC_2,           KC_3,           KC_DOT,
//         TO(0),          KC_SPC,         HYPR_T(KC_TAB),                              LT(1, KC_ENT),         TT(2),          TT(3)
//     ),
// };

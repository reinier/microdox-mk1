// COMBOS

enum combos {
  DF_CBO,
  JK_CBO,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM df_combo[]   = {LALT_T(KC_D), LGUI_T(KC_F), COMBO_END};
const uint16_t PROGMEM jk_combo[]   = {RGUI_T(KC_J), RALT_T(KC_K), COMBO_END};

combo_t key_combos[] = {
    // D+F = TAB
    [DF_CBO] = COMBO(df_combo, KC_TAB),
    // J+K = ENTER
    [JK_CBO] = COMBO(jk_combo, KC_ENT),
};

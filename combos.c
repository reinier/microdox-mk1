// COMBOS

enum combos {
  DF_CBO,
  JK_CBO,
  CV_CBO,
  MCOM_CBO,
  N45_CBO,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM df_combo[]   = {LALT_T(KC_D), LGUI_T(KC_F), COMBO_END};
const uint16_t PROGMEM jk_combo[]   = {RGUI_T(KC_J), RALT_T(KC_K), COMBO_END};
const uint16_t PROGMEM n45_combo[]  = {KC_4, KC_5, COMBO_END};
const uint16_t PROGMEM cv_combo[]   = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM mcom_combo[] = {KC_M, KC_COMMA, COMBO_END};

combo_t key_combos[] = {
    // D+F = TAB
    [DF_CBO] = COMBO(df_combo, KC_TAB),
    // J+K = ENTER
    [JK_CBO] = COMBO(jk_combo, KC_ENT),
    // C + V = (
    [CV_CBO] = COMBO(cv_combo, KC_LPRN),
    // M + , = )
    [MCOM_CBO] = COMBO(mcom_combo, KC_RPRN),
    // NUMPAD 4+5 = ENTER
    [N45_CBO] = COMBO(n45_combo, KC_ENT),
};

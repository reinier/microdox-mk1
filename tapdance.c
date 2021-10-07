// Tap Dance keycodes
enum td_keycodes {
    DOT_EL, // `…` when double tap, `.` when pressed
    EUR_DOL, // `$` when double pressed, `€` when pressed
    PI_PASTE, // `SHFT-OPT-CMD v` when held, | when pressed
    ESC_FRC, // `Force quit` when held, ESC when pressed
    CMD_EXL,
    CTRL_AMP,
    CMD_LPRN,
    ALT_RPRN
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

void pipaste_finished(qk_tap_dance_state_t *state, void *user_data);
void pipaste_reset(qk_tap_dance_state_t *state, void *user_data);

void escfrc_finished(qk_tap_dance_state_t *state, void *user_data);
void escfrc_reset(qk_tap_dance_state_t *state, void *user_data);

void cmdexl_finished(qk_tap_dance_state_t *state, void *user_data);
void cmdexl_reset(qk_tap_dance_state_t *state, void *user_data);

void ctrlamp_finished(qk_tap_dance_state_t *state, void *user_data);
void ctrlamp_reset(qk_tap_dance_state_t *state, void *user_data);

void cmdlprn_finished(qk_tap_dance_state_t *state, void *user_data);
void cmdlprn_reset(qk_tap_dance_state_t *state, void *user_data);

void altrprn_finished(qk_tap_dance_state_t *state, void *user_data);
void altrprn_reset(qk_tap_dance_state_t *state, void *user_data);

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
        case TD_DOUBLE_TAP: // ..
            tap_code16(KC_DOT);
            register_code16(KC_DOT);  
            break;
        case TD_TRIPLE_TAP: // …
            register_code16(LOPT(KC_SCLN));
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
        case TD_DOUBLE_TAP:
            unregister_code16(KC_DOT);
            break;
        case TD_TRIPLE_TAP:
            unregister_code16(LOPT(KC_SCLN));
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
        case TD_DOUBLE_TAP: // $
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
        case TD_DOUBLE_TAP:
            unregister_code16(LSFT(KC_4));
            break;
        default:
            break;
    }
}

// PIPASTE

void pipaste_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP: // |
            register_code16(LSFT(KC_BSLASH));
            break;
        case TD_DOUBLE_TAP: // Paste and match style
            register_code16(LSA(LGUI(KC_V)));
            break;
        default:
            break;
    }
}

void pipaste_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(LSFT(KC_BSLASH));
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(LSA(LGUI(KC_V)));
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
        case TD_DOUBLE_TAP: // |
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
        case TD_DOUBLE_TAP:
            unregister_code16(LAG(KC_ESC));
            break;
        default:
            break;
    }
}

// CMD EXL

void cmdexl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_EXLM);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_LGUI);
            break;
        default:
            break;
    }
}

void cmdexl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_EXLM);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_LGUI);
            break;
        default:
            break;
    }
}

// CTRL EXL

void ctrlamp_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_AMPR);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_LCTRL);
            break;
        default:
            break;
    }
}

void ctrlamp_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_AMPR);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_LCTRL);
            break;
        default:
            break;
    }
}

// CMD LPRN

void cmdlprn_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_LPRN);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_RGUI);
            break;
        default:
            break;
    }
}

void cmdlprn_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_LPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_RGUI);
            break;
        default:
            break;
    }
}

// ALT RPRN

void altrprn_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_RPRN);
            break;
        case TD_SINGLE_HOLD:
            register_code16(KC_RALT);
            break;
        default:
            break;
    }
}

void altrprn_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_RPRN);
            break;
        case TD_SINGLE_HOLD:
            unregister_code16(KC_RALT);
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [DOT_EL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dotel_finished, dotel_reset),
    [EUR_DOL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, eurdol_finished, eurdol_reset),
    [PI_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pipaste_finished, pipaste_reset),
    [ESC_FRC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, escfrc_finished, escfrc_reset),
    [CMD_EXL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cmdexl_finished, cmdexl_reset),
    [CTRL_AMP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrlamp_finished, ctrlamp_reset),
    [CMD_LPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cmdlprn_finished, cmdlprn_reset),
    [ALT_RPRN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altrprn_finished, altrprn_reset),
};

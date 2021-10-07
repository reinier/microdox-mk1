///////

bool is_cmd_tab_active = false; // ADD this near the begining of keymap.c
uint16_t cmd_tab_timer = 0;     // we will be using them soon.

enum custom_keycodes {          // Make sure have the awesome keycode ready
  CMD_TAB = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { // This will do most of the grunt work with the keycodes.
	case CMD_TAB:
	  if (record->event.pressed) {
		if (!is_cmd_tab_active) {
		  is_cmd_tab_active = true;
		  register_code(KC_LGUI);
		}
		cmd_tab_timer = timer_read();
		register_code(KC_TAB);
	  } else {
		unregister_code(KC_TAB);
	  }
	  break;
  }
  return true;
}

void matrix_scan_user(void) { // The very important timer.
  if (is_cmd_tab_active) {
	if (timer_elapsed(cmd_tab_timer) > 1000) {
	  unregister_code(KC_LGUI);
	  is_cmd_tab_active = false;
	}
  }
}

////////////
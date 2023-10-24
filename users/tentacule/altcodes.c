#include QMK_KEYBOARD_H
#include "print.h"

bool led_get_numlock(void) {
    led_t led_state = host_keyboard_led_state();

    return led_state.num_lock;
}

void send_altcode(uint16_t mask, keyrecord_t *record) {
	
	/* Sends the "alt code" defined in mask, i.e. send_altcode(1234) 
	holds left alt while sending KP_1, KP_2, KP_3 and KP_4 taps, 
	then releases left alt if it wasn't being held by the user. 
	
	NOTE: If your alt code starts with a 0, leave that out, else the
	mask will be treated as octal and your firmware won't compile.
	send_altcode(123) will output KP_0, KP_1, KP_2 and KP_3. */

    uint8_t temp_mods = get_mods();
    unregister_mods(temp_mods);

	// Check & save numlock state
	bool bNumLockWasOn = led_get_numlock();
	
	// Split up the mask into its 4 decimals
	static uint16_t kp[4];
	
	kp[0] = mask / 1000;
	kp[1] = mask / 100 - kp[0] * 100;
	kp[2] = mask / 10 - kp[0] * 1000 - kp[1] * 10;
	kp[3] = mask - kp[0] * 1000 - kp[1] * 100 - kp[2] * 10;
	
	// Convert to keycodes
	for (uint8_t i=0; i<=3; i++) {
		switch(kp[i]) {
			case 0:
				kp[i] = KC_KP_0; break;
			case 1:
				kp[i] = KC_KP_1; break;
			case 2:
				kp[i] = KC_KP_2; break;
			case 3:
				kp[i] = KC_KP_3; break;
			case 4:
				kp[i] = KC_KP_4; break;
			case 5:
				kp[i] = KC_KP_5; break;
			case 6:
				kp[i] = KC_KP_6; break;
			case 7:
				kp[i] = KC_KP_7; break;
			case 8:
				kp[i] = KC_KP_8; break;
			case 9:
				kp[i] = KC_KP_9; break;
		}
	}
        	
	// If not enabled, enable numlock
	if (!bNumLockWasOn) {
        tap_code(KC_LNUM);
	}

    set_mods(MOD_BIT(KC_LALT));    

    for (int i = 0; i < 4; i++) {
        add_key(kp[i]);
        send_keyboard_report();
        del_key(kp[i]);
        send_keyboard_report();
    }

    unregister_mods(MOD_BIT(KC_LALT));    

	// If it wasn't enabled before, disable numlock
	if (!bNumLockWasOn) {      
        tap_code(KC_LNUM);
	}

    set_mods(temp_mods); 
}

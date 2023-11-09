#include QMK_KEYBOARD_H
#include "tentacule.h"

bool process_record_invert_shift(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (get_mods()&MOD_SHIFT_MASK) { // Shift held
            // Save current modifiers, remove shift modifier, register keycode, re-apply modifiers
            uint8_t temp_mods = get_mods();

            unregister_mods(MOD_MASK_SHIFT);
            register_code16(keycode);
            set_mods(temp_mods);
        } else {
            add_key(KC_LSFT);
            add_key(keycode);
	        send_keyboard_report();

            del_key(KC_LSFT);
        }

         return false;
    }

    return true;
}

bool process_record_altcode(uint16_t keycode, keyrecord_t *record, uint16_t noMod, uint16_t shiftMod, uint16_t altMod) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
    if (record->event.pressed) {
        uint8_t temp_mods = get_mods();

        if (temp_mods & MOD_SHIFT_MASK) { // Shift held
            send_altcode(shiftMod, record);
        }
        else if (temp_mods & MOD_ALT_MASK) { // ALT held
            send_altcode(altMod, record);
        } else {
            send_altcode(noMod, record);
        }       
    }

    return false;
}

bool process_record_replace_key(uint16_t keycode, keyrecord_t *record, uint16_t newKey, uint16_t newShiftedKey) {    
    uint8_t temp_mods = get_mods();
    bool isShifted  = get_mods() & MOD_SHIFT_MASK;
    unregister_mods(MOD_MASK_SHIFT);

    if (record->event.pressed) {
        if (isShifted) {           
            register_code16(newKey);
        } else {
            register_code16(newShiftedKey);
        }
    } else {
        if (isShifted){
           unregister_code16(newKey);
        } else {
           unregister_code16(newShiftedKey);
        }
    }

    set_mods(temp_mods);

    return false;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

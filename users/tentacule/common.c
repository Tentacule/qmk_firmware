#include QMK_KEYBOARD_H
#include "tentacule.h"

bool process_record_invert_shift(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (get_mods() & MOD_SHIFT_MASK) { // Shift held
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
    if (record->event.pressed) {
        uint8_t temp_mods = get_mods();
        bool isKeyboardShifted  = get_mods() & MOD_SHIFT_MASK;

        if (isKeyboardShifted)
            unregister_mods(MOD_MASK_SHIFT);

        register_code16(isKeyboardShifted ? newKey : newShiftedKey);

        if (isKeyboardShifted)
            set_mods(temp_mods);
    } else {
      unregister_code16(newKey);
      unregister_code16(newShiftedKey);
    }

    return false;
}

bool process_record_accented(uint16_t keycode, keyrecord_t *record) {
        if (record->event.pressed && IS_LAYER_ON(3)) {
            uint16_t noMod;
            uint16_t shiftMod= 0;
            uint16_t ctrlMod= 0;
            uint16_t shiftAndCtrlMod = 0;

            switch (keycode) {
                case KC_2:
                  noMod =64; // @
                  break;
// A
                case KC_A:
                   noMod = 224; // à
                   shiftMod = 192; // À
                   ctrlMod = 225; // á
                   shiftAndCtrlMod = 193; // Á
                   break;

                case KC_Z:
                   noMod = 226; // â
                   shiftMod = 194; // Â
                   ctrlMod = 228; // ä
                   shiftAndCtrlMod = 196; // Ä
                   break;

//E
                case KC_E:
                            noMod = 233; // é
                            shiftMod = 201; // É
                            ctrlMod = 232; // è
                            shiftAndCtrlMod = 200; // È
                            break;

                   case KC_D:
                            noMod = 234; // ê	
                            shiftMod = 202; // Ê
                            ctrlMod = 235; // ë
                            shiftAndCtrlMod = 203; // Ë
                            break;

// U
                 case KC_U:
                    noMod = 249; // ù
                    shiftMod = 217; // Ù
                    ctrlMod = 251; // û
                    shiftAndCtrlMod = 219; // Û
                    break;

                 case KC_J:
                    noMod = 252; //	ü
                    shiftMod = 220; // Ü
                    break;

// I
                 case KC_I:
                     noMod = 238; // î
                     shiftMod = 206; // Î
                     ctrlMod =  239; // ï
                     shiftAndCtrlMod = 207; // Ï
                     break;

// O
                 case KC_O:
                      noMod = 244; // ô
                      shiftMod = 212; // Ô
                      ctrlMod = 246; //	ö
                      shiftAndCtrlMod = 214; //	Ö
                      break;
//Œ
                 case KC_0:         
                     noMod = 156; // œ
                     shiftMod = 140; // Œ
                     break;

// C
                case KC_C:         
                     noMod = 231; // ç
                     shiftMod = 199; // Ç
                     break;

                default:
                    return true; // Process all other keycodes normally
            }

            uint8_t temp_mods = get_mods();

            if ((temp_mods & MOD_MASK_CTRL) && (temp_mods & MOD_MASK_SHIFT)) { // ctrl + Shift held
                send_altcode(shiftAndCtrlMod, record);                
            } else if (temp_mods & MOD_MASK_SHIFT) { // Shift held
                send_altcode(shiftMod, record);
            } else if (temp_mods & MOD_MASK_CTRL) { // ctrl held
                send_altcode(ctrlMod, record);
            } else {
                send_altcode(noMod, record);
            }

            return false;
    }
    
    return true;
}


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

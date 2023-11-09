#include QMK_KEYBOARD_H
#include "tentacule.h"

bool process_record_programmer_keys(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case KC_2:
             return process_record_altcode(keycode, record, 233, 50, 64); // é 2 @
             break;
        case KC_3:
             return process_record_altcode(keycode, record, 34, 51, 35); // " 3 #
             break;
        case KC_6:
             return process_record_altcode(keycode, record, 232, 54, 94); // è 6 ^
             break;
        case KC_7:
             return process_record_altcode(keycode, record, 38, 55, 124); // & 7 |
             break;

        // invert Shift
        case KC_LBRC: // [{
        case KC_RBRC: // ]}
        case KC_1:
        case KC_4:
        case KC_5:
        case KC_8:
        case KC_9:
        case KC_0:
            return process_record_invert_shift(keycode, record);
            break;

        case KC_NUBS:
            return process_record_replace_key(keycode, record, S(KC_GT), S(KC_LT));
            break;

        default:
            return true; // Process all other keycodes normally
    }
}

bool process_record_custom(uint16_t keycode, keyrecord_t *record) {
    if(!process_record_programmer_keys(keycode, record))
        return false;

    return true;
}

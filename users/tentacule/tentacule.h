#pragma once
#include QMK_KEYBOARD_H
#include "config.h"

enum tap_dances { TD_RESET, TD_SCLN, TD_MINS };

#define MOD_SHIFT_MASK (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))
#define MOD_ALT_MASK (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define MOD_LALT_MASK (MOD_BIT(KC_LALT))

extern void send_altcode(uint16_t mask, keyrecord_t *record);
extern bool process_record_custom(uint16_t keycode, keyrecord_t *record);
extern bool process_record_invert_shift(uint16_t keycode, keyrecord_t *record);
extern bool process_record_altcode(uint16_t keycode, keyrecord_t *record, uint16_t noMod, uint16_t shiftMod, uint16_t altMod);
extern bool process_record_replace_key(uint16_t keycode, keyrecord_t *record, uint16_t newKey, uint16_t newShiftedKey);

#include QMK_KEYBOARD_H
#include "tentacule.h"

void dance_advanced_shift_finished (uint16_t keycode, tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (keycode);
  } else {
    register_code (KC_LSFT);
    register_code (keycode);
  }
}

void dance_advanced_shift_reset (uint16_t keycode, tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (keycode);
  } else {
    unregister_code (KC_LSFT);
    unregister_code (keycode);
  }
}

// _ -
void dance_mins_finished (tap_dance_state_t *state, void *user_data) {
    dance_advanced_shift_finished(KC_MINS, state, user_data);
}

void dance_mins_reset (tap_dance_state_t *state, void *user_data) {
    dance_advanced_shift_reset(KC_MINS, state, user_data);
}

// ; :
void dance_scln_finished (tap_dance_state_t *state, void *user_data) {
   dance_advanced_shift_finished(KC_SCLN, state, user_data);
}

void dance_scln_reset (tap_dance_state_t *state, void *user_data) {
  dance_advanced_shift_reset(KC_SCLN, state, user_data);
}

// Reset keyboard
void dance_safe_reset(tap_dance_state_t *state, void *user_data) {
  if (state->count >= 3) {
    // Reset the keyboard if you tap the key more than three times
    reset_keyboard();
    reset_tap_dance(state);
  }
}

//All tap dance functions would go here. Only showing this one.
tap_dance_action_t tap_dance_actions[] = {
    [TD_RESET] = ACTION_TAP_DANCE_FN(dance_safe_reset),
    [TD_SCLN]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_scln_finished, dance_scln_reset),
    [TD_MINS]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_mins_finished, dance_mins_reset)
};

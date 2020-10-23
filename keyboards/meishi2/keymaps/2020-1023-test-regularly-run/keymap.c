/* Copyright 2019 Biacco42
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

bool regrun_enter;
uint16_t regrun_timer = false;
uint16_t regrun_interval = 1000; // (1000ms == 1s)

enum my_keycodes {
    TOGGLE_REGRUN = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    TOGGLE_REGRUN,  LCTL(KC_X),  LCTL(KC_C), LCTL(KC_V) \
  )
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {
    if (regrun_enter && timer_elapsed(regrun_timer) >= regrun_interval) {
        regrun_timer = timer_read();
        SEND_STRING("test regularly run");
        SEND_STRING(SS_TAP(X_ENTER));
    }
}

void led_set_user(uint8_t usb_led) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
        case TOGGLE_REGRUN:
            if (record->event.pressed) {
                regrun_enter ^= 1;
                regrun_timer = timer_read();
            }
            return false;
    }
    return true;
}

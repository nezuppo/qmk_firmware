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
#include <../mymacros.h>
    // 以下を定義
    // MACRO_STR_KEY2
    // MACRO_STR_KEY3
    // MACRO_STR_KEY4

#define PRO_MICRO_LED_TX D5

bool regrun_enter;
uint16_t regrun_timer = false;
uint16_t regrun_interval = 30000; // (1000ms == 1s)

enum my_keycodes {
    TOGGLE_REGRUN = SAFE_RANGE,
    KEY2,
    KEY3,
    KEY4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    TOGGLE_REGRUN, KEY2, KEY3, KEY4 \
  )
};

void matrix_init_user(void) {
    setPinOutput(PRO_MICRO_LED_TX);
    writePin(PRO_MICRO_LED_TX, !regrun_enter);
}

void matrix_scan_user(void) {
    if (regrun_enter && timer_elapsed(regrun_timer) >= regrun_interval) {
        regrun_timer = timer_read();

        tap_code(KC_MS_L);
        tap_code(KC_MS_R);
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

                writePin(PRO_MICRO_LED_TX, !regrun_enter);
            }
            return false;
        case KEY2:
            if (record->event.pressed) {
                SEND_STRING(MACRO_STR_KEY2);
	    }
            return false;
        case KEY3:
            if (record->event.pressed) {
                SEND_STRING(MACRO_STR_KEY3);
	    }
            return false;
        case KEY4:
            if (record->event.pressed) {
                SEND_STRING(MACRO_STR_KEY4);
	    }
            return false;
    }
    return true;
}

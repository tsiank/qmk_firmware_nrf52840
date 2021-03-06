/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"
#include "ble_service.h"
#include "rgb_matrix.h"
#include "i2c_master.h"

// extern keymap_config_t keymap_config;
extern rgb_config_t rgb_matrix_config;

enum ciank67_layers {
    _DVORAKR,
    _SIGN,
    _FN,
    _QWERTY,
    _SPACE,
    _RGBST,
    _MOUSE
};


enum planck_keycodes { DISC = SAFE_RANGE, ADVW, ADVS, SEL0, SEL1, SEL2, DELB, SLEEP, REBOOT };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_DVORAKR] = LAYOUT(
        GRAVE_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_J,  KC_L,  KC_M,    KC_F,    KC_P,    KC_SLSH,    KC_LBRC,        KC_RBRC,   KC_BSPC,
        KC_TAB,   KC_5,    KC_6,    KC_Q,    KC_DOT,  KC_O,  KC_R,  KC_S,    KC_U,    KC_Y,    KC_B,          KC_SCLN,        KC_EQL,  KC_BSLS,
        KC_CAPS,   KC_7,    KC_8,    KC_Z,    KC_A,             KC_E,    KC_H,    KC_T,    KC_D,    KC_C,    KC_K,          KC_MINS,           KC_ENT,
        KC_LSFT,      KC_9,    KC_0,    KC_X,     KC_COMM,     KC_I,    KC_N,    KC_W,    KC_V, KC_G,      KC_QUOT,   KC_GRAVE, KC_UP,   TG(_QWERTY),
        KC_LCTL,    KC_LALT, KC_LWIN,  MO(_SIGN),              RSFT_T(KC_SPC), MO(_FN),  KC_MENU, KC_RALT,                   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
                        ),
    [_SIGN]   = LAYOUT(
        _______,  KC_F1,  KC_F2,  KC_F3,  KC_TAB,  KC_EXCLAIM,    KC_AT,    KC_HASH,   KC_LBRC,   KC_RBRC  , KC_SLSH, _______,    _______,   _______,
        _______,  KC_F4,  KC_F5,  KC_F6,    KC_LCBR,  KC_DOLLAR, KC_PERCENT,   KC_CIRCUMFLEX,    KC_COLON,  KC_EQL,    KC_PIPE,    _______,   _______,   _______,
        _______,    KC_F7,  KC_F8,  KC_F9,    KC_RCBR ,   KC_AMPERSAND,   KC_ASTERISK,     KC_LEFT_PAREN,   KC_MINS,    KC_PLUS,    KC_TILDE,   _______,  _______,
        RESET,       KC_F10,  KC_F11,   KC_F12,   KC_BSLS,         KC_RIGHT_PAREN,    KC_QUOT,    KC_DOUBLE_QUOTE,   KC_UNDERSCORE,    _______,   _______, _______,_______, _______,
        _______,    _______, _______, KC_TRNS,              RSFT_T(KC_SPC),       KC_TRNS,  _______, _______, _______,    _______, _______, _______
                      ),
    [_FN]   = LAYOUT(
       _______,  SLEEP,  MAGIC_TOGGLE_NKRO, _______,    _______, _______,  _______, _______, KC_PSCREEN, KC_SCROLLLOCK, KC_PAUSE, _______,_______, RESET,
        _______,  OUT_USB, OUT_BT,  _______,   _______, _______,   _______, _______, KC_INSERT, KC_HOME, KC_PGUP, _______,_______, REBOOT,
        _______,  DELB,   DISC,  _______,  _______, _______, _______, _______, _______, _______, KC_DELETE, KC_END,KC_PGDOWN,
         _______,   ADVW, SEL0, SEL1, SEL2, _______, _______, _______,  _______,_______, _______, _______,ADVS, _______,
        RGB_TOG, _______, RGB_MOD,  _______, KC_SPC, KC_TRNS,_______, _______, _______, _______, TO(_RGBST), TO(_MOUSE)
                      ),
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_GRAVE,  KC_UP,  TG(_QWERTY),
        KC_LCTL,    KC_LALT, KC_LWIN,  MO(_SIGN),              RSFT_T(KC_SPC), MO(_FN),  KC_MENU, KC_RALT,                   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
                       ),
    [_RGBST] = LAYOUT(
        _______, RGB_HUI, RGB_HUD, RGB_SAI, _______, KC_WH_D, KC_MS_U, KC_WH_U, _______, _______,_______, _______,_______, _______,
        _______, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, _______, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, _______,_______, _______,
        _______, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_RAINBOW, _______, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,_______,
        _______, RGB_MODE_SWIRL, RGB_MODE_SNAKE, RGB_MODE_KNIGHT, RGB_MODE_XMAS, RGB_MODE_GRADIENT, RGB_MODE_RGBTEST, _______, _______, _______, _______, _______,_______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,TO(_DVORAKR),  _______
                     ),
    [_MOUSE] = LAYOUT(
        _______, KC_MS_UP, KC_MS_DOWN, KC_MS_LEFT, KC_MS_RIGHT,_______, _______,_______,  _______, _______,_______, _______,_______, _______,
        _______, KC_MS_BTN1, KC_MS_BTN2, _______, _______,  _______, _______, _______, _______, _______,_______, _______, _______,_______, 
        _______, KC_MS_WH_UP, KC_MS_WH_DOWN, _______, _______, _______, _______,_______,_______, _______,_______, _______,_______,
        KC_PWR, KC_MUTE, KC_VOLU, KC_VOLD, KC_MNXT, KC_MPRV, KC_MSTP, KC_MPLY, _______, _______, _______, _______,_______, _______,
        KC_MY_COMPUTER,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_DVORAKR)
                     )
};

void keyboard_post_init_user() {
    #ifdef IS31FL3737
    // Shutdown IS31FL3737 if rgb disabled
    if (!rgb_matrix_config.enable) {
        i2c_stop();
    }
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef POWER_SAVE_TIMEOUT
        if (record->event.pressed) {
            reset_power_save_counter();
        }
    #endif
    switch (keycode) {
        case DISC:
            if (record->event.pressed) {
                ble_disconnect();
            }
            return false;

        case ADVW:
            if (record->event.pressed) {
                advertising_without_whitelist();
            }
            return false;

        case ADVS:
            if (record->event.pressed) {
                advertising_start(false);
            }
            return false;

        case SEL0:
            if (record->event.pressed) {
                restart_advertising_id(0);
            }
            return false;

        case SEL1:
            if (record->event.pressed) {
                restart_advertising_id(1);
            }
            return false;

        case SEL2:
            if (record->event.pressed) {
                restart_advertising_id(2);
            }
            return false;

        case DELB:
            if (record->event.pressed) {
                advertising_start(true);
            }
            return false;

        case REBOOT:
            if (record->event.pressed) {
                NVIC_SystemReset();
            }

        case RGB_TOG:
            if (record->event.pressed) {
                if (rgb_matrix_config.enable) {
                    i2c_stop();
                } else {
                    i2c_start();
                }
            }
            return true;

        case SLEEP:
            if (!record->event.pressed) {
                deep_sleep_mode_enter();
            }
            return false;
    }
    return true;
}

void rgb_matrix_indicators_user(void) {
	  uint8_t this_led = host_keyboard_leds();
	  if (!g_suspend_state) {
	    switch (biton32(layer_state)) {
        case _QWERTY:
          rgb_matrix_set_color(0, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(1, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(1, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(2, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(3, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(4, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(5, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(6, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(7, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(8, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(9, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(10, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(11, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(12, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(14, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(15, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(16, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(17, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(18, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(19, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(20, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(21, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(22, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(23, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(24, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(25, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(26, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(27, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(28, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(29, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(30, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(31, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(32, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(33, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(34, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(35, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(36, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(37, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(38, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(39, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(40, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(41, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(42, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(43, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(44, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(45, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(46, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(47, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(48, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(49, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(50, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(51, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(52, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(53, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(54, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(55, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(56, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(57, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(58, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(59, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(60, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(61, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(62, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(63, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(64, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(65, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(66, 0x00, 0x00, 0x00);
          rgb_matrix_set_color(67, 0x00, 0xFF, 0xFF);
          rgb_matrix_set_color(68, 0xFF, 0x00, 0x00);
          rgb_matrix_set_color(69, 0xFF, 0x00, 0x00);
          rgb_matrix_set_color(70, 0x00, 0xFF, 0x00);
          rgb_matrix_set_color(71, 0x00, 0xFF, 0x00);
          rgb_matrix_set_color(72, 0xFF, 0xFF, 0x00);
          rgb_matrix_set_color(73, 0xFF, 0xFF, 0x00);
          rgb_matrix_set_color(74, 0xFF, 0xFF, 0x00);
          rgb_matrix_set_color(75, 0x00, 0xFF, 0x00);
          rgb_matrix_set_color(76, 0x00, 0x00, 0xFF);
          rgb_matrix_set_color(77, 0x00, 0xFF, 0x00);
          rgb_matrix_set_color(78, 0xFF, 0x00, 0x00);
          rgb_matrix_set_color(79, 0xFF, 0xFF, 0x00);
          rgb_matrix_set_color(80, 0xFF, 0xFF, 0x00);
          rgb_matrix_set_color(81, 0xFF, 0x00, 0x00);
          rgb_matrix_set_color(82, 0xFF, 0x00, 0x00);
          break;
	      case _SIGN:
	        rgb_matrix_set_color_all(0x7A, 0x00, 0xFF);
          break;
	      case _FN:
	        rgb_matrix_set_color(77,0xFF, 0x80, 0x00);
          break;
	      case _RGBST:
	        rgb_matrix_set_color(78,0xFF, 0x80, 0xBF);
          break;
	      case _MOUSE:
	        rgb_matrix_set_color_all(0x99, 0xf5, 0xFF);
          break;
      }
    }
    if ( this_led & (1<<USB_LED_CAPS_LOCK)) {
          rgb_matrix_set_color(28, 0xFF, 0xFF, 0xFF);
          rgb_matrix_set_color(76, 0xFF, 0xFF, 0xFF);
    }
}
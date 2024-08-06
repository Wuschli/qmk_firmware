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
#include "action_layer.h"
#include "keymap_german.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _SYMBOLS,
  _LOWER,
  _RAISE,
  _ADJUST,
  _ARROWS
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  M_LSFT,
  M_LESS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = {
  {KC_TAB,              DE_Q,    DE_W,     DE_E,    DE_R,    DE_T,    DE_Y,    DE_U,    DE_I,    DE_O,    DE_P,    KC_BSPC              },
  {LT(_ARROWS, KC_ESC), DE_A,    DE_S,     DE_D,    DE_F,    DE_G,    DE_H,    DE_J,    DE_K,    DE_L,    DE_SCLN, KC_ENT               },
  {M_LSFT,              DE_Z,    DE_X,     DE_C,    DE_V,    DE_B,    DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_SLSH, DE_QUOT              },
  {KC_LCTL,             KC_F19,  KC_LGUI,  KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT             }
},
[_SYMBOLS] = {
	{ _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ },
	{ _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, DE_DOT,  _______ },
	{ _______, _______, _______, _______, _______, _______, _______, _______, M_LESS,  DE_RABK, DE_QUES, DE_DQUO },
	{ _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ }
},
[_LOWER] = {
  {DE_TILD, DE_EXLM, DE_AT,   DE_HASH, DE_DLR,  DE_PERC, DE_CIRC, DE_AMPR, DE_ASTR, DE_LPRN, DE_RPRN, KC_DEL  },
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   DE_UNDS, DE_PLUS, DE_LCBR, DE_RCBR, DE_PIPE },
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_HOME, KC_END,  _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY }
},
[_RAISE] = {
  {DE_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL  },
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   DE_MINS, DE_EQL,  DE_LBRC, DE_RBRC, DE_BSLS },
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_PGUP, KC_PGDN, _______ },
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY }
},
[_ADJUST] = {
	{ _______, QK_BOOT, _______, DE_EURO, _______, _______, _______, DE_UDIA,               _______,             DE_ODIA, _______,  KC_DEL },
	{ _______, DE_ADIA, DE_SS,   _______, _______, _______, _______,  LCTL(LGUI(KC_LEFT)), LCTL(LGUI(KC_RIGHT)), _______, _______, _______ },
	{ _______, _______, _______, _______, _______, _______, _______,  _______,             _______,              _______, _______, _______ },
	{ _______, _______, _______, _______, _______, _______, _______,  _______,             _______,              _______, _______, _______ }
},
[_ARROWS] = {
	{ _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,  _______, _______ },
	{ _______, _______, KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT, KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT, _______, _______ },
	{ _______, _______, _______, _______, _______,  _______, _______, _______, _______, KC_HOME,  KC_END,  _______ },
	{ _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,  _______, _______ }
}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
	case RAISE:
		if (record->event.pressed) {
			layer_on(_RAISE);
			update_tri_layer(_LOWER, _RAISE, _ADJUST);
		}
		else {
			layer_off(_RAISE);
			update_tri_layer(_LOWER, _RAISE, _ADJUST);
		}
		return false;
		break;
    case M_LSFT:
		if (record->event.pressed) {
			register_code(KC_LSFT);
			layer_on(_SYMBOLS);
		}
		else {
			layer_off(_SYMBOLS);
			unregister_code(KC_LSFT);
		}
		break;
	case M_LESS: // M(1)
		if (record->event.pressed) {
			unregister_code(KC_LSFT);
			register_code(DE_LABK);
		}
		else {
			unregister_code(DE_LABK);
			register_code(KC_LSFT);
		}
		break;
  }
  return true;
}

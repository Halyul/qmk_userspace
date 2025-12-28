/* Copyright 2022 @ Teimor Epstein
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
#include "keymap_user.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix_user.h"
#endif
#ifdef TAP_DANCE_ENABLE
#   include "tap_dance_mac_caps.h"
#   include "tap_dance_win_caps.h"
#endif

#define TG_NKRO MAGIC_TOGGLE_NKRO

#ifdef TAP_DANCE_ENABLE
tap_dance_action_t tap_dance_actions[] = {
    [MAC_CAPS_LANGUAGE_CHANGE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mac_caps_language_finished, mac_caps_language_reset),
    [WIN_CAPS_LANGUAGE_CHANGE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, win_caps_language_finished, win_caps_language_reset)
};
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,            KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_DEL,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGUP,
        KC_LGWIN, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_WINFN, KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_82(
        QK_RBT,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,    KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            UG_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,            _______,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,            KC_HOME,
        KC_CAPS,  UG_PREV, UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  _______,  _______,  _______, KC_LOCKWIN,  _______,  _______,            QK_BOOT,            KC_END,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                TO(MAC_BASE),                             _______,  _______,  _______,  _______,  _______,  _______),

    [MAC_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,           KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,           KC_DEL,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,           KC_PGUP,
        KC_LGMAC, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,            KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LALT,  KC_LGUI,                                KC_SPC,                                 KC_RGUI,  KC_MACFN, KC_RCTL,  KC_LEFT,  KC_DOWN, KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_82(
        QK_RBT,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            UG_TOGG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            KC_HOME,
        KC_CAPS,  UG_PREV, UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  _______,  _______,  _______,  KC_LMAC,  _______,  _______,            QK_BOOT,            KC_END,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                TO(WIN_BASE),                           _______,  _______,  _______,  _______,  _______,  _______)
};

// clang-format on

void matrix_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init_user();
#endif
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [MAC_FN]   = { ENCODER_CCW_CW(UG_VALU, UG_VALD) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [WIN_FN]   = { ENCODER_CCW_CW(UG_VALU, UG_VALD) },
};
#endif

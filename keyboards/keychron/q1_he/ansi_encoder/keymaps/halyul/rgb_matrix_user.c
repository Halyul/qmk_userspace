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
#include "rgb_matrix_user.h"
#include "keymap_user.h"

keypos_t led_index_key_position[RGB_MATRIX_LED_COUNT];

void rgb_matrix_init_user(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index != NO_LED) {
                led_index_key_position[led_index] = (keypos_t){.row = row, .col = col};
            }
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t current_layer = get_highest_layer(layer_state | default_layer_state);
    switch (current_layer) {
        case MAC_BASE:
        case WIN_BASE:
#if defined CAPS_LOCK_INDICATOR_COLOR
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_alphabet_or_caps_lock_indicator, CAPS_LOCK_INDICATOR_COLOR);
            }
#endif
            break;
        case MAC_FN:
        case WIN_FN:
#ifdef FN_LAYER_TRANSPARENT_KEYS_OFF
            rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_transparent, RGB_OFF);
#endif
            break;
    }
    return true;
}

void rgb_matrix_set_color_by_keycode(uint8_t led_min, uint8_t led_max, uint8_t layer, bool (*is_keycode)(uint16_t), uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(layer, led_index_key_position[i]);
        if ((*is_keycode)(keycode)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
    }
}

bool is_alphabet_or_caps_lock_indicator(uint16_t keycode) {
    return keycode == KC_CAPS || keycode == KC_LGMAC || keycode == KC_LGWIN ||
    keycode == KC_A  || keycode == KC_B  || keycode == KC_C  || keycode == KC_D  || keycode == KC_E  ||
    keycode == KC_F  || keycode == KC_G  || keycode == KC_H  || keycode == KC_I  || keycode == KC_J  ||
    keycode == KC_K  || keycode == KC_L  || keycode == KC_M  || keycode == KC_N  || keycode == KC_O  ||
    keycode == KC_P  || keycode == KC_Q  || keycode == KC_R  || keycode == KC_S  || keycode == KC_T  ||
    keycode == KC_U  || keycode == KC_V  || keycode == KC_W  || keycode == KC_X  || keycode == KC_Y  ||  keycode == KC_Z;
}

bool is_transparent(uint16_t keycode) { return keycode == KC_TRNS; }
bool is_not_transparent(uint16_t keycode) { return keycode != KC_TRNS; }

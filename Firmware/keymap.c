// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Buttons & Clicks
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        // Top Row of 3 Mechanical Switches
        KC_A,    KC_B,    KC_C, 
        
        // Bottom Row of 3 Mechanical Switches
        KC_D,    KC_E,    KC_F, 
        
        // The 2 Rotary Encoder Clicks (Left Click, Right Click)
        KC_MUTE, KC_MPLY  
    )
};

// Encoder Turns
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { 
        // LEFT ENCODER (Index 0): Volume Control
        if (clockwise) {
            tap_code(KC_VOLU); // Volume Up
        } else {
            tap_code(KC_VOLD); // Volume Down
        }
    } else if (index == 1) { 
        // RIGHT ENCODER (Index 1): Mouse Scrolling
        if (clockwise) {
            tap_code16(MS_WHLD); // Scroll Down
        } else {
            tap_code16(MS_WHLU); // Scroll Up
        }
    }
    return false;
}
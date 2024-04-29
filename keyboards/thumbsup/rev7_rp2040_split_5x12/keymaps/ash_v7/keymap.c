/* Copyright 2022
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
#include "features/achordion.h"
// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _NAV,
    _NUM,
    _FUNC,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    BASE,
    // These three wiil work as RAISE, LOWER  and ADJUST in the original PLANCK
    NAV,
    NUM,
    FUNC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


/* BASE
 * ,-----------------------------------------++-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  ||   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * | Esc  |   Q  |   W  |   E  |   R  |   T  ||   Y  |   U  |   I  |   O  |   P  |BackSp|
 * |------+------+------+------+------+------++------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  ||   H  |   J  |   K  |   L  |   ;  |Enter |
Hold:
   Extra-Rt
 * |------+------+------+------+------+------||------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  ||   N  |   M  |   ,  |   .  |   /  |RCtrl |
 * +------+------+------+------+------+------++------+------+------+------+------+------+
		 |  GUI | Alt  |      |      ||      |      | RAlt | Menu |
	      |  +------+------+      |      ||      |      +------+------+   |
Hold:  	      |	               | LSft |CursLt||CursRt| RSft |                 |
Single hit:   |		       |      |Space ||Space |      |                 |
              |                +------+------||------+------+                 |
              +------>                | Space||Space |              <---------+
                                      +------||------+

 */
[_BASE] = LAYOUT_ortho_5x12( \
    KC_GRV,     KC_1,           KC_2,       KC_3,       KC_4,           KC_5,           KC_6,           KC_7,           KC_8,       KC_9,       KC_0,       KC_MINUS,  \
    KC_ESC,     KC_Q,           KC_W,       KC_E,       KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,       KC_O,       KC_P,       KC_DEL, \
    KC_TAB,     KC_A,           KC_S,       KC_D,       KC_F,           KC_G,           KC_H,           KC_J,           KC_K,       KC_L,       KC_SCLN,    KC_QUOTE,  \
    KC_BSPC,    KC_Z,           KC_X,       KC_C,       KC_V,           KC_B,           KC_N,           KC_M,           KC_COMMA,   KC_DOT,     KC_SLSH,    KC_MINUS, \
                GUI_T(KC_CAPS), KC_LALT,    SC_LSPO,    CTL_T(KC_TAB),  LT(3,KC_SPC),   LT(2,KC_SPC),   CTL_T(KC_DEL),  SC_SENT,    KC_RALT,    GUI_T(KC_BSLS)   \
),



/*

Layers below are used on top of BASE layer defined above.
(Except the PLOVER/STENO layers.)
                                           +-------+
The keys which are shown empty, like this: |       |, represent a transparent key,
                                           +-------+
meaning the key from the underlaying layer (i.e. BASE) will be used.
In the keymaps those keys are defined as "_______".

                                           +-------+         +-------+
The keys which are shown solid, like this: | XXXXX | or this |  ...  |, represent an opaque/blocking key?
                                           +-------+         +-------+
Such key is not doing anything in that layer nor allowing the key from the underlaying layer
to be invoked.
In the keymaps those keys are defined as "XXXXXXX".

Most of the modifiers are the same in all layers.
So in most layers they are defined as transparent keys,
letting the keys from BASE layer to do the work.

With that idea all the layers below leave the unmodified keys as transparent keys.
In the same time - the layers block the keys that have no sense to be used
in that given layer. For instance in the cursor control layers
some of the keys are not used in the layer, but they are blocked to avoid
alpha-keys from BASE layer to appear.

For the same reason the keymaps below are shown simplified,
without separate thumbcluster.

*/



/* Cursor Control on the right (Right Space)
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |Break |WheelD|MousUp|WheelU| Del  |  Ins | Home |  Up  | End  |   `  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |SelAll|MousLt|MousDn|MousRt| ...  | PgUp | Left | Down |Right | ...  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Paste| ...  | PgDn |MsBtLe|MsBtMi|MsBtRt| ...  |      |
 * `------+------+------+------+------+------+------+------+------+------+------+------.
 *               |      |      |      |      |   X  |      |      |      |
 *               `-------------------------------------------------------'
 */
[_NAV] = LAYOUT_ortho_5x12( \
  _______, _______,          _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______, _______, \
  _______, KC_BRK,           KC_WH_D,      KC_MS_U,      KC_WH_U,      KC_DEL,              KC_PGUP,  KC_HOME, KC_UP,   KC_END,  KC_GRV,  KC_DEL, \
  KC_ENT,  LCTL(KC_A),       KC_MS_L,      KC_MS_D,      KC_MS_R,      XXXXXXX,             KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______, \
  _______, LCTL(KC_Z),       LSFT(KC_DEL), LCTL(KC_INS), LSFT(KC_INS), XXXXXXX,             KC_INS,   KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, _______, \
    	    		     _______,      _______,      _______,      _______, _______, _______,  _______, _______, _______, _______           \
),



 /* Cursor Control on the left (Left Space)
 * ,-----------------------------------------------------------------------------------.
 * |      |Break | Home |  Up  | End  |  Ins | Del  |WheelU|MousUp|WheelD|   `  | Del  |
 * |------+------+------+------+------+------+-------------+------+------+------+------|
 * | Enter|SelAll|Right | Down | Left | PgUp | xxx  |MousLt|MousDn|MousRt| xxx  |Enter |
 * |------+------+------+------+------+------+------|------+------+------+------+------|
 * |      | xxx  |MsBtRt|MsBtMi|MsBtLe| PgDn | xxx  | Cut  | Copy | Paste| xxx  |      |
 * `------+------+------+------+------+------+------+------+------+------+------+------.
 *               |      |      |      |   X  |       |      |      |      |
 *               `-------------------------------------------------------'
 */
[_NUM] = LAYOUT_ortho_5x12( \
  _______, _______,         _______, _______, _______, _______,       _______, _______,	     _______,      _______,      _______, _______, \
  _______, KC_BRK,          KC_HOME, KC_UP,   KC_END,  KC_PGUP,       KC_DEL,  KC_WH_U,      KC_MS_U,      KC_WH_D,      KC_GRV,  KC_DEL, \
  KC_ENT,  LCTL(KC_A),      KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,       XXXXXXX, KC_MS_L,      KC_MS_D,      KC_MS_R,      XXXXXXX, _______, \
  _______, XXXXXXX,         KC_BTN2, KC_BTN3, KC_BTN1, KC_INS,        XXXXXXX, LCTL(KC_DEL), LCTL(KC_INS), LSFT(KC_INS), XXXXXXX, _______, \
    	    		     _______,      _______,      _______,      _______, _______, _______,  _______, _______, _______, _______           \

),


 /* FUNC on the home row, FNs on the top row, symbols in the second row
 * (Lower or Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |BackSp|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   F1 |   F2 |   F3 |   F4 |   F5 |   F6 |   F7 |   F8 |   F9 |   F10| Enter|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F11 |  F12 | LAlt |LShift| LAlt | RAlt |RShift|   ,  |   .  |   /  |      |
 * `------+------+------+------+------+------+------+------+------+------+------+------.
 *               |      |      |      |      |      |      |      |      |
 *               `-------------------------------------------------------'
 */
[_FUNC] = LAYOUT_ortho_5x12( \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9, KC_F10,  _______, \
  _______, KC_F11,  KC_F12,  KC_LALT, KC_LSFT, KC_LALT, KC_RALT, KC_RSFT, KC_COMM, KC_DOT,  KC_SLSH, _______, \
    	    		     _______,      _______,      _______,      _______, _______, _______,  _______, _______, _______, _______           \
),
};

void matrix_init_user() {
//   persistent_default_layer_set(1UL<<_BASE);
//  steno_set_mode(STENO_MODE_BOLT); // or STENO_MODE_BOLT
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    //  debug_enable=false;
    //  debug_matrix=false;
    //  debug_keyboard=false;
  //debug_mouse=true;
}

void matrix_scan_user(void) {
  achordion_task();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _NAV, _NUM, _FUNC);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_achordion(keycode, record)) { return false; }

    switch (keycode) {

        case NAV:
        if (record->event.pressed) {
            layer_on(_NAV);
            update_tri_layer(_NAV, _NUM, _FUNC);
        } else {
            layer_off(_NAV);
            update_tri_layer(_NAV, _NUM, _FUNC);
        }
        return true;// false;
        break;

        case NUM:
        if (record->event.pressed) {
            layer_on(_NUM);
            update_tri_layer(_NAV, _NUM, _FUNC);
        } else {
            layer_off(_NUM);
            update_tri_layer(_NAV, _NUM, _FUNC);
        }
        return true;// 	false;
        break;

        case BASE:
        if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_BASE, false, 0);
            #endif
            layer_off(_NAV);
            layer_off(_NUM);
            layer_off(_FUNC);
            layer_on(_BASE);

            //persistent_default_layer_set(1UL<<_BASE);
            set_single_persistent_default_layer(_BASE);
        }
        return false;
        break;




 }
  return true;
}

/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
//#include "keychron_common.h"

// clang-format off

enum layers
{
    BASE_LAYER_HOME,
    BASE_LAYER_WORK,
    LAYER_WORK_FN,
    LAYER_GIT,
    LAYER_VSCODE
};

// layer shorthands for keymap use
#define L_HME   BASE_LAYER_HOME
#define L_WRK   BASE_LAYER_WORK
#define L_FN    LAYER_WORK_FN
#define L_GIT   LAYER_GIT
#define L_VSC   LAYER_VSCODE

// layer mask for lighting use
#define LIGHTING_LAYERS ((layer_state_t)((1 << LAYER_GIT) | (1 << LAYER_VSCODE)))

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// led indexes
#define F1_LED_INDEX (1)
#define F2_LED_INDEX (2)
#define F3_LED_INDEX (3)
#define F4_LED_INDEX (4)
#define F5_LED_INDEX (5)
#define F6_LED_INDEX (6)
#define F7_LED_INDEX (7)
#define F8_LED_INDEX (8)
#define F9_LED_INDEX (9)
#define F10_LED_INDEX (10)
#define F11_LED_INDEX (11)
#define F12_LED_INDEX (12)

//colours
#define RGB_GIT_GREEN    0x00, 0x60, 0x00
#define RGB_VSC_BLUE     0x00, 0x48, 0x80


// define some macro keycodes
enum custom_keycodes {
        GIT1 = SAFE_RANGE, // see quantum_keycodes.h and keycodes.h
        GIT2,
        GIT3,
        VS_ST, // vs code debug step
        VS_SI, // vs code debug step in
        VS_SO, // vs code debug step out
        LONGV
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE_LAYER_HOME] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,            KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_DEL,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_HOME,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_END,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(L_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    //can strip down
    [BASE_LAYER_WORK] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,            KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_DEL,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_HOME,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_END,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(L_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [LAYER_WORK_FN] = LAYOUT_ansi_82(
        QK_MAKE,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,            RGB_TOG,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            LONGV,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  TG(L_VSC),
        _______, TG(L_WRK),  _______,                                _______,                                _______,  _______,    _______,TG(L_GIT),  _______,  _______),

    [LAYER_GIT] = LAYOUT_ansi_82(
        _______,  _______,  GIT1,     GIT2,     GIT3,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

    [LAYER_VSCODE] = LAYOUT_ansi_82(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  VS_SO,    VS_ST,    VS_SI,    _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),
};

/* keep this here in case I need it:

    [LAYER_UNUSED] = LAYOUT_ansi_82(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

*/

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE_LAYER_HOME]           = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [BASE_LAYER_WORK]           = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [LAYER_WORK_FN]             = { ENCODER_CCW_CW(KC_C, KC_W)},
    [LAYER_GIT]                 = { ENCODER_CCW_CW(_______, _______)},
    [LAYER_VSCODE]              = { ENCODER_CCW_CW(_______, _______)}
};
#endif // ENCODER_MAP_ENABLE

// clang-format on

// define macros for return values of below functions
#define CONTINUE (true)     // continue processing this event
#define FINISHED (false)    // no further processing needed

static bool work_mode = false;
//static bool mode_git = false;
//static bool mode_vsc = false;



// called by process_record_kb() in v1.c whenever a key is pressed or released
// return true if further processing of the action is required, false if not
// funcs for each based on layer
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    bool return_val = FINISHED;

    if (record->event.pressed)
    {
        // global customs
        switch (keycode)
        {
        case GIT1:
            SEND_STRING("git status -s");
            tap_code(KC_ENTER);
            goto exit;
        case GIT2:
            if (work_mode)
            {
                SEND_STRING("git switch develop");
            }
            
            goto exit;
        // case GIT3:
        //     SEND_STRING("git fetch && git pull && git submodule update");
        //     goto exit;
        case LONGV:
            SEND_STRING("longview");
            goto exit;
        case VS_ST:
            tap_code(KC_F10);
            goto exit;
        case VS_SI:
            tap_code(KC_F11);
            goto exit;
        case VS_SO:
            add_mods(MOD_MASK_SHIFT);
            tap_code(KC_F11);
            del_mods(MOD_MASK_SHIFT);
            goto exit;
        default:
            break;
        }

        //work customs
        if (IS_LAYER_ON(BASE_LAYER_WORK))
        {
            switch (keycode)
            {
                case GIT3:
                SEND_STRING("git fetch && git pull && git submodule update");
                goto exit;
            default:
                break;
            }
        };
    }

    return_val = CONTINUE;
    
exit:
    return return_val;
};


void set_all_keys_in_layer(uint8_t layer, \
                            uint8_t led_min, uint8_t led_max, \
                            uint8_t red, uint8_t green, uint8_t blue)
{
    for (uint8_t row = 0; row < MATRIX_ROWS; ++row)
    {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col)
        {
            uint8_t index = g_led_config.matrix_co[row][col];

            if ((index >= led_min)
                && (index < led_max)
                && (index != NO_LED)
                && (keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS))
            {
                rgb_matrix_set_color(index, red, green, blue);
            }
        }
    }
}



void do_mode_lighting(uint8_t led_min, uint8_t led_max)
{
    if (IS_LAYER_ON(LAYER_GIT))
    {
        set_all_keys_in_layer(LAYER_GIT, led_min, led_max, RGB_GIT_GREEN);
    }

    if (IS_LAYER_ON(LAYER_VSCODE))
    {
        set_all_keys_in_layer(LAYER_VSCODE, led_min, led_max, RGB_VSC_BLUE);
    }
}

void do_mode_lighting_all_leds(void)
{
    do_mode_lighting(0, 255);
}

void set_base_rgb(void)
{
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_set_color_all(RGB_OFF);
}

void matrix_init_user(void)
{
    if (work_mode)
    {
        set_base_rgb();
    }
}

// called before the set_color calls?
bool rgb_matrix_indicators_user(void)
{
    do_mode_lighting_all_leds();
    return FINISHED;
}

bool layer_state_cmp_bitmasks(layer_state_t cmp_layer_state, layer_state_t test_layer_state)
{
    return ((cmp_layer_state & test_layer_state) != 0);
}

layer_state_t layer_state_set_user(layer_state_t state)
{
    //do_work_rgb_override(); new

    if (work_mode != (IS_LAYER_ON(BASE_LAYER_WORK)))
    {
        work_mode = (IS_LAYER_ON(BASE_LAYER_WORK));
        set_base_rgb();
        //clear_keyboard();
        //do_work_rgb_override();
    }

    // handle layer lighting
    do_mode_lighting_all_leds();

    // return unmodified layer state
    return state;
}

// all the default and dip stuff is sus

// static void enable_work_mode(void)
// {
//     work_mode = true;
//     layer_on(BASE_LAYER_WORK);
    //default_layer_set((layer_state_t)1 << layer);
    // clear_keyboard();
    // do_work_rgb_override();
    // do_mode_lighting_all_leds();

//}

// called by dip_switch_update_kb() in v1.c
bool dip_switch_update_user(uint8_t index, bool val)
{
    default_layer_set(1UL << (BASE_LAYER_HOME));
    if (index == 0)
    {
        work_mode = val;
        if (work_mode)
        {
            SEND_STRING("WORK_MODE");
            layer_on(BASE_LAYER_WORK);
        }
        else
        {
            SEND_STRING("HOME_MODE");
        }
    }
    return FINISHED;
}
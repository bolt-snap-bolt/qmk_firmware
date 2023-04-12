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

/* bsb keymap */
#define BSB_VERSION "v1.1.1"

// clang-format off
enum layers
{
    BASE_LAYER_HOME,
    BASE_LAYER_WORK,
    LAYER_FN,
    LAYER_GIT,
    LAYER_VSCODE,
};

// layer shorthands for keymap use
#define L_HME   BASE_LAYER_HOME
#define L_WRK   BASE_LAYER_WORK
#define L_FN    LAYER_FN
#define L_GIT   LAYER_GIT
#define L_VSC   LAYER_VSCODE

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// return value defines
#define CONTINUE (true)     // continue processing this event
#define FINISHED (false)    // no further processing needed

/* Keycodes */
enum custom_keycodes {
    // see quantum_keycodes.h and keycodes.h
    FWVER = SAFE_RANGE,
    ENCDR,
    VS_ST, // vsc debug step
    VS_SI, // vsc debug step in
    VS_SO, // vsc debug step out
};

/****************** TAP DANCE STUFF ******************/

enum {
    WSL_H, // wsl helper
    GT_ST, // git status
    GT_SW, // git switch
};

void td_wsl_helper(tap_dance_state_t *state, void *user_data)
{
    (void)user_data;

    if (IS_LAYER_ON(LAYER_GIT))
    {
        switch (state->count)
        {
        case 1:
            SEND_STRING("cd ~/");
            break;
        case 2:
            SEND_STRING("code .");
            tap_code(KC_ENTER);
            break;
        case 3:
            SEND_STRING("explorer.exe .");
            tap_code(KC_ENTER);
            break;
        default:
            break;
        }

    }
    reset_tap_dance(state);
}

void td_git_status(tap_dance_state_t *state, void *user_data)
{
    (void)user_data;

    if (IS_LAYER_ON(LAYER_GIT))
    {
        SEND_STRING("git ");
        switch (state->count)
        {
        default:
        case 1:
            SEND_STRING("status");
            break;
        case 2:
            SEND_STRING("fetch");
            break;
        case 3:
            SEND_STRING("pull");
            break;
        case 4:
            SEND_STRING("fetch && git pull && git submodule update");
            break;
        }
        tap_code(KC_ENTER);
    }
    reset_tap_dance(state);
}

void td_git_switch(tap_dance_state_t *state, void *user_data)
{
    (void)user_data;

    if (IS_LAYER_ON(LAYER_GIT))
    {
        SEND_STRING("git switch ");
        switch (state->count)
        {
        default:
        case 1:
            break;
        case 2:
            SEND_STRING("develop");
            break;
        case 3:
            SEND_STRING("feature/");
            break;
        }
    }
    reset_tap_dance(state);
}

tap_dance_action_t tap_dance_actions[] = {
    [WSL_H] = ACTION_TAP_DANCE_FN(td_wsl_helper),
    [GT_ST] = ACTION_TAP_DANCE_FN(td_git_status),
    [GT_SW] = ACTION_TAP_DANCE_FN(td_git_switch)
};

/****************** END TAP DANCE STUFF ******************/

//  ██████████ ██████   █████   █████████     ███████    ██████████   ██████████ ███████████
// ░░███░░░░░█░░██████ ░░███   ███░░░░░███  ███░░░░░███ ░░███░░░░███ ░░███░░░░░█░░███░░░░░███
//  ░███  █ ░  ░███░███ ░███  ███     ░░░  ███     ░░███ ░███   ░░███ ░███  █ ░  ░███    ░███
//  ░██████    ░███░░███░███ ░███         ░███      ░███ ░███    ░███ ░██████    ░██████████
//  ░███░░█    ░███ ░░██████ ░███         ░███      ░███ ░███    ░███ ░███░░█    ░███░░░░░███
//  ░███ ░   █ ░███  ░░█████ ░░███     ███░░███     ███  ░███    ███  ░███ ░   █ ░███    ░███
//  ██████████ █████  ░░█████ ░░█████████  ░░░███████░   ██████████   ██████████ █████   █████
// ░░░░░░░░░░ ░░░░░    ░░░░░   ░░░░░░░░░     ░░░░░░░    ░░░░░░░░░░   ░░░░░░░░░░ ░░░░░   ░░░░░



enum encoder_modes {
    em_first,
    em_volume = em_first,
    em_scroll,
    em_alttab,
    em_last = em_alttab,
};

static enum encoder_modes current_encoder_mode = em_volume;


void set_encoder_mode(enum encoder_modes new_encoder_mode)
{
    current_encoder_mode = new_encoder_mode;
}

void toggle_encoder_mode(void)
{
    switch (current_encoder_mode)
    {
    case em_last:
        current_encoder_mode = em_first;
        break;
    default:
        ++current_encoder_mode;
        break;
    }
}

/****************** ALT TAB ENCODER STUFF ****************/
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool alt_tab_encoder(uint8_t index, bool clockwise)
{
    if (clockwise)
    {
        if (!is_alt_tab_active)
        {
            is_alt_tab_active = true;
            register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        tap_code16(KC_TAB);
    }
    else
    {
        if (!is_alt_tab_active)
        {
            is_alt_tab_active = true;
            register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        tap_code16(S(KC_TAB));
    }
    return false;
}

/* The encoder_update_user is a function.
 * It'll be called by QMK every time you turn the encoder.
 *
 * The index parameter tells you which encoder was turned. If you only have
 * one encoder, the index will always be zero.
 *
 * The clockwise parameter tells you the direction of the encoder. It'll be
 * true when you turned the encoder clockwise, and false otherwise.
 */
bool encoder_update_user(uint8_t index, bool clockwise)
{
    bool return_val = false;

    if (index == 0)
    {
        switch (current_encoder_mode)
        {
        case em_alttab:
            return_val = alt_tab_encoder(index, clockwise);
            break;
        case em_scroll:
            if (clockwise)
            {
                tap_code16(KC_MS_WH_DOWN);
            }
            else
            {
                tap_code16(KC_MS_WH_UP);
            }
            break;
        case em_volume:
        default:
            // fall back to volume control
            if (clockwise)
            {
                tap_code16(KC_VOLU);
            }
            else
            {
                tap_code16(KC_VOLD);
            }
            break;
        }
    }
    return return_val;
}

bool press_encoder(keyrecord_t *record)
{
    if (record->event.pressed)
    {
        switch (current_encoder_mode)
        {
        default:
        case em_volume:
            tap_code16(KC_MUTE);
            return FINISHED;

        case em_scroll:
            // currently nothing?
            return FINISHED;

        case em_alttab:
            tap_code16(KC_ENTER);
            return FINISHED;
        }
    }
    else
    {
        return CONTINUE;
    }

}

#define ALT_TAB_TIMEOUT_MS (2000)
void matrix_scan_user(void)
{
    if (is_alt_tab_active)
    {
        if (timer_elapsed(alt_tab_timer) > ALT_TAB_TIMEOUT_MS)
        {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}

/****************** END ALT TAB ENCODER STUFF ****************/

#define TH(kc) (LT(0, kc))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE_LAYER_HOME] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,  TH(KC_F12),  KC_PSCR,            ENCDR,
    TH(KC_GRV),   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,    KC_BSPC,          TH(KC_DEL),
        KC_TAB,   KC_Q,     KC_W,     KC_E, TH(KC_R),     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,   KC_BSLS,          TH(KC_HOME),
        QK_LEAD,  KC_A,     KC_S,     KC_D, TH(KC_F),     KC_G,     KC_H,     KC_J,     KC_K,     TH(KC_L), KC_SCLN,  KC_QUOT,             KC_ENT,           TH(KC_END),
        KC_LSFT,            KC_Z, TH(KC_X), TH(KC_C), TH(KC_V),     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,             KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(L_FN),  KC_RCTL,   KC_LEFT,  KC_DOWN,  KC_RGHT),

    // Main work layer currently empty, except for encoder map
    [BASE_LAYER_WORK] = LAYOUT_ansi_82(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

    [LAYER_FN] = LAYOUT_ansi_82(
        QK_MAKE,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,            KC_MUTE,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            KC_PGUP,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,            KC_PGDN,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,            KC_END,
        _______,            _______,  _______,  _______,  FWVER,    _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,    _______,TG(L_GIT),  TG(L_VSC),  _______),

    [LAYER_GIT] = LAYOUT_ansi_82(
        _______,  _______,TD(WSL_H),TD(GT_ST),TD(GT_SW),  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
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
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______)
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
    [BASE_LAYER_HOME]       = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [BASE_LAYER_WORK]       = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [LAYER_FN]              = { ENCODER_CCW_CW(_______, _______)},
    [LAYER_GIT]             = { ENCODER_CCW_CW(_______, _______)},
    [LAYER_VSCODE]          = { ENCODER_CCW_CW(_______, _______)},
    [LAYER_ENCODER_ALTTAB]  = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
};
#endif // ENCODER_MAP_ENABLE

// clang-format on

static bool work_mode = false;

// called by process_record_kb() in v1.c whenever a key is pressed or released
// return true if further processing of the action is required, false if not
// funcs for each based on layer
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (keycode == ENCDR)
    {
        return press_encoder(record);
    }

    // catch enter during leader sequence?

    if (record->event.pressed)
    {
        /*
         * tap & hold
         *
         * if (record->tap.count >= 1) && (record->event.pressed)
         *      --> either return CONTINUE for regular processing
         *      OR perform tap action then return FINISHED (replace regular processing)
         * else record->event.pressed
         *       --> perform hold action
         *      --> return FINISHED (override)
         * else
         *      --> return CONTINUE for regular hold
         */

        // global customs
        switch (keycode)
        {
        case TH(KC_GRV):
            if (!record->tap.count && record->event.pressed)
            {
                SEND_STRING("cd ~/");; // Intercept hold function to send "cd ~/"
                return FINISHED;
            }
            return CONTINUE;

        case TH(KC_X):
            if (!record->tap.count && record->event.pressed)
            {
                tap_code16(C(KC_X)); // Intercept hold function to send Ctrl-X
                return FINISHED;
            }
            return CONTINUE;

        case TH(KC_C):
            if (!record->tap.count && record->event.pressed)
            {
                tap_code16(C(KC_C)); // Intercept hold function to send Ctrl-C
                return FINISHED;
            }
            return CONTINUE;

        case TH(KC_V):
            if (!record->tap.count && record->event.pressed)
            {
                tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
                return FINISHED;
            }
            return CONTINUE;

        case TH(KC_F):
            if (!record->tap.count && record->event.pressed)
            {
                tap_code16(C(KC_F)); // Intercept hold function to send Ctrl-F
                return FINISHED;
            }
            return CONTINUE;

        case TH(KC_DEL):
            if (!record->tap.count && record->event.pressed)
            {
                set_encoder_mode(em_scroll);
                return FINISHED;
            }
            return CONTINUE;

        case TH(KC_HOME):
            if (!record->tap.count && record->event.pressed)
            {
                set_encoder_mode(em_alttab);
                return FINISHED;
            }
            return CONTINUE;

        case TH(KC_END):
            if (!record->tap.count && record->event.pressed)
            {
                set_encoder_mode(em_volume);
                return FINISHED;
            }
            return CONTINUE;

        case TH(KC_L):
            if (!record->tap.count && record->event.pressed)
            {
                SEND_STRING("longview");
                return FINISHED;
            }
            return CONTINUE;

        case TH(KC_R):
            if (!record->tap.count && record->event.pressed)
            {
                SEND_STRING("reliable");
                return FINISHED;
            }
            return CONTINUE;

        case TH(KC_F12):
            if (!record->tap.count && record->event.pressed)
            {
                /* open the R/W props dialog & read the SEL */
                tap_code16(KC_F12);
                tap_code16(KC_TAB);
                tap_code16(KC_TAB);
                SEND_STRING("128");
                tap_code16(KC_TAB);
                tap_code16(KC_TAB);
                tap_code16(KC_1);
                tap_code16(KC_TAB);
                SEND_STRING("2091");

                return FINISHED;
            }
            return CONTINUE;

        // case TH(KC_CAPS):
        //     if (!record->tap.count && record->event.pressed)
        //     {
        //         leader_start(); // Intercept hold function to send LEADER
        //         return FINISHED;
        //     }
        //     return CONTINUE;

        case FWVER:
            SEND_STRING(BSB_VERSION);
            return FINISHED;

        default:
            break;
        }

        if (IS_LAYER_ON(LAYER_VSCODE))
        {
            switch (keycode)
            {
            case VS_ST:
                tap_code16(KC_F10);
                break;
            case VS_SI:
                tap_code16(KC_F11);
                break;
            case VS_SO:
                tap_code16(S(KC_F11));
                break;
            default:
                break;
            }
            return FINISHED;
        }
    }

//exit:
    return CONTINUE;
};


/****************** LEADER STUFF ****************/

void leader_start_user(void)
{
    // Do something when the leader key is pressed
}

void leader_end_user(void)
{
    if (leader_first_key_is(KC_G))
    {
        if (leader_sequence_two_keys(KC_G, KC_F))
        {
            SEND_STRING("git fetch");
        }
        else if (leader_sequence_two_keys(KC_G, KC_S))
        {
            SEND_STRING("git status");
        }
        else if (leader_sequence_two_keys(KC_G, KC_A))
        {
            SEND_STRING("git fetch && git pull && git submodule update");
        }
        else if (leader_sequence_two_keys(KC_G, KC_P))
        {
            SEND_STRING("git pull");
        }
        else if (leader_sequence_two_keys(KC_G, KC_W))
        {
            SEND_STRING("git switch");
        }
        else if (leader_sequence_three_keys(KC_G, KC_W, KC_D))
        {
            SEND_STRING("git switch develop");
        }
        else if (leader_sequence_three_keys(KC_G, KC_W, KC_F))
        {
            SEND_STRING("git switch feature/");
        }
        else if (leader_sequence_three_keys(KC_G, KC_F, KC_P))
        {
            SEND_STRING("git fetch && git pull");
        }
        else if (leader_sequence_three_keys(KC_G, KC_S, KC_U))
        {
            SEND_STRING("git submodule update");
        }
    }
    else
    {
        if (leader_sequence_one_key(KC_C))
        {
            SEND_STRING("code .");
            tap_code(KC_ENTER);
        }
        else if (leader_sequence_one_key(KC_E))
        {
            SEND_STRING("explorer.exe .");
            tap_code(KC_ENTER);
        }
        else if (leader_sequence_one_key(KC_L))
        {
            SEND_STRING("longview");
        }
    }
}

/****************** END LEADER STUFF ****************/

// ██████╗  ██████╗ ██████╗     ███████╗████████╗██╗   ██╗███████╗███████╗
// ██╔══██╗██╔════╝ ██╔══██╗    ██╔════╝╚══██╔══╝██║   ██║██╔════╝██╔════╝
// ██████╔╝██║  ███╗██████╔╝    ███████╗   ██║   ██║   ██║█████╗  █████╗
// ██╔══██╗██║   ██║██╔══██╗    ╚════██║   ██║   ██║   ██║██╔══╝  ██╔══╝
// ██║  ██║╚██████╔╝██████╔╝    ███████║   ██║   ╚██████╔╝██║     ██║
// ╚═╝  ╚═╝ ╚═════╝ ╚═════╝     ╚══════╝   ╚═╝    ╚═════╝ ╚═╝     ╚═╝

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
        set_all_keys_in_layer(LAYER_GIT, led_min, led_max, RGB_GIT_GREEN);

    if (IS_LAYER_ON(LAYER_VSCODE))
        set_all_keys_in_layer(LAYER_VSCODE, led_min, led_max, RGB_VSC_BLUE);

    // turn del purple if alt-tab layer active
    switch (current_encoder_mode)
    {
        case em_volume:
            rgb_matrix_set_color(13, RGB_PURPLE);
            break;
        case em_scroll:
            rgb_matrix_set_color(13, RGB_BLUE);
            break;
        case em_alttab:
            rgb_matrix_set_color(13, RGB_RED);
            break;
        default:
            // do nothing
            break;
    }

//exit:
    return;
}

void do_mode_lighting_all_leds(void)
{
    do_mode_lighting(0, 255);
}

void set_base_work_rgb(void)
{
    rgb_matrix_enable_noeeprom();
    rgb_matrix_set_flags(LED_FLAG_ALL);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_set_color_all(RGB_WHITE);
}

void matrix_init_user(void)
{
    if (work_mode)
    {
        set_base_work_rgb();
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
    // handle layer lighting
    do_mode_lighting_all_leds();

    // return unmodified layer state
    return state;
}

// called by dip_switch_update_kb() in v1.c
bool dip_switch_update_user(uint8_t index, bool val)
{
    //default_layer_set(1UL << (BASE_LAYER_HOME));
    if (index == 0)
    {
        if (work_mode != val)
        {
            work_mode = val;
            if (work_mode)
            {
                //SEND_STRING("WORK_MODE");
                layer_on(BASE_LAYER_WORK);
                layer_on(LAYER_GIT);
                set_base_work_rgb();
            }
            else
            {
                //SEND_STRING("HOME_MODE");
                layer_off(BASE_LAYER_WORK);
                layer_off(LAYER_GIT);
            }
        }
    }
    return FINISHED;
}

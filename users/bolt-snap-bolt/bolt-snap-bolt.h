#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define BSB_VERSION "v2.0.0"

/* Enable compile keycode */
#define ENABLE_COMPILE_KEYCODE

#define TH(kc) (LT(0, kc))

/* LAYER INFO */

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

/* Keycodes */
enum custom_keycodes {
    // see quantum_keycodes.h and keycodes.h
    FWVER = SAFE_RANGE,
    ENCDR,
    VS_ST, // vsc debug step
    VS_SI, // vsc debug step in
    VS_SO, // vsc debug step out
};

enum {
    WSL_H, // wsl helper
    GT_ST, // git status
    GT_SW, // git switch
};

enum encoder_modes {
    em_first,
    em_volume = em_first,
    em_scroll,
    em_alttab,
    em_last = em_alttab,
};

// tap dance stuff
void td_wsl_helper(tap_dance_state_t *state, void *user_data);
void td_git_status(tap_dance_state_t *state, void *user_data);
void td_git_switch(tap_dance_state_t *state, void *user_data);

// encoder stuff
void set_encoder_mode(enum encoder_modes new_encoder_mode);
void toggle_encoder_mode(void);
bool alt_tab_encoder(uint8_t index, bool clockwise);
bool encoder_update_user(uint8_t index, bool clockwise);
bool press_encoder(keyrecord_t *record);
void matrix_scan_user(void);

bool process_record_user(uint16_t keycode, keyrecord_t *record);

// leader stuff
void leader_start_user(void);
void leader_end_user(void);

// rgb stuff
void set_all_keys_in_layer(uint8_t layer, uint8_t led_min, uint8_t led_max, uint8_t red, uint8_t green, uint8_t blue);
void do_mode_lighting(uint8_t led_min, uint8_t led_max);
void do_mode_lighting_all_leds(void);
void set_base_work_rgb(void);
void matrix_init_user(void);
bool rgb_matrix_indicators_user(void);

bool layer_state_cmp_bitmasks(layer_state_t cmp_layer_state, layer_state_t test_layer_state);
layer_state_t layer_state_set_user(layer_state_t state);
bool dip_switch_update_user(uint8_t index, bool val);

#endif

/* keep this here in case I need it:

    [LAYER_UNUSED] = LAYOUT_ansi_82(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

*/

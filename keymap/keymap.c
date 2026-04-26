/* Copyright 2024 – Custom ISO-DE Keymap für AKKO 5075
 *
 * Verwendet das Standard-LAYOUT Makro (ANSI-Physik).
 * [4,1]  = Y (erste Taste nach LShift)
 * [4,10] = -/_ (letzte Taste vor RShift)
 * [5,11] = <>| (nach Fn in Reihe 5)
 * Encoder: CW = lauter, CCW = leiser
 */

#include QMK_KEYBOARD_H
#include "keymap_german.h"

/* ═══ Layers ═════════════════════════════════════════════════════════ */
enum layers { _BL = 0, _FL = 1 };

/* ═══ Custom Keycodes ════════════════════════════════════════════════ */
enum custom_keycodes {
    RGB_BASE_NEXT = SAFE_RANGE,
    RGB_BASE_PREV,
};

/* ═══ Basisfarben-Presets ════════════════════════════════════════════ */
typedef struct { uint8_t r; uint8_t g; uint8_t b; } rgb_color_t;

static const rgb_color_t BASE_COLORS[] = {
    {  0,   0, 255},  /* 0 – Blau      */
    {255, 200,   0},  /* 1 – Gelb      */
    {148,   0, 211},  /* 2 – Violett   */
    {255,  20, 147},  /* 3 – Rosa      */
    {  0, 200, 200},  /* 4 – Türkis    */
    {255,  80,   0},  /* 5 – Orange    */
    { 50, 255,  50},  /* 6 – Hellgrün  */
    {255, 255, 255},  /* 7 – Weiß      */
    {255,   0,   0},  /* 8 – Rot       */
    {  0,   0,   0},  /* 9 – Aus       */
};
#define BASE_COLOR_COUNT ((uint8_t)(sizeof(BASE_COLORS) / sizeof(BASE_COLORS[0])))

/* ═══ EEPROM-Persistenz ══════════════════════════════════════════════ */
typedef union {
    uint32_t raw;
    struct { uint8_t color_idx : 8; };
} user_config_t;

static user_config_t user_config;
static uint8_t       base_color_idx = 0;

void eeconfig_init_user(void) {
    user_config.raw = 0;
    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    if (user_config.color_idx >= BASE_COLOR_COUNT) user_config.color_idx = 0;
    base_color_idx = user_config.color_idx;
}

/* ═════════════════════════════════════════════════════════════════════
 *  Standard LAYOUT Makro – Slot-Reihenfolge (83 Tasten):
 *
 *  Das LAYOUT-Makro (aus keyboard.json generiert) hat folgende
 *  Parameterzuordnung für Reihe 4 und 5:
 *
 *  R4:  k4A=[4,0]  k4B=[4,1]  k4C=[4,2] ... k4K=[4,10]  k4N=[4,13]  k4O=[4,14]  k4P=[4,15]
 *       LShift     Y          X              -/_          RShift      Up           End
 *
 *  R5:  k5A=[5,0]  k5B=[5,1]  k5C=[5,2]  k5F=[5,5]  k5J=[5,9]  k5K=[5,10]  k5L=[5,11]  k5N=[5,13]  k5O=[5,14]  k5P=[5,15]
 *       Ctrl       Win        Alt         Space       AltGr      Fn           <>|          Left        Down        Right
 * ═════════════════════════════════════════════════════════════════════ */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BL] = LAYOUT(
    /* FN-Reihe: ESC F1-F12 DEL [ENC] */
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_MUTE,
    /* R1: ^° 1-0 ß ´` Bksp | Hom */
    DE_CIRC, DE_1,    DE_2,    DE_3,    DE_4,    DE_5,    DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    DE_SS,   DE_ACUT, KC_BSPC,           KC_HOME,
    /* R2: Tab Q-P Ü +* #' | PgU */
    KC_TAB,  DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,    DE_Z,    DE_U,    DE_I,    DE_O,    DE_P,    DE_UDIA, DE_PLUS, DE_HASH,           KC_PGUP,
    /* R3: Caps A-L Ö Ä Enter | PgD */
    KC_CAPS, DE_A,    DE_S,    DE_D,    DE_F,    DE_G,    DE_H,    DE_J,    DE_K,    DE_L,    DE_ODIA, DE_ADIA,          KC_ENT,            KC_PGDN,
    /* R4: LSft Y X C V B N M ,; .: -/_ RSft ↑ End */
    KC_LSFT, DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,    DE_N,    DE_M,    DE_COMM, DE_DOT,  DE_MINS,          KC_RSFT,          KC_UP,   KC_END,
    /* R5: Strg Win Alt Space AltGr Fn <>| ← ↓ → */
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FL), DE_LABK, KC_LEFT, KC_DOWN, KC_RGHT
),

[_FL] = LAYOUT(
    /* FN-Reihe: FN+ESC = Bootloader */
    QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_NEXT,
    /* R1: 1–ß → F1–F12  |  FN+Bksp → EE_CLR */
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  EE_CLR,            KC_HOME,
    /* R2 */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           KC_END,
    /* R3 */
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,           _______,
    /* R4: Y→Prev X→Stop C→Play V→Next B→Mute N→Vol+ M→Vol- */
    _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLU, KC_VOLD, _______, _______, _______,          _______,          RM_VALU, _______,
    /* R5: <>| bleibt, ←→ = Farbe wechseln */
    _______, _______, _______,                            _______,                            _______, _______, _______, RGB_BASE_PREV, RM_VALD, RGB_BASE_NEXT
),
};

/* ═══ Encoder Map ════════════════════════════════════════════════════
 * Hardware-Pin-Reihenfolge auf dem AKKO 5075 ist invertiert,
 * daher: erster Param (CCW) = VOLU, zweiter (CW) = VOLD.
 * Das ergibt physisch: im Uhrzeigersinn = lauter.
 * ════════════════════════════════════════════════════════════════════ */
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BL] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_FL] = { ENCODER_CCW_CW(RM_VALU, RM_VALD) },
};
#endif

/* ═══ Reaktive Events ════════════════════════════════════════════════ */
#define MAX_EVENTS          16
#define REACTIVE_TIMEOUT_MS 500
#define WAVE_RADIUS          80

typedef struct {
    uint8_t  led_idx;
    uint32_t timestamp;
    bool     is_special;
    bool     active;
} key_event_t;

static key_event_t key_events[MAX_EVENTS];
static uint8_t     event_head = 0;

static void record_event(uint8_t led, bool special) {
    key_events[event_head] = (key_event_t){led, timer_read32(), special, true};
    event_head = (event_head + 1) % MAX_EVENTS;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case RGB_BASE_NEXT:
                base_color_idx = (base_color_idx + 1) % BASE_COLOR_COUNT;
                user_config.color_idx = base_color_idx;
                eeconfig_update_user(user_config.raw);
                return false;
            case RGB_BASE_PREV:
                base_color_idx = (base_color_idx == 0) ? (BASE_COLOR_COUNT - 1) : (base_color_idx - 1);
                user_config.color_idx = base_color_idx;
                eeconfig_update_user(user_config.raw);
                return false;
            default: {
                uint8_t led = g_led_config.matrix_co[record->event.key.row][record->event.key.col];
                if (led != NO_LED) {
                    bool special = (keycode == KC_ESC || keycode == KC_ENT || keycode == KC_PENT);
                    record_event(led, special);
                }
                break;
            }
        }
    }
    return true;
}

/* ═══ RGB-Render-Loop ════════════════════════════════════════════════ */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t val    = rgb_matrix_get_val();
    rgb_color_t bc = BASE_COLORS[base_color_idx];
    uint8_t r = (uint8_t)((uint16_t)bc.r * val / 255);
    uint8_t g = (uint8_t)((uint16_t)bc.g * val / 255);
    uint8_t b = (uint8_t)((uint16_t)bc.b * val / 255);

    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, r, g, b);
    }

    for (uint8_t e = 0; e < MAX_EVENTS; e++) {
        if (!key_events[e].active) continue;
        uint32_t elapsed = timer_elapsed32(key_events[e].timestamp);
        if (elapsed > REACTIVE_TIMEOUT_MS) { key_events[e].active = false; continue; }

        uint8_t brightness = (uint8_t)(255 - (elapsed * 255) / REACTIVE_TIMEOUT_MS);
        uint8_t src_led    = key_events[e].led_idx;

        if (key_events[e].is_special) {
            uint8_t src_x      = g_led_config.point[src_led].x;
            uint8_t src_y      = g_led_config.point[src_led].y;
            uint8_t wave_front = (uint8_t)((elapsed * WAVE_RADIUS) / REACTIVE_TIMEOUT_MS);
            uint8_t wave_width = 14;
            for (uint8_t i = led_min; i < led_max; i++) {
                uint8_t  dx   = (uint8_t)abs((int16_t)g_led_config.point[i].x - src_x);
                uint8_t  dy   = (uint8_t)abs((int16_t)g_led_config.point[i].y - src_y);
                uint16_t dist = dx + dy;
                if (dist <= (uint16_t)(wave_front + wave_width) && dist + wave_width >= wave_front) {
                    int16_t diff = (int16_t)wave_front - (int16_t)dist;
                    if (diff < 0) diff = -diff;
                    uint8_t lb = (diff < wave_width) ? (uint8_t)((uint16_t)brightness * (wave_width - diff) / wave_width) : 0;
                    if (lb > 0) rgb_matrix_set_color(i, lb, 0, 0);
                }
            }
        } else {
            if (src_led >= led_min && src_led < led_max) {
                rgb_matrix_set_color(src_led, 0, brightness, 0);
            }
        }
    }
    return false;
}

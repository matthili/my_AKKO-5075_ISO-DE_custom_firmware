/* Custom config für AKKO 5075 – German ISO-DE Layout */

#pragma once

/* ─── Key Chatter / Debouncing ─────────────────────────────────────────
 * 25ms zum sicheren Unterdrücken prellender Schalter.
 * QMK-Standard wäre 5ms.
 */
#define DEBOUNCE 25

/* ─── EEPROM / VIA Dynamic Keymap ──────────────────────────────────────
 * Layer auf 2 begrenzt (Base + Function).
 * WEAR_LEVELING_BACKING_SIZE ist bereits in keyboard.json auf 8192 gesetzt.
 */
#undef  DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 2

/* ─── RGB Matrix ────────────────────────────────────────────────────────
 * Startmodus: Solid Colour (wird durch eigene Render-Funktion ersetzt).
 */
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_DEFAULT_HUE  160
#define RGB_MATRIX_DEFAULT_SAT  255
#define RGB_MATRIX_DEFAULT_VAL  100

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_MAX_KEY_EVENTS 16
#define RGB_MATRIX_REACTIVE_TIMEOUT 600

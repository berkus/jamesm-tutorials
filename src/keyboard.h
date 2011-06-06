#if CHAPTER >= 11
//
// keyboard.h - Defines the interface for the keyboard driver.
//         Also defines needed structures.
//         Based on code from Bran's kernel development tutorials.
//         Rewritten for JamesM's kernel development tutorials.
//

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "common.h"
#include "idt.h"

#define CONTROL 0x1
#define ALT 0x2
#define ALTGR 0x4
#define LSHIFT 0x8
#define RSHIFT 0x10
#define CAPSLOCK 0x20
#define SCROLLLOCK 0x40
#define NUMLOCK 0x80

#define RELEASED_MASK 0x80

/*
 * 8 Bits for control key statuses (1 = set, 0 = not set):
 *
 * 0: control
 * 1: alt
 * 2: alt-gr
 * 3: left shift
 * 4: right shift
 * 5: caps_lock
 * 6: scroll_lock
 * 7: num_lock
 */
typedef uint8_t key_status_t;

typedef struct keymap
{
  // All the chars mapped to their respective scancodes
  uint8_t scancodes[128];
  uint8_t shift_scancodes[128];

  // The function keys mapped to the bit position in the key status map.
  uint8_t control_map[8];

  // The statuses of the control keys, initialized to 0
  key_status_t controls;
} keymap_t;

void init_keyboard_driver();
void switch_layout(keymap_t *layout);
void keyboard_handler(registers_t *regs);

// Returns a character from the keyboard; does not block.
// Returns '\0' if no character is available.
char keyboard_getchar();

#endif
#endif // CHAPTER >= 11

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

/*
 * 8 Bits for control key statuses (1 = set, 2 = not set):
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

typedef struct keymap {
  //All the chars mapped to their respective scancodes
  uint8_t scancodes[128];
  uint8_t shift_scancodes[128];

  //The function keys mapped to the bit position in the key status map.
  uint8_t control_map[8];

  //The statuses of the control keys, initialized to 0
  key_status_t controls;
} keymap_t;

void init_keyboard_driver();
void switch_layout(keymap_t *layout);
interrupt_handler_t keyboard_handler(registers_t regs);

#endif

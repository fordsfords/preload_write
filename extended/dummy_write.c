/* dummy_write.c
 *
 * This code and its documentation is Copyright 2024, 2025 Steven Ford,
 * http://geeky-boy.com and licensed "public domain" style under Creative
 * Commons "CC0": http://creativecommons.org/publicdomain/zero/1.0/
 * To the extent possible under law, the contributors to this project have
 * waived all copyright and related or neighboring rights to this work.
 * In other words, you can use this code for any purpose without any
 * restrictions. This work is published from: United States. The project home
 * is https://github.com/fordsfords/preload_write
 */


#include <stddef.h>
#include "dummy_write.h"


size_t preload_write_call_count() {
  return -1;
}  /* preload_write_call_count */


/* Could define init() and fini(), but no need. */

/* preload_write_test.c - self-test.
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

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
  const char *message1 = "This is test message 1\n";
  const char *message2 = "This is test message 2\n";

  (void)argc; (void)argv;  /* Shut up compiler warnings. */
  write(STDOUT_FILENO, message1, strlen(message1));
  write(STDOUT_FILENO, message2, strlen(message2));

  printf("All messages printed.\n"); fflush(stdout);

  return 0;
}  /* main */

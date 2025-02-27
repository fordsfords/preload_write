/* preload_write.c - example LD Preload library to hook the Unix "write" function.
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

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdatomic.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* Global counter for write calls. */
volatile size_t call_count = 0;

/* Function pointer to the real write function. */
typedef ssize_t (*real_write_t)(int fd, const void *buf, size_t count);
static real_write_t real_write = NULL;
static int stdout_dup;


/* Our hooked version of write. */
ssize_t write(int fd, const void *buf, size_t count) {
  /* Atomically increment the call counter */
  __sync_fetch_and_add(&call_count, 1);
  
  /* Call the real write function */
  return real_write(fd, buf, count);
}  /* write */


/* Optional constructor function run when library is loaded. */
__attribute__((constructor))
static void init(void) {
  /* Get handle to the real write function. Must turn off pedantic because
   * dlsym returns type "(void *)" which ISO C doesn't allow to be cast to
   * a function pointer. But with GNU Linux, you have to. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
  real_write = (real_write_t)dlsym(RTLD_NEXT, "write");
#pragma GCC diagnostic pop
  if (real_write == NULL) {
    fprintf(stderr, "Error: failed to find the real 'write' function\n");
    _exit(1);  /* Avoid calling exit() which might call write() */
  }

  /* Some programs close stdout, but we want to write a message when
   * we exit, so we save a new FD to stdout for later use. */
  stdout_dup = dup(1);
  real_write(stdout_dup, "write hook initialized.\n", 24);
}  /* init */


/* Optional destructor function run when library is unloaded. */
__attribute__((destructor))
static void fini(void) {
  char pbuf[1024];
  sprintf(pbuf, "write hook finalized. Final call count: %zu\n", call_count);
  real_write(stdout_dup, pbuf, strlen(pbuf));
  close(stdout_dup);
}  /* fini */

# preload_write
Example preloaded library to hook Linux's "write()".


## Table of contents

<!-- mdtoc-start -->
&bull; [preload_write](#preload_write)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Table of contents](#table-of-contents)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Introduction](#introduction)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Quick Start](#quick-start)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [The Count Is Wrong](#the-count-is-wrong)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [License](#license)  
<!-- TOC created by '../mdtoc/mdtoc.pl README.md' (see https://github.com/fordsfords/mdtoc) -->
<!-- mdtoc-end -->


## Introduction

Unix lets you "hook" calls to dynamic libraries (.so) so that you can
intercept those calls and perform some work of your own.
This can be useful for debugging,
where you can record information or check for illegal parameters.
Or you can use it to measure performance by taking timestamps.

This project is a reasonably minimal example that shows how to write,
build, and run a preload library.

## Quick Start

Build the preload and the test program using:
```
$ ./bld.sh
```

Run the test program:
```
$ ./tst.sh
```

## The Count Is Wrong

On my Linux system, when I run the test program it prints:
```
write hook finalized. Final call count: 2
```
This properly counts the number of `write()` calls,
but it does NOT count the `printf()`, which also calls `write()`.
Why not?

I'm not sure.
Both Claude.ai and ChatGPT hypothesize that glibc optimizes its
system calls.
Remember that when your code calls `write()`, that itself is a glibc
function that performs the proper kernel trap.
Why should glibc code call that same `write()` function when they can
save an instruction or two by directly trapping to the kernel?

This explanation makes sense, but I didn't feel like proving it.

## License

I want there to be NO barriers to using this code, so I am releasing it to the public domain.
But "public domain" does not have an internationally agreed upon definition, so I use CC0:

Copyright 2024-2025 Steven Ford http://geeky-boy.com and licensed
"public domain" style under
[CC0](http://creativecommons.org/publicdomain/zero/1.0/):
![CC0](https://licensebuttons.net/p/zero/1.0/88x31.png "CC0")

To the extent possible under law, the contributors to this project have
waived all copyright and related or neighboring rights to this work.
In other words, you can use this code for any purpose without any
restrictions.  This work is published from: United States.  The project home
is https://github.com/fordsfords/preload_write

To contact me, Steve Ford, project owner, you can find my email address
at http://geeky-boy.com.  Can't see it?  Keep looking.

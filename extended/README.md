# preload_write/extended
Example preloaded library to hook Linux's "write()"
and also offers extended capability.


## Table of contents

<!-- mdtoc-start -->
&bull; [preload_write/extended](#preload_writeextended)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Table of contents](#table-of-contents)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Introduction](#introduction)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Quick Start](#quick-start)  
<!-- TOC created by '../mdtoc/mdtoc.pl ./extended/README.md' (see https://github.com/fordsfords/mdtoc) -->
<!-- mdtoc-end -->


## Introduction

Most usages of a preload library is to hook functions for
applications that "don't know" they are being hooked.
The application should simply use its desired APIs,
and the preload hooks the ones you want it to.

But there can be situations where an application specifically wants to use
the preload and access extended capabilities.
For example, the Onload network driver can simply be preloaded to hook
socket calls, but it can also be more fully integrated into an application
that wasnts to call Onload-specific functions.

But this presents a problem.
The application explicitly call library-specific APIs,
which means it needs to link with it, which includes it as a dependency.
This doesn't allow it to be "preloaded", which means it can't hook the
intended calls.

My solution is to create a second "dummy" library.
This presents the desired library-specific APIs,
but the dummy library's implementation is essentially empty.
It just returns an indication that the function cannot be performed.
Thus, the appliation links with the dummy library and it gets loaded
normally when the application loads.

Then, the preload library hooks *those* functions.
Thus, instead of calling the dummy versions,
the application ends up calling the hooked versions.

Regular applications don't need to reference the dummy library at all.
They can just use the normal APIs, and the preload will hook them.
But for an application that want to access the extended functions,
it links with the dummy library, and the preload will hook them too.

## Quick Start

Build the preload and the test program using:
```
$ ./bld.sh
```

Run the test program:
```
$ ./tst.sh
```

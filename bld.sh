#!/bin/sh
# bld.sh

for F in *.md; do :
  if egrep "<!-- mdtoc-start -->" $F >/dev/null; then :
    # Update doc table of contents (see https://github.com/fordsfords/mdtoc).
    if which mdtoc.pl >/dev/null 2>&1; then LANG=C mdtoc.pl -b "" $F;
    elif [ -x ../mdtoc/mdtoc.pl ]; then LANG=C ../mdtoc/mdtoc.pl -b "" $F;
    else echo "FYI: mdtoc.pl not found; Skipping doc build"; echo ""; fi
  fi
done

echo "Building code"

rm -f err_test example1 example2

gcc $* -std=c99 -pedantic -Wall -Wextra -Werror -g -fPIC -o libpreload_write.so preload_write.c -shared -ldl
if [ $? -ne 0 ]; then exit 1; fi

gcc $* -std=c99 -pedantic -Wall -Wextra -Werror -g -o preload_write_test preload_write_test.c
if [ $? -ne 0 ]; then exit 1; fi

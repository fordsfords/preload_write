#!/bin/sh
# bld.sh

echo "Building code"

rm -f err_test example1 example2

gcc $* -std=c99 -pedantic -Wall -Wextra -Werror -g -fPIC -o libpreload_write.so preload_write.c -shared -ldl
if [ $? -ne 0 ]; then exit 1; fi

gcc $* -std=c99 -pedantic -Wall -Wextra -Werror -g -fPIC -o libdummy_write.so dummy_write.c -shared -ldl
if [ $? -ne 0 ]; then exit 1; fi

gcc $* -std=c99 -pedantic -Wall -Wextra -Werror -g -o preload_write_test preload_write_test.c -L . -l dummy_write
if [ $? -ne 0 ]; then exit 1; fi

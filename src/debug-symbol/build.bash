#!/bin/bash

# generate executable files, -g means have debug info
gcc -O0 foo.c -o foo.nog
gcc -O0 foo.c -g -o  foo.g

# copy files, whose debug-info will be stripped
cp foo.nog foo.nog.strip
cp foo.g foo.g.strip

# strip debug info 
objcopy --strip-debug foo.nog.strip 
objcopy --strip-debug foo.g.strip 


# generate debug-info file
objcopy --only-keep-debug foo.nog foo.nog.debug
objcopy --only-keep-debug foo.g foo.g.debug

# add debug link
# foo.g.strip-all.with-debug-link have gnu-debuglink, foo.g.strip-all does not
objcopy  --strip-all foo.g foo.g.strip-all
cp  foo.g.strip-all  foo.g.strip-all.with-debug-link
objcopy --add-gnu-debuglink=foo.g.debug foo.g.strip-all.with-debug-link




# dump sections to file
objdump -s foo.g > foo.g.s
objdump -s foo.nog > foo.nog.s
objdump -s foo.g.strip-all > foo.g.strip-all.s
objdump -s foo.g.strip-all.with-debug-link > foo.g.strip-all.with-debug-link.s

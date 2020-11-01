#! /bin/bash

FILES="CMakeCache.txt \
   CMakeFiles \
   cmake_install.cmake \
   Makefile \
   *~"

echo "This command will remove the following files and dirs:"
#echo "${FILES}"
for i in ${FILES} ; do echo "$i" ;done
echo ""
echo "Cleaning CMAKE files finished!"
rm -rf $FILES
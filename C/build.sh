
# usage: ./build.sh {filename.c} e.g. ./build.sh 16_power_digit_sum.c
gcc -ggdb $1 -o build/main

if [ $? -eq 0 ]; then
  ./build/main
  exit $?
fi

exit $?

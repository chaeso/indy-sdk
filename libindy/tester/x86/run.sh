#/bin/sh

rm r
gcc -o r main.c -lindy -L../../target/debug/
chmod +x r
./r

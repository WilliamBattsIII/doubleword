cd src/emu/src

gcc main.c cpu.c util.c mem.c -o ../../../bin/emulator

cd ../../..

./bin/emulator
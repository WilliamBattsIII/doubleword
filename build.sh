cmd=$(gcc src/emu/src/main.c src/emu/src/cpu.c src/emu/src/util.c -o bin/emulator)

if [ cmd != 0 ]; then
    ./bin/emulator
else
    echo "Compilation Failed!"
fi
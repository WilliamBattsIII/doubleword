#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "cpu.h"

int main(void) { // TODO: program arguments to change size at runtime
    printf("%d\n", CPF);
    bool running = true;
    emu_loop();
    return 0;
}

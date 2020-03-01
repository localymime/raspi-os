#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <kernel/mem.h>
#include <kernel/atag.h>
#include <kernel/kerio.h>
#include <kernel/gpu.h>
#include <kernel/interrupts.h>
#include <kernel/timer.h>
#include <kernel/process.h>
#include <kernel/mutex.h>
#include <common/stdlib.h>

mutex_t test_mut;

void test(void) {
    int i = 0;
    while (1) {
        printf("test %d\n", i++);
        udelay(1000000);
    }
}



void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    int i = 0;
    // Declare as unused
    (void) r0;
    (void) r1;
    (void) atags;

    mem_init((atag_t *)atags);
    gpu_init();
    printf("CPU = arm1176jzf-s\n");
    printf("DIRECTIVES = -D MODEL_1\n");
    interrupts_init();
    printf("ARCHDIR = model1\n");
    printf("KERNEL = kernel.elf\n");
    timer_init();
    process_init();
    printf("DONE\n");

    puts("Welcome To mimenet!\n");

    // mutex_init(&test_mut);
    create_kernel_thread(test, "TEST", 4);

    while (1) {
        printf("main %d\n", i++);
        udelay(1000000);
    }
}
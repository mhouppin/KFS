#include "kernel/kernel.h"
#include "kernel/console.h"

void kernel_init(void)
{
    // Initialize the console (with basic cpu terminal)
    console_system_driver_load(&console_vga_register);

    // Initialize the memory manager

    // Initialize the event/interrupts manager

    // Initialize the process manager
}

void kernel_main(void)
{
    kernel_init();

    // Initialize modules manager

    // Initialize the device

    // Initialize the file system

    // Start init process

}

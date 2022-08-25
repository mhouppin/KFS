#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "kstring.h"
#include "vga_term.h"

// Check if the compiler thinks we are targeting the wrong operating system.
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

// This kernel will only work for the 32-bit ix86 targets.
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
void kernel_main(void) 
{
	vga_init();
	vga_writestr("Hello, World!\n\nWelcome to VaultOS v0.1.0\n\n");
    vga_writestr("42\n");
}

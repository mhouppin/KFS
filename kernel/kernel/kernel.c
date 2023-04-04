#include <stdio.h>

#include <kernel/kinit.h>
#include <kernel/kversion.h>
#include <kernel/vga_tty.h>

void kernel_main(void)
{
	vga_init();
    printf("[LOG] Initializing GDT segments...\n");
    gdt_init();
    printf("\nHello, World!\n\nWelcome to VaultOS %d.%d.%d%s\n",
        __VAULT_MAJOR_VER,
        __VAULT_MINOR_VER,
        __VAULT_PATCH_VER,
        __VAULT_PRERELEASE_VER);
    printf("%d", 42);
}

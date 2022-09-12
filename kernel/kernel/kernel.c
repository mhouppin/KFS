#include <stdio.h>

#include <kernel/kinit.h>
#include <kernel/kversion.h>
#include <kernel/vga_tty.h>

void kernel_main(void)
{
	vga_init();
    gdt_init();
    printf("Hello, World!\n\nWelcome to VaultOS %d.%d.%d%s\n\n42\n",
        __VAULT_MAJOR_VER,
        __VAULT_MINOR_VER,
        __VAULT_PATCH_VER,
        __VAULT_PRERELEASE_VER);
}

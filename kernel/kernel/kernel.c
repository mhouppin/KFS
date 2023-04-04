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
    printf("%d\n", 42);
    printf("Bonus:\n");
    for (size_t i = 0; i < 16; i++)
    {
        vga_setcolor(vga_entry_color(0, i));
        printf(" ");
    }
    printf("\n");
    for (size_t i = 0; i < 16; i++)
    {
        vga_setcolor(vga_entry_color(i, 0));
        printf("H");
    }
    

}
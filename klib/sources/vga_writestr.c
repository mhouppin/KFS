#include "kstring.h"
#include "vga_term.h"

void vga_writestr(const char* data) 
{
    vga_writebuf(data, kstrlen(data));
}

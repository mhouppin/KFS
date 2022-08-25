#include "vga_term.h"
 
void vga_writebuf(const void* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		vga_write(((const char *)data)[i]);
}

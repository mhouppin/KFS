section .data
gdt_buffer:
    dw 0
    dd 0

section .text
    global gdt_configure

gdt_configure:
    mov ax, [esp + 8]
    mov [gdt_buffer], ax
    mov eax, [esp + 4]
    mov [gdt_buffer + 2], eax
    lgdt [gdt_buffer]
    ret

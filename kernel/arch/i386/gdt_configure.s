section .data
gdt_buffer:
    dw 0
    dd 0

section .text
    global gdt_configure

gdt_configure:
    mov ax, [esp + 8]
    lea eax, [eax * 8 - 1]
    mov [gdt_buffer], ax
    mov eax, [esp + 4]
    mov [gdt_buffer + 2], eax
    lgdt [gdt_buffer]

; Now set segment register values.
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ax, 0x18
    mov ss, ax

; Note that for setting CS, we perform a far jump to the required segment,
; directly after the jump instruction.
    jmp 0x08:.reload_cs

.reload_cs:
    ret

section .data
global x, t1
x: dd 0
t1: dd 0
t10: dd 0
t2: dd 0
t3: dd 0
t4: dd 0
t5: dd 0
t6: dd 0
t7: dd 0
t8: dd 0
t9: dd 0

section .text
global _start

_start:

_pow:
    ; Input: eax = base, ecx = exponent
    ; Output: eax = result
    push ebx
    mov ebx, eax
    mov eax, 1
    cmp ecx, 0
    je .pow_end
.pow_loop:
    imul eax, ebx
    dec ecx
    jnz .pow_loop
.pow_end:
    pop ebx
    ret

    ; t1 = 1 + x
    mov eax, 1
    add eax, [x]
    mov [t1], eax

    ; t2 = x ^ 2
    mov eax, [x]
    mov ecx, 2
    call _pow
    mov [t2], eax

    ; t3 = t2 / 2
    mov eax, [t2]
    cdq
    mov ebx, 2
    idiv ebx
    mov [t3], eax

    ; t4 = t1 + t3
    mov eax, [t1]
    add eax, [t3]
    mov [t4], eax

    ; t5 = x ^ 3
    mov eax, [x]
    mov ecx, 3
    call _pow
    mov [t5], eax

    ; t6 = t5 / 6
    mov eax, [t5]
    cdq
    mov ebx, 6
    idiv ebx
    mov [t6], eax

    ; t7 = t4 + t6
    mov eax, [t4]
    add eax, [t6]
    mov [t7], eax

    ; t8 = x ^ 4
    mov eax, [x]
    mov ecx, 4
    call _pow
    mov [t8], eax

    ; t9 = t8 / 24
    mov eax, [t8]
    cdq
    mov ebx, 24
    idiv ebx
    mov [t9], eax

    ; t10 = t7 + t9
    mov eax, [t7]
    add eax, [t9]
    mov [t10], eax

    ; Exit program
    mov eax, 1
    xor ebx, ebx
    int 0x80

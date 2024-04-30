section .text
    global  ft_strcmp

ft_strcmp:
    push    rbp
    mov     rbp, rsp

    push    rdi ; s1
    push    rsi ; s2
    push    rbx

    xor     rcx, rcx
    .loop:
    mov     al, [rdi + rcx]
    test    al, al
    je      .loop_end
    mov     bl, [rsi + rcx]
    test    bl, bl
    je      .loop_end
    cmp     al, bl
    jne     .loop_end
    inc     rcx
    jmp     .loop
    .loop_end:

    xor     rax, rax
    mov     al, [rdi + rcx]
    sub     al, [rsi + rcx]

    pop     rbx
    pop     rsi
    pop     rdi

    pop     rbp
    ret

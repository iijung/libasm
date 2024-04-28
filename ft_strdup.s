section .text
    global  ft_strdup
    extern  malloc

ft_strdup:
    push    rbp
    mov     rbp, rsp

    push    rdi ; s
    push    rsi ;
    push    rbx
    push    rcx

    xor     rax, rax
    mov     rcx, -1
    repne   scasb
    mov     rbx, -1
    sub     rbx, rcx

    ; rax = malloc(rdi)
    mov     rdi, rbx
    call    malloc wrt ..plt
    cmp     rax, 0
    je      .copy_end
    mov     rdi, rax
    mov     rsi, [rbp - 8]
    mov     rcx, rbx
    rep     movsb
    .copy_end:

    pop     rcx
    pop     rbx
    pop     rsi
    pop     rdi

    pop     rbp
    ret

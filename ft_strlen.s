section .text
    global  ft_strlen

ft_strlen:
    push    rbp
    mov     rbp, rsp

    push    rdi
    push    rcx

    xor     rax, rax
    mov     rcx, -1
    repne   scasb
    mov     rax, -1
    sub     rax, rcx
    dec     rax

    pop     rcx
    pop     rdi

    pop     rbp
    ret

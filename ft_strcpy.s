section .text
    global  ft_strcpy

ft_strcpy:
    push    rbp
    mov     rbp, rsp

    push    rdi ; dest
    push    rsi ; src
    push    rcx

    xor     rax, rax
    mov     rcx, -1
    mov     rdi, rsi
    repne   scasb
    mov     rax, -1
    sub     rax, rcx

    mov     rcx, rax
    mov     rdi, [rbp - 8]
    mov     rsi, [rbp - 16]
    rep     movsb
    mov     rax, [rbp - 8]

    pop     rcx
    pop     rsi
    pop     rdi

    pop     rbp
    ret

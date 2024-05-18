%include    "libasm.inc"

section .text
    global  ft_strcmp

ft_strcmp:
    procedure_start

    xor     rcx, rcx
    .loop:
    mov     al, [rdi + rcx]
    mov     bl, [rsi + rcx]
    test    al, al
    je      .negative
    test    bl, bl
    je      .positive
    cmp     al, bl
    jc      .negative
    jne     .positive
    inc     rcx
    jmp     .loop

    .negative:
    sub     bl, al
    movzx   rax, bl
    neg     rax
    procedure_end

    .positive:
    sub     al, bl
    movzx   rax, al
    procedure_end

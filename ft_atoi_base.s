%ifdef __LINUX__
    %define ERRNO_SYM   __errno_location
    %define ERRNO_CALL  __errno_location wrt ..plt
%else
    %define ERRNO_SYM   ___error
    %define ERRNO_CALL  ___error
%endif

section .rodata
    whitespace: db 9, 10, 11, 12, 13, 32, 0
    sign: db '+', '-', 0

section .text
    global  ft_atoi_base
    global  _ft_atoi_base
    extern  ERRNO_SYM

;===============================================================================
; macro
;===============================================================================

%macro  procedure_start 0
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    r12
    push    r13
    push    r14
    push    r15
%endmacro

%macro  procedure_end 0
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     rbx
    pop     rbp
    ret
%endmacro

;===============================================================================
; char *strchr(const char *s, int c)
;===============================================================================

ft_strchr:
    procedure_start

    ; maximum count
    push    rdi       ; save rdi
    mov     rcx, -1
    xor     rax, rax
    repne   scasb
    not     rcx

    ; compare
    pop     rdi       ; restore rdi
    movzx   rax, sil
    repne   scasb

    ; calculate return value
    dec     rdi
    xor     rax, rax
    test    rcx, rcx
    jz      .not_found
    mov     rax, rdi
    .not_found:

    procedure_end

;===============================================================================
; int   _base_len(char *base)
;===============================================================================

base_len:
    procedure_start

    mov     rbx, rdi
    xor     rcx, rcx
    .loop:
        cmp byte [rbx + rcx], 0
        je  .loop_next

        ; if whitespace, fail
        push    rcx
        lea     rdi, [rel whitespace]
        movzx   rsi, byte [rbx + rcx]
        call    ft_strchr
        pop     rcx
        test    rax, rax
        jnz     .loop_fail
        
        ; if duplicate, fail
        push    rcx
        lea     rdi, [rbx + rcx + 1]
        movzx   rsi, byte [rbx + rcx]
        call    ft_strchr
        pop     rcx
        test    rax, rax
        jnz     .loop_fail

        inc     rcx
        jmp     .loop
    .loop_fail:
    xor     rcx, rcx
    .loop_next:
    mov     rax, rcx

    procedure_end

;===============================================================================
; extern int ft_atoi_base(char *str, char *base);
;===============================================================================

ft_atoi_base:
_ft_atoi_base:
    procedure_start

    mov     rbx, rdi ; save str
    mov     r12, rsi ; save base
    xor     r13, r13 ; base length
    xor     r14, r14 ; minus flag (0: positive, 1: negative)
    xor     r15, r15 ; accumulate result

    ; check base
    mov     rdi, r12
    call    base_len
    cmp     rax, 2
    jle     .einval
    mov     r13, rax
  
    ; skip whitespace of str
    .skip_whitespace:
        ; if null, skip
        cmp     byte [rbx], 0
        je      .skip_whitespace_end

        ; if whitespace, skip
        lea     rdi, [rel whitespace]
        movzx   rsi, byte [rbx]
        call    ft_strchr
        test    rax, rax
        jz      .skip_whitespace_end

        inc     rbx
        jmp     .skip_whitespace
    .skip_whitespace_end:

    ; minus flag
    lea     rdi, [rel sign]
    movzx   rsi, byte [rbx]
    call    ft_strchr
    test    rax, rax
    jz      .no_sign
    inc     rbx
    cmp     [rbx - 1], byte '-'
    sete    r14b
    .no_sign:

    ; calculate result
    .accumulate:
        cmp     byte [rbx], 0
        je      .accumulate_end

        mov     rdi, r12
        movzx   rsi, byte [rbx]
        call    ft_strchr
        test    rax, rax
        je      .accumulate_end

        inc     rbx           ; ++rbx
        sub     rax, r12      ; rax = index
        imul    r15, r13      ; r15 *= base_len

        test    r14, r14
        jz      .positive
        .negative:
            sub     r15, rax  ; r15 -= index
            cmp     r15, 0xffffffff80000000
            jge     .accumulate
            mov     rax, 0x80000000
            jmp     .erange

        .positive:
            add     r15, rax  ; r15 += index
            cmp     r15, 0x7fffffff
            jle     .accumulate
            mov     rax, 0x7fffffff
            jmp     .erange
    .accumulate_end:
    mov     rax, r15
    procedure_end

    .einval:
    call    ERRNO_CALL
    mov     [rax], byte 22 ; EINVAL
    xor     rax, rax
    procedure_end

    .erange:
    push    rax
    call    ERRNO_CALL
    mov     [rax], byte 34 ; ERANGE
    pop     rax
    procedure_end

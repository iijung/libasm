%include    "libasm.inc"

section .text
    global  ft_list_push_front
    extern  ERRNO_LOCATION
    extern  malloc

;===============================================================================
; extern t_list *ft_create_elem(void *data);
;===============================================================================

ft_create_elem:
    procedure_start
    push    rdi
    mov     rdi, t_list_size
    symbol_call malloc
    pop     rdi
    test    rax, rax
    jz      .enomem
    mov     qword [rax + t_list.data], rdi
    mov     qword [rax + t_list.next], 0
    procedure_end

    .enomem:
    symbol_call ERRNO_LOCATION
    mov     [rax], byte 12 ; ENOMEM
    xor     rax, rax
    procedure_end

;===============================================================================
; extern void ft_list_push_front(t_list **begin_list, void *data);
;===============================================================================

ft_list_push_front:
    procedure_start

    ; if begin_list == NULL, return
    test    rdi, rdi
    jnz     .create_elem
    procedure_end

    ; if ft_create_elem is fail, return
    .create_elem:
    push    rdi
    mov     rdi, rsi
    call    ft_create_elem
    pop     rdi
    test    rax, rax
    jnz     .initial
    procedure_end

    .initial:
    mov     rsi, [rdi]
    mov     qword [rax + t_list.next], rsi
    mov     qword [rdi], rax
    procedure_end

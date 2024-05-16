%include    "libasm.inc"

%ifdef __LINUX__
    %define ERRNO_SYM   __errno_location
    %define ERRNO_CALL  __errno_location wrt ..plt
%else
    %define ERRNO_SYM   __error
    %define ERRNO_CALL  __error
%endif

section .bss
    head: resb t_list_size
    cmp:  resq 1

section .text
    global  ft_list_sort
    extern  ft_list_size
    extern  ERRNO_SYM

;===============================================================================
; static t_list *merge(t_list *left, t_list *right)
;===============================================================================

merge:
    procedure_start

    mov     r12, rdi  ; left
    mov     r13, rsi  ; right

    ; curr = &head
    lea     rbx, [rel head]
    .loop:
        ; if (left == NULL) curr->next = right
        .is_left_null:
        test    r12, r12
        jnz     .is_right_null
        mov     qword [rbx + t_list.next], r13
        jmp     .loop_end

        ; if (right == NULL) curr->next = left
        .is_right_null:
        test    r13, r13
        jnz     .compare_both
        mov     qword [rbx + t_list.next], r12
        jmp     .loop_end

        .compare_both:
        mov     rax, [rel cmp]
        mov     rdi, qword [r12 + t_list.data]
        mov     rsi, qword [r13 + t_list.data]
        safe_call rax

        test    eax, eax
        jg      .get_right
        .get_left:
            mov   qword [rbx + t_list.next], r12
            mov   r12, qword [r12 + t_list.next]
            jmp   .next
        .get_right:
            mov   qword [rbx + t_list.next], r13
            mov   r13, qword [r13 + t_list.next]
            jmp   .next
        .next:
        mov     rbx, qword [rbx + t_list.next]
        mov     qword [rbx + t_list.next], 0
        jmp     .loop
    .loop_end:
    lea     rax, [rel head]
    mov     rax, qword [rax + t_list.next]
    procedure_end

;===============================================================================
; static t_list *divide(t_list *head, int count)
;===============================================================================

divide:
    cmp     rsi, 2
    jge     .start
    mov     rax, rdi
    ret

    .start:
    procedure_start

    mov     rbx, rdi  ; head
    mov     r12, rsi  ; count
    mov     r13, rsi  ; mid = count / 2
    shr     r13, 1

    ; left = head
    mov     r14, rbx
    mov     rcx, r13
    dec     rcx
    ; left = left->next
    test    rcx, rcx
    jz      .left_next_end
    .left_next:
        test    r14, r14
        jz      .left_next_end
        mov r14, qword [r14 + t_list.next]
        loop .left_next
    .left_next_end:
 
    ; right = left->next
    mov     r15, qword [r14 + t_list.next]
    mov     qword [r14 + t_list.next], 0

    ; left = divide(head, mid)
    mov     rdi, rbx
    mov     rsi, r13
    call    divide
    mov     r14, rax

    ; right = divide(right, count - mid)
    mov     rdi, r15
    mov     rsi, r12
    sub     rsi, r13
    call    divide
    mov     r15, rax

    ; merge(left, right)
    mov     rdi, r14
    mov     rsi, r15
    call    merge

    procedure_end

;===============================================================================
; extern void ft_list_sort(t_list **begin_list, int (*cmp)());
;===============================================================================

ft_list_sort:
    ; if rdi == NULL || rsi == NULL, return
    test    rdi, rsi
    jnz     .start
    ret

    .start:
    procedure_start
    mov     rbx, rdi       ; begin_list
    lea     rax, [rel cmp] ; cmp = cmp
    mov     [rax], rsi

    ; rax = ft_list_size(*begin_list)
    mov     rdi, [rbx]
    call    ft_list_size

    ; rax = divide(*begin_list, ft_list_size(*begin_list))
    mov     rdi, [rbx]
    mov     rsi, rax
    call    divide
  
    ; *head = rax 
    mov   [rbx], rax
    procedure_end

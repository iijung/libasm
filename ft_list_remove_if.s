%include    "libasm.inc"

section .bss
    head: resb t_list_size

section .text
    global  ft_list_remove_if
    extern  free

;===============================================================================
; static t_list *delete_node(t_list *node, void (*free_fct)(void *));
;===============================================================================

delete_node:
    procedure_start

    mov     rbx, rdi                        ; node
    mov     r12, qword [rbx + t_list.next]  ; node->next

    test    rsi, rsi
    jz      .node

    .data:
    mov   rdi, qword [rbx + t_list.data]
    safe_call rsi

    .node:
    mov   qword [rbx + t_list.data], 0
    mov   rdi, rbx
    mov   rbx, qword [rbx + t_list.next]
    call  free

    mov     rax, r12
    procedure_end

;===============================================================================
; extern void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
;===============================================================================

ft_list_remove_if:
    ; if begin_list == NULL || cmp == NULL, return
    test    rdi, rdx
    jnz     .start
    ret

    .start:
    procedure_start
 
    mov     r12, rdi ; begin_list
    mov     r13, rsi ; data_ref
    mov     r14, rdx ; cmp
    mov     r15, rcx ; free_fct

    ; curr = &head
    lea     rbx, [rel head]

    ; curr->next = *begin_list
    mov     rax, [r12]
    mov     qword [rbx + t_list.next], rax
    .loop:
        ; if (curr == NULL) break
        test    rbx, rbx
        jz      .loop_end

        ; if ((next = curr->next) == NULL) break
        mov     rdx, qword [rbx + t_list.next]
        test    rdx, rdx
        jz      .loop_end

        ; if (cmp(next->data, ref) != 0) continue
        mov     rdi, qword [rdx + t_list.data]
        mov     rsi, r13
        safe_call r14
        test    eax, eax
        jz      .delete

        .continue:
        mov     rbx, qword [rbx + t_list.next]  ; curr = curr->next
        jmp     .loop

        .delete:
        mov     rdi, qword [rbx + t_list.next]
        mov     rsi, r15
        call    delete_node
        mov     qword [rbx + t_list.next], rax  ; curr->next = next->next
        jmp     .loop
    .loop_end:

    lea   rax, [rel head]
    mov   rax, qword [rax + t_list.next]
    mov   [r12], rax
    procedure_end

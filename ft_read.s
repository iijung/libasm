%ifdef __LINUX__
    SYS_READ    equ 0
    %define ERRNO_SYM   __errno_location
    %define ERRNO_CALL  __errno_location wrt ..plt
%else
    SYS_READ    equ 0x2000003
    %define ERRNO_SYM   ___error
    %define ERRNO_CALL  ___error
%endif

section .text
    global  ft_read
    global  _ft_read
    extern  ERRNO_SYM

;===============================================================================
; macro
;===============================================================================

%macro  safe_call 1
    push    rbp
    mov     rbp, rsp
    sub     rsp, 8
    and     rsp, -16
    call    %1
    leave
%endmacro

;===============================================================================
; ssize_t ft_read(int fildes, void *buf, size_t nbyte);
;===============================================================================

ft_read:
_ft_read:
    mov     rax, SYS_READ
    syscall
    cmp     rax, 0
    jl     .errno
    ret

    .errno:
    neg     rax
    mov     rdx, rax
    safe_call ERRNO_CALL
    mov     [rax], rdx
    mov     rax, -1
    ret

%include    "libasm.inc"

%ifdef __LINUX__
    SYS_WRITE   equ 1
    %define ERRNO_SYM   __errno_location
    %define ERRNO_CALL  __errno_location wrt ..plt
%else
    SYS_WRITE   equ 0x2000004
    %define ERRNO_SYM   __error
    %define ERRNO_CALL  __error
%endif

section .text
    global  ft_write
    extern  ERRNO_SYM

;===============================================================================
; ssize_t ft_write(int fildes, const void *buf, size_t nbytes);
;===============================================================================

ft_write:
    mov     rax, SYS_WRITE
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

%ifdef __LINUX__
    SYS_WRITE   equ 1
    %define ERRNO_SYM   __errno_location
    %define ERRNO_CALL  __errno_location wrt ..plt
%else
    SYS_WRITE   equ 0x2000004
    %define ERRNO_SYM   ___error
    %define ERRNO_CALL  ___error
%endif

section .text
    global  ft_write
    global  _ft_write
    extern  ERRNO_SYM

ft_write:
_ft_write:
    mov     rax, SYS_WRITE
    syscall
    cmp     rax, 0
    jl     .errno
    ret

    .errno:
    neg     rax
    mov     rdx, rax
    call    ERRNO_CALL
    mov     [rax], rdx
    mov     rax, -1
    ret

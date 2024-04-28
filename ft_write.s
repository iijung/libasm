%ifdef __LINUX__
    SYS_WRITE   equ 1
    %define ERRNO   __errno_location
%else
    SYS_WRITE   equ 0x2000004
    %define ERRNO   ___error
%endif

section .text
    global  ft_write
    extern  __errno_location

ft_write:
    mov     rax, SYS_WRITE
    syscall
    cmp     rax, 0
    jl     .errno
    ret

.errno:
    neg     rax
    mov     rdx, rax
    call    ERRNO wrt ..plt
    mov     [rax], rdx
    mov     rax, -1
    ret

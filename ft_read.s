%ifdef __LINUX__
    SYS_READ    equ 0
    %define ERRNO   __errno_location
%else
    SYS_READ    equ 0x2000000
    %define ERRNO   ___error
%endif

section .text
    global  ft_read
    extern  __errno_location

ft_read:
    mov     rax, SYS_READ
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

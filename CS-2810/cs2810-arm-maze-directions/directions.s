.global directions, _start

.equ    sys_write, 4
.equ    stdout, 1
.equ    sys_exit, 1
.equ    err_write, 1

.text

_start:
        ldr     r0, =4
        bl      directions
        ldr     r7, =sys_exit
        svc     #0


.func directions
directions:
        # r0 is the memory location of the list of directions in binary
        # is r1 the count of the list?
        push    {r7, r8, r9, lr}
        ldr     r1, =left
        ldr     r2, =left_len
        ldr     r2, [r2]
        ldr     r3, =0
        ldr     r7, =sys_write
        ldr     r8, =dirs
        ldr     r9, =dirs_len
        ldr     r9, [r9]
        mov     r12, r0

        # compare the two registers
2:      cmp     r3, r12
        ldr     r0, =stdout
        bge     3f
        svc     #0
        tst     r0, r0
        bge     1f
        ldr     r0, =err_write
        pop     {r7, pc}
1:      add     r3, r3, #1
        b       2b


3:      ldr     r0, =0
        pop     {r7, r8, r9, pc}
.endfunc


.data
left:           .ascii "left\n"
left_len:       .word (.-left)
right:          .ascii "right\n"
right_len:      .word (.-right)
up:             .ascii "up\n"
up_len:         .word (.-up)
down:           .ascii "down\n"
down_len:       .word (.-down)
start:          .ascii "go to the start\n"
start_len:      .word (.-start)
finish:         .ascii "you are finished!\n"
finish_len:     .word (.-finish)
dirs:           .word 4, 0, 1, 2, 3, 5
dirs_len:       .word 6
test:           .word 0
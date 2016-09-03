
bal _start, main

.equ	stdout, 1
.equ	sys_exit, 1
.equ	sys_write, 4
.equ    err_write, 57

.data
msg:	.ascii "Hello, world\n"
.equ	msg_len, .-msg


.text

_start:
        bl      main
        ldr     r7, =sys_exit
        svc     #0

.func main
main:
        push    {r7,lr}

	@ write(stdout, msg, len(msg))
	ldr	r0, =stdout
	ldr	r1, =msg
	ldr	r2, =msg_len
	ldr	r7, =sys_write
	svc	#0

        tst     r0, r0
        bge     .quit
        ldr     r0, =err_write
        pop     {r7,pc}

.quit:
	@ exit(0)
	ldr	r0, =0
        pop     {r7,pc}
.endfunc

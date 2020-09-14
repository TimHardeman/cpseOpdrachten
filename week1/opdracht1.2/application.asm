.cpu cortex-m0
.text
.align 2
.global application

application:
	ldr r0, =msg
	bl print_asciz

.data
.align 4
msg:
.asciz "Hello world, the ANSWER is 42! @[]`{}~\n"


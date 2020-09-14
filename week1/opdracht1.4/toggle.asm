.cpu cortex-m0
.text
.align 2
.global toggle

toggle:
	push {lr}

	cmp r0, #65
	blt other

	cmp r0, #122	
	bgt other

	cmp r0, #90
	blt upper

	cmp r0, #97
	bgt lower
	bl other

upper: 
	add r0, #32
	bl other
lower:
	sub r0, #32
other:
	pop {pc}


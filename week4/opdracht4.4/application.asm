.cpu cortex-m0
.text
.align 2
.global application

application:
	push {lr}
	ldr r0, =msg
	bl print_asciz
	pop {pc}

.data
.align 4
msg:
	.asciz "Hello world, the ANSWER is 42! @[]`{}~\n"
#	.asciz "Wilhelmus van Nassouwe\n@1: \n Ben ick@R5Duytsch@A3Bloedt,@O3D@O3Vaderland ghetrouwe@I3Blijf ick tot inden doet;@K3E@;3Prince van Orangi@O3\n B@U3ick vry onverveert.@I3D@O3Conin@M4an Hispangi@F3\n Heb i@H3altijt gheeert.\n\nIn Go$"


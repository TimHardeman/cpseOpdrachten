.cpu cortex-m0
.text
.align 2
.global decompressor

decompressor:
   push { r4, r5, r6, r7, lr }
   mov  r5, r0
   mov  r7, #0
   mov  r2, #0

loop: 
   ldrb r0, [ r5 ]
   add  r0, #0
   beq  done
   cmp  r7, #1
   bge  printCounter
   cmp  r0, #'@'
   beq  printCounter
   bl   uart_put_char
   ldrb r0, [ r5 ]
   add  r5, r5, #1

storeCycle:
   push { r6 }
   ldr  r3, =buffer
   mov  r1, #0
storeCycleLoop:
   add  r3, r3, #1
   ldrb r6, [ r3 ]
   sub  r3, r3, #1
   strb r6, [ r3 ]
   add  r3, r3, #1
   add  r1, r1, #1
   cmp  r1, #79
   beq  storeCycleDone
   b    storeCycleLoop
storeCycleDone:
   strb r0, [ r3 ]
   pop { r6 }
   cmp  r2, #1
   beq  printLoop
   b    loop

printCounter:
   add  r7, #1
   add  r5, r5, #1
   cmp  r7, #3
   bge  print
   b    loop
print:
   mov  r2, #1
   mov  r7, #0
   sub  r5, #1
   ldrb r6, [ r5 ]
   sub  r6, #'0'
   sub  r5, #1
   ldrb r1, [ r5 ]
   sub  r1, #'0'
   add  r5, #2
   ldr  r4, =buffer
   add  r4, #79
   sub  r4, r1
printLoop: 
   cmp  r6, #0
   ble  printDone
   ldrb r0, [ r4 ]
   push { r2 }
   bl   uart_put_char
   pop  { r2 }
   ldrb r0, [ r4 ]
   sub  r6, r6, #1
   b    storeCycle
printDone:
   mov  r2, #0
   b    loop

done: 
   pop  { r5, r6, r7, pc }

.data
.align 2
buffer:
   .zero 80


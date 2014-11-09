.text
.globl entry
entry:
.arm
	/* mode 4, bg2 */
	mov r0, #0x04000000
	ldr r1, =0x0404
	str r1, [r0]
	
	/* white & red & blue & black */
	mov r0, #0x05000000
	ldr r1, =0x001F7FFF
	str r1, [r0]
	ldr r1, =0x00007C00
	str r1, [r0, #4]
	ldr sp, =0x03007F00
	
	/* startup */
	b entry_c
	
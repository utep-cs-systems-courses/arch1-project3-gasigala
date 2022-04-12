	.balign 2

	.text
	.global switch_interrupt_handler
	.extern switch_update_interrupt_sense
	.extern switches

switch_interrupt_handler:
	call #switch_update_interrupt_sense
	xor.b  #255, r12
	
	and.b #15, r12
	mov.b r12, &switches
	pop r0

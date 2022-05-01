	.balign 2
	
	.text
	.global switch_interrupt_handler ;function is gonna be available oustide of this file.
	.extern switch_update_interrupt_sense ;inlcude all functions and variables used from another file.
	.extern switches

switch_interrupt_handler:
	call  #switch_update_interrupt_sense
	xor.b #255, r12 ; coulde also be 0xff to get 1111 1111. r12 -> p2val from original. Instruction: .~p2val -> xor r12 with 1111 1111
	and.b #15, r12 ; p2val & switches. switches -> 0000 1111
	mov.b r12, &switches
	pop r0

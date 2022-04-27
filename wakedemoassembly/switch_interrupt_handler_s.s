	.balign 2

	.text
	.global switch_interrupt_handler
	.extern switch_update_interrupt_sense
	.extern switches

	.extern P2IN
	.extern P2IES 

switch_interrupt_handler:
	call #switch_update_interrupt_sense
	xor.b  #255, r12	; switches can be 15 max and p2val can be 255
	
	and.b #15, r12
	mov.b r12, &switches
	pop r0

switch_update_interrupt_sence:
	mov.b &P2IN, r12	;p2val = P2IN
	and.b #15, r12		;(p2val & SWITCHES)
	bis.b r12, &P2IES	;P2IES |= p2val & SWITCHES
	xor.b #255, &switches	;~SWITCHES
	bis.b &switches, r12	;(p2val | ~SWITCHES)
	and.b r12, &P2IES	;P2IES &= (p2val & SWITCHES)
	pop r0
	

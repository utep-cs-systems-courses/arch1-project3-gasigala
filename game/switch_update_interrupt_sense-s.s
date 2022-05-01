	.balign 2
	.text
	.global switch_update_interrupt_sense ; function is gonna be availible outside the file

	.extern P2IES
	.extern P2IN

switch_update_interrupt_sense:
	sub #4, r1

	mov.b &P2IN, 0(r1)	;move P2IN into p2val
	mov.b 0(r1), 1(r1)	;T1
	mov.b 0(r1), 2(r1)	;T2

	and.b #31, 0(r1)	;T1 = p2val & SWITCHESS
	bis.b 1(r1), &P2IES

	bis.b #0x7f, 2(r1)	;T2 = (p2val | SWITCHES)
	and.b 2(r1), &P2IES

	mov.b 0(r1), r12	;move p2val into return adress register
	add   #4, r1		;add stack to pointer back
	pop   r0		;pop program counter
	

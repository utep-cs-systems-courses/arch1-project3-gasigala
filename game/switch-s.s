	.balign 2
	.text

	.extern idx
	.global jumpTable

cases:
	.word default
	.word case1
	.word case2

jumpTable:
	cmp #3, r12
	jhs default
	add r12, r12 		;if carry is set that means it did not borrow which means we passed somethin greater than 2
	mov cases(r12), r0

case1:
	mov #0, &idx
	jmp end

case2:
	mov #1, &idx
	jmp end

default:

end:
	pop r0
	

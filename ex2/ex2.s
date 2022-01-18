	.text
	.globl even
	.type even, @function
even:
	movq 	%rdi,%rax
	movq 	%rsi,%rcx
	sall 	%cl, %eax
	ret

	.globl go
	.type go, @function
go:
	pushq 	%rbx
	xorq 	%rbx, %rbx			# rbx = sum
	xorq 	%rcx, %rcx			# rcx = i
	movq 	%rdi, %rdx			# rdx = A
compare:
	movq 	(%rdx,%rcx,4),%rdi	# rdi = A[i]
	cmpq 	$10, %rcx			# loop condition
	jge 	end 				# end loop
	testq 	$1, %rdi 			# check if the number is odd or even
	jne 	else 				# jump to else if odd
	movq 	%rcx, %rsi
	call 	even
	addq 	%rax, %rbx 			# add return value to sum
	jmp 	cnt
else:
	addq 	%rdi, %rbx 
cnt:
	inc 	%rcx 				# increment loop counter
	jmp 	compare
end:
	movq 	%rbx, %rax
	popq 	%rbx
	ret

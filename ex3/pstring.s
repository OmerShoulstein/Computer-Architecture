.section .rodata
	.align 8	
	invalidMsg: .string "invalid input!\n"

	.text
	.globl pstrlen
	.type pstrlen, @function
pstrlen:
	pushq 	%rbx			# store rbx
	movq 	(%rdi),%rbx 	# get the value of the pointer
	xorq 	%rax,%rax
	movb	%bl,%al 		# bl is the first char which stores the length 
	popq 	%rbx
	ret

	.globl replaceChar
	.type replaceChar, @function
replaceChar:
	pushq 	%rbx
	xorq 	%rbx,%rbx 		 # rbx = 0
	call 	pstrlen 		 # get length of first argument
	movq 	%rax,%rbx
	incq 	%rbx 			 # rbx++ because first char stores length
	movq 	$1,%rcx 		 # rcx = 1
loop:
	cmpq 	%rcx,%rbx 		 # loop over all chars
	je 		endLoop
	cmp 	%sil,(%rdi,%rcx) # if i=A[rcx]
	jne 	inc
	mov 	%dl,(%rdi,%rcx)  # A[rcx]=j
inc:
	incq 	%rcx 			 # rcx++
	jmp 	loop
endLoop:
	popq 	%rbx
	movq 	%rdi,%rax
	ret

	.globl pstrijcpy
	.type pstrijcpy, @function
pstrijcpy:
	pushq 	%rbx
	pushq 	%r12
	movq 	%rsi,%r12 		 # save the second string in a callee saved register
	call 	pstrlen
	movq 	%rax,%rbx 		 # store length in rbx
	xorq 	%rdi,%rsi 		 # switch rsi and rdi
	xorq 	%rsi,%rdi
	xorq 	%rdi,%rsi
	call 	pstrlen   		 # store the length in rax
	xorq 	%rdi,%rsi 		 # switch rdi and rsi
	xorq 	%rsi,%rdi
	xorq 	%rdi,%rsi
	incq 	%rcx 	  		 # increase all parameters by 1 beacuse the first byte stores length
	incq 	%rax
	incq 	%rbx
	incq 	%rdx
	cmp 	$0,%rdx	  		 # if i < 0
	jl 		invalid
	cmp 	%rax,%rcx 		 # if j >= length(dst)
	jge 	invalid
	cmp 	%rbx,%rcx 		 # if j >= length(src)
	jge 	invalid
	cmp 	%rdx,%rcx 		 # if i > j
	jl 		invalid
	movq 	%rdx,%rbx 		 # rbx = i 
compare:
	cmp 	%rbx,%rcx 		 # if j < i
	jl 		endCpy
	movb 	(%rdi,%rbx),%dl  # dst[i] = src[i]
	movb 	%dl,(%rsi,%rbx)
	inc 	%bl
	jmp 	compare
invalid:
	xorq 	%rax,%rax 		 # print invalid message
	leaq 	invalidMsg,%rdi
	call 	printf
	movq 	%r12,%rax 		 # return original dst
	jmp 	leaveCopy
endCpy:
	movq 	%rsi,%rax
leaveCopy:
	popq 	%r12
	popq 	%rbx
	ret

	.globl swapCase
	.type swapCase, @function
swapCase:
	pushq 	%rbx
	call 	pstrlen 		# get string length
	movq 	%rax,%rcx 		# rcx = len(str)
	movq 	$1,%rbx 		# rbx = 1
comapreCopy:
	cmp 	%rbx,%rcx		# if rcx < rbx
	jl 		endSwap
	xorq 	%rdx,%rdx 		# dl = str[i]
	movb 	(%rdi,%rbx),%dl
	cmp 	$65,%rdx 		# str[i] < A
	jl 		increment
	cmp 	$90,%rdx 		# str[i] <= Z
	jle 	toLower
	cmp 	$122,%rdx 		# str[i] > z
	jg 		increment
	cmp 	$97,%rdx 		# str[i] >= a
	jge 	toUpper
	jmp 	increment
toLower:
	addq 	$32,(%rdi,%rbx) # 'a'-'A' = 32
	jmp 	increment
toUpper:
	subq 	$32,(%rdi,%rbx)
	jmp 	increment
increment:
	incq 	%rbx
	jmp 	comapreCopy
endSwap:
	movq 	%rdi,%rax 		# return modified string
	popq 	%rbx
	ret

	.globl pstrijcmp
	.type pstrijcmp, @function
pstrijcmp:
	pushq 	%rbx
	pushq 	%r12
	pushq 	%r13
	incq 	%rdx 			# raise i and j by 1 because first byte stores length
	incq 	%rcx
	movq 	%rdi,%rbx
	movq 	%rsi,%r12
	call 	pstrlen
	movq 	%rax,%r13
	incq 	%r13
	movq 	%rsi,%rdi
	call 	pstrlen
	incq 	%rax
	cmp 	$0,%rdx	      	# if i < 0
	jl 		invalidCmp
	cmp 	%rcx,%r13	  	# if j >= length(dst)
	jl  	invalidCmp
	cmp 	%rax,%rcx 	  	# if j >= length(src)
	jge 	invalidCmp
	cmp 	%rdx,%rcx 	  	# if i > j
	jl 		invalidCmp
cmpLoop:
	cmp 	%rdx,%rcx 		# if i > j, end loop
	jl 		equalCmp
	movb 	(%rbx,%rdx),%r8b # get firstString[i]
	movb 	(%r12,%rdx),%al  # get secondString[i]
	cmp 	%al,%r8b 		 # compare firstString[i] secondString[i]
	je 		cmpIncrement
	jl 		lowerCmp
	jg 		greaterCmp
cmpIncrement:
	incq 	%rdx 			 # continue loop
	jmp 	cmpLoop
lowerCmp:
	movq 	$-1,%rax		 # return -1
	jmp 	endCmp
greaterCmp:
	movq 	$1,%rax 		 # return 1
	jmp 	endCmp
invalidCmp:
	leaq 	invalidMsg,%rdi
	xorq 	%rax,%rax
	call 	printf
	movq 	$-2,%rax
	jmp 	endCmp
equalCmp:
	xorq 	%rax,%rax 		 # return 0
endCmp:
	popq 	%r13
	popq 	%r12
	popq 	%rbx
	ret

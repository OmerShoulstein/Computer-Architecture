.section .rodata
	.align 8	
.base:
	.quad	.pstrlenLabel
	.quad	.default
	.quad	.replaceChar
	.quad	.copyString
	.quad	.swapLetter
	.quad	.compare
	.quad	.default
	.quad	.default
	.quad	.default
	.quad	.default
	.quad	.pstrlenLabel
format: .string "invalid option!\n"
pstrlenFormat: .string "first pstring length: %d, second pstring length: %d\n"
scanChars: .string " %c %c"
scanInts: .string " %d\n%d"
replaceCharFormat: .string "old char: %c, new char: %c, first string: %s, second string: %s\n"
lengthAndStr: .string "length: %d, string: %s\n"
compareMsg: .string "compare result: %d\n"


	.text
	.globl run_func
	.type run_func, @function
run_func:
	cmpq	$50,%rdi
	jl  	.default
	cmpq 	$60,%rdi
	jg  	.default
	subq 	$50, %rdi
	jmp 	*.base(,%rdi,8)
	
end:
	ret

.default:
	leaq  	format, %rdi
  	xor 	%rax, %rax
  	call 	printf
	jmp 	end

.pstrlenLabel:
	movq 	%rsi, %rdi
	movq 	%rdx, %rsi
	call pstrlenPrint
	jmp end

.replaceChar:
	movq 	%rsi, %rdi
	movq 	%rdx, %rsi
	call replaceCharFunc
	jmp end

.copyString:
	movq 	%rsi, %rdi
	movq 	%rdx, %rsi
	call 	printPstrijcpy
	jmp end

.swapLetter:
	movq 	%rsi, %rdi
	movq 	%rdx, %rsi
	call 	printSwapCase
	jmp end

.compare:
	movq 	%rsi, %rdi
	movq 	%rdx, %rsi
	call 	printPstrijcmp
	jmp end

	.globl pstrlenPrint
	.type pstrlenPrint, @function
pstrlenPrint:
	pushq 	%rbx
	movq 	%rsi,%rbx 				# store the second argument
	call 	pstrlen 				# get the length of the first argument
	movq 	%rbx,%rdi 				# second argumnet is in rdi
	movq 	%rax,%rbx 				# store return value in rbx
	call 	pstrlen 				# get the length of the second argument
	movq 	%rax,%rdx 				# store return value in rdx
	leaq 	pstrlenFormat,%rdi 		# store the message format as the first argument
	movq 	%rbx,%rsi 				# move the first length to rsi
	xorq 	%rax,%rax
	call 	printf 					# print
	popq 	%rbx
	ret

	.globl replaceCharFunc
	.type replaceCharFunc, @function
replaceCharFunc:
	pushq 	%rbx
	pushq 	%r12
	pushq 	%rbp 					# create a stack frame with 8 bytes
	movq 	%rsp,%rbp
	subq 	$8, %rsp
	movq 	%rdi,%rbx 				# store first and second arguments in callee saved registers
	movq 	%rsi,%r12

	leaq 	scanChars, %rdi 		# store scaning format in rdi
	leaq 	-1(%rbp), %rsi 			# rdi points to a byte on the stack
	leaq 	-2(%rbp), %rdx  		# rdx points to a byte on the stack
	xorq 	%rax, %rax				# call scanf
	call 	scanf

	xorq 	%rsi,%rsi 				# store the scanned chars in rsi and rdx
	xorq 	%rdx,%rdx
	movb 	-1(%rbp),%sil
	movb 	-2(%rbp),%dl
	movq 	%rbx,%rdi 				# rbx sotres the first string
	call 	replaceChar
	movq 	%rax,%rbx

	xorq 	%rsi,%rsi 				# store the scanned chars in rsi and rdx
	xorq 	%rdx,%rdx
	movb 	-1(%rbp),%sil
	movb 	-2(%rbp),%dl
	movq 	%r12,%rdi 				# r12 stores the second string
	call 	replaceChar

	leaq 	replaceCharFormat,%rdi  # store the message format in rdi
	xorq 	%rsi,%rsi 			    # rsi stores first char
	xorq 	%rdx,%rdx 			    # rdi stores second char
	mov 	-1(%rbp),%sil
	mov 	-2(%rbp),%dl
	leaq 	1(%rbx),%rcx			# rcx stores the first string after replacement
	leaq 	1(%rax), %r8			# r8 stores the second string after replacement
	xorq 	%rax,%rax
	call 	printf
	leave
	popq 	%r12
	popq 	%rbx
	ret

	.globl printPstrijcpy
	.type printPstrijcpy, @function
printPstrijcpy:
	pushq 	%rbp 					# create a stack frame with 8 bytes
	movq 	%rsp,%rbp
	subq 	$8, %rsp
	movq 	%rdi,%rbx 				# store strings in calle saved registers
	movq 	%rsi,%r12
	leaq 	scanInts, %rdi  		# rdi stores the scan format
	leaq 	-4(%rbp), %rsi  		# rsi points to 4 bytes on the stack
	leaq 	-8(%rbp), %rdx  		# rdx points to 4 bytes on the stack
	xorq 	%rax, %rax				# call scanf
	call 	scanf
	movq 	%rbx,%rsi 				# rsi stores first string
	movq 	%r12,%rdi 				# rdi stores second string
	xorq 	%rdx,%rdx 				# rdx stores scanned int
	xorq 	%rcx,%rcx				# rcx stores scanned int
	movl 	-4(%rbp),%edx
	movl 	-8(%rbp),%ecx
	call 	pstrijcpy 				# copy second string into first
	movq 	%rbx,%rdi 				# rdi stores first string
	movq 	%rax,%rbx 				# rbx stores modified string
	call 	pstrlen
	movq 	%rax,%rsi 				# store length in rsi
	leaq 	lengthAndStr,%rdi 
	leaq 	1(%rbx),%rdx 			# rdx stores modified strings
	xorq 	%rax,%rax
	call 	printf

	movq 	%r12,%rdi 				# get length of second string
	call 	pstrlen
	movq 	%rax,%rsi
	leaq 	lengthAndStr,%rdi
	leaq 	1(%r12),%rdx 			# rdx stores second string
	xorq 	%rax,%rax
	call 	printf
	leave
	ret

	.globl printSwapCase
	.type printSwapCase, @function
printSwapCase:
	pushq 	%rbx
	pushq  	%r12
	movq 	%rsi,%rbx 				# store second argument in rbx
	call 	pstrlen
	movq 	%rax,%r12 				# store length in r12
	call 	swapCase
	leaq 	1(%rax),%rdx			# print length and modified string
	movq 	%r12,%rsi
	leaq 	lengthAndStr,%rdi
	xorq 	%rax,%rax
	call 	printf

	movq 	%rbx,%rdi 				# rdi = secondString
	call 	pstrlen
	movq 	%rax,%r12 				# store length in r12
	call 	swapCase
	leaq 	1(%rax),%rdx 			# store swapped string in rdx
	movq 	%r12,%rsi 				# print length and string
	leaq 	lengthAndStr,%rdi
	xorq 	%rax,%rax
	call 	printf

	popq 	%r12
	popq 	%rbx
	ret

	.globl printPstrijcmp
	.type printPstrijcmp, @function
printPstrijcmp:
	pushq 	%rbx
	pushq 	%r12
	pushq 	%rbp 					# create a stack frame with 8 bytes
	movq 	%rsp,%rbp
	subq 	$8, %rsp
	movq 	%rdi,%rbx 				# store arguments in callee saved registers
	movq 	%rsi,%r12
	leaq 	scanInts, %rdi 			# scan 2 integers
	leaq 	-4(%rbp), %rsi
	leaq 	-8(%rbp), %rdx
	xorq 	%rax, %rax
	call 	scanf
	movq 	%rbx,%rdi 				# restore arguments
	call 	pstrlen
	movq 	%rax,%r13
	movq 	%r12,%rdi
	call 	pstrlen
	movq 	%rbx,%rdi
	movq 	%r12,%rsi
	xorq 	%rdx,%rdx
	xorq 	%rcx,%rcx
	movl 	-4(%rbp),%edx 			# move scanned integers to edx and ecx
	movl 	-8(%rbp),%ecx
	call 	pstrijcmp
	movq 	%rax,%rsi 				# print return value
	leaq 	compareMsg,%rdi
	xorq 	%rax,%rax
	call 	printf
	leave 
	popq 	%r12
	popq 	%rbx
	ret

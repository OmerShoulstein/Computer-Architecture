.section .rodata
	.align 16
	scanInt: .string " %d"
	scanString : .string " %s"

	.text 
	.globl run_main
	.type  run_main, @function
run_main:
	pushq 	%rbp 					# create a stack frame with 528 bytes
	movq 	%rsp,%rbp
	subq 	$528, %rsp
	leaq 	scanInt,%rdi 			# scan the length of the first string
	leaq 	-528(%rbp),%rsi
	xorq 	%rax,%rax
	call 	scanf
	leaq 	scanString,%rdi 		# scan the first string
	leaq 	-527(%rbp),%rsi
	xorq 	%rax,%rax
	call 	scanf
	leaq 	scanInt,%rdi 			# scan the length of the second string
	leaq 	-272(%rbp),%rsi
	xorq 	%rax,%rax
	call 	scanf
	leaq 	scanString,%rdi 		# scan the second string
	leaq 	-271(%rbp),%rsi
	xorq 	%rax,%rax
	call 	scanf
	leaq 	scanInt,%rdi 			# scan the int that the user chose
	leaq 	-16(%rbp),%rsi
	xorq 	%rax,%rax
	call 	scanf
	movq 	-16(%rbp),%rdi 			# set function parameters
	leaq 	(%rsp),%rsi
	leaq 	-272(%rbp),%rdx
	call 	run_func
	leave
	ret

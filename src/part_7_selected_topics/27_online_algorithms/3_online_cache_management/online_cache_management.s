	.file	"online_cache_management.c"
	.text
	.def	time;	.scl	3;	.type	32;	.endef
	.seh_proc	time
time:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	16(%rbp), %rax
	movq	%rax, %rcx
	movq	__imp__time64(%rip), %rax
	call	*%rax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	fifo_cache
	.def	fifo_cache;	.scl	2;	.type	32;	.endef
	.seh_proc	fifo_cache
fifo_cache:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L4
.L12:
	movl	$0, -20(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L5
.L8:
	movl	-24(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %edx
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	16(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L6
	movl	$1, -20(%rbp)
	jmp	.L7
.L6:
	addl	$1, -24(%rbp)
.L5:
	movl	-24(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L8
.L7:
	cmpl	$0, -20(%rbp)
	jne	.L14
	addl	$1, -12(%rbp)
	movl	-8(%rbp), %eax
	cmpl	32(%rbp), %eax
	jge	.L11
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-8(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -8(%rbp)
	movl	(%rcx), %edx
	cltq
	movl	%edx, -48(%rbp,%rax,4)
	jmp	.L10
.L11:
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-4(%rbp), %eax
	cltq
	movl	%edx, -48(%rbp,%rax,4)
	movl	-4(%rbp), %eax
	addl	$1, %eax
	cltd
	idivl	32(%rbp)
	movl	%edx, -4(%rbp)
	jmp	.L10
.L14:
	nop
.L10:
	addl	$1, -16(%rbp)
.L4:
	movl	-16(%rbp), %eax
	cmpl	24(%rbp), %eax
	jl	.L12
	movl	-12(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	lifo_cache
	.def	lifo_cache;	.scl	2;	.type	32;	.endef
	.seh_proc	lifo_cache
lifo_cache:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L16
.L24:
	movl	$0, -16(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L17
.L20:
	movl	-20(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %edx
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	16(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L18
	movl	$1, -16(%rbp)
	jmp	.L19
.L18:
	addl	$1, -20(%rbp)
.L17:
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jl	.L20
.L19:
	cmpl	$0, -16(%rbp)
	jne	.L26
	addl	$1, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	32(%rbp), %eax
	jge	.L23
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -4(%rbp)
	movl	(%rcx), %edx
	cltq
	movl	%edx, -48(%rbp,%rax,4)
	jmp	.L22
.L23:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	-4(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	(%rax), %edx
	movslq	%ecx, %rax
	movl	%edx, -48(%rbp,%rax,4)
	jmp	.L22
.L26:
	nop
.L22:
	addl	$1, -12(%rbp)
.L16:
	movl	-12(%rbp), %eax
	cmpl	24(%rbp), %eax
	jl	.L24
	movl	-8(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	lru_cache
	.def	lru_cache;	.scl	2;	.type	32;	.endef
	.seh_proc	lru_cache
lru_cache:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$96, %rsp
	.seh_stackalloc	96
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	pxor	%xmm0, %xmm0
	movups	%xmm0, -96(%rbp)
	movups	%xmm0, -80(%rbp)
	movups	%xmm0, -64(%rbp)
	movups	%xmm0, -48(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L28
.L41:
	movl	$0, -20(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L29
.L34:
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$84, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L43
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$96, %rax
	movl	(%rax), %edx
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	16(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L43
	movl	$1, -20(%rbp)
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	leaq	-92(%rax), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, (%rdx)
	jmp	.L33
.L43:
	nop
	addl	$1, -24(%rbp)
.L29:
	movl	-24(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L34
.L33:
	cmpl	$0, -20(%rbp)
	jne	.L44
	addl	$1, -12(%rbp)
	movl	-8(%rbp), %eax
	cmpl	32(%rbp), %eax
	jge	.L37
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	-8(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rbp, %rdx
	subq	$96, %rdx
	movl	%eax, (%rdx)
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	leaq	-92(%rax), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, (%rdx)
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$84, %rax
	movl	$1, (%rax)
	addl	$1, -8(%rbp)
	jmp	.L36
.L37:
	movl	$0, -28(%rbp)
	movl	$1, -32(%rbp)
	jmp	.L38
.L40:
	movl	-32(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$92, %rax
	movl	(%rax), %edx
	movl	-28(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$92, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jge	.L39
	movl	-32(%rbp), %eax
	movl	%eax, -28(%rbp)
.L39:
	addl	$1, -32(%rbp)
.L38:
	movl	-32(%rbp), %eax
	cmpl	32(%rbp), %eax
	jl	.L40
	movl	-16(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rbp, %rdx
	subq	$96, %rdx
	movl	%eax, (%rdx)
	movl	-28(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	leaq	-92(%rax), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, (%rdx)
	jmp	.L36
.L44:
	nop
.L36:
	addl	$1, -16(%rbp)
	addl	$1, -4(%rbp)
.L28:
	movl	-16(%rbp), %eax
	cmpl	24(%rbp), %eax
	jl	.L41
	movl	-12(%rbp), %eax
	addq	$96, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	lfu_cache
	.def	lfu_cache;	.scl	2;	.type	32;	.endef
	.seh_proc	lfu_cache
lfu_cache:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$96, %rsp
	.seh_stackalloc	96
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	pxor	%xmm0, %xmm0
	movups	%xmm0, -96(%rbp)
	movups	%xmm0, -80(%rbp)
	movups	%xmm0, -64(%rbp)
	movups	%xmm0, -48(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L46
.L59:
	movl	$0, -16(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L47
.L52:
	movl	-20(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$84, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L61
	movl	-20(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$96, %rax
	movl	(%rax), %edx
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	16(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L61
	movl	$1, -16(%rbp)
	movl	-20(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$88, %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movl	-20(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$88, %rax
	movl	%edx, (%rax)
	jmp	.L51
.L61:
	nop
	addl	$1, -20(%rbp)
.L47:
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jl	.L52
.L51:
	cmpl	$0, -16(%rbp)
	jne	.L62
	addl	$1, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	32(%rbp), %eax
	jge	.L55
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rbp, %rdx
	subq	$96, %rdx
	movl	%eax, (%rdx)
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$88, %rax
	movl	$1, (%rax)
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$84, %rax
	movl	$1, (%rax)
	addl	$1, -4(%rbp)
	jmp	.L54
.L55:
	movl	$0, -24(%rbp)
	movl	$1, -28(%rbp)
	jmp	.L56
.L58:
	movl	-28(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$88, %rax
	movl	(%rax), %edx
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$88, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jge	.L57
	movl	-28(%rbp), %eax
	movl	%eax, -24(%rbp)
.L57:
	addl	$1, -28(%rbp)
.L56:
	movl	-28(%rbp), %eax
	cmpl	32(%rbp), %eax
	jl	.L58
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	addq	%rbp, %rdx
	subq	$96, %rdx
	movl	%eax, (%rdx)
	movl	-24(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$88, %rax
	movl	$1, (%rax)
	jmp	.L54
.L62:
	nop
.L54:
	addl	$1, -12(%rbp)
.L46:
	movl	-12(%rbp), %eax
	cmpl	24(%rbp), %eax
	jl	.L59
	movl	-8(%rbp), %eax
	addq	$96, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "%s misses: %d\12\0"
	.text
	.def	print_cache_result;	.scl	3;	.type	32;	.endef
	.seh_proc	print_cache_result
print_cache_result:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movl	%r9d, 40(%rbp)
	movl	48(%rbp), %ecx
	movl	40(%rbp), %edx
	movq	32(%rbp), %rax
	movq	24(%rbp), %r9
	movl	%ecx, %r8d
	movq	%rax, %rcx
	call	*%r9
	movl	%eax, %edx
	movq	16(%rbp), %rax
	movl	%edx, %r8d
	movq	%rax, %rdx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	printf
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC1:
	.ascii "Initialized tests with %d request and a cache of size %d\12\0"
.LC2:
	.ascii "FIFO\0"
.LC3:
	.ascii "LIFO\0"
.LC4:
	.ascii "LRU\0"
.LC5:
	.ascii "LFU\0"
	.text
	.globl	test_deterministic_caches
	.def	test_deterministic_caches;	.scl	2;	.type	32;	.endef
	.seh_proc	test_deterministic_caches
test_deterministic_caches:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$112, %rsp
	.seh_stackalloc	112
	.seh_endprologue
	movl	$1, -64(%rbp)
	movl	$2, -60(%rbp)
	movl	$3, -56(%rbp)
	movl	$4, -52(%rbp)
	movl	$1, -48(%rbp)
	movl	$2, -44(%rbp)
	movl	$5, -40(%rbp)
	movl	$1, -36(%rbp)
	movl	$2, -32(%rbp)
	movl	$3, -28(%rbp)
	movl	$4, -24(%rbp)
	movl	$5, -20(%rbp)
	movl	$12, -4(%rbp)
	movl	$4, -8(%rbp)
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %r8d
	movl	%eax, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	-4(%rbp), %ecx
	leaq	-64(%rbp), %rdx
	movl	-8(%rbp), %eax
	movl	%eax, 32(%rsp)
	movl	%ecx, %r9d
	movq	%rdx, %r8
	leaq	fifo_cache(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	print_cache_result
	movl	-4(%rbp), %ecx
	leaq	-64(%rbp), %rdx
	movl	-8(%rbp), %eax
	movl	%eax, 32(%rsp)
	movl	%ecx, %r9d
	movq	%rdx, %r8
	leaq	lifo_cache(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	print_cache_result
	movl	-4(%rbp), %ecx
	leaq	-64(%rbp), %rdx
	movl	-8(%rbp), %eax
	movl	%eax, 32(%rsp)
	movl	%ecx, %r9d
	movq	%rdx, %r8
	leaq	lru_cache(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	call	print_cache_result
	movl	-4(%rbp), %ecx
	leaq	-64(%rbp), %rdx
	movl	-8(%rbp), %eax
	movl	%eax, 32(%rsp)
	movl	%ecx, %r9d
	movq	%rdx, %r8
	leaq	lfu_cache(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC5(%rip), %rax
	movq	%rax, %rcx
	call	print_cache_result
	nop
	addq	$112, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	unmark_all;	.scl	3;	.type	32;	.endef
	.seh_proc	unmark_all
unmark_all:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L66
.L67:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	movq	%rax, %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	$0, 4(%rax)
	addl	$1, -4(%rbp)
.L66:
	movl	-4(%rbp), %eax
	cmpl	24(%rbp), %eax
	jl	.L67
	nop
	nop
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	randomized_marking_cache
	.def	randomized_marking_cache;	.scl	2;	.type	32;	.endef
	.seh_proc	randomized_marking_cache
randomized_marking_cache:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$144, %rsp
	.seh_stackalloc	144
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	pxor	%xmm0, %xmm0
	movups	%xmm0, -96(%rbp)
	movups	%xmm0, -80(%rbp)
	movups	%xmm0, -64(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, %ecx
	call	time
	movl	%eax, %ecx
	call	srand
	movl	$0, -12(%rbp)
	jmp	.L69
.L88:
	movl	$0, -16(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L70
.L75:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$88, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L90
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$96, %rax
	movl	(%rax), %edx
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	16(%rbp), %rax
	addq	%rcx, %rax
	movl	(%rax), %eax
	cmpl	%eax, %edx
	jne	.L90
	movl	$1, -16(%rbp)
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$92, %rax
	movl	$1, (%rax)
	jmp	.L74
.L90:
	nop
	addl	$1, -20(%rbp)
.L70:
	movl	-20(%rbp), %eax
	cmpl	-4(%rbp), %eax
	jl	.L75
.L74:
	cmpl	$0, -16(%rbp)
	jne	.L91
	addl	$1, -8(%rbp)
	movl	-4(%rbp), %eax
	cmpl	32(%rbp), %eax
	jge	.L78
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$96, %rax
	movl	%ecx, (%rax)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$92, %rax
	movl	$1, (%rax)
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$88, %rax
	movl	$1, (%rax)
	addl	$1, -4(%rbp)
	jmp	.L87
.L78:
	movl	$1, -24(%rbp)
	movl	$0, -28(%rbp)
	jmp	.L79
.L82:
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$92, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L80
	movl	$0, -24(%rbp)
	jmp	.L81
.L80:
	addl	$1, -28(%rbp)
.L79:
	movl	-28(%rbp), %eax
	cmpl	32(%rbp), %eax
	jl	.L82
.L81:
	cmpl	$0, -24(%rbp)
	je	.L83
	movl	32(%rbp), %edx
	leaq	-96(%rbp), %rax
	movq	%rax, %rcx
	call	unmark_all
.L83:
	movl	$0, -32(%rbp)
	movl	$0, -36(%rbp)
	jmp	.L84
.L86:
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$92, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L85
	movl	-32(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -32(%rbp)
	cltq
	movl	-36(%rbp), %edx
	movl	%edx, -112(%rbp,%rax,4)
.L85:
	addl	$1, -36(%rbp)
.L84:
	movl	-36(%rbp), %eax
	cmpl	32(%rbp), %eax
	jl	.L86
	call	rand
	cltd
	idivl	-32(%rbp)
	movl	%edx, %eax
	cltq
	movl	-112(%rbp,%rax,4), %eax
	movl	%eax, -40(%rbp)
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	16(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movl	-40(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$96, %rax
	movl	%ecx, (%rax)
	movl	-40(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$92, %rax
	movl	$1, (%rax)
	movl	-40(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	salq	$2, %rax
	addq	%rbp, %rax
	subq	$88, %rax
	movl	$1, (%rax)
	jmp	.L87
.L91:
	nop
.L87:
	addl	$1, -12(%rbp)
.L69:
	movl	-12(%rbp), %eax
	cmpl	24(%rbp), %eax
	jl	.L88
	movl	-8(%rbp), %eax
	addq	$144, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC6:
	.ascii "Randomized marking\0"
	.text
	.globl	test_non_deterministic_caches
	.def	test_non_deterministic_caches;	.scl	2;	.type	32;	.endef
	.seh_proc	test_non_deterministic_caches
test_non_deterministic_caches:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$112, %rsp
	.seh_stackalloc	112
	.seh_endprologue
	movl	$1, -64(%rbp)
	movl	$2, -60(%rbp)
	movl	$3, -56(%rbp)
	movl	$4, -52(%rbp)
	movl	$1, -48(%rbp)
	movl	$2, -44(%rbp)
	movl	$5, -40(%rbp)
	movl	$1, -36(%rbp)
	movl	$2, -32(%rbp)
	movl	$3, -28(%rbp)
	movl	$4, -24(%rbp)
	movl	$5, -20(%rbp)
	movl	$12, -4(%rbp)
	movl	$4, -8(%rbp)
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %r8d
	movl	%eax, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	-4(%rbp), %ecx
	leaq	-64(%rbp), %rdx
	movl	-8(%rbp), %eax
	movl	%eax, 32(%rsp)
	movl	%ecx, %r9d
	movq	%rdx, %r8
	leaq	randomized_marking_cache(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC6(%rip), %rax
	movq	%rax, %rcx
	call	print_cache_result
	nop
	addq	$112, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (Rev3, Built by MSYS2 project) 13.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	srand;	.scl	2;	.type	32;	.endef
	.def	rand;	.scl	2;	.type	32;	.endef

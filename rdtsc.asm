bits 64
section .text

global read_clock
read_clock:
	push rbp
	mov rbp, rsp
	cpuid
	rdtsc
	mov rsp, rbp
	pop rbp
	ret


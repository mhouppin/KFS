HOSTARCH := $(shell uname -m | sed \
	-e s/i.86/x86/ -e s/x86_64/x86/ \
	-e s/sun4u/sparc64/ \
	-e s/arm.*/arm/ -e s/sa110/arm/ \
	-e s/s390x/s390/ \
	-e s/ppc.*/powerpc/ -e s/mips.*/mips/ \
	-e s/sh[234].*/sh/ -e s/aarch64.*/arm64/ \
	-e s/riscv.*/riscv/ -e s/loongarch.*/loongarch/)

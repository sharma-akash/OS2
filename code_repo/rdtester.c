#include <stdio.h>
#include <string.h>

int rdtester()
{

	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;

	char vendor[13];

	eax = 0x01;

	__asm__ __volatile__(
		"cpuid;"
		: "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
		: "a"(eax)
	);

	if (ecx & 0x40000000) {
		return 1;
	}
	else {
		return 2;
	}
}
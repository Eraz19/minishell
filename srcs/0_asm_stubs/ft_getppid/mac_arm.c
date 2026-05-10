#if defined(__APPLE__) && (defined(__aarch64__) || defined(__arm64__))
# include <sys/syscall.h>
# include <unistd.h>

/*
GLOBAL FLOW:
1. The compiler prepares SYS_getppid in a register for %1.
2. `mov x16, %1` copies that syscall number into x16.
3. `svc #0x80` enters the kernel.
4. The kernel executes the getppid syscall.
5. On return, the result is in x0.
6. `mov %0, x0` copies that result into the C output operand bound to `ret`.
7. The C function then casts `ret` to int and returns it.

__asm__
=> tells the compiler: "insert this assembly template here".

volatile
=> tells the compiler not to remove this block as if it had no effect,
   and not to treat it like a normal pure computation.

"mov x16, %1"
=> mov  => copies a value from a source register to a destination register.
=> x16  => 64-bit general-purpose register used here to hold the syscall number.
=> %1   => [GCC/Clang] operand placeholder replaced by the compiler with
           the location chosen for input operand #1.

"svc #0x80"
=> svc   => (Supervisor Call) traps into the kernel.
=> #0x80 => immediate constant passed to `svc` for this target.

"mov %0, x0"
=> mov  => copies a value from a source register to a destination register.
=> %0   => [GCC/Clang] operand placeholder replaced by the compiler with
           the location chosen for output operand #0.
=> x0   => 64-bit register holding the syscall return value.

:
=> [GCC/Clang] separates the 4 parts of an extended asm block:
   template : outputs : inputs : clobbers.

"=r"(ret)
=> =    => [GCC/Clang] write-only output operand.
=> r    => [GCC/Clang] this operand must be placed in a register.
=> ret  => C variable bound to this output operand.

"r"((long)SYS_getppid)
=> r                  => [GCC/Clang] this operand must be placed in a register.
=> (long)SYS_getppid  => input value: the syscall number for getppid.

"x0", "x16", "memory"
=> x0     => [GCC/Clang] this asm may modify x0.
=> x16    => [GCC/Clang] this asm may modify x16.
=> memory => [GCC/Clang] this asm may affect memory-observable state, so the
            compiler must not make normal assumptions around memory here.
*/
pid_t	ft_getppid(void)
{
	long	ret;

	__asm__ volatile (
		"mov x16, %1\n"
		"svc #0x80\n"
		"mov %0, x0\n"
		: "=r"(ret)
		: "r"((long)SYS_getppid)
		: "x0", "x16", "memory"
	);
	return ((pid_t)ret);
}

#endif

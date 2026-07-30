#if defined(__APPLE__) && defined(__x86_64__)
# include <sys/syscall.h>
# include <unistd.h>

/*
GLOBAL FLOW:
1. The compiler prepares the Darwin x86_64 syscall number in %1.
2. The input constraint puts that value into rax.
3. `syscall` enters the kernel.
4. The kernel executes the getppid syscall.
5. On return, the result is in rax.
6. The output constraint copies that result into the C output operand bound to
	`ret`.
7. The C function then casts `ret` to int and returns it.

__asm__
=> tells the compiler: "insert this assembly template here".

volatile
=> tells the compiler not to remove this block as if it had no effect,
   and not to treat it like a normal pure computation.

"syscall"
=> syscall => enters the kernel and executes the requested syscall.

:
=> [GCC/Clang] separates the 4 parts of an extended asm block:
   template : outputs : inputs : clobbers.

"=a"(ret)
=> =    => [GCC/Clang] write-only output operand.
=> a    => [GCC/Clang] this operand must be placed in rax/eax.
=> ret  => C variable bound to this output operand.

"a"(0x2000000L | (long)SYS_getppid)
=> a                                 => [GCC/Clang] this operand must be placed 
										in rax/eax.
=> 0x2000000L                        => Darwin x86_64 UNIX/BSD syscall class 
										prefix.
=> (long)SYS_getppid                 => syscall number for getppid.
=> 0x2000000L | (long)SYS_getppid    => full Darwin x86_64 syscall number passed
										to the kernel.

"rcx", "r11", "memory"
=> rcx    => [GCC/Clang] this asm may modify rcx.
=> r11    => [GCC/Clang] this asm may modify r11.
=> memory => [GCC/Clang] this asm may affect memory-observable state, so the
            compiler must not make normal assumptions around memory here.
*/
pid_t	ft_getppid(void)
{
	long	ret;

	__asm__ volatile (
		"syscall\n"
		: "=a"(ret)
		: "a"(0x2000000L | (long)SYS_getppid)
		: "rcx", "r11", "memory"
	);
	return ((pid_t)ret);
}

#endif

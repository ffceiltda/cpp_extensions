#ifndef _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_INTERRUPT_GCC_CLANG_INTRINSICS_HPP_
#define _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_INTERRUPT_GCC_CLANG_INTRINSICS_HPP_

extern "C"
{
#if __has_include(<signal.h>)
#include <signal.h>
#endif //  __has_include(<signal.h>)
}

namespace cpp_extensions
{
	namespace debugger
	{
		namespace detail
		{
#if defined(__i386__) || defined(__x86_64__)
			static inline void interrupt()
			{
				__asm__ volatile("int3");
			}
#elif defined(__arm__) && !defined(__thumb__)
			static inline void interrupt()
			{
				__asm__ volatile(".inst 0xe7f001f0");
			}
#elif defined(__aarch64__) && defined(__APPLE__)
			static inline void interrupt()
			{
				__builtin_trap();
			}
#elif defined(__aarch64__)
			static inline void interrupt()
			{
				__asm__ volatile(".inst 0xd4200000");
			}
#elif defined(__powerpc__)
			static inline void interrupt()
			{
				__asm__ volatile(".4byte 0x7d821008");
			}
#elif defined(__riscv)
			static inline void interrupt()
			{
				__asm__ volatile(".4byte 0x00100073");
			}
#elif defined(SIGTRAP)
			static inline void interrupt()
			{
				raise(SIGTRAP);
			}
#elif // defined(?)
#error cpp_extensions/debugger/detail/debugger_interrupt_gcc_clang_intrinsicscpu not supported
#endif // defined(?)
		}
	}
}

#endif // _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_DETECT_APPLE_XNU_KERNEL_SYSCTL_HPP_

#ifndef _CPP_EXTENSIONS_DEBUGGER_DEBUGGER_HPP_
#define _CPP_EXTENSIONS_DEBUGGER_DEBUGGER_HPP_

#include <cpp_extensions/prolog.hpp>
#if (CPP_EXTENSIONS_DEBUGGER_DETECT == CPP_EXTENSIONS_DEBUGGER_DETECT_WINDOWS_API)
#include <cpp_extensions/debugger/detail/debugger_detect_windows_api.hpp>
#elif (CPP_EXTENSIONS_DEBUGGER_DETECT == CPP_EXTENSIONS_DEBUGGER_DETECT_APPLE_XNU_KERNEL_SYSCTL)
#include <cpp_extensions/debugger/detail/debugger_detect_apple_xnu_kernel_sysctl.hpp>
#elif (CPP_EXTENSIONS_DEBUGGER_DETECT == CPP_EXTENSIONS_DEBUGGER_DETECT_LINUX_PROCFS)
#include <cpp_extensions/debugger/detail/debugger_detect_linux_procfs.hpp>
#endif // (CPP_EXTENSIONS_DEBUGGER_DETECT == CPP_EXTENSIONS_DEBUGGER_DETECT_WINDOWS_API)
#if (CPP_EXTENSIONS_DEBUGGER_INTERRUPT == CPP_EXTENSIONS_DEBUGGER_INTERRUPT_WINDOWS_API)
#include <cpp_extensions/debugger/detail/debugger_interrupt_windows_api.hpp>
#elif (CPP_EXTENSIONS_DEBUGGER_INTERRUPT == CPP_EXTENSIONS_DEBUGGER_INTERRUPT_GCC_CLANG_INTRINSICS)
#include <cpp_extensions/debugger/detail/debugger_interrupt_gcc_clang_intrinsics.hpp>
#endif // (CPP_EXTENSIONS_DEBUGGER_INTERRUPT == CPP_EXTENSIONS_DEBUGGER_INTERRUPT_WINDOWS_API)

#include <iostream>

namespace cpp_extensions
{
	namespace debugger
	{
		static inline bool attached()
		{
			return detail::attached();
		}

		static inline void interrupt()
		{
			detail::interrupt();
		}

		static inline bool interrupt_if_attached()
		{
			bool const was_attached = attached();

			if (was_attached)
			{
				interrupt();
			}

			return was_attached;
		}

		static inline void assert_expression(bool const value, char const* message)
		{
			if (!value)
			{
				std::cerr << "cpp_extensions::debugger::assert_expression - test failed: " << message << std::endl << std::flush;

				interrupt_if_attached();

				std::terminate();
			}
		}
	}
}

#endif // _CPP_EXTENSIONS_DEBUGGER_DEBUGGER_HPP_

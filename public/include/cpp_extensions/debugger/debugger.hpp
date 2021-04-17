#ifndef _CPP_EXTENSIONS_DEBUGGER_DEBUGGER_HPP_
#define _CPP_EXTENSIONS_DEBUGGER_DEBUGGER_HPP_

#include <cpp_extensions/prolog.hpp>

#include <iostream>

namespace cpp_extensions
{
	namespace debugger
	{
		static inline bool attached()
		{
			return false;
		}

		static inline void interrupt()
		{
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
				std::cerr << message << std::endl << std::flush;

				if (!interrupt_if_attached())
				{
					std::terminate();
				}
			}
		}
	}
}

#endif // _CPP_EXTENSIONS_DEBUGGER_DEBUGGER_HPP_

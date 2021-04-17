#ifndef _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_INTERRUPT_WINDOWS_API_HPP_
#define _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_INTERRUPT_WINDOWS_API_HPP_

namespace cpp_extensions
{
	namespace debugger
	{
		namespace detail
		{
			static inline void interrupt()
			{
				::DebugBreak();
			}
		}
	}
}

#endif // _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_INTERRUPT_WINDOWS_API_HPP_

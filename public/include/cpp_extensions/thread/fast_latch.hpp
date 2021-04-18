#ifndef _CPP_EXTENSIONS_THREAD_FAST_LATCH_HPP_
#define _CPP_EXTENSIONS_THREAD_FAST_LATCH_HPP_

#include <cpp_extensions/prolog.hpp>

#ifndef CPP_EXTENSIONS_FAST_LATCH_TYPE
#include <latch>
#endif // CPP_EXTENSIONS_FAST_LATCH_TYPE

namespace cpp_extensions
{
	namespace thread
	{
		using fast_latch =
#ifndef CPP_EXTENSIONS_FAST_LATCH_TYPE
			std::latch
#else // CPP_EXTENSIONS_FAST_LATCH_TYPE
			CPP_EXTENSIONS_FAST_LATCH_TYPE
#endif // CPP_EXTENSIONS_FAST_LATCH_TYPE
			;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_FAST_LATCH_HPP_

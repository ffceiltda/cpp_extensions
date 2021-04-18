#ifndef _CPP_EXTENSIONS_THREAD_FAST_BARRIER_HPP_
#define _CPP_EXTENSIONS_THREAD_FAST_BARRIER_HPP_

#include <cpp_extensions/prolog.hpp>

#ifndef CPP_EXTENSIONS_FAST_BARRIER_TYPE
#include <barrier>
#endif // CPP_EXTENSIONS_FAST_BARRIER_TYPE

namespace cpp_extensions
{
	namespace thread
	{
		using fast_barrier =
#ifndef CPP_EXTENSIONS_FAST_BARRIER_TYPE
			std::barrier
#else // CPP_EXTENSIONS_FAST_BARRIER_TYPE
			CPP_EXTENSIONS_FAST_BARRIER_TYPE
#endif // CPP_EXTENSIONS_FAST_BARRIER_TYPE
			;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_FAST_BARRIER_HPP_

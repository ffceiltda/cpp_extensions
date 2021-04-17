#ifndef _CPP_EXTENSIONS_THREAD_FAST_TIMED_MUTEX_HPP_
#define _CPP_EXTENSIONS_THREAD_FAST_TIMED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>

#ifndef CPP_EXTENSIONS_FAST_TIMED_MUTEX_TYPE
#include <mutex>
#endif // CPP_EXTENSIONS_FAST_TIMED_MUTEX_TYPE

namespace cpp_extensions
{
	namespace thread
	{
		using fast_timed_mutex =
#ifndef CPP_EXTENSIONS_FAST_TIMED_MUTEX_TYPE
			std::timed_mutex
#else // CPP_EXTENSIONS_FAST_TIMED_MUTEX_TYPE
			CPP_EXTENSIONS_FAST_TIMED_MUTEX_TYPE
#endif // CPP_EXTENSIONS_FAST_TIMED_MUTEX_TYPE
			;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_FAST_TIMED_MUTEX_HPP_

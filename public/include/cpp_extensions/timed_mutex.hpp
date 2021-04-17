#ifndef _CPP_EXTENSIONS_TIMED_MUTEX_HPP_
#define _CPP_EXTENSIONS_TIMED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_timed_mutex.hpp>
#include <cpp_extensions/thread/checked_timed_mutex.hpp>

namespace cpp_extensions
{
	using timed_mutex =
#ifndef CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		thread::fast_timed_mutex
#else // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		thread::checked_timed_mutex
#endif // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		;
}

#endif // _CPP_EXTENSIONS_TIMED_MUTEX_HPP_

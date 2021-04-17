#ifndef _CPP_EXTENSIONS_SHARED_MUTEX_HPP_
#define _CPP_EXTENSIONS_SHARED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_shared_mutex.hpp>
#include <cpp_extensions/thread/checked_shared_mutex.hpp>

namespace cpp_extensions
{
	using shared_mutex =
#ifndef CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		thread::fast_shared_mutex
#else // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		thread::checked_shared_mutex
#endif // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		;
}

#endif // _CPP_EXTENSIONS_SHARED_MUTEX_HPP_

#ifndef _CPP_EXTENSIONS_MUTEX_HPP_
#define _CPP_EXTENSIONS_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_mutex.hpp>
#include <cpp_extensions/thread/checked_mutex.hpp>

namespace cpp_extensions
{
	using mutex =
#ifndef CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		thread::fast_mutex
#else // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		thread::checked_mutex
#endif // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		;
}

#endif // _CPP_EXTENSIONS_MUTEX_HPP_

#ifndef _CPP_EXTENSIONS_SHARED_TIMED_MUTEX_HPP_
#define _CPP_EXTENSIONS_SHARED_TIMED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_shared_timed_mutex.hpp>
#include <cpp_extensions/thread/checked_shared_timed_mutex.hpp>

namespace cpp_extensions
{
	using shared_timed_mutex =
#ifndef CPP_EXTENSIONS_CHECKED_SYNCHRONIZATION_OBJECTS
		thread::fast_shared_timed_mutex
#else // CPP_EXTENSIONS_CHECKED_SYNCHRONIZATION_OBJECTS
		thread::checked_shared_timed_mutex
#endif // CPP_EXTENSIONS_CHECKED_SYNCHRONIZATION_OBJECTS
		;
}

#endif // _CPP_EXTENSIONS_SHARED_TIMED_MUTEX_HPP_

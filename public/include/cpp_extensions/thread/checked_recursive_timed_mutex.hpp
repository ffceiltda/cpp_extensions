#ifndef _CPP_EXTENSIONS_THREAD_CHECKED_RECURSIVE_TIMED_MUTEX_HPP_
#define _CPP_EXTENSIONS_THREAD_CHECKED_RECURSIVE_TIMED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_recursive_timed_mutex.hpp>
#include <cpp_extensions/thread/detail/checked_unique_lock_timed_tracker.hpp>

namespace cpp_extensions
{
	namespace thread
	{
		using checked_recursive_timed_mutex = detail::checked_unique_lock_timed_tracker<fast_recursive_timed_mutex, true>;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_CHECKED_RECURSIVE_TIMED_MUTEX_HPP_

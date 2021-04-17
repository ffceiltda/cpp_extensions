#ifndef _CPP_EXTENSIONS_THREAD_CHECKED_TIMED_MUTEX_HPP_
#define _CPP_EXTENSIONS_THREAD_CHECKED_TIMED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_timed_mutex.hpp>
#include <cpp_extensions/thread/detail/checked_unique_lock_timed_tracker.hpp>

namespace cpp_extensions
{
	namespace thread
	{
		using checked_timed_mutex = detail::checked_unique_lock_timed_tracker<fast_timed_mutex, false>;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_CHECKED_TIMED_MUTEX_HPP_

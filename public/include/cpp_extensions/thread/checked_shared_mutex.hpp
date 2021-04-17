#ifndef _CPP_EXTENSIONS_THREAD_CHECKED_SHARED_MUTEX_HPP_
#define _CPP_EXTENSIONS_THREAD_CHECKED_SHARED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_shared_mutex.hpp>
#include <cpp_extensions/thread/detail/checked_shared_lock_tracker.hpp>

namespace cpp_extensions
{
	namespace thread
	{
		using checked_shared_mutex = detail::checked_shared_lock_tracker<fast_shared_mutex, false>;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_CHECKED_SHARED_MUTEX_HPP_

#ifndef _CPP_EXTENSIONS_THREAD_CHECKED_SPIN_LOCK_HPP_
#define _CPP_EXTENSIONS_THREAD_CHECKED_SPIN_LOCK_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_spin_lock.hpp>
#include <cpp_extensions/thread/detail/checked_unique_lock_tracker.hpp>

namespace cpp_extensions
{
	namespace thread
	{
		using checked_spin_lock = detail::checked_unique_lock_tracker<fast_spin_lock, false>;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_CHECKED_SPIN_LOCK_HPP_

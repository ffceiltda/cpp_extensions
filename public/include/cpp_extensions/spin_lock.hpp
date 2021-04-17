#ifndef _CPP_EXTENSIONS_SPIN_LOCK_HPP_
#define _CPP_EXTENSIONS_SPIN_LOCK_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_spin_lock.hpp>
#include <cpp_extensions/thread/checked_spin_lock.hpp>

namespace cpp_extensions
{
	using spin_lock =
#ifndef CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		thread::fast_spin_lock
#else // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		thread::checked_spin_lock
#endif // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES
		;
}

#endif // _CPP_EXTENSIONS_SPIN_LOCK_HPP_

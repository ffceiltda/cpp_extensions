#ifndef _CPP_EXTENSIONS_THREAD_FAST_SPIN_LOCK_HPP_
#define _CPP_EXTENSIONS_THREAD_FAST_SPIN_LOCK_HPP_

#include <cpp_extensions/prolog.hpp>

#ifndef CPP_EXTENSIONS_FAST_SPIN_LOCK_TYPE
#include <cpp_extensions/thread/spin_lock.hpp>
#endif // CPP_EXTENSIONS_FAST_SPIN_LOCK_TYPE

namespace cpp_extensions
{
	namespace thread
	{
		using fast_spin_lock =
#ifndef CPP_EXTENSIONS_FAST_SPIN_LOCK_TYPE
			spin_lock
#else // CPP_EXTENSIONS_FAST_SPIN_LOCK_TYPE
			CPP_EXTENSIONS_FAST_SPIN_LOCK_TYPE
#endif // CPP_EXTENSIONS_FAST_SPIN_LOCK_TYPE
			;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_FAST_SPIN_LOCK_HPP_

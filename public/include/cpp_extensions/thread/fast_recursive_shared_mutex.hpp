#ifndef _CPP_EXTENSIONS_FAST_RECURSIVE_SHARED_MUTEX_HPP_
#define _CPP_EXTENSIONS_FAST_RECURSIVE_SHARED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>

#ifndef CPP_EXTENSIONS_FAST_RECURSIVE_SHARED_MUTEX_TYPE
#include <cpp_extensions/thread/recursive_shared_mutex.hpp>
#endif // CPP_EXTENSIONS_FAST_RECURSIVE_SHARED_MUTEX_TYPE

namespace cpp_extensions
{
	namespace thread
	{
		using fast_recursive_shared_mutex =
#ifndef CPP_EXTENSIONS_FAST_RECURSIVE_SHARED_MUTEX_TYPE
			recursive_shared_mutex
#else // CPP_EXTENSIONS_FAST_RECURSIVE_SHARED_MUTEX_TYPE
			CPP_EXTENSIONS_FAST_RECURSIVE_SHARED_MUTEX_TYPE
#endif // CPP_EXTENSIONS_FAST_RECURSIVE_SHARED_MUTEX_TYPE
			;
	}
}

#endif // _CPP_EXTENSIONS_FAST_RECURSIVE_SHARED_MUTEX_HPP_

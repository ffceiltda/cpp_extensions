#ifndef _CPP_EXTENSIONS_FAST_SHARED_MUTEX_HPP_
#define _CPP_EXTENSIONS_FAST_SHARED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>

#ifndef CPP_EXTENSIONS_FAST_SHARED_MUTEX_TYPE
#include <shared_mutex>
#endif // CPP_EXTENSIONS_FAST_SHARED_MUTEX_TYPE

namespace cpp_extensions
{
	namespace thread
	{
		using fast_shared_mutex =
#ifndef CPP_EXTENSIONS_FAST_SHARED_MUTEX_TYPE
			std::shared_mutex
#else // CPP_EXTENSIONS_FAST_SHARED_MUTEX_TYPE
			CPP_EXTENSIONS_FAST_SHARED_MUTEX_TYPE
#endif // CPP_EXTENSIONS_FAST_SHARED_MUTEX_TYPE
			;
	}
}

#endif // _CPP_EXTENSIONS_FAST_SHARED_MUTEX_HPP_
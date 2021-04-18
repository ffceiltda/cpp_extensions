#ifndef _CPP_EXTENSIONS_THREAD_FAST_binary_semaphore_HPP_
#define _CPP_EXTENSIONS_THREAD_FAST_binary_semaphore_HPP_

#include <cpp_extensions/prolog.hpp>

#ifndef CPP_EXTENSIONS_FAST_BINARY_SEMAPHORE_TYPE
#include <semaphore>
#endif // CPP_EXTENSIONS_FAST_BINARY_SEMAPHORE_TYPE

namespace cpp_extensions
{
	namespace thread
	{
		using fast_binary_semaphore =
#ifndef CPP_EXTENSIONS_FAST_BINARY_SEMAPHORE_TYPE
			std::binary_semaphore
#else // CPP_EXTENSIONS_FAST_BINARY_SEMAPHORE_TYPE
			CPP_EXTENSIONS_FAST_BINARY_SEMAPHORE_TYPE
#endif // CPP_EXTENSIONS_FAST_BINARY_SEMAPHORE_TYPE
			;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_FAST_binary_semaphore_HPP_

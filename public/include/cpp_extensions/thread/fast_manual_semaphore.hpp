#ifndef _CPP_EXTENSIONS_THREAD_FAST_MANUAL_SEMAPHORE_HPP_
#define _CPP_EXTENSIONS_THREAD_FAST_MANUAL_SEMAPHORE_HPP_

#include <cpp_extensions/prolog.hpp>

#ifndef CPP_EXTENSIONS_FAST_MANUAL_SEMAPHORE_TYPE
#include <cpp_extensions/thread/manual_semaphore.hpp>
#endif // CPP_EXTENSIONS_FAST_MANUAL_SEMAPHORE_TYPE

namespace cpp_extensions
{
	namespace thread
	{
		using fast_manual_semaphore =
#ifndef CPP_EXTENSIONS_FAST_MANUAL_SEMAPHORE_TYPE
			manual_semaphore
#else // CPP_EXTENSIONS_FAST_MANUAL_SEMAPHORE_TYPE
			CPP_EXTENSIONS_FAST_MANUAL_SEMAPHORE_TYPE
#endif // CPP_EXTENSIONS_FAST_MANUAL_SEMAPHORE_TYPE
			;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_FAST_MANUAL_SEMAPHORE_HPP_

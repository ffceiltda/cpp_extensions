#ifndef _CPP_EXTENSIONS_COUNTING_SEMAPHORE_HPP_
#define _CPP_EXTENSIONS_COUNTING_SEMAPHORE_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_counting_semaphore.hpp>

namespace cpp_extensions
{
	using counting_semaphore = thread::fast_counting_semaphore;
}

#endif // _CPP_EXTENSIONS_COUNTING_SEMAPHORE_HPP_

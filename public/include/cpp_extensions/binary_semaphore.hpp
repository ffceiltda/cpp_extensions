#ifndef _CPP_EXTENSIONS_BINARY_SEMAPHORE_HPP_
#define _CPP_EXTENSIONS_BINARY_SEMAPHORE_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_binary_semaphore.hpp>

namespace cpp_extensions
{
	using binary_semaphore = thread::fast_binary_semaphore;
}

#endif // _CPP_EXTENSIONS_BINARY_SEMAPHORE_HPP_

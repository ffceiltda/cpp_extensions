#ifndef _CPP_EXTENSIONS_MANUAL_SEMAPHORE_HPP_
#define _CPP_EXTENSIONS_MANUAL_SEMAPHORE_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_manual_semaphore.hpp>

namespace cpp_extensions
{
	using manual_semaphore = thread::fast_manual_semaphore;
}

#endif // _CPP_EXTENSIONS_MANUAL_SEMAPHORE_HPP_

#ifndef _CPP_EXTENSIONS_BARRIER_HPP_
#define _CPP_EXTENSIONS_BARRIER_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_barrier.hpp>

namespace cpp_extensions
{
	using barrier = thread::fast_barrier;
}

#endif // _CPP_EXTENSIONS_BARRIER_HPP_

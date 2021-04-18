#ifndef _CPP_EXTENSIONS_LATCH_HPP_
#define _CPP_EXTENSIONS_LATCH_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_latch.hpp>

namespace cpp_extensions
{
	using latch = thread::fast_latch;
}

#endif // _CPP_EXTENSIONS_LATCH_HPP_

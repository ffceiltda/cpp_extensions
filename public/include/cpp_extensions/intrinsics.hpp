#ifndef _CPP_EXTENSIONS_INSTRINSICS_HPP_
#define _CPP_EXTENSIONS_INSTRINSICS_HPP_

#include <cpp_extensions/prolog.hpp>

extern "C"
{
#include <immintrin.h>
}

namespace cpp_extensions
{
	namespace intrinsics
	{
		static inline void cpu_pause()
		{
			_mm_pause();
		}
	}
}

#endif // _CPP_EXTENSIONS_INSTRINSICS_HPP_

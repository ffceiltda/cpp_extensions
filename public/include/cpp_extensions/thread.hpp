#ifndef _CPP_EXTENSIONS_THREAD_HPP_
#define _CPP_EXTENSIONS_THREAD_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/intrinsics.hpp>

#include <thread>

namespace cpp_extensions
{
	namespace this_thread
	{
		static inline void pause_or_yield()
		{
			static bool pausing = false;

			const bool value = (pausing = !pausing);

			if (value)
			{
				cpp_extensions::intrinsics::cpu_pause();
			}
			else
			{
				std::this_thread::yield();
			}
		}
	}
}

#endif // _CPP_EXTENSIONS_THREAD_HPP_

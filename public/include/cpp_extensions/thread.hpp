#ifndef _CPP_EXTENSIONS_THREAD_HPP_
#define _CPP_EXTENSIONS_THREAD_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/intrinsics.hpp>

#include <thread>

namespace cpp_extensions
{
	namespace this_thread
	{
		static inline void yield()
		{
			static std::atomic<int> value {};

			int const new_value = value.fetch_add(1, std::memory_order_acquire);
			 
			if (new_value < 16)
			{
				cpp_extensions::intrinsics::cpu_pause();
			}
			else
			{
				std::this_thread::yield();

				value.store(0, std::memory_order_release);
			}
		}
	}
}

#endif // _CPP_EXTENSIONS_THREAD_HPP_

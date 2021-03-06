#ifndef _CPP_EXTENSIONS_THREAD_FAST_CONDITION_VARIABLE_HPP_
#define _CPP_EXTENSIONS_THREAD_FAST_CONDITION_VARIABLE_HPP_

#include <cpp_extensions/prolog.hpp>

#if !(defined(CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_TYPE) && defined(CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_MUTEX_TYPE))
#include <condition_variable>
#endif // !(defined(CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_TYPE) && defined(CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_MUTEX_TYPE))

namespace cpp_extensions
{
	namespace thread
	{
#if !(defined(CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_TYPE) && defined(CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_MUTEX_TYPE))
		using fast_condition_variable = std::condition_variable;
		using fast_condition_variable_mutex = std::mutex;
#else //  !(defined(CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_TYPE) && defined(CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_MUTEX_TYPE))
		using fast_condition_variable = CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_TYPE;
		using fast_condition_variable_mutex = CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_MUTEX_TYPE;
#endif // !(defined(CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_TYPE) && defined(CPP_EXTENSIONS_FAST_CONDITION_VARIABLE_MUTEX_TYPE))
	}
}

#endif // _CPP_EXTENSIONS_THREAD_FAST_CONDITION_VARIABLE_HPP_

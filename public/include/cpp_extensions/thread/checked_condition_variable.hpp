#ifndef _CPP_EXTENSIONS_THREAD_CHECKED_CONDITION_VARIABLE_HPP_
#define _CPP_EXTENSIONS_THREAD_CHECKED_CONDITION_VARIABLE_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_condition_variable.hpp>

namespace cpp_extensions
{
	namespace thread
	{
		// There's no checked condition_variable version yet, so
		// use the default fastest condition_variable for system

		using checked_condition_variable = fast_condition_variable;
		using checked_condition_variable_mutex = fast_condition_variable_mutex;
	}
}

#endif // _CPP_EXTENSIONS_THREAD_CHECKED_CONDITION_VARIABLE_HPP_

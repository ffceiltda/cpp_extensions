#ifndef _CPP_EXTENSIONS_CONDITION_VARIABLE_HPP_
#define _CPP_EXTENSIONS_CONDITION_VARIABLE_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_condition_variable.hpp>
#include <cpp_extensions/thread/checked_condition_variable.hpp>

namespace cpp_extensions
{
#ifndef CPP_EXTENSIONS_CHECKED_DEBUG_CONDITION_VARIABLEES
	using condition_variable = thread::fast_condition_variable;
	using condition_variable_mutex = thread::fast_condition_variable_mutex;
#else // CPP_EXTENSIONS_CHECKED_DEBUG_CONDITION_VARIABLEES
	using condition_variable = thread::checked_condition_variable;
	using condition_variable_mutex = thread::checked_condition_variable_mutex;
#endif // CPP_EXTENSIONS_CHECKED_DEBUG_CONDITION_VARIABLEES
}

#endif // _CPP_EXTENSIONS_CONDITION_VARIABLE_HPP_

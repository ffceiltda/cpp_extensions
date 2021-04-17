#ifndef _CPP_EXTENSIONS_MAKE_UNIQUE_LOCK_HPP_
#define _CPP_EXTENSIONS_MAKE_UNIQUE_LOCK_HPP_

#include <cpp_extensions/prolog.hpp>

#include <mutex>

namespace cpp_extensions
{
	template <typename LockableType, typename... ArgumentTypes>
    [[nodiscard]]
	static inline std::unique_lock<LockableType> make_unique_lock(LockableType& lockable, ArgumentTypes&&... argument_values) noexcept
		(noexcept(std::unique_lock<LockableType>(lockable, std::forward<ArgumentTypes>(argument_values) ...)))
	{
		return std::unique_lock<LockableType>(lockable, std::forward<ArgumentTypes>(argument_values) ...);
	}
}

#endif // _CPP_EXTENSIONS_MAKE_UNIQUE_LOCK_HPP_

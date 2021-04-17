#ifndef _CPP_EXTENSIONS_MAKE_SHARED_LOCK_HPP_
#define _CPP_EXTENSIONS_MAKE_SHARED_LOCK_HPP_

#include <cpp_extensions/prolog.hpp>

#include <shared_mutex>

namespace cpp_extensions
{
	template <typename LockableType, typename... ArgumentTypes>
    [[nodiscard]]
	static inline std::shared_lock<LockableType> make_shared_lock(LockableType& lockable, ArgumentTypes&&... argument_values) noexcept
		(noexcept(std::shared_lock<LockableType>(lockable, std::forward<ArgumentTypes>(argument_values) ...)))
	{
		return std::shared_lock<LockableType>(lockable, std::forward<ArgumentTypes>(argument_values) ...);
	}
}

#endif // _CPP_EXTENSIONS_MAKE_SHARED_LOCK_HPP_

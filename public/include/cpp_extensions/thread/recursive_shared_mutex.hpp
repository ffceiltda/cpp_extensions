#ifndef _CPP_EXTENSIONS_THREAD_RECURSIVE_SHARED_MUTEX_HPP_
#define _CPP_EXTENSIONS_THREAD_RECURSIVE_SHARED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/debugger.hpp>
#include <cpp_extensions/thread/detail/checked_unique_lock_tracker.hpp>
#include <cpp_extensions/shared_timed_mutex.hpp>

namespace cpp_extensions
{
    namespace thread
    {
        class recursive_shared_mutex
            : public detail::checked_unique_lock_tracker<cpp_extensions::shared_timed_mutex, true>
        {
        public:
            constexpr recursive_shared_mutex() noexcept = default;

            recursive_shared_mutex(recursive_shared_mutex const&) = delete;
            recursive_shared_mutex(recursive_shared_mutex&&) = delete;

            recursive_shared_mutex& operator = (recursive_shared_mutex const&) = delete;
            recursive_shared_mutex& operator = (recursive_shared_mutex&&) = delete;

            void lock_shared()
            {
                m_lockable.lock_shared();
            }

            [[nodiscard]]
            bool try_lock_shared()
            {
                return m_lockable.try_lock_shared();
            }

            void unlock_shared()
            {
                m_lockable.unlock_shared();
            }
        };
    }
}

#endif // _CPP_EXTENSIONS_THREAD_RECURSIVE_SHARED_MUTEX_HPP_

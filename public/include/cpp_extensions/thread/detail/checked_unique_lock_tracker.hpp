#ifndef _CPP_EXTENSIONS_THREAD_CHECKED_UNIQUE_LOCK_TRACKER_HPP_
#define _CPP_EXTENSIONS_THREAD_CHECKED_UNIQUE_LOCK_TRACKER_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/debugger.hpp>
#include <cpp_extensions/make_unique_lock.hpp>
#ifdef CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES_USE_SPIN_LOCK
#include <cpp_extensions/thread/spin_lock.hpp>
#endif // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES_USE_SPIN_LOCK

#include <mutex>
#include <thread>
#include <cstdint>

namespace cpp_extensions
{
    namespace thread
    {
        namespace detail
        {
            template <typename LockableType, bool const Recursive>
            class checked_unique_lock_tracker
            {
            public:
                using lockable_type = LockableType;

                constexpr static bool const recursive = Recursive;

            protected:
                lockable_type m_lockable;

#ifdef CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES_USE_SPIN_LOCK
                using internal_lockable_type = cpp_extensions::thread::spin_lock;
#endif // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES_USE_SPIN_LOCK
#ifdef CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES_USE_MUTEX
                using internal_lockable_type = std::mutex;
#endif // CPP_EXTENSIONS_CHECKED_DEBUG_MUTEXES_USE_MUTEX

            private:
                internal_lockable_type m_unique_lock_tracker_mutex;
                std::thread::id m_unique_lock_thread_id = {};
                size_t m_unique_lock_recursion_count = 0;

            protected:
                template <typename LockFunctorType>
                [[nodiscard]]
                bool lock_track_unique_current_thread(LockFunctorType&& lock_functor)
                {
                    auto const locked = lock_functor();

                    if (locked)
                    {
                        auto const unique_lock_thread_id = std::this_thread::get_id();

                        auto recursion_lock = cpp_extensions::make_unique_lock(m_unique_lock_tracker_mutex);

                        m_unique_lock_thread_id = unique_lock_thread_id;
                        m_unique_lock_recursion_count = 1;
                    }

                    return locked;
                }

                [[nodiscard]]
                bool try_lock_track_unique_current_thread()
                {
                    auto const unique_lock_thread_id = std::this_thread::get_id();

                    auto recursion_lock = cpp_extensions::make_unique_lock(m_unique_lock_tracker_mutex);

                    if (m_unique_lock_thread_id == unique_lock_thread_id)
                    {
                        if constexpr (recursive)
                        {
                            ++m_unique_lock_recursion_count;

                            return true;
                        }
                        else
                        {
                            throw std::logic_error("non recursive object already locked by this thread");
                        }
                    }
                     
                    return false;
                }

                template <typename UnlockFunctorType>
                void unlock_track_unique_current_thread(UnlockFunctorType&& unlock_functor)
                {
                    auto const unique_lock_thread_id = std::this_thread::get_id();

                    auto recursion_lock = cpp_extensions::make_unique_lock(m_unique_lock_tracker_mutex);

                    if (m_unique_lock_thread_id == unique_lock_thread_id)
                    {
                        [[likely]]

                        if (--m_unique_lock_recursion_count == 0)
                        {
                            m_unique_lock_thread_id = {};

                            recursion_lock.unlock();

                            unlock_functor();
                        }
                    }
                    else
                    {
                        [[unlikely]]

                        throw std::logic_error("object not locked by this thread");
                    }
                }

            public:
                constexpr checked_unique_lock_tracker() noexcept = default;

                checked_unique_lock_tracker(checked_unique_lock_tracker const&) = delete;
                checked_unique_lock_tracker(checked_unique_lock_tracker&&) = delete;

                checked_unique_lock_tracker& operator = (checked_unique_lock_tracker const&) = delete;
                checked_unique_lock_tracker& operator = (checked_unique_lock_tracker&&) = delete;

                void lock()
                {
                    if (try_lock_track_unique_current_thread())
                    {
                        return;
                    }

                    bool result = lock_track_unique_current_thread([this]() { m_lockable.lock(); return true; });

                    if (!result)
                    {
                        [[unlikely]]
                        cpp_extensions::debugger::assert_expression(result, "lock() method failure");
                    }
                }

                [[nodiscard]]
                bool try_lock()
                {
                    if (try_lock_track_unique_current_thread())
                    {
                        return true;
                    }

                    return lock_track_unique_current_thread([this]() { return m_lockable.try_lock(); });
                }

                void unlock()
                {
                    unlock_track_unique_current_thread([this]() { m_lockable.unlock(); });
                }
            };
        }
    }
}

#endif // _CPP_EXTENSIONS_THREAD_CHECKED_UNIQUE_LOCK_TRACKER_HPP_

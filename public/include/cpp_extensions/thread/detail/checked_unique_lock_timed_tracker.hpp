#ifndef _CPP_EXTENSIONS_THREAD_CHECKED_UNIQUE_LOCK_TIMED_TRACKER_HPP_
#define _CPP_EXTENSIONS_THREAD_CHECKED_UNIQUE_LOCK_TIMED_TRACKER_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/detail/checked_unique_lock_tracker.hpp>

#include <chrono>

namespace cpp_extensions
{
    namespace thread
    {
        namespace detail
        {
            template <typename LockableType, bool const Recursive>
            class checked_unique_lock_timed_tracker
                : public checked_unique_lock_tracker<LockableType, Recursive>
            {
            public:
                constexpr checked_unique_lock_timed_tracker() noexcept = default;

                checked_unique_lock_timed_tracker(checked_unique_lock_timed_tracker const&) = delete;
                checked_unique_lock_timed_tracker(checked_unique_lock_timed_tracker&&) = delete;

                checked_unique_lock_timed_tracker& operator = (checked_unique_lock_timed_tracker const&) = delete;
                checked_unique_lock_timed_tracker& operator = (checked_unique_lock_timed_tracker&&) = delete;

                template <class Rep, class Period>
                [[nodiscard]]
                bool try_lock_for(std::chrono::duration<Rep, Period> const& timeout_duration)
                {
                    if (this->try_lock_track_unique_recursive_current_thread())
                    {
                        return true;
                    }

                    return this->lock_track_unique_recursive_current_thread([this, &timeout_duration]() { return this->m_lockable.try_lock_for(timeout_duration); });
                }

                template <class Clock, class Duration>
                [[nodiscard]]
                bool try_lock_until(std::chrono::time_point<Clock, Duration> const& timeout_time)
                {
                    if (this->try_lock_track_unique_recursive_current_thread())
                    {
                        return true;
                    }

                    return this->lock_track_unique_recursive_current_thread([this, &timeout_time]() { return this->m_lockable.try_lock_until(timeout_time); });
                }
            };
        }
    }
}

#endif // _CPP_EXTENSIONS_THREAD_CHECKED_UNIQUE_LOCK_TRACKER_HPP_

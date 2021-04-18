#ifndef _CPP_EXTENSIONS_THREAD_CHECKED_SHARED_LOCK_TIMED_TRACKER_HPP_
#define _CPP_EXTENSIONS_THREAD_CHECKED_SHARED_LOCK_TIMED_TRACKER_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/detail/checked_shared_lock_tracker.hpp>
#include <cpp_extensions/thread/detail/checked_unique_lock_timed_tracker.hpp>

namespace cpp_extensions
{
	namespace thread
	{
		namespace detail
		{
			template <typename LockableType, bool const Recursive>
			class checked_shared_lock_timed_tracker
				: public checked_shared_lock_tracker_template<LockableType, checked_unique_lock_timed_tracker<LockableType, Recursive>>
			{
			public:
				constexpr checked_shared_lock_timed_tracker() noexcept = default;

				checked_shared_lock_timed_tracker(checked_shared_lock_timed_tracker const&) = delete;
				checked_shared_lock_timed_tracker(checked_shared_lock_timed_tracker&&) = delete;

				checked_shared_lock_timed_tracker& operator = (checked_shared_lock_timed_tracker const&) = delete;
				checked_shared_lock_timed_tracker& operator = (checked_shared_lock_timed_tracker&&) = delete;

				template <class Rep, class Period>
				[[nodiscard]]
				bool try_lock_shared_for(std::chrono::duration<Rep, Period> const& timeout_duration)
				{
					return this->lock_track_shared_recursive_current_thread([this, &timeout_duration]() -> bool { return this->m_lockable.try_lock_shared_for(timeout_duration); });
				}

				template <class Clock, class Duration>
				[[nodiscard]]
				bool try_lock_shared_until(std::chrono::time_point<Clock, Duration> const& timeout_time)
				{
					return this->lock_track_shared_recursive_current_thread([this, &timeout_time]() -> bool { return this->m_lockable.try_lock_shared_until(timeout_time); });
				}
			};
		}
	}
}

#endif // _CPP_EXTENSIONS_THREAD_CHECKED_SHARED_LOCK_TIMED_TRACKER_HPP_

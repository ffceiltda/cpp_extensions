#ifndef _CPP_EXTENSIONS_THREAD_RECURSIVE_SHARED_TIMED_MUTEX_HPP_
#define _CPP_EXTENSIONS_THREAD_RECURSIVE_SHARED_TIMED_MUTEX_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/recursive_shared_mutex.hpp>

#include <chrono>

namespace cpp_extensions
{
	namespace thread
	{
		class recursive_shared_timed_mutex final
			: public recursive_shared_mutex
		{
		public:
			constexpr recursive_shared_timed_mutex() noexcept = default;

			recursive_shared_timed_mutex(recursive_shared_timed_mutex const&) = delete;
			recursive_shared_timed_mutex(recursive_shared_timed_mutex&&) = delete;

			recursive_shared_timed_mutex& operator = (recursive_shared_timed_mutex const&) = delete;
			recursive_shared_timed_mutex& operator = (recursive_shared_timed_mutex&&) = delete;

			template <class Rep, class Period>
			[[nodiscard]]
			bool try_lock_for(std::chrono::duration<Rep, Period> const& timeout_duration)
			{
				if (this->try_lock_track_unique_current_thread())
				{
					return true;
				}

				return this->lock_track_unique_current_thread([this, &timeout_duration]() -> bool { return this->m_lockable.try_lock_for(timeout_duration); });
			}

			template <class Clock, class Duration>
			[[nodiscard]]
			bool try_lock_until(std::chrono::time_point<Clock, Duration> const& timeout_time)
			{
				if (this->try_lock_track_unique_current_thread())
				{
					return true;
				}

				return this->lock_track_unique_current_thread([this, &timeout_time]() -> bool { return this->m_lockable.try_lock_until(timeout_time); });
			}

			template <class Rep, class Period>
			[[nodiscard]]
			bool try_lock_shared_for(std::chrono::duration<Rep, Period> const& timeout_duration)
			{
				return this->m_lockable.try_lock_shared_for(timeout_duration);
			}

			template <class Clock, class Duration>
			[[nodiscard]]
			bool try_lock_shared_until(std::chrono::time_point<Clock, Duration> const& timeout_time)
			{
				return this->m_lockable.try_lock_shared_until(timeout_time);
			}
		};
	}
}

#endif // _CPP_EXTENSIONS_THREAD_RECURSIVE_SHARED_TIMED_MUTEX_HPP_

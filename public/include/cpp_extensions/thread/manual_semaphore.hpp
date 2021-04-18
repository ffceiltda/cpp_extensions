#ifndef _CPP_EXTENSIONS_THREAD_MANUAL_SEMAPHORE_HPP_
#define _CPP_EXTENSIONS_THREAD_MANUAL_SEMAPHORE_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/fast_binary_semaphore.hpp>

#include <atomic>

namespace cpp_extensions
{
	namespace thread
	{
		class manual_semaphore final
		{
		private:
			fast_binary_semaphore m_semaphore{ 0 };
			std::atomic<bool> m_state = { false };

		public:
			manual_semaphore() noexcept = default;

			explicit manual_semaphore(bool const initial_state) noexcept
				: m_semaphore(initial_state ? 1 : 0), m_state{ initial_state }
			{
			}

			manual_semaphore(manual_semaphore const&) = delete;
			manual_semaphore(manual_semaphore&&) = delete;

			manual_semaphore& operator = (manual_semaphore const&) = delete;
			manual_semaphore& operator = (manual_semaphore&&) = delete;

			[[nodiscard]]
			bool is_set() const noexcept
			{
				return m_state.load(std::memory_order_relaxed);
			}

			void set()
			{
				if (!is_set())
				{
					m_state.store(true, std::memory_order_release);

					m_semaphore.release();
				}
			}

			void unset()
			{
				if (is_set())
				{
					m_state.store(false, std::memory_order_release);

					if (!m_semaphore.try_acquire())
					{
						return;
					}
				}
			}

			void acquire()
			{
				while (!is_set())
				{
					m_semaphore.acquire();

					if (is_set())
					{
						m_semaphore.release();

						break;
					}
				}
			}

			[[nodiscard]]
			bool try_acquire()
			{
				if (!is_set())
				{
					if (m_semaphore.try_acquire())
					{
						if (is_set())
						{
							m_semaphore.release();
						}
					}
				}

				return is_set();
			}

			template<class Rep, class Period>
			[[nodiscard]]
			bool try_acquire_for(std::chrono::duration<Rep, Period> const& timeout_duration)
			{
				if (!is_set())
				{
					if (m_semaphore.try_acquire_for(timeout_duration))
					{
						if (is_set())
						{
							m_semaphore.release();
						}
					}
				}

				return is_set();
			}

			template <class Clock, class Duration>
			[[nodiscard]]
			bool try_acquire_until(std::chrono::duration<Clock, Duration> const& timeout_time)
			{
				if (!is_set())
				{
					if (m_semaphore.try_acquire_until(timeout_time))
					{
						if (is_set())
						{
							m_semaphore.release();
						}
					}
				}

				return is_set();
			}

			void release()
			{
			}
		};
	}
}

#endif // _CPP_EXTENSIONS_THREAD_MANUAL_SEMAPHORE_HPP_

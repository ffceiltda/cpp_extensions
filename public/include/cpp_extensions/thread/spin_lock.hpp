#ifndef _CPP_EXTENSIONS_THREAD_SPIN_LOCK_HPP_
#define _CPP_EXTENSIONS_THREAD_SPIN_LOCK_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/thread/spin_yield.hpp>

#include <atomic>

namespace cpp_extensions
{
	namespace thread
	{
		class spin_lock final
		{
		private:
			std::atomic<bool> m_state = { false };
			uint16_t const m_number_of_spins_before_yield = 4096;

		public:
			constexpr spin_lock() noexcept = default;

			constexpr explicit spin_lock(bool const initial_state) noexcept
				: m_state{ initial_state }
			{
			}

			constexpr explicit spin_lock(uint16_t const number_of_spins_before_yield) noexcept
				: m_number_of_spins_before_yield(number_of_spins_before_yield)
			{
			}

			constexpr explicit spin_lock(bool const initial_state, uint16_t const number_of_spins_before_yield) noexcept
				: m_state{ initial_state }, m_number_of_spins_before_yield(number_of_spins_before_yield)
			{
			}

			spin_lock(spin_lock const&) = delete;
			spin_lock(spin_lock&&) = delete;

			spin_lock& operator = (spin_lock const&) = delete;
			spin_lock& operator = (spin_lock&&) = delete;

			[[nodiscard]]
			bool locked() const noexcept
			{
				return m_state.load(std::memory_order_relaxed);
			}

			void lock() noexcept
			{
				if (try_lock())
				{
					return;
				}

				spin_yield yield(m_number_of_spins_before_yield);

				while (m_state.exchange(true, std::memory_order_acquire) == true)
				{
					while (locked())
					{
						yield.execute();
					}
				}
			}

			[[nodiscard]]
			bool try_lock() noexcept
			{
				if (locked())
				{
					return false;
				}

				return (m_state.exchange(true, std::memory_order_acquire) == false);
			}

			void unlock() noexcept
			{
				m_state.store(false, std::memory_order_release);
			}
		};
	}
}

#endif // _CPP_EXTENSIONS_THREAD_SPIN_LOCK_HPP_

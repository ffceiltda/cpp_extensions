#ifndef _CPP_EXTENSIONS_THREAD_SPIN_YIELD_HPP_
#define _CPP_EXTENSIONS_THREAD_SPIN_YIELD_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/intrinsics.hpp>
#include <cpp_extensions/thread.hpp>

#include <cstdint>

namespace cpp_extensions
{
    namespace thread
    {
        class spin_yield final
        {
        private:
            uint16_t m_spin_count = 0;
            uint16_t const m_number_of_spins_before_yield = 4096;

        public:
            constexpr spin_yield() noexcept = default;

            constexpr explicit spin_yield(uint16_t const number_of_spins_before_yield) noexcept
                : m_number_of_spins_before_yield(number_of_spins_before_yield)
            {
            }

            constexpr spin_yield(spin_yield const&) noexcept = delete;
            constexpr spin_yield(spin_yield&&) noexcept = delete;

            constexpr spin_yield& operator = (spin_yield const&) noexcept = delete;
            constexpr spin_yield& operator = (spin_yield&&) noexcept = delete;

            void execute() noexcept
            {
                if (++m_spin_count > m_number_of_spins_before_yield)
                {
                    [[unlikely]]

                    std::this_thread::yield();

                    m_spin_count = 0;
                }
                else
                {
                    [[likely]]

                    cpp_extensions::intrinsics::cpu_pause();
                }
            }
        };
    }
}

#endif // _CPP_EXTENSIONS_THREAD_SPIN_YIELD_HPP_

#ifndef _CPP_EXTENSIONS_THREAD_SPIN_LOCK_HPP_
#define _CPP_EXTENSIONS_THREAD_SPIN_LOCK_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/intrinsics.hpp>

#include <atomic>

namespace cpp_extensions
{
    namespace thread
    {
        class spin_lock final
        {
        private:
            std::atomic<bool> m_flag = { false };
            uint16_t m_spin_count_before_pause = 16;

        public:
            constexpr spin_lock() noexcept = default;

            constexpr explicit spin_lock(bool const state) noexcept
                : m_flag{ state }
            {
            }

            constexpr explicit spin_lock(uint16_t const spin_count_before_pause) noexcept
                : m_spin_count_before_pause(spin_count_before_pause)
            {
            }

            constexpr explicit spin_lock(bool const state, uint16_t const spin_count_before_pause) noexcept
                : m_flag{ state }, m_spin_count_before_pause(spin_count_before_pause)
            {
            }

            spin_lock(spin_lock const&) = delete;
            spin_lock(spin_lock&&) = delete;

            spin_lock& operator = (spin_lock const&) = delete;
            spin_lock& operator = (spin_lock&&) = delete;

            void lock() noexcept
            {
                while (true)
                {
                    if (!m_flag.exchange(true, std::memory_order_acquire))
                    {
                        break;
                    }

                    uint16_t loop_count = 0;

                    while (m_flag.load(std::memory_order_relaxed))
                    {
                        ++loop_count;

                        if (loop_count > m_spin_count_before_pause)
                        {
                            loop_count = 0;

                            cpp_extensions::intrinsics::cpu_idle_pause();
                        }
                    }
                }
            }

            bool try_lock() noexcept
            {
                if (m_flag.load(std::memory_order_relaxed))
                {
                    return false;
                }
                
                return !m_flag.exchange(true, std::memory_order_acquire);
            }

            void unlock() noexcept
            {
                m_flag.store(false, std::memory_order_release);
            }
        };
    }
}

#endif // _CPP_EXTENSIONS_THREAD_SPIN_LOCK_HPP_

#ifndef _CPP_EXTENSIONS_THREAD_CHECKED_SHARED_LOCK_TRACKER_HPP_
#define _CPP_EXTENSIONS_THREAD_CHECKED_SHARED_LOCK_TRACKER_HPP_

#include <cpp_extensions/prolog.hpp>
#include <cpp_extensions/debugger.hpp>
#include <cpp_extensions/make_unique_lock.hpp>
#include <cpp_extensions/thread/detail/checked_unique_lock_tracker.hpp>

#include <unordered_map>

namespace cpp_extensions
{
	namespace thread
	{
		namespace detail
		{
			template <typename LockableType, typename UniqueLockableType>
			class checked_shared_lock_tracker_template
				: public UniqueLockableType
			{
			private:
				typename UniqueLockableType::internal_lockable_type m_shared_lock_tracker_mutex;
				std::unordered_map<std::thread::id, size_t> m_shared_lock_thread_id_map = {};

			protected:
				template <typename LockFunctorType>
				bool lock_track_shared_recursive_current_thread(LockFunctorType&& lock_functor)
				{
					auto const locked = lock_functor();

					if (locked)
					{
						auto const shared_lock_thread_id = std::this_thread::get_id();

						auto recursion_lock = cpp_extensions::make_unique_lock(m_shared_lock_tracker_mutex);

						auto iterator = m_shared_lock_thread_id_map.find(shared_lock_thread_id);

						if (iterator == std::end(m_shared_lock_thread_id_map))
						{
							m_shared_lock_thread_id_map.emplace(shared_lock_thread_id, 1U);
						}
						else
						{
							++iterator->second;
						}
					}

					return locked;
				}

				template <typename UnlockFunctorType>
				void unlock_track_shared_recursive_current_thread(UnlockFunctorType&& unlock_functor)
				{
					auto const shared_lock_thread_id = std::this_thread::get_id();

					auto recursion_lock = cpp_extensions::make_unique_lock(m_shared_lock_tracker_mutex);

					auto iterator = m_shared_lock_thread_id_map.find(shared_lock_thread_id);

					if (iterator != std::end(m_shared_lock_thread_id_map))
					{
						[[likely]]

						if (--iterator->second == 0)
						{
							m_shared_lock_thread_id_map.erase(iterator);
						}

						recursion_lock.unlock();

						unlock_functor();
					}
					else
					{
						[[unlikely]]

						throw std::logic_error("object not locked by this thread");
					}
				}

			public:
				constexpr checked_shared_lock_tracker_template() noexcept = default;

				checked_shared_lock_tracker_template(checked_shared_lock_tracker_template const&) = delete;
				checked_shared_lock_tracker_template(checked_shared_lock_tracker_template&&) = delete;

				checked_shared_lock_tracker_template& operator = (checked_shared_lock_tracker_template const&) = delete;
				checked_shared_lock_tracker_template& operator = (checked_shared_lock_tracker_template&&) = delete;

				void lock_shared()
				{
					lock_track_shared_recursive_current_thread([this]() -> bool { this->m_lockable.lock_shared(); return true; });
				}

				[[nodiscard]]
				bool try_lock_shared()
				{
					return lock_track_shared_recursive_current_thread([this]() -> bool { return this->m_lockable.try_lock_shared(); });
				}

				void unlock_shared()
				{
					unlock_track_shared_recursive_current_thread([this]() -> void { this->m_lockable.unlock_shared(); });
				}
			};

			template <typename LockableType, bool const Recursive>
			using checked_shared_lock_tracker = checked_shared_lock_tracker_template<LockableType, checked_unique_lock_tracker<LockableType, Recursive>>;
		}
	}
}

#endif // _CPP_EXTENSIONS_THREAD_CHECKED_SHARED_LOCK_TRACKER_HPP_

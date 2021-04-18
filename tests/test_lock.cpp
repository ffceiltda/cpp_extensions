#include <cpp_extensions/debugger.hpp>
#include <cpp_extensions/make_unique_lock.hpp>
#include <cpp_extensions/make_shared_lock.hpp>

#include <cpp_extensions/mutex.hpp>
#include <cpp_extensions/timed_mutex.hpp>
#include <cpp_extensions/shared_mutex.hpp>
#include <cpp_extensions/shared_timed_mutex.hpp>
#include <cpp_extensions/recursive_mutex.hpp>
#include <cpp_extensions/recursive_timed_mutex.hpp>
#include <cpp_extensions/recursive_shared_mutex.hpp>
#include <cpp_extensions/recursive_shared_timed_mutex.hpp>
#include <cpp_extensions/spin_lock.hpp>
#include <cpp_extensions/condition_variable.hpp>
// #include <cpp_extensions/latch.hpp>
// #include <cpp_extensions/barrier.hpp>
// #include <cpp_extensions/binary_semaphore.hpp>
// #include <cpp_extensions/counting_semaphore.hpp>
// #include <cpp_extensions/manual_semaphore.hpp>

#include <cpp_extensions/all.hpp>

template <typename Lockable>
bool test_unique_locks(bool const recursive = false)
{
	std::cout << "test_unique_locks<" << typeid(Lockable).name() << ">" << std::endl;

	bool test_ok = false;

	try
	{
		Lockable lockable;

		auto unique_lock_1 = cpp_extensions::make_unique_lock(lockable);

		unique_lock_1.unlock();

		auto unique_lock_2 = cpp_extensions::make_unique_lock(lockable, std::try_to_lock);

		try
		{
			auto unique_lock_3 = cpp_extensions::make_unique_lock(lockable, std::try_to_lock);
		}
		catch (std::exception const& e)
		{
			if (recursive)
			{
				throw e;
			}

			std::cerr << "OK: exception while trying to recursive lock: " << e.what() << std::endl;
		}

		auto unique_lock_3 = cpp_extensions::make_unique_lock(lockable, std::defer_lock);

		unique_lock_2.unlock();

		unique_lock_3.lock();
		unique_lock_3.unlock();

		try
		{
			unique_lock_3.unlock();
			unique_lock_3.lock();
		}
		catch (std::exception const& e)
		{
			std::cerr << "OK: exception while trying to unlock without lock: " << e.what() << std::endl;
		}

		lockable.lock();
		lockable.unlock();

		if (!lockable.try_lock())
		{
			throw std::logic_error("raw lock unexpected failure");
		}

		try
		{
			bool locked = lockable.try_lock();

			if (recursive != locked)
			{
				throw std::logic_error("try lock behaviour mismatch");
			}
		}
		catch (std::exception const& e)
		{
			if (recursive)
			{
				throw e;
			}

			std::cerr << "OK: exception while trying to raw recursive lock: " << e.what() << std::endl;
		}

		lockable.unlock();

		try
		{
			lockable.unlock();
			lockable.lock();
		}
		catch (std::exception const& e)
		{
			std::cerr << "OK: exception while trying to raw unlock without lock: " << e.what() << std::endl;
		}

		test_ok = true;
	}
	catch (std::exception const& e)
	{
		std::cerr << "TEST FAILURE: " << e.what() << std::endl;
	}

	std::cout << std::endl << std::endl;

	return test_ok;
}

template <typename Lockable>
bool test_recursive_locks()
{
	bool test_ok = test_unique_locks<Lockable>(true);

	std::cout << "test_recursive_locks<" << typeid(Lockable).name() << ">" << std::endl;

	try
	{
		Lockable lockable;

		auto unique_lock_1 = cpp_extensions::make_unique_lock(lockable);

		unique_lock_1.unlock();
		unique_lock_1.lock();

		try
		{
			unique_lock_1.lock();
			unique_lock_1.unlock();
		}
		catch (std::exception const& e)
		{
			std::cerr << "exception while trying to recursive lock: " << e.what() << std::endl;
		}

		auto unique_lock_2 = cpp_extensions::make_unique_lock(lockable, std::try_to_lock);

		unique_lock_1.unlock();

		try
		{
			auto unique_lock_3 = cpp_extensions::make_unique_lock(lockable, std::try_to_lock);
		}
		catch (std::exception const& e)
		{
			std::cerr << "exception while trying to recursive lock: " << e.what() << std::endl;
		}

		auto unique_lock_3 = cpp_extensions::make_unique_lock(lockable, std::defer_lock);

		unique_lock_2.unlock();

		unique_lock_3.lock();
		unique_lock_3.unlock();

		try
		{
			unique_lock_3.unlock();
			unique_lock_3.lock();
		}
		catch (std::exception const& e)
		{
			std::cerr << "exception while trying to unlock: " << e.what() << std::endl;
		}

		test_ok = true;
	}
	catch (std::exception const& e)
	{
		std::cerr << "TEST FAILURE: " << e.what() << std::endl;
	}

	std::cout << std::endl << std::endl;

	return test_ok;
}

template <typename Lockable>
bool test_timed_locks()
{
	bool test_ok = test_unique_locks<Lockable>(true);

	std::cout << "test_recursive_locks<" << typeid(Lockable).name() << ">" << std::endl;

	try
	{
		Lockable lockable;

		auto unique_lock_1 = cpp_extensions::make_unique_lock(lockable);

		unique_lock_1.unlock();
		unique_lock_1.lock();

		try
		{
			unique_lock_1.lock();
			unique_lock_1.unlock();
		}
		catch (std::exception const& e)
		{
			std::cerr << "exception while trying to recursive lock: " << e.what() << std::endl;
		}

		auto unique_lock_2 = cpp_extensions::make_unique_lock(lockable, std::try_to_lock);

		unique_lock_1.unlock();

		try
		{
			auto unique_lock_3 = cpp_extensions::make_unique_lock(lockable, std::try_to_lock);
		}
		catch (std::exception const& e)
		{
			std::cerr << "exception while trying to recursive lock: " << e.what() << std::endl;
		}

		auto unique_lock_3 = cpp_extensions::make_unique_lock(lockable, std::defer_lock);

		unique_lock_2.unlock();

		unique_lock_3.lock();
		unique_lock_3.unlock();

		try
		{
			unique_lock_3.unlock();
			unique_lock_3.lock();
		}
		catch (std::exception const& e)
		{
			std::cerr << "exception while trying to unlock: " << e.what() << std::endl;
		}

		test_ok = true;
	}
	catch (std::exception const& e)
	{
		std::cerr << "TEST FAILURE: " << e.what() << std::endl;
	}

	std::cout << std::endl << std::endl;

	return test_ok;
}

int main(int /* argc */, char* [] /* argv */)
{
	cpp_extensions::debugger::assert_expression(test_unique_locks<cpp_extensions::thread::fast_spin_lock>(), "test_unique_locks failed for fast_spin_lock failed");
	cpp_extensions::debugger::assert_expression(test_unique_locks<cpp_extensions::thread::fast_mutex>(), "test_unique_locks failed for fast_mutex");
	cpp_extensions::debugger::assert_expression(test_recursive_locks<cpp_extensions::thread::fast_recursive_mutex>(), "test_recursive_locks failed for fast_recursive_mutex failed");
	cpp_extensions::debugger::assert_expression(test_timed_locks<cpp_extensions::thread::fast_timed_mutex>(), "test_unique_locks test_timed_locks for fast_timed_mutex failed");

	cpp_extensions::debugger::assert_expression(test_unique_locks<cpp_extensions::thread::checked_spin_lock>(), "test_unique_locks failed for checked_spin_lock failed");
	cpp_extensions::debugger::assert_expression(test_unique_locks<cpp_extensions::thread::checked_mutex>(), "test_unique_locks failed for checked_mutex");
	cpp_extensions::debugger::assert_expression(test_recursive_locks<cpp_extensions::thread::checked_recursive_mutex>(), "test_recursive_locks failed for checked_recursive_mutex failed");
	cpp_extensions::debugger::assert_expression(test_timed_locks<cpp_extensions::thread::checked_timed_mutex>(), "test_unique_locks test_timed_locks for checked_timed_mutex failed");

	// test_unique_timed_locks<cpp_extensions::thread::checked_timed_mutex>();
	// test_unique_timed_locks<cpp_extensions::thread::fast_timed_mutex>();


	// test_recursive_timed_locks<cpp_extensions::thread::checked_recursive_timed_mutex>();
	// test_recursive_timed_locks<cpp_extensions::thread::fast_recursive_timed_mutex>();

	// test_shared_locks<cpp_extensions::thread::checked_shared_mutex>();
	// test_shared_locks<cpp_extensions::thread::fast_shared_mutex>();

	// test_shared_timed_locks<cpp_extensions::thread::checked_shared_timed_mutex>();
	// test_shared_timed_locks<cpp_extensions::thread::fast_shared_timed_mutex>();

	// test_recursive_shared_locks<cpp_extensions::thread::checked_recursive_shared_mutex>();
	// test_recursive_shared_locks<cpp_extensions::thread::fast_recursive_shared_mutex>();

	// test_recursive_shared_timed_locks<cpp_extensions::thread::checked_recursive_shared_timed_mutex>();
	// test_recursive_shared_timed_locks<cpp_extensions::thread::fast_recursive_shared_timed_mutex>();

	return 0;
}

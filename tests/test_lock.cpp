#include <cpp_extensions/mutex.hpp>
#include <cpp_extensions/timed_mutex.hpp>
#include <cpp_extensions/shared_mutex.hpp>
#include <cpp_extensions/shared_timed_mutex.hpp>
#include <cpp_extensions/recursive_mutex.hpp>
#include <cpp_extensions/recursive_timed_mutex.hpp>
#include <cpp_extensions/recursive_shared_mutex.hpp>
#include <cpp_extensions/recursive_shared_timed_mutex.hpp>
#include <cpp_extensions/spin_lock.hpp>

#include <cpp_extensions/make_unique_lock.hpp>
#include <cpp_extensions/make_shared_lock.hpp>

template <typename Lockable>
void test_unique_locks()
{
	std::cout << "test_unique_locks<" << typeid(Lockable).name() << ">" << std::endl;

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

	std::cout << std::endl;
}

template <typename Lockable>
void test_recursive_locks()
{
	test_unique_locks<Lockable>();

	std::cout << "test_recursive_locks<" << typeid(Lockable).name() << ">" << std::endl;

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

	std::cout << std::endl;
}

int main(int /* argc */, char*[] /* argv */)
{
	test_unique_locks<cpp_extensions::thread::checked_spin_lock>();
	test_unique_locks<cpp_extensions::thread::fast_spin_lock>();

	test_unique_locks<cpp_extensions::thread::checked_mutex>();
	test_unique_locks<cpp_extensions::thread::fast_mutex>();

	// test_unique_timed_locks<cpp_extensions::thread::checked_timed_mutex>();
	// test_unique_timed_locks<cpp_extensions::thread::fast_timed_mutex>();

	test_recursive_locks<cpp_extensions::thread::checked_recursive_mutex>();
	test_recursive_locks<cpp_extensions::thread::fast_recursive_mutex>();

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

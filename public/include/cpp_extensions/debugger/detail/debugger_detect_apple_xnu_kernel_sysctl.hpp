#ifndef _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_DETECT_APPLE_XNU_KERNEL_SYSCTL_HPP_
#define _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_DETECT_APPLE_XNU_KERNEL_SYSCTL_HPP_

#include <chrono>
#include <cstdbool>

extern "C"
{
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysctl.h>
}

namespace cpp_extensions
{
	namespace debugger
	{
		namespace detail
		{
			static inline bool attached()
			{
                static bool cached_result = false;
                static std::chrono::steady_clock::time_point last_os_pool = {};

                auto current_time = std::chrono::steady_clock::now();

                if (std::chrono::duration_cast<std::chrono::seconds>(current_time - last_os_pool).count() > 10)
                {
                    struct kinfo_proc kernel_process_info = {};
                    size_t kernel_process_info_size = sizeof(kernel_process_info);

                    int kernel_sysctl_command[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PID, ::getpid() };

                    int syscall_result = ::sysctl(kernel_sysctl_command, 4, std::addressof(kernel_process_info),
                        std::addressof(kernel_process_info_size), nullptr, 0);

                    if (syscall_result == 0)
                    {
                        last_os_pool = current_time;

                        cached_result = ((kernel_process_info.kp_proc.p_flag & P_TRACED) != 0);
                    }
                }

                return cached_result;
			}
		}
	}
}

#endif // _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_DETECT_APPLE_XNU_KERNEL_SYSCTL_HPP_

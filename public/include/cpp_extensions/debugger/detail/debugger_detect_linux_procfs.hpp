#ifndef _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_DETECT_LINUX_PROCFS_HPP_
#define _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_DETECT_LINUX_PROCFS_HPP_

#include <chrono>
#include <string>
#include <cctype>
#include <cstddef>
#include <cstring>

extern "C"
{
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
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
                    char buffer[2048] = {};

                    auto handle = ::open("/proc/self/status", O_RDONLY);

                    if (handle != -1)
                    {
                        auto bytes_read = ::read(handle, buffer, sizeof(buffer) - 1);

                        ::close(handle);

                        if (bytes_read > 0)
                        {
                            buffer[bytes_read] = 0;

                            auto buffer_begin = buffer;
                            auto buffer_end = buffer_begin + bytes_read;

                            constexpr char tracer_pid_string[] = "TracerPid:";

                            auto tracer_pid_ptr = ::strstr(buffer_begin, tracer_pid_string);

                            if (tracer_pid_ptr)
                            {
                                for (const char* character_ptr = tracer_pid_ptr + sizeof(tracer_pid_string) - 1; character_ptr <= buffer_end; ++character_ptr)
                                {
                                    if (::isspace(*character_ptr))
                                    {
                                        continue;
                                    }

                                    cached_result = ::isdigit(*character_ptr) && (*character_ptr != '0');

                                    break;
                                }
                            }
                        }
                    }
                }

                return cached_result;
            }
        }
    }
}

#endif // _CPP_EXTENSIONS_DEBUGGER_DETAIL_DEBUGGER_DETECT_LINUX_PROCFS_HPP_

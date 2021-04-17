cmake_minimum_required(VERSION 3.20)

project (cpp_extensions LANGUAGES CXX C)

find_package(Threads REQUIRED)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set(CMAKE_GENERATE_DEBUG_BUILD TRUE)
	set(CMAKE_INCLUDE_DEBUG_INFORMATION TRUE)
else()
	set(CMAKE_GENERATE_DEBUG_BUILD FALSE)
	set(CMAKE_INCLUDE_DEBUG_INFORMATION FALSE)
endif()

if(MSVC)
	# System definitions
    add_compile_definitions(WINVER=0x0601)
	add_compile_definitions(_WIN32_WINNT=0x0601)
    add_compile_definitions(_CRT_NONSTDC_NO_DEPRECATE)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(_WINSOCK_DEPRECATED_NO_WARNINGS)
	add_compile_definitions(_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)

	# Compiler definitions
	add_compile_options(/W4)
	add_compile_options(/WX)

	# C+ language definitions
	add_compile_options(/EHsc)
	add_compile_options(/permissive-)
	add_compile_options(/std:c++latest)
	add_compile_options(/Zc:__cplusplus)
	add_compile_options(/Zc:preprocessor)
	add_compile_options(/fp:precise)

	# Debug information	
	if("${CMAKE_INCLUDE_DEBUG_INFORMATION}" STREQUAL "TRUE")
		add_compile_options(/FC)
		add_compile_options(/Zi)
		add_compile_options(/Zf)
	endif()
	
	# Optimizations
	if("${CMAKE_GENERATE_DEBUG_BUILD}" STREQUAL "TRUE")
		add_link_options(/INCREMENTAL)
	else()
		add_compile_options(/Oi)
		add_compile_options(/Ot)
		add_compile_options(/Gy)

		add_link_options(/INCREMENTAL:NO)
		add_link_options(/LTCG)
		add_link_options(/OPT:REF)
		add_link_options(/OPT:ICF)
	endif()
else()
	# System definitions
	add_compile_definitions(_REENTRANT)
	add_compile_definitions(_LARGEFILE_SOURCE)
	add_compile_definitions(_LARGEFILE64_SOURCE)
	add_compile_definitions(_FILE_OFFSET_BITS=64)	
	add_compile_definitions(_GNU_SOURCE)
	add_compile_definitions(_FORTIFY_SOURCE=2)
	add_compile_definitions(_POSIX_C_SOURCE=200809L)

	# Compiler definitions
	add_compile_options(-Wall)
	add_compile_options(-Wextra)
	add_compile_options(-Werror)
	add_compile_options(-pedantic)
	add_compile_options(-pedantic-errors)

	# C+ language definitions
	add_compile_options(-fexceptions)
	add_compile_options(-std=c++2a)

	# Debug information	
	if("${CMAKE_INCLUDE_DEBUG_INFORMATION}" STREQUAL "TRUE")
		add_compile_options(-g)
	endif()

	# Optimizations
	if("${CMAKE_GENERATE_DEBUG_BUILD}" STREQUAL "TRUE")
	else()
	endif()	
endif()

if("${CMAKE_GENERATE_DEBUG_BUILD}" STREQUAL "TRUE")
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)
else()
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

add_subdirectory(tests)

cmake_minimum_required(VERSION 2.8)

project(ffts C ASM)

option(ENABLE_SSE "Enables the use of SSE instructions." OFF)
option(ENABLE_NEON "Enables the use of NEON instructions." OFF)
option(ENABLE_VFP "Enables the use of VFP instructions." OFF)
option(ENABLE_SINGLE "Enables the use of single precision floating point numbers." ON)
option(DISABLE_DYNAMIC_CODE "Disables the use of dynamic machine code generation." OFF)
option(ENABLE_JNI "Builds the JNI code." OFF)
option(ENABLE_SHARED "Enable building a shared library." OFF)

add_definitions("-std=c99")
add_definitions("-I./source/")

if(ENABLE_SSE)
	set(sse_SOURCES source/sse.s source/arch/sse.c)
	add_definitions(-DHAVE_SSE -msse2)
endif()

if(ENABLE_NEON)
	if(DISABLE_DYNAMIC_CODE)
		set(neon_SOURCES source/neon_static_f.s source/neon_static_i.s)
	else()
		set(neon_SOURCES source/neon.s source/arch/neon.c)
	endif()

	add_definitions("-DHAVE_NEON")
endif()

if(ENABLE_VFP)
	set(vfp_SOURCES source/vfp.s source/arch/vfp.c)
	add_definitions("-DHAVE_VFP")
endif()

if(ENABLE_SINGLE)
	add_definitions("-DHAVE_SINGLE")
endif()

if(DISABLE_DYNAMIC_CODE)
	set(dynamic_SOURCES source/ffts_static.c)
else()
	set(dynamic_SOURCES source/codegen.c)
endif()

add_library(
	ffts
	source/ffts_real_nd.c
	source/ffts_real.c
	source/ffts.c
	source/ffts_nd.c
	source/patterns.c
	source/ffts_small.c
	${sse_SOURCES}
	${neon_SOURCES}
	${vfp_SOURCES}
	${dynamic_SOURCES}
)

add_executable(
	test
	tests/test.c
)

target_link_libraries(
	test
	m
	ffts
)

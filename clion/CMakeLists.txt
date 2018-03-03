cmake_minimum_required(VERSION 3.9)
project(pll)

set(CMAKE_CXX_STANDARD 14)

include_directories(../src /usr/local/systemc-2.3.2/include /usr/local/systemc-ams-2.1/include)
set(SOURCE_FILES
        ../src/main.cpp
        ../src/sc_delay.cpp
        ../src/sc_lfilter.cpp
        ../src/sc_pfdetector.cpp
        ../src/sc_pll.cpp
        ../src/sca_tdf_chargepump.cpp
        ../src/sca_tdf_divider.cpp
        ../src/sca_tdf_vcoscillator.cpp)


add_executable(pll ${SOURCE_FILES})

target_link_libraries (pll /usr/local/systemc-ams-2.1/lib-macosx64/libsystemc-ams.a
                            /usr/local/systemc-2.3.2/lib-macosx64/libsystemc.a )

add_library(liboption
    SHARED
    BSCall.cpp
    MonteCarloCall.cpp
    OptionCalc.cpp
)

target_compile_options(liboption PUBLIC -std=c++20)

target_include_directories(liboption
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
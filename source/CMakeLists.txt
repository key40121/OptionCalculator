add_library(option
    SHARED
    BSCall.cpp
    MonteCarloCall.cpp
    OptionCalc.cpp
)

target_compile_options(option PUBLIC -std=c++20)

target_include_directories(option
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
set(LIBRARY_NAME PEXPLORE_SRC)

add_library(${LIBRARY_NAME} OBJECT
        task_manager.cpp
        score.cpp
        exploration.cpp
        )

foreach(WARN ${LIBRARY_EXCLUSIVE_WARN})
    target_compile_options(${LIBRARY_NAME} PUBLIC -W${WARN})
endforeach()

if(COVERAGE)
    target_link_libraries(${LIBRARY_NAME} PUBLIC coverage_config)
endif()

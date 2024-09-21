cmake_minimum_required(VERSION 3.30)
project(SXL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++23")
set(INCLUDE_DIR ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC
    src/cpp/app.cpp
    src/cpp/utils.cpp
    src/cpp/element.cpp
    src/cpp/window.cpp
    src/cpp/event_handler.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    /usr/local/lib/libSDL3.a
    /usr/local/lib/libSDL3_ttf.a
    /usr/lib/Mlib.a
)

file(MAKE_DIRECTORY ${INCLUDE_DIR})
file(COPY "src/include/SXL.h" DESTINATION "${INCLUDE_DIR}")

install(DIRECTORY ${INCLUDE_DIR} DESTINATION include)
install(FILES ${CMAKE_BINARY_DIR}/lib${PROJECT_NAME}.a DESTINATION lib)
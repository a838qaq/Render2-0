project(Render)

aux_source_directory(./src SRC)
aux_source_directory(./json JSON)

add_executable(${PROJECT_NAME} ${SRC} ${JSON})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS"-O2 -W")
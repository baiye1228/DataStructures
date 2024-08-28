cmake_minimum_required(VERSION 3.5.0)
project(DataStructures VERSION 0.1.0 LANGUAGES C CXX)

# 线性表相关子目录
add_subdirectory(list)

# 栈相关子目录
add_subdirectory(stack)

# 队列相关子目录
add_subdirectory(queue)


include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

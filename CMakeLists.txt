cmake_minimum_required(VERSION 3.8)
project(HeterogeneousContainer)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Containers/BaseContainer/BaseContainer.h Containers/Stack.h Containers/Queue.h Containers/DLinkedList.h MainContainer.h)
add_executable(HeterogeneousContainer ${SOURCE_FILES})
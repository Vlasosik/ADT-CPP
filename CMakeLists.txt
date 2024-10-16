cmake_minimum_required(VERSION 3.29)
project(ADT)

set(CMAKE_CXX_STANDARD 17)

add_executable(ADT main.cpp
        forward_list/ForwardList.h
        linked_list/LinkedList.h
        stack/Stack.h
        queue/Queue.h
        binary_tree/BinaryTree.h)

cmake_minimum_required(VERSION 3.4.1)

add_library(hello-ROP SHARED
            hello-ROP.c)

# Include libraries needed for hello-ROP lib
target_link_libraries(hello-ROP
                      android
                      log)

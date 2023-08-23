#v1.0 copyright Comine.com 20230823W1304

cmake_minimum_required(VERSION 3.1.6)

########################################
# Project
########################################
project(MWatch)
file(GLOB msource "src/*.h" "src/*.cpp" "src/*.c")
add_executable(MWatch ${msource} )




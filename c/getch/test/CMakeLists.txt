CMAKE_MINIMUM_REQUIRED(VERSION 2.9)
PROJECT(TEST)
INCLUDE_DIRECTORIES(../include)
AUX_SOURCE_DIRECTORY(./ DIR_SRCS)
ADD_EXECUTABLE(test ${DIR_SRCS})

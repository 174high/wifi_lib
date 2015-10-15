PROJECT (HELLO) 

cmake_minimum_required(VERSION 2.8)


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_C_FLAGS "-g -Wall") 

ADD_SUBDIRECTORY(src)

#bao han tou wenjian  caineng zhaodao tou wenjian 
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

SET(DIR_SRCS main.c )  

ADD_EXECUTABLE(main ${DIR_SRCS}  ) 

#zhi xing ke zhi  xing chengxu diaoyong de ku wenjian mingcheng 
TARGET_LINK_LIBRARIES( main Test ) 



cmake_minimum_required(VERSION 3.3)
project(incapache)

set(SOURCE_FILES
        aux.c
        http.c
        incApache.h
        main.c
        threads.c)

add_definitions(
        -DDEBUG
        -DHTML_404="404_Not_Found.html"
        -DHTML_501="501_Method_Not_Implemented.html"
        -DIMAGE="uncadunca.jpg"
        -DSTYLE="000_style.css"
        -DPRETEND_TO_BE_ROOT
        #-DINCaPACHE_2_1
        )

add_executable(incapache ${SOURCE_FILES})

target_link_libraries(incapache pthread)


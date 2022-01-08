# Focus stacker example
add_executable(IST_FocusStackExample FocusStackExample.cpp)
target_link_libraries(IST_FocusStackExample ist stdc++fs ${REQUIRED_OPENCV_LIBS})
install(TARGETS IST_FocusStackExample DESTINATION bin)

find_package(GTest REQUIRED)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_executable(CcpMathTest
    AxisAlignedBox.cpp
    CcpFloat.h
    Color.cpp
    Float16.cpp
    Matrix.cpp
    Plane.cpp
    Quaternion.cpp
    Vector2.cpp
    Vector3.cpp
    Vector4.cpp
)
target_link_libraries(CcpMathTest PRIVATE CcpMath GTest::GTest GTest::Main)
if(APPLE)
    target_link_libraries(CcpMathTest PRIVATE "-framework CoreFoundation")
endif()

if(CMAKE_IMPORT_LIBRARY_SUFFIX)
    add_custom_command(TARGET CcpMathTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:CcpMathTest> $<TARGET_FILE_DIR:CcpMathTest>
        COMMAND_EXPAND_LISTS
        VERBATIM
    )
endif()

set_target_properties(CcpMathTest PROPERTIES FOLDER "Tests")
# Up the minimum Test discovery timeout from 10 seconds to 60
gtest_discover_tests(CcpMathTest DISCOVERY_TIMEOUT 60)


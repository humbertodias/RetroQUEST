# SPDX-License-Identifier: Unlicense

# Platform-specific settings
if (ANDROID)
    target_link_libraries(${PROJECT_NAME} PUBLIC dl log)
    add_definitions(-DPLATFORM_ANDROID)
elseif (APPLE) # macOS
    target_link_libraries(${PROJECT_NAME} PUBLIC dl)
    add_definitions(-DPLATFORM_MACOS)
elseif (UNIX) # Linux
    target_link_libraries(${PROJECT_NAME} PUBLIC dl)
    add_definitions(-DPLATFORM_LINUX)
elseif (WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
endif()

# Add sources
target_sources(${PROJECT_NAME}
    PRIVATE
        RegisterExtension.cpp
        RetroHost.hpp
        RetroHost.cpp
        CoreEnvironment.cpp
        CoreVariables.cpp
        Audio.cpp
        Input.cpp
        Video.cpp
        KeyboardMap.hpp
        VFS.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PRIVATE
        "src"
)

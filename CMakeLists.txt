cmake_minimum_required(VERSION 3.16)
project(EngineOne)

# If you like, set a default build type if none specified:
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the build type." FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# 1) Add subdirectories for third-party libs
#    Each of these subdirectories has its own CMakeLists.txt
# -----------------------------
# Example if you have "thirdparty/glfw" and "thirdparty/glad" each containing a CMakeLists.txt
# that defines a library named `glfw` and `glad`, respectively.

add_subdirectory(thirdparty/glfw)  # This should create the 'glfw' library target
add_subdirectory(thirdparty/glad)  # This should create the 'glad' library target
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/stb_image)

# If you have more libs, just repeat:
# add_subdirectory(thirdparty/glm)
# add_subdirectory(thirdparty/imgui)
# add_subdirectory(thirdparty/whatever)
# ...

# -----------------------------
# 2) Gather your own game/engine source code
#    (Adjust the globbing pattern as needed)
# -----------------------------
file(GLOB_RECURSE MY_SOURCES 
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

# -----------------------------
# 3) Create the main executable
# -----------------------------
add_executable(${PROJECT_NAME} ${MY_SOURCES})

# -----------------------------
# 4) Include your own headers
# -----------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# -----------------------------
# 5) Link with your third-party libs
#    plus OpenGL on macOS if needed
# -----------------------------
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        glad
        glm
        stb_image
)

if(APPLE)
    find_library(OpenGL_LIBRARY OpenGL)
    if(OpenGL_LIBRARY)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenGL_LIBRARY})
    else()
        message(FATAL_ERROR "Could not find the macOS OpenGL framework.")
    endif()
endif()

# Copy textures to the build directory
set(TEXTURES_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/textures")
set(TEXTURES_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/textures")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${TEXTURES_SOURCE_DIR}"
        "${TEXTURES_DEST_DIR}"
    COMMENT "Copying textures to the build directory..."
)

# Copy assets to the build directory
set(ASSETS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSETS_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSETS_SOURCE_DIR}"
        "${ASSETS_DEST_DIR}"
    COMMENT "Copying assets to the build directory..."
)

# Copy shaders to the build directory
set(SHADERS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADERS_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SHADERS_SOURCE_DIR}"
        "${SHADERS_DEST_DIR}"
    COMMENT "Copying shaders to the build directory..."
)

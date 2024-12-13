find_package(Vulkan REQUIRED)
set(SDL_STATIC ON)
set(ENABLE_VULKAN ON)
add_subdirectory(sdl3)
add_subdirectory(glm)

add_library(external INTERFACE)
target_link_libraries(external INTERFACE
        SDL3::SDL3
        glm::glm
        Vulkan::Vulkan)
target_compile_definitions(external INTERFACE
        GLM_FORCE_CTOR_INIT
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE)
add_executable(hello-vulkan main.cpp)

if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET hello-vulkan PROPERTY CXX_STANDARD 20)
endif()

find_package(Vulkan REQUIRED)
target_link_libraries(hello-vulkan PRIVATE Vulkan::Vulkan)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(hello-vulkan PRIVATE glfw)

find_package(glm CONFIG REQUIRED)
target_link_libraries(hello-vulkan PRIVATE glm::glm)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(hello-vulkan PRIVATE imgui::imgui)

# Define DEBUG macro based on the build type
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(hello-vulkan PRIVATE DEBUG=1)
else()
    target_compile_definitions(hello-vulkan PRIVATE DEBUG=0)
endif()

target_compile_definitions(hello-vulkan PRIVATE 
    "$<$<CONFIG:Debug>:VALIDATION_LAYERS_ENABLED=1>"
    "$<$<NOT:$<CONFIG:Debug>>:VALIDATION_LAYERS_ENABLED=0>"
)
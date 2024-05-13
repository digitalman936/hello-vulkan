function(compile_shader shader_source shader_output)
    find_program(GLSLC_EXECUTABLE NAMES glslc HINTS ${VULKAN_SDK}/Bin)
    if(NOT GLSLC_EXECUTABLE)
        message(FATAL_ERROR "glslc not found")
    endif()

    set(shader_source_file "${CMAKE_CURRENT_SOURCE_DIR}/${shader_source}")
    set(shader_output_file "${CMAKE_BINARY_DIR}/${shader_output}")

    add_custom_command(
        OUTPUT ${shader_output_file}
        COMMAND ${GLSLC_EXECUTABLE} ${shader_source_file} -o ${shader_output_file}
        DEPENDS ${shader_source_file}
        COMMENT "Compiling ${shader_source}"
    )

    set_source_files_properties(${shader_output_file} PROPERTIES GENERATED TRUE)
    list(APPEND SPIRV_BINARY_FILES ${shader_output_file})
    set(SPIRV_BINARY_FILES ${SPIRV_BINARY_FILES} PARENT_SCOPE)

    set_property(GLOBAL APPEND PROPERTY COMPILED_SHADERS ${shader_output_file})
    set_property(GLOBAL APPEND PROPERTY SOURCE_SHADERS ${shader_source_file})

endfunction()

compile_shader("shaders/shader.vert" "vert.spv")
compile_shader("shaders/shader.frag" "frag.spv")

add_executable(hello-vulkan main.cpp ${SPIRV_BINARY_FILES})

get_property(COMPILED_SHADER_PATHS GLOBAL PROPERTY COMPILED_SHADERS)
get_property(SOURCE_SHADER_PATHS GLOBAL PROPERTY SOURCE_SHADERS)

list(GET COMPILED_SHADER_PATHS 0 COMPILED_VERT_SHADER_PATH)
list(GET COMPILED_SHADER_PATHS 1 COMPILED_FRAG_SHADER_PATH)
list(GET SOURCE_SHADER_PATHS 0 SOURCE_VERT_SHADER_PATH)
list(GET SOURCE_SHADER_PATHS 1 SOURCE_FRAG_SHADER_PATH)

target_compile_definitions(hello-vulkan PRIVATE 
    TEXTURE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/textures"
    COMPILED_VERT_SHADER_PATH="${COMPILED_VERT_SHADER_PATH}"
    COMPILED_FRAG_SHADER_PATH="${COMPILED_FRAG_SHADER_PATH}"
    SOURCE_VERT_SHADER_PATH="${SOURCE_VERT_SHADER_PATH}"
    SOURCE_FRAG_SHADER_PATH="${SOURCE_FRAG_SHADER_PATH}"
)

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

 find_package(Stb REQUIRED)
target_include_directories(hello-vulkan PRIVATE ${Stb_INCLUDE_DIR})

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
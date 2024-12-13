### Hello Triangle with Vulkan C++

This is a small passion project written with the VulkanHpp C++ bindings to render a triangle to the screen. It's my
first ever public repository and is relatively bare bones and straight forward to understand. Anyone can use this code
without copyright restrictions, it's a public resource for everyone!

See the [Credits](doc/credits) to view all the projects' dependencies and who I got my inspiration from.

Hopefully this repository will be useful to someone out there, happy coding :)

### Requirements

* **OS**: Windows, Linux, macOS.
* **Hardware**: Drivers with Vulkan 1.2 or higher API support. Vulkan is available via the Vulkan SDK version 1.2 or
  higher.
* **Language**: C++ 20 or higher with a Clang, GCC or MSVC compiler.
* **(Optional) Windows Build Environment**: CMake with a generator such as Ninja, Make, or Visual Studio 17 (2022).

### Build

> **NOTE:** See the [Build Page](doc/build) if you're unsure what any of this means or if you get an error at any point.

Get the sources:
```markdown
git clone --recurse-submodules https://github.com/digitalman936/hello-vulkan.git
cd hello-vulkan
```

Generate one of the presets based on your compiler.
```markdown
cmake --preset clang-debug && cmake --preset clang-release     # Uses Ninja-Build with the Clang compiler
cmake --preset gcc-debug && cmake --preset gcc-release         # Uses Ninja-Build with the GCC compiler
cmake --preset msvc-debug && cmake --preset msvc-release       # Uses Ninja-Build with the MSVC compiler
```

Build your chosen preset.

```markdown
cmake --build --preset clang-debug-build && cmake --build --preset clang-release-build
cmake --build --preset gcc-debug-build && cmake --build --preset gcc-release-build
cmake --build --preset msvc-debug-build && cmake --build --preset msvc-release-build
```

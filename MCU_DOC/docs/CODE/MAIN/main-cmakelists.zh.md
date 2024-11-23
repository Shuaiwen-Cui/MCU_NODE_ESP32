# MAIN 文件夹下的 CMakeLists.txt 文件

```cmake
# Define source directories
set(src_dirs
    .
    app
)

# Define include directories
set(include_dirs
    .
    app
)

# Define required components
set(requires
)

# Register the component
idf_component_register(
    SRC_DIRS ${src_dirs}
    INCLUDE_DIRS ${include_dirs}
    REQUIRES ${requires}
)

# Add compilation options
component_compile_options(-ffast-math -O3 -Wno-error=format -Wno-format)


```
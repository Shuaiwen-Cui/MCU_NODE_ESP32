set(src_dirs
            .
            config
            ) # Specify source file(s)

set(include_dirs
            .
            config
            ) # Include header files in the current directory

set(requires

            ) # Specify dependencies (can be omitted if none)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})

# Add compilation options (if required)
component_compile_options(-ffast-math -O3 -Wno-error=format=-Wno-format)

# PROJECT FRAMEWORK

## Overview

!!! note "Project Framework"
    After completing the project initialization, we also need to reorganize and sort the generated project to better support our project development. This section will introduce how to reorganize and sort the project.

## Project Framework

In this project, the project code organization structure is as follows:

```shell
project-name/
├── CMakeLists.txt          # top-level build file for the project
├── partitions-16MiB.csv    # partition table
├── sdkconfig               # current configuration file
├── sdkconfig.old           # old configuration file for reference
├── main/                   # main application code
│   ├── CMakeLists.txt      # build file for the main directory
│   ├── main.c              # entry point of the application
│   └── app/                # application logic
│       ├── app.c           # application layer implementation
│       ├── app.h           # header file for application interface
│       └── ...             # additional files
├── components/             # peripheral modules
│   ├── CMakeLists.txt      # build file for components
│   ├── setup/              # setup for components
│   │   ├── setup.h         # header file for setup module
│   │   └── setup.c         # implementation of setup module
│   ├── component1/         # component1 module
│   │   ├── component1.h    # header file for component1
│   │   ├── component1.c    # implementation of component1
│   │   └── ...
│   └── ...                 # additional peripheral modules
├── tinyshm/                # tinyshm framework
│   ├── CMakeLists.txt      # build file for tinyshm
│   ├── config/             # configuration module
│   │   ├── config.h        # header file for configuration
│   │   └── config.c        # implementation of configuration
│   ├── componentA/         # componenta module
│   │   ├── componentA.h    # header file for componenta
│   │   ├── componentA.c    # implementation of componenta
│   │   └── ...
│   └── ...                 # additional modules
├── build/                  # build directory (auto-generated)
│   └── ...                 # files generated during the build process
└── README.md               # project documentation
```

!!! note
    - main folder: main application code + user code inside the app folder
    - components folder: peripheral module BSP, low-level oriented.
    - tinyshm folder: TinySHM framework code, high-level oriented.
    - build folder: auto-generated build directory.

!!! tip "Important Reminder"
    Every time you add a new module, you must remember to add the new module path in the corresponding CMakelists.txt file, otherwise there will be an error that the file cannot be found during compilation. In addition to adding the path of the module (source and include), the dependency (requirement) also needs to be added in the corresponding CMakelists.txt file. For example, if GPIO related functions are used, you need to add driver, and if a timer is used, you need to add esp_timer.
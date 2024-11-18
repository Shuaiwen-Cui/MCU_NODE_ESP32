# PROJECT FRAMEWORK

## Overview

!!! note "Project Framework"
    After completing the project initialization, we also need to reorganize and sort the generated project to better support our project development. This section will introduce how to reorganize and sort the project.

## Project Framework

In this project, the project code organization structure is as follows:

```shell
project-name/
├── CMakeLists.txt          # Top-level build file for the project
├── partitions-16MiB.csv    # Partition table
├── sdkconfig               # Current configuration file
├── sdkconfig.old           # Old configuration file for reference
├── main/                   # Main application code
│   ├── CMakeLists.txt      # Build file for the main directory
│   ├── main.c              # Entry point of the application
│   └── app/                # Application logic
│       ├── app.c           # Application layer implementation
│       ├── app.h           # Header file for application interface
│       └── ...             # Additional files
├── components/             # Peripheral modules
│   ├── CMakeLists.txt      # Build file for components
│   ├── led/                # LED module
│   │   ├── led.c           # Implementation of LED module
│   │   ├── led.h           # Header file for LED module
│   │   └── ...
│   ├── rgb/                # RGB module
│   │   ├── rgb.c           # Implementation of RGB module
│   │   ├── rgb.h           # Header file for RGB module
│   │   └── ...
│   ├── sensor/             # Sensor module
│   │   ├── sensor.c        # Implementation of sensor module
│   │   ├── sensor.h        # Header file for sensor module
│   │   └── ...
│   └── ...                 # Additional peripheral modules
├── tinyshm/                # TinySHM framework
│   ├── CMakeLists.txt      # Build file for TinySHM
│   ├── data_processing/    # Data processing module
│   │   ├── data_proc.c     # Implementation of data processing
│   │   ├── data_proc.h     # Header file for data processing
│   │   └── ...
│   ├── fault_detection/    # Fault detection module
│   │   ├── fault_detect.c  # Implementation of fault detection
│   │   ├── fault_detect.h  # Header file for fault detection
│   │   └── ...
│   ├── sensor_integration/ # Sensor integration module
│   │   ├── sensor_integ.c  # Implementation of sensor integration
│   │   ├── sensor_integ.h  # Header file for sensor integration
│   │   └── ...
│   └── ...                 # Additional modules
├── build/                  # Build directory (auto-generated)
│   └── ...                 # Files generated during the build process
└── README.md               # Project documentation

```

!!! note
    - main folder: main application code + user code inside the app folder
    - components folder: peripheral module BSP, low-level oriented.
    - tinyshm folder: TinySHM framework code, high-level oriented.
    - build folder: auto-generated build directory.

!!! tip "Important Reminder"
    Every time you add a new module, you must remember to add the new module path in the corresponding CMakelists.txt file, otherwise there will be an error that the file cannot be found during compilation. In addition to adding the path of the module (source and include), the dependency (requirement) also needs to be added in the corresponding CMakelists.txt file. For example, if GPIO related functions are used, you need to add driver, and if a timer is used, you need to add esp_timer.
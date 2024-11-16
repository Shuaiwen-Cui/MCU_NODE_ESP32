# ARCHITECTURE

## HARDWARE ARCHITECTURE

MAIN CONTROL + PERCEPTION + COMMUNICATION + INTERFACING

## SOFTWARE ARCHITECTURE

HARDWARE LAYER + PLATFORM ABSTRACTION LAYER + SYSTEM SERVICES LAYER + APPLICATION LAYER

```shell
+------------------------------+
| Application Layer            | <-- Application Code
+------------------------------+
| System Services Layer        | <-- OS + Middleware
+------------------------------+
| Platform Abstraction Layer   | <-- Startup Code + HAL (register-level) + BSP (board-level)
+------------------------------+
| Hardware Layer               | <-- Main Control + Peripherals
+------------------------------+
```
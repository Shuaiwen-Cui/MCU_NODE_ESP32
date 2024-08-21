# ARCHITECTURE

## HARDWARE ARCHITECTURE

MAIN CONTROL + PERCEPTION + COMMUNICATION + INTERFACING

## SOFTWARE ARCHITECTURE

PHYSICAL LAYER -> DRIVER LAYER -> MIDWARE LAYER -> APPLICATION LAYER

## DEV TOOLCHAIN

| TOOLCHAIN | DESCRIPTION | PROS | CONS |
| --- | --- | --- | --- |
| ESP_IDF | Espressif IoT Development Framework | Rich in features, good documentation | Steep learning curve |
| MICROPYTHON | Python for microcontrollers | Easy to learn, rapid development | Limited resources |
| ARDUINO | Open-source electronics platform | Easy to use, large community | Limited resources |

!!! note
    For rapid prototyping, we use MICROPYTHON; for high-performance applications, we use ESP_IDF.
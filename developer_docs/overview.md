# ESP-Miner Architecture Overview

ESP-Miner is firmware for the ESP32 family that manages Bitaxe mining hardware.
At a high level the firmware performs the following tasks:

1. **Initialization** – during boot the device loads configuration from NVS,
   configures peripherals (I²C, ADC, display, Wi‑Fi) and sets up tasks.
2. **Network Connection** – the `connect` component manages Wi‑Fi connectivity
   and Access Point (AP) setup. Once connected it communicates with a mining
   pool using the Stratum protocol.
3. **Job Handling** – Stratum messages are parsed and translated into work for
   the ASIC chips. Jobs are queued and dispatched to the ASIC via a UART serial
   interface.
4. **ASIC Management** – the `asic` component contains model specific drivers
   (BM1366, BM1368, BM1370, BM1397). It initializes the chain, sets frequency and
   reads results.
5. **System Monitoring** – power management, thermal monitoring and display
   updates are performed periodically. A small web UI (AxeOS) is provided over
   HTTP for configuration and monitoring.

The firmware uses FreeRTOS tasks to split work between network communication,
job creation, ASIC interaction and result processing. The entry point in
`main/main.c` sets up these tasks and starts the event loop.

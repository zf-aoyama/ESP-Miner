# Module Overview

This section lists the major source directories and describes their role in the
system.

## `components/`

The ESP-IDF build system treats each subdirectory under `components` as an
independent component.

- **asic** – Drivers for specific ASIC chips. Files such as
  `bm1366.c`, `bm1368.c`, `bm1370.c` and `bm1397.c` implement model specific
  commands and serial protocol handling.
- **connect** – Wi‑Fi connection management, AP mode and network configuration.
- **dns_server** – Simple DNS server used when serving the configuration UI in
  AP mode.
- **stratum** – Stratum protocol implementation used to communicate with mining
  pools. Includes job parsing, difficulty handling and result submission.

## `main/`

Application level code. Important files include:

- **main.c** – entry point that initializes the system and starts FreeRTOS tasks.
- **system.c** – tracks run time statistics, handles power and thermal
  management and maintains the global state structure.
- **http_server/** – hosts the AxeOS web interface, REST API endpoints and
  firmware update logic.
- **power/** – drivers for voltage and current monitoring ICs and utilities for
  controlling the core voltage of the ASIC.
- **tasks/** – FreeRTOS tasks for sending work to the ASIC, receiving results and
  interfacing with the Stratum component.

## `test/`

Contains unit tests that can be built and flashed to the ESP32 for on‑device
validation. See `doc/unit_testing.md` for instructions.

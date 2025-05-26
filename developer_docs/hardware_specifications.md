# Hardware Specifications

This section summarizes the key peripherals and sensors found on a typical Bitaxe board running ESP‑Miner.

## Microcontroller

- **ESP32‑S3** running ESP‑IDF. UART1 connects to the ASIC chain.
- I²C bus operated at 100 kHz for power and thermal sensors.

## Power Management

- **TPS546** voltage regulator (I²C address `0x24`, alert `0x0C`). Controls the core voltage supplied to the ASIC and monitors input/output current.
- **INA260** power monitor (address `0x40`). Measures bus voltage, current and power draw.

## Thermal Monitoring and Fan Control

- **EMC2101** (address `0x4C`) or **EMC2103** (address `0x2E`) used for external temperature sensing and fan PWM control.
- **TMP1075** digital temperature sensor (address `0x4A`) for auxiliary readings.

## Display

- Optional small OLED/LCD display managed by the `display` module. Display timeout and brightness can be configured via AxeOS.

## ASIC Interface

- UART1 on GPIO17 (TX) and GPIO18 (RX) communicates with the ASIC. A reset GPIO may be defined by `CONFIG_GPIO_ASIC_RESET`.
- Job data are sent over this UART using the protocol described in [communication_protocols.md](communication_protocols.md).

These components may vary slightly depending on the exact Bitaxe revision, but the addresses and functions above reflect the current reference design.


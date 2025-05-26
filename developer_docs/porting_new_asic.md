# Porting ESP-Miner to a New ASIC

This guide outlines the typical steps required to add support for another ASIC
model. Existing implementations for the BM1366/BM1368/BM1370/BM1397 can be used
as references.

1. **Create a new ASIC driver**
   - Add source and header files under `components/asic/` implementing the
     command set for the chip. See `bm1366.c` and `bm1366.h` for a template.
   - Provide functions for initialization, sending work and parsing results.
2. **Define the ASIC model**
   - Extend `asic.h` with a new enumeration value and configuration constants
     (core count, difficulty value, etc.).
   - Update `ASIC_set_device_model` in `asic.c` to recognize the new device name
     and set the appropriate parameters in `GlobalState`.
3. **Frequency Management**
   - If the ASIC supports dynamic frequency changes, implement a function similar
     to `BM1368_set_frequency` and reference it from `ASIC_set_frequency`.
4. **Update Build Configuration**
   - Add any required Kconfig options or sdkconfig defaults so users can select
     the new device model when compiling.
5. **Test on Hardware**
   - Use the unit testing framework in `components/asic/test` or create custom
     test applications under `test` to validate communication with the new ASIC.

By following the structure of the existing drivers and updating the global
initialization logic, ESP-Miner can be adapted to control alternative mining
hardware.

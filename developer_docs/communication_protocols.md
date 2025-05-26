# Communication Protocols

This document provides a brief overview of the protocols used by ESP‑Miner to communicate with the outside world and with the ASIC hardware.

## Stratum Mining Protocol

ESP‑Miner acts as a Stratum client to obtain work from a mining pool and to submit results. The implementation lives in `components/stratum`.

- **Subscribe and authorize** – The firmware sends standard `mining.subscribe` and `mining.authorize` messages on connection.
- **Job notifications** – `mining.notify` messages are parsed and converted into ASIC work items. Jobs are queued for the mining tasks.
- **Difficulty and version** – The pool may send `mining.set_difficulty` and `mining.set_version_mask` messages. These affect nonce validation and version bits for submitted shares.
- **Share submission** – Results returned by the ASIC are wrapped in `mining.submit` JSON‑RPC messages.

For message formats refer to the [Stratum protocol specification](https://reference.cash/mining/stratum-protocol).

## REST API

The HTTP server exposes a small REST style API that can be used for configuration and monitoring. The complete interface is documented in `main/http_server/openapi.yaml`. Key endpoints include:

- `GET /api/system/info` – Return system status such as hash rate and temperature.
- `GET /api/system/asic` – Provide the ASIC model and available frequency/voltage options.
- `GET /api/system/wifi/scan` – List nearby Wi‑Fi networks.
- `POST /api/system/restart` – Reboot the device.
- `PATCH /api/system` – Update configuration settings.
- `POST /api/system/OTA` – Flash new firmware images.
- `POST /api/system/OTAWWW` – Update the web interface files.
- `GET /api/ws` – WebSocket endpoint used for live log streaming.

## ASIC Serial Protocol

Communication with the ASIC chips uses a custom UART protocol. Packets begin with a two‑byte preamble `0x55 0xAA` followed by a header byte describing the command type and a length byte. The payload is appended and a CRC is added:

```
Preamble (0x55 0xAA) | Header | Length | Data... | CRC
```

- Job packets use a CRC‑16 value covering the header and payload.
- Command packets use a CRC‑5 value.

UART1 is configured on pins GPIO17 (TX) and GPIO18 (RX) at 115200 bps by default. The serial implementation can be found in `components/asic/serial.c`.


# 通信プロトコル

このドキュメントでは、ESP‑Miner が外部と ASIC ハードウェア間で使用する主な通信プロトコルについて簡単に説明します。

## Stratum マイニングプロトコル

ESP‑Miner はマイニングプールから仕事を受け取り、結果を提出するための Stratum クライアントとして動作します。実装は `components/stratum` にあります。

- **Subscribe と Authorize** ― 接続時に `mining.subscribe` と `mining.authorize` を送信します。
- **ジョブ通知** ― `mining.notify` メッセージを解析して ASIC への仕事に変換し、キューへ追加します。
- **難易度とバージョン** ― プールから `mining.set_difficulty` や `mining.set_version_mask` が送られてくることがあります。これらは結果検証やバージョンビットに影響します。
- **シェア提出** ― ASIC から返された結果は `mining.submit` JSON‑RPC メッセージとして送信されます。

詳細なフォーマットは [Stratum プロトコル仕様](https://reference.cash/mining/stratum-protocol) を参照してください。

## REST API

HTTP サーバーは設定や監視を行うための簡易的な REST 形式の API を提供します。完全な仕様は `main/http_server/openapi.yaml` に記載されています。主なエンドポイントは次の通りです。

- `GET /api/system/info` ― ハッシュレートや温度などのシステム状態を取得。
- `GET /api/system/asic` ― ASIC モデルと利用可能な周波数・電圧の一覧を取得。
- `GET /api/system/wifi/scan` ― 近辺の Wi‑Fi ネットワークを列挙。
- `POST /api/system/restart` ― デバイスを再起動。
- `PATCH /api/system` ― 設定を更新。
- `POST /api/system/OTA` ― 新しいファームウェアを書き込み。
- `POST /api/system/OTAWWW` ― Web インターフェースファイルを更新。
- `GET /api/ws` ― ログ配信用の WebSocket エンドポイント。

## ASIC シリアルプロトコル

ASIC との通信には UART を用いた独自プロトコルを使用します。パケットは 2 バイトのプレアンブル `0x55 0xAA`、ヘッダ、長さ、データ、CRC の順に並びます。

```
プレアンブル (0x55 0xAA) | ヘッダ | 長さ | データ... | CRC
```

- ジョブパケットはヘッダとデータを対象とした CRC‑16 を付加します。
- コマンドパケットは CRC‑5 を使用します。

UART1 は GPIO17 (TX) と GPIO18 (RX) に接続され、デフォルトでは 115200 bps で動作します。実装は `components/asic/serial.c` を参照してください。


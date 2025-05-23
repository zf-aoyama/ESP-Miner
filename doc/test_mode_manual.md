# ASIC Test Mode Manual

This document describes the experimental ASIC test mode. The feature is designed for development and diagnostics.

## 概要
テストモードでは ASIC チップの詳細な動作確認を行うための各種機能を提供します。HTTP API またはシリアル出力から操作できます。

## セットアップ
1. ファームウェアにテストモード機能を含めてビルドします。
2. WebUI から `/api/test/start` を呼び出すか、シリアルコマンドを利用して開始します。

## 基本使用方法
- **WebUI / HTTP API**: `POST /api/test/start` でテスト開始、`POST /api/test/stop` で停止します。進捗は `GET /api/test/status` で確認できます。
- **シリアル出力**: テストログは UART に出力されます。
- **設定ファイル**: 将来的に NVS に保存された設定を利用する予定です。

## テスト項目詳細
現在の実装ではテスト処理はダミーであり、実際のハードウェア検証処理は `main/test_mode/` 以下に追加実装してください。

## トラブルシューティング
テスト開始や停止ができない場合は、デバイスを再起動して再度お試しください。

## 開発者向け情報
テスト機能はまだ開発途中です。`test_mode.c` にある TODO コメントを参考に、チップ識別、通信テスト、ハッシュレート測定などの処理を追加してください。


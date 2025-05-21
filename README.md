# M5StickCとAmbientによる環境センサーの視覚化プログラム

本プログラムはAmbient公式の[M5StickCで小型環境センサ端末を作る](https://ambidata.io/samples/m5stack/m5sitckc/)からソースコードを流用しています。

## 用意するもの
- M5StickC
    - Plusではなく初代StickCです
    - Plusの場合は、includeするヘッダファイルをM5StickCPlus.hとする必要があります
- M5StickC ENV Hat
    - DHT12/BMP280/BMM150搭載の初代モデル
    - IIやIIIではセンサーが異なります
    - Hatは作業前にM5StickCに装着してください

## 使い方

### Ambientの準備

- [Ambient](https://ambidata.io/)にアカウントを作成
- 新規チャンネルを作成
- チャンネルIDとライトキーを控える
- チャンネル設定で温度、湿度、気圧、電圧を設定
    - 順番が重要なので以下のように設定すること
        - データー１が温度
        - データー２が湿度
        - データー３が気圧
        - データー４が電圧
- 必要に応じてダッシュボードも設定

### Arduino IDEの準備

- [Arduino](https://www.arduino.cc/)のサイトからArduino IDEをダウンロード
- Arduino IDEをインストールして実行し、環境設定
    - ボードマネージャーで以下をインストール
        - esp32
    - ライブラリマネージャーで以下をインストール
        - M5StickC
        - Ambient ESP32 ESP8266 lib
        - Adafruit BMP280 Library

### プログラムの修正

- Arduinoでプログラムを開く
    - m5stickc_env_ambient.inoを開く
    - ファイル構造は変更しないこと
- 環境にあわせてソースを修正
    - 17行目のyour_ssidを使用したいWiFiのssidへ変更
    - 18行目のyour_passwordを適切なパスフレーズに変更
    - 20行目のCHANNEL_IDを控えておいたチャンネルIDに変更
    - 21行目のWRITE_KEYを控えておいたライトキーに変更
- プログラム自体はAmbient公式のサンプルプログラムを流用しています
    - [M5StickCで小型環境センサ端末を作る](https://ambidata.io/samples/m5stack/m5sitckc/)

### 書き込み

- Arduinoの書き込み設定
    - ボードを設定
        - ツール > ボード > esp32 > M5StickCを選択
    - ポートを設定
        - M5StickCをUSB接続してポートを選択
- チェックボタンをクリックしてビルド検証
    - エラーが出なければビルドOK
- →ボタンをクリックしてM5StickCへ書き込み
    - 書き込みが正常に終了すると再起動されてプログラムが起動します

以上で5分毎にAmbientにデータが送信され、Ambient側でチャート化されます。
Ambientの仕様により、無料ユーザーの場合、過去データは4か月分参照できます。
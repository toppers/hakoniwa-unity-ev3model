# Mac環境

- [ ] Intel系 Mac
- [x] Arm系 Mac

# 前提とする環境

- Homebrew
- Blender
  - 3.0 以降
- Unity Hub
- Unity（各CPUアーキテクチャに対応したもの）
  - 2021.3.17f1 以降
- Python3.10（pyenvでインストールされたもの）

# インストール方法

本リポジトリを以下のようにクローンします。

```
git clone --recursive https://github.com/toppers/hakoniwa-unity-ev3model.git
```

クローンが終わったら、以下のようにディレクトリ移動します。

```
cd hakoniwa-unity-ev3model/
```

そして、必要な Unity モジュール類をインストールします。

```
 bash install.bash 
```

次に、`hakoniwa-base` に移動して、必要なライブラリ群をインストールします。

```
cd hakoniwa-base
```

arm系の場合：

```
bash native/template/runtime/ai/mac/install.bash arm
```

intel系の場合：

```
bash native/template/runtime/ai/mac/install.bash intel
```

途中、パスワードが聞かれますので、入力してください。


# Unity起動

この状態で Unity Hub で当該プロジェクトを開きましょう。

注意：Unityエディタは、当該CPUアーキテクチャに対応したものをインストールしてご利用ください。

対象フォルダ：hakoniwa-unity-ev3model\plugin\plugin-srcs

以下のダイアログが出ますが、`Continue` してください。

<img width="526" alt="スクリーンショット 2023-08-05 17 02 16" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/ade85aee-b08e-4920-b148-ce3ef09f5545">


次に、以下のダイアログが出ますので、`Ignore` してください。

<img width="257" alt="スクリーンショット 2023-08-05 17 03 38" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/6448e882-b0a3-42c1-8a01-398dbcd450dd">


成功するとこうなります。

<img width="1382" alt="スクリーンショット 2023-08-05 17 05 32" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/de7c9fec-1bb2-411b-90b1-71e2577b6cf1">

起動直後の状態ですと、コンソール上にたくさんエラーが出ています。原因は以下の２点です。

* gRPC のライブラリ利用箇所がエラー出力している
* Newtonsoft.Json が不足している

順番に対応しましょう。

## gRPC のライブラリ利用箇所がエラー出力している問題の対応

Unityエディタの `Editor/ProjectSettings/Player/ScriptCompilation` を開きます。

![スクリーンショット 2023-08-05 17 11 12](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/f3bc26de-2daf-482c-abc3-f891d7f5984e)

上図のように、`NO_USE_GRPC` を追加して `Apply` します。

## Newtonsoft.Json が不足している問題の対応

gRPC の対応をしても、Unityエディタのバージョンによっては、下図のようなエラーが出ている場合があります。

<img width="1046" alt="スクリーンショット 2023-08-05 17 12 38" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/63e7e31b-80d0-447e-9c77-5555293fa685">

原因は、Newtonsoft.Json が不足しているためです。 

Unityのパッケージマネージャから Newtonsoft.Jsonをインストールすることで解消できます。

`Window/PackageManger`を開き、下図のように、`+` をクリックし、`Add pacakge from git` をクリックします。
`com.unity.nuget.newtonsoft-json` を入力して、`Add` をクリックすると、インストールが始まり、エラーが解消されます。

<img width="794" alt="スクリーンショット 2023-08-05 17 15 16" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/828e3256-7e8b-4677-92b4-55cbb980db0f">


# シミュレーション環境の準備

## Unity側

下図のように、Unity のシーンをダブルクリックします。

<img width="459" alt="スクリーンショット 2023-08-05 17 22 47" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/b3befac6-85dc-4c60-83b5-86259ccb87be">

そして、｀Window/Hakoniwa/Generate` をクリックします。

<img width="325" alt="スクリーンショット 2023-08-05 17 24 11" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/8eae6801-cc2e-4d05-9c14-c26f6e1bc54d">

## Python側

Unityのオペレーションが成功すると、Pythonプログラム側に `hakoniwa-base/dev/ai/custom.json` が出力されます。

出力例：

```json
{
  "robots": [
    {
      "name": "EV3TrainModelWithBaggage",
      "shm_proxy": {
        "name": "Athrill",
        "class_name": "Hakoniwa.PluggableAsset.Assets.Micon.EV3.Ev3MiconAssetController"
      },
      "shm_pdu_readers": [
        {
          "type": "ev3_msgs/Ev3PduActuator",
          "org_name": "ev3_actuator",
          "name": "EV3TrainModelWithBaggage_ev3_actuator",
          "class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduReader",
          "class_path": null,
          "conv_class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduReaderConverter",
          "conv_class_path": null,
          "channel_id": 0,
          "pdu_size": 196
        }
      ],
      "shm_pdu_writers": [
        {
          "type": "ev3_msgs/Ev3PduSensor",
          "org_name": "ev3_sensor",
          "name": "EV3TrainModelWithBaggage_ev3_sensor",
          "class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduWriter",
          "class_path": "",
          "conv_class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduWriterConverter",
          "conv_class_path": "",
          "channel_id": 1,
          "pdu_size": 248,
          "method_type": "SHM"
        }
      ]
    }
  ]
}
```

`hakoniwa-base/workspace/runtime/asset_def.txt` を編集します。

今回の場合は、以下とします。

```
dev/ai/ev3_train.py
```

次に、ロボット制御プログラム `dev/ai/ev3_train.py` を開き、ロボットの名前を以下に変更します。

変更前：
```
env = hako_env.make("EV3TrainModel", "ev3")
```

変更後：
```
env = hako_env.make("delWithBaggageithBaggage", "ev3")
```

# シミュレーション実行方法

## 箱庭とPythonプログラムを起動する

以下のコマンドで箱庭環境を起動します。

```
bash native/template/runtime/ai/mac/run.bash
```

起動成功すると、以下のログが出力されます。

```
INFO: ACTIVATING HAKONIWA-CONDUCTOR
INFO: ACTIVATING :dev/ai/ev3_train.py
START TEST
INFO: delWithBaggageithBaggage create_lchannel: logical_id=0 real_id=0 size=196
WAIT START:
```

## Unityのシミュレーションを開始する

先ほどのUnityのシーンに戻って、シミュレーション開始ボタンを押すと、下図のように待機状態になります。

<img width="1377" alt="スクリーンショット 2023-08-05 17 36 38" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/894223ba-1ef5-4bc2-ab07-0c164ceef918">

この状態で、STARTボタンを押下すると、ロボットが走り出します。

## シミュレーションを停止する

シミュレーションを停止する場合は、Unityのシミュレーションボタンを押して、Unity側のシミュレーションを終了させます。
次に、`run.bash`を `Ctrl+C` で停止します。


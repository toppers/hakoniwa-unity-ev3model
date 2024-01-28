# 前提とする環境

- Blender
  - 3.0 以降
- Unity Hub
- Unity（各CPUアーキテクチャに対応したもの）
  - 2022.3.10f1 以降

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

# Unity起動

この状態で Unity Hub で当該プロジェクトを開きましょう。

注意：Unityエディタは、当該CPUアーキテクチャに対応したものをインストールしてご利用ください。

対象フォルダ：hakoniwa-unity-ev3model\plugin\plugin-srcs

以下のダイアログが出ますが、`Continue` してください。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/8677ab91-a1c3-4e3b-8c2a-cecaf4998be0)


次に、以下のダイアログが出ますので、`Ignore` してください。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/57e53403-14d9-446f-8f58-7642c1d0615c)

成功するとこうなります。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/c6cbb179-f977-49d0-9c72-f015a865208d)

起動直後の状態ですと、コンソール上にたくさんエラーが出てる場合があります。
原因は、Newtonsoft.Json が不足しているためです。 

Unityのパッケージマネージャから Newtonsoft.Jsonをインストールすることで解消できます。

`Window/PackageManger`を開き、下図のように、`+` をクリックし、`Add pacakge from git` をクリックします。
`com.unity.nuget.newtonsoft-json` を入力して、`Add` をクリックすると、インストールが始まり、エラーが解消されます。

<img width="794" alt="スクリーンショット 2023-08-05 17 15 16" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/828e3256-7e8b-4677-92b4-55cbb980db0f">

# シミュレーション環境の準備

## Unity側

下図のように、Unity のシーン(`Scenes/TrainModel/Hakoniwa`)をダブルクリックします。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/bb3ba7e2-98cb-4a8e-9f9d-1ccde09fbc56)


![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/a6687f1d-65bf-4f74-a6fc-272fe53360fe)


そして、｀Window/Hakoniwa/Generate` をクリックします。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/e0e4119c-004a-4a26-809d-d248399573ae)

成功すると、plugin_srcs 配下に、各種コンフィグファイルが生成されます。

特に、ロボットのコンフィグファイルが以下のようになっていることを確認ください。
コンフィグデータの仕様は[こちら](https://github.com/toppers/hakoniwa-core-cpp-client?tab=readme-ov-file#%E3%82%B3%E3%83%B3%E3%83%95%E3%82%A3%E3%82%B0%E9%A0%85%E7%9B%AE%E3%81%AE%E8%A9%B3%E7%B4%B0)。

```
{
  "robots": [
    {
      "name": "EV3TrainModel",
      "rpc_proxy": {
        "name": "Athrill",
        "class_name": "Hakoniwa.PluggableAsset.Assets.Micon.EV3.Ev3MiconAssetController"
      },
      "rpc_pdu_readers": [
        {
          "type": "ev3_msgs/Ev3PduActuator",
          "org_name": "ev3_actuator",
          "name": "EV3TrainModel_ev3_actuator",
          "class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduReader",
          "class_path": "",
          "conv_class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduReaderConverter",
          "conv_class_path": "",
          "channel_id": 0,
          "pdu_size": 196
        }
      ],
      "rpc_pdu_writers": [
        {
          "type": "ev3_msgs/Ev3PduSensor",
          "org_name": "ev3_sensor",
          "name": "EV3TrainModel_ev3_sensor",
          "class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduWriter",
          "class_path": "",
          "conv_class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduWriterConverter",
          "conv_class_path": "",
          "channel_id": 1,
          "pdu_size": 248,
          "write_cycle": 1,
          "method_type": "UDP"
        }
      ]
    },
    {
      "name": "EV3SignalModel",
      "rpc_proxy": {
        "name": "Athrill",
        "class_name": "Hakoniwa.PluggableAsset.Assets.Micon.EV3.Ev3MiconAssetController"
      },
      "rpc_pdu_readers": [
        {
          "type": "ev3_msgs/Ev3PduActuator",
          "org_name": "ev3_actuator",
          "name": "EV3SignalModel_ev3_actuator",
          "class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduReader",
          "class_path": "",
          "conv_class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduReaderConverter",
          "conv_class_path": "",
          "channel_id": 0,
          "pdu_size": 196
        }
      ],
      "rpc_pdu_writers": [
        {
          "type": "ev3_msgs/Ev3PduSensor",
          "org_name": "ev3_sensor",
          "name": "EV3SignalModel_ev3_sensor",
          "class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduWriter",
          "class_path": "",
          "conv_class_name": "Hakoniwa.PluggableAsset.Communication.Pdu.Raw.RawPduWriterConverter",
          "conv_class_path": "",
          "channel_id": 1,
          "pdu_size": 248,
          "write_cycle": 1,
          "method_type": "UDP"
        }
      ]
    }
  ]
}
```


# シミュレーション実行方法

Unityのシーンで、シミュレーション開始ボタンを押すと、下図のように待機状態になります。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/51a8c8be-f7de-4dd0-83e6-ac46adf37895)

この状態で、STARTボタンを押下すると、ロボットが走り出します。

## シミュレーションを停止する

シミュレーションを停止する場合は、Unityのシミュレーションボタンを押して、Unity側のシミュレーションを終了させます。


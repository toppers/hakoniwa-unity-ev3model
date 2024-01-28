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

<img width="526" alt="スクリーンショット 2023-08-05 17 02 16" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/ade85aee-b08e-4920-b148-ce3ef09f5545">


次に、以下のダイアログが出ますので、`Ignore` してください。

<img width="257" alt="スクリーンショット 2023-08-05 17 03 38" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/6448e882-b0a3-42c1-8a01-398dbcd450dd">


成功するとこうなります。

<img width="1382" alt="スクリーンショット 2023-08-05 17 05 32" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/de7c9fec-1bb2-411b-90b1-71e2577b6cf1">

起動直後の状態ですと、コンソール上にたくさんエラーが出てる場合があります。原因は以下です。

* Newtonsoft.Json が不足している


## Newtonsoft.Json が不足している問題の対応

gRPC の対応をしても、Unityエディタのバージョンによっては、下図のようなエラーが出ている場合があります。

<img width="1046" alt="スクリーンショット 2023-08-05 17 12 38" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/63e7e31b-80d0-447e-9c77-5555293fa685">

原因は、Newtonsoft.Json が不足しているためです。 

Unityのパッケージマネージャから Newtonsoft.Jsonをインストールすることで解消できます。

`Window/PackageManger`を開き、下図のように、`+` をクリックし、`Add pacakge from git` をクリックします。
`com.unity.nuget.newtonsoft-json` を入力して、`Add` をクリックすると、インストールが始まり、エラーが解消されます。

<img width="794" alt="スクリーンショット 2023-08-05 17 15 16" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/828e3256-7e8b-4677-92b4-55cbb980db0f">

# Unity の各種設定

`Editor/ProjectSettings/Physics` を開き、Friction Type を `One Directional Friction Type` に変更してください。

![スクリーンショット 2023-08-16 7 50 32](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/4098b72c-44d5-4029-80be-9981bfd3e73a)

# シミュレーション環境の準備

## Unity側

下図のように、Unity のシーンをダブルクリックします。

<img width="459" alt="スクリーンショット 2023-08-05 17 22 47" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/b3befac6-85dc-4c60-83b5-86259ccb87be">

そして、｀Window/Hakoniwa/Generate` をクリックします。

<img width="325" alt="スクリーンショット 2023-08-05 17 24 11" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/8eae6801-cc2e-4d05-9c14-c26f6e1bc54d">


# シミュレーション実行方法

Unityのシーンで、シミュレーション開始ボタンを押すと、下図のように待機状態になります。

<img width="1377" alt="スクリーンショット 2023-08-05 17 36 38" src="https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/894223ba-1ef5-4bc2-ab07-0c164ceef918">

この状態で、STARTボタンを押下すると、ロボットが走り出します。

## シミュレーションを停止する

シミュレーションを停止する場合は、Unityのシミュレーションボタンを押して、Unity側のシミュレーションを終了させます。


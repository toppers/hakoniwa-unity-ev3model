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


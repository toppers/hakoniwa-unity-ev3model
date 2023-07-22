Hakoniwa Robot Asset Unity Repository for EV3

# 前提環境

## Unity

* Unity Hub
  * Unity Hub 3.5.0
* Unity
  * Unity 2021.3.7f1

なお、Unityおよび Unity Hub はインストールされていることを前提として解説します。

# Windows環境
* Windows10 Home, Windows 11
* WSL2/WSLg/Ubuntu20.0.4
* WSL2/Docker Engine

# インストール方法

本リポジトリを以下のようにクローンします。

```
git clone --recursive https://github.com/toppers/hakoniwa-unity-ev3model.git
```

クローンぐ終わったら、以下のようにディレクトリ移動します。

```
cd hakoniwa-unity-ev3model/
```

そして、必要なUnityモジュール類をインストールします。

```
 bash install.bash 
```

この状態で Unity Hub で当該プロジェクトを開きましょう。

対象フォルダ：`hakoniwa-unity-ev3model\plugin\plugin-srcs`

成功するとこうなります。

![image](https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/2712f400-ffef-4294-a9a5-4ccbdc407740)

なお、Unityエディタのバージョンによっては、起動中にエラーとなる場合があります。
その場合、途中、ダイアログがポップアップされて警告されますが、気にせず起動しましょう。

原因は、`Newtonsoft.Json` が不足しているためです。
対応方法は、下記記事にある通り、Unityのパッケージマネージャから `Newtonsoft.Json`をインストールすることで解消できます。

https://qiita.com/sakano/items/6fa16af5ceab2617fc0f

## 電車モデルのシーン表示

Unityエディタ起動後、プロジェクトビューの　`Scenes/TraninModel/Work` をダブルクリックしてください。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/af772f9c-a79f-4712-8ad5-bbc24a874d24)


このまま、`Window/Hakoniwa/GenerateDebug` をクリックしましょう。

![image](https://github.com/toppers/hakoniwa-openel-cpp/assets/164193/8be12b93-48d8-4fee-bac0-4e02ca0e6a9d)


## シミュレーション実行方法

Unityの再生ボタンをクリックします。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/a5ac2eee-76bd-4bfd-be2f-1bb0f7b9f676)


## 電車モデル

電車モデルは、下図のものです。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/871aed5e-8741-4dba-a16a-8da5e332ea55)

この電車モデルにはタッチセンサがついています。画面右上のボタン部分をクリックすると反応します。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/cfd9df48-18e0-4855-85d2-0245b87df3c8)

また、電車モデルには、信号読み取り用のカラーセンサが下図のようについています。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/d42c48a9-950e-42b7-b593-912857b8f013)

以下は、電車モデルのテストドライバです。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/f17de823-ac97-4365-a29b-8a82854de25d)


キーボード操作で、電車を前後に移動できます。

* ↑キー押下
  * モータにかける力を +1 します。
* ↓キー押下
  * モータにかける力を -1 します。
* スペースキー押下
  * モータにかける力を 0 にします。

電車モデルのタッチセンサをマウスクリックすると、下図のようにテストドライバの左上のキューブが赤色になります。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/5abe4c7e-da7b-4591-8a88-2d52d3ae3c07)

離すと、下図のようにテストドライバの左上のキューブが青色になります。

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/89a2ba77-53b3-4a73-b482-811cce522b66)

カラーセンサが認識した色に応じて、下図のようにテストドライバの右上のキューブが変化します。

イエローを認識：
![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/d22d5786-0e7d-414c-a665-45f49f640dd1)


## 信号モデル

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/1fdca183-2ee1-4c52-a19f-ca38c3403a7d)

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/f50d1181-c6b2-451e-9d90-c4ba0253e970)

![image](https://github.com/toppers/hakoniwa-unity-ev3model/assets/164193/a047ff81-b18e-4a67-ac95-57a305b217e9)

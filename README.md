# rrase_mosi_lover
授業よう

## 目標
### 12/6まで
ひとまず最低限動くものを作る！

## 共有内容
### 共通の構造体

#### 入出力周り(DataStructure)
- input_structure
	実際の入力を構造体にしたもの
- middle_structure
	不確定要素を決定する人たちが確定しやすい構造にする
- output_structure
	結果の出力

#### 設定周り(Settings)
- execute_setting
	実行時の設定
- generator_setting
	テスト作成の際の設定、比率とかはもしかしたら変更したほうがいいかもしれないから、変えられるようにしといてほしいかも
- confirm_solver_setting
	確定アルゴリズムの部分で、可変の設定をまとめる(後々の最適化のために設定しやすいと良い)
- predection_solver_setting
	上に同じ

## 処理のフロー
- Generator
	- 入力の受付(本番前までは、関数から生成) 
- Solver
	- 確定的な部分の選出(confirm_solver)
		input_structure -> middle_structure
	- 不確定な部分の予測(prediction_solver)
		middle_structure -> output_structure
- Presenter
	- 結果の出力(本番前までは、解析用に使いたいね)

## 重要
必ずやってほしいこと
### 作業場所について

- 入力の作成は'Generator'
- 確定部分のアルゴリズムの作成は'Solver/ConfirmSolver'
- 推測部分のアルゴリズムの作成は'Solver/PredictionSolver'
- 出力の作成は'Presenter'

にて作業してください。それぞれについてブランチを作成！

人じゃなくて、やる内容ごとにブランチを作りましょう。

### ブランチの管理について

ブランチにはいくつか挙げてはいけないファイルがあります。

例を挙げると実行ファイルなどです。後、自分の環境だけにおいておくものはブランチに挙げないようにお願いします。

### headerファイルについて

\*.hと\*.cのファイルを作ることになると思います。

\*.hのファイルに書くのは外部に公開したい関数を書いておきます。これによって、関数名の重複を避けます。

もう一つ\*.hの多重参照(?)するとエラーになるので\*.hファイルには,以下の内容を書いてください

	#ifndef [好きな名前、内容に合わせた名前がいいかも]
	#define [上と同じ文字列]
	/*
	ここにコードを書く
	*/
	#endif

サンプルはすでに上がっているコードを参考に...

### テストコードの作成
自身が担当するプログラムが一度完成したら、そのコードを使ってのサンプルコードを作成してください

各自の作業ディレクトリにtest.cというのを作って、Makefileを各自テスト用に作ってください。

テストコードは、ある程度その中身が正しく動いていることを確認できる状態にしてください。

#### テストコードの意義
テストコードの作成は他の人のためにあるもので、テストで動かし方を見ると他の人も理解しやすいね！ということで、集団で作成するときには重要になってきます。

サンプルは後ほど...
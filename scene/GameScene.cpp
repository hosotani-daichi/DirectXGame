#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>


GameScene::GameScene() {}
//デストラクタ
GameScene::~GameScene() {
	delete model_;
	delete modelBlock_;
	for (WorldTransform* worldTransformBlocks : worldTransformBlocks_) {
		delete worldTransformBlocks;
	}
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルの生成
	model_ = Model::Create();
	//モデル読み込み
	modelBlock_ = Model::CreateFromOBJ("cube");
	//要素数
	const uint32_t kNumBlockHorizontal = 20;
	//ブロック一個分の横幅
	const float kBlockWidth = 2.0f;
	//要素数を変更する
	worldTransformBlocks_.resize(kNumBlockHorizontal);
	//キューブの生成
	for (uint32_t i = 0; i < kNumBlockHorizontal; ++i) {
		worldTransformBlocks_[i] = new WorldTransform();
		worldTransformBlocks_[i]->Initialize();
		worldTransformBlocks_[i]->translation_.x = kBlockWidth * i;
		worldTransformBlocks_[i]->translation_.y = 0.0f;
	}

}

void GameScene::Update() { 
	for (WorldTransform* worldTransformblock : worldTransformBlocks_) {
	
		//平行移動
		Matrix4x4 result{
		    1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			worldTransformblock->translation_.x, 
			worldTransformblock->translation_.y, 
			worldTransformblock->translation_.z,
		    1.0f};

		//平行移動だけ代入
		worldTransformblock->matWorld_ = result;

		//定数バッファに転送する
		worldTransformblock->TransferMatrix();

	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// ブロックの描画
	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		modelBlock_->Draw(*worldTransformBlock, viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

	

#pragma endregion
}

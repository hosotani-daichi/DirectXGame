#include "Player.h"
#include <cassert>

// 初期化
void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}

// 更新
void Player::Update() {
	// 行列を定数でバッファに転送
	worldTransform_.TransferMatrix();
}

// 描画
void Player::Draw() {
	// ３Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}
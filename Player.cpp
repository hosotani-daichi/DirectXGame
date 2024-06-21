#include "Player.h"
#include <cassert>
#include <numbers>
#include "Input.h"

// 初期化
void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}

// 更新
void Player::Update() {

	//移動入力
	//左右移動操作
	if (Input::GetInstance()->PushKey(DIK_RIGHT)||
		Input:: GetInstance()->PushKey(DIK_LEFT)) {
		// 左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
			acceleration.x += kAcceleration;
		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
			acceleration.x += kAcceleration;
		}
		// 加速/減速
		velocity_ += acceleration;
	}
	
	//移動
	worldTransform_.translation_ += velocity_;
	// 行列を定数でバッファに転送
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw() {

	// ３Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}
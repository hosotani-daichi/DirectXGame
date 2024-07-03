#define NOMINMAX
#include "Player.h"
#include "Input.h"
#include <algorithm>
#include <cassert>
#include <numbers>

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

	// 移動入力
	// 接地状態
	if (onGround_) {
		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;

				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					// 旋回開始時の角度を記録する
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーに時間を設定する
					turnTimer_ = kTimeTurn;
				}
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				// 右移動中の左入力
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;

				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					// 旋回開始時の角度を記録する
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					// 旋回タイマーに時間を設定する
					turnTimer_ = kTimeTurn;
				}

				// 加速/減速
				velocity_ += acceleration;
				// 最大速度制限
				velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
			} else {

				// 非入力時は移動減衰をかける
				velocity_.x *= (1.0f - kAttenuation);
			}

			if (Input::GetInstance()->PushKey(DIK_UP)) {
				// ジャンプ速度
				velocity_ += Vector3(0, kJumpAcceleration, 0);

		} else {

			// 落下速度
			velocity_ += Vector3(0, -kGravityAcceleration, 0);
			// 落下速度制限
			velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
		}

		// 旋回制御
		if (turnTimer_ > 0.0f) {
			turnTimer_ -= 1 / 60.0f;

			// 左右の自キャラ角度テーブル
			float destinationRotationYTable[]{std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
			// 状態に応じた角度を取得する
			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
			// 自キャラの角度を設定する
			worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);
			// 旋回タイマーを1/60秒分カウントダウンする
		}
	}

	// 着地フラグ
	bool landing = false;

	// 地面との当たり判定
	// 下降中？
	if (velocity_.y < 0) {
		// Y座標が地面以下になったら着地
		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;

			// 移動
			worldTransform_.translation_ += velocity_;
			// 行列を定数でバッファに転送
			worldTransform_.UpdateMatrix();
		}
	}

	//接地判定
	if (onGround_) {
	//ジャンプ開始
		if (velocity_.y > 0.0f) {
		//空中状態に移行
			onGround_ = false;
		}
	} else {
	//着地
		if (landing) {
		//めり込み
			worldTransform_.translation_.y = 1.0f;
			//摩擦で横方向速度が減衰する
			velocity_.x *= (1.0f - kAttenuation);
			//下方向速度をリセット
			velocity_.y = 0.0f;
			//接地状態に移行
			onGround_ = true;
		}
	}


}

// 描画
void Player::Draw() {

	// ３Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}
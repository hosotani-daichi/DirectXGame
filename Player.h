#include "MathUtilityForText.h"
#include "WorldTransform.h"
#include "model.h"

#pragma once
class Player {
public:
	///< summary>
	/// 初期化
	///  </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	///< summary>
	/// 更新
	///  </summary>
	void Update();

	///< summary>
	/// 描画
	///  </summary>
	void Draw();

	enum class LRDirection {
		kRight,
		kLeft,
	};

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 接地状態フラグ
	bool onGround_ = true;

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Vector3 velocity_ = {};

	ViewProjection* viewProjection_ = nullptr;

	LRDirection lrDirection_ = LRDirection::kRight;

	static inline const float kAcceleration = 0.01f;
	static inline const float kAttenuation = 0.1f;
	static inline const float kLimitRunSpeed = 0.1f;
	static inline const float kTimeTurn = 1.0f;
	// 重力加速度（下方向）
	static inline const float kGravityAcceleration = 0.1f;
	// 最大落下速度（下方向）
	static inline const float kLimitFallSpeed = 1.0f;
	// ジャンプ初速（上方向）
	static inline const float kJumpAcceleration = 1.0f;
};
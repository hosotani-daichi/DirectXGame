#include "AABB.h"
#include "MathUtilityForText.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "model.h"

class MapChipField;
class Enemy;

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

	LRDirection lrDirection_ = LRDirection::kRight;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;

	// 接地状態フラグ
	bool onGround_ = true;

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const Vector3& GetVelocity() const { return velocity_; }

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	void InputMove();

	// 衝突応答
	void OnCollision(const Enemy* enemy);

	// マップとの当たり判定情報
	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitWall = false;
		Vector3 move;
	};

	void CheckMapCollision(CollisionMapInfo& info);
	void CheckMapCollisionUp(CollisionMapInfo& info);
	void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);

	void CheckMapMove(CollisionMapInfo& info);

	void CheckMapCeiling(CollisionMapInfo& info);

	void AnimateTurn();

	void CheckMapLanding(const CollisionMapInfo& info);

	void CheckMapWall(const CollisionMapInfo& info);

	enum Corner {
		kRightBottom, // 右下
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 左上

		kNumCorner // 要素数
	};

	// ワールド座標を取得
	Vector3 GetWorldPosition();
	// AABBを取得
	AABB GetAABB();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	Vector3 velocity_ = {};

	ViewProjection* viewProjection_ = nullptr;

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	// 加速
	static inline const float kAcceleration = 0.01f;
	// 減速
	static inline const float kAttenuation = 0.02f;
	// 最大速度
	static inline const float kLimitRunSpeed = 1.0f;
	// 着地時の速度減衰率
	static inline const float kTimeTurn = 1.0f;
	// 重力加速度（下方向）
	static inline const float kGravityAcceleration = 0.1f;
	// 最大落下速度（下方向）
	static inline const float kLimitFallSpeed = 1.0f;
	// ジャンプ初速（上方向）
	static inline const float kJumpAcceleration = 1.0f;
	// 着地時の速度減衰率
	static inline const float kAttenuationLanding = 0.1f;
	// 落下用
	static inline const float kGroundSearchHeight = 0.06f;
	// 着地時の速度減衰率
	static inline const float kAttenuationWall = 0.1f;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	static inline const float kBlank = 0.04f;
};
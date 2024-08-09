#pragma once
#include "AABB.h"
#include "MathUtilityForText.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Player;

class Enemy {

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

	// 衝突応答
	void OnCollision(const Player* player);
	// AABBを取得
	AABB GetAABB();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	// ワールド座標を取得
	Vector3 GetWorldPosition();
	// 歩行の速さ
	static inline const float kWalkSpeed = 0.01f;
	// 速度
	Vector3 velocity_ = {};
	// 最初の角度「度」
	static inline const float kWalkMotionAngleStart = 0.0f;
	// 最後の角度「度」
	static inline const float kWalkMotionAngleEnd = 30.0f;
	// アニメーションの周期となる時間「秒」
	static inline const float kWalkMotionTime = 1.0f;
	// 経過時間
	float walkTimer_ = 0.0f;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
};

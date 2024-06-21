#include "WorldTransform.h"
#include "model.h"
#include "MathUtilityForText.h"

#pragma once
class Player {
public:
	///< summary>
	/// 初期化
	///  </summary>
	void Initialize(Model* model, ViewProjection* viewProjection,const Vector3& position);

	///< summary>
	/// 更新
	///  </summary>
	void Update();

	///< summary>
	/// 描画
	///  </summary>
	void Draw();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Vector3 velocity_ = {};

	ViewProjection* viewProjection_ = nullptr;

	static inline const float kAcceleration = 5;
};
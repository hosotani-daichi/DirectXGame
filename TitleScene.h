#include "Input.h"
#include "DirectXCommon.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "model.h"
#include "Audio.h"

#pragma once
class TitleScene {

public:
	TitleScene();
	~TitleScene();

	///< summary>
	/// 初期化
	///  </summary>
	void Initialize();

	///< summary>
	/// 更新
	///  </summary>
	void Update();

	///< summary>
	/// 描画
	///  </summary>
	void Draw();

	// 終了フラグ
	bool finished_ = false;
	// デスフラグのgetter
	bool IsFinished() const { return finished_; }

private:

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Model* modelFont_ = nullptr;
	Model* modelPlayer_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	WorldTransform worldTransformFont_;
	WorldTransform worldTransformPlayer_;

	float timer_ = 0.0f;
	static inline const float kMotionTime = 1.0f;
};

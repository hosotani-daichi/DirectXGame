#include "DirectXCommon.h"
#include "Input.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "model.h"
#include <Audio.h>

#pragma once
class TitleScene {
public:
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

	//// 終了フラグ
	//bool finished_ = false;
	//// デスフラグのgetter
	//bool IsFinished() const { return finished_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
};

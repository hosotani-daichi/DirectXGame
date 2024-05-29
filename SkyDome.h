#include "WorldTransform.h"
#include "model.h"

#pragma once
class SkyDome {
public:
	///< summary>
	/// 初期化
	///  </summary>
	void Initialize(Model* model, ViewProjection* viewProjection);

	///< summary>
	/// 更新
	///  </summary>
	void Update();

	///< summary>
	/// 描画
	///  </summary>
	void Draw();

	private:
		//ワールド変換データ
	    WorldTransform worldTransform_;
		//モデル
	    Model* model_ = nullptr;
		//ビュープロジェクション
	    ViewProjection* viewProjection_ = nullptr;

};

#include "SkyDome.h"
#include <cassert>

void SkyDome::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	// ワールド変換の初期化
	worldTransform_.Initialize();
	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjection;
}

void SkyDome::Update()
{ 
	worldTransform_.UpdateMatrix();
}

void SkyDome::Draw() {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}



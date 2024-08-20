#include "TitleScene.h"
#include <numbers>

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
}

void TitleScene::Update() {
	//if (Input::GetInstance()->PushKey(DIK_SPACE)) {
	//	finished_ = true;
	//}
}

void TitleScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	// ここに3Dオブジェクトの描画処理を追加できる
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
}

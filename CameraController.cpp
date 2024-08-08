#include "CameraController.h"
#include "Player.h"

void CameraController::Initialize() {
	// 引数の内容をメンバ変数に記録
	viewProjection_.Initialize();
}

void CameraController::Update() {

	const Vector3& targetVelocity = target_->GetVelocity();

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットと追従対象の速度からカメラの目標座標を計算
	cameraTarget_ = targetWorldTransform.translation_ + targetOffset_ + targetVelocity * kVelocityBias;

	////座標補間によりゆったり追従
	viewProjection_.translation_ = Lerp(viewProjection_.translation_, cameraTarget_, kInterpolationRate);

	//// 移動範囲制限
	viewProjection_.translation_.x = max(viewProjection_.translation_.x, targetWorldTransform.translation_.x + targetmargin.left);
	viewProjection_.translation_.x = min(viewProjection_.translation_.x, targetWorldTransform.translation_.x + targetmargin.right);
	viewProjection_.translation_.y = max(viewProjection_.translation_.y, targetWorldTransform.translation_.y + targetmargin.bottom);
	viewProjection_.translation_.y = min(viewProjection_.translation_.y, targetWorldTransform.translation_.y + targetmargin.top);

	// 行列を更新する
	viewProjection_.UpdateMatrix();
}

void CameraController::Reset() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットからカメラの座標を計算
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}

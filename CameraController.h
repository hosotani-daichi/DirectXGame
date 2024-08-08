#include "ViewProjection.h"
#include "MathUtilityForText.h"

#pragma once

class Player;

class CameraController {
public:
	///< summary>
	/// 初期化
	///  </summary>
	void Initialize();

	///< summary>
	/// 更新
	///  </summary>
	void Update();

	void SetTarget(Player* target) { 
		target_ = target;
	}

	void Reset();
	const ViewProjection& GetViewProjection() const { return viewProjection_; }

	//速度掛け率
	static inline const float kVelocityBias = 30;	

	//座標補間割合
	static inline const float kInterpolationRate = 0.06f;

	struct Rect {
		float left = 0.0f;//右端
		float right = 1.0f;//左端
		float bottom = 0.0f;//下端
		float top = 1.0f;//上端
	};

		// 追従対象の各方向へのカメラ移動範囲
	static inline const Rect targetmargin = {-9.0f, 9.0f, -5.0f, 5.0f};

	void SetMovableArea(Rect area) { movableArea_ = area; }

	private:

		Rect movableArea_ = {0, 100, 0, 100};

	Vector3 targetOffset_ = {0, 0, -15.0f};

	//カメラの目標座標
	Vector3 cameraTarget_;

	ViewProjection viewProjection_;

	    Player* target_ = nullptr;
};

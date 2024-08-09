#pragma once

#include "AABB.h"
#include "Audio.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "MapChipField.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <CameraController.h>
#include <DebugCamera.h>
#include <Player.h>
#include <SkyDome.h>
#include <vector>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void GenerateBlocks();

	void CheckAllCollosions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	// 3Dモデル
	Model* model_ = nullptr;

	// ３Dブロックモデル
	Model* modelBlock_ = nullptr;

	// 敵キャラモデル
	Model* modelEnemy_ = nullptr;

	/// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// スプライト
	Sprite* sprite_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 自キャラ
	Player* player_ = nullptr;

	// 敵キャラ
	Enemy* enemy_;
	std::list<Enemy*> enemies_;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;

	// スカイドームの3Dモデル
	Model* modelSkyDome_ = nullptr;

	// スカイドーム
	SkyDome* skydome_ = nullptr;

	// マップチップフィールド
	MapChipField* mapChipField_;

	// カメラコントロール
	CameraController* cameracontroller_ = nullptr;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
};

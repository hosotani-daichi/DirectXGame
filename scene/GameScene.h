#pragma once

#include "AABB.h"
#include "Audio.h"
#include "DeathParticles.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Input.h"
#include "MapChipField.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "TitleScene.h"
#include "DeathParticles.h"
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

	void ChangePhase();

	//	// 終了フラグ
	//bool finished_ = false;
	//// デスフラグのgetter
	//bool IsFinished() const { return finished_; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ゲームのフェーズ（型）
	enum class Phase {
		kPlay,  // ゲームプレイ
		kDeath, // デス演出
	};
	// ゲームの現在フェーズ
	Phase phase_;

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

	DeathParticles* deathParticles_ = nullptr;
	Model* modelDeath_ = nullptr;

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

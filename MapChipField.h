#pragma once
#include <cstdint>
#include <vector>
#include "WorldTransform.h"
#include "model.h"

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {

public:
	void ResetMapChipData();
	void LoadMapChipCsv(const std::string& filePath);

private:
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeidht = 1.0f;
	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

};

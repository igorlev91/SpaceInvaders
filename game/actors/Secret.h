#pragma once

#include "../../pk/core/world/Actor.h"
#include "Alien.h"

class Game;

using namespace pk;

class Secret : public Actor
{
public:
	typedef std::weak_ptr<Game> GameWeakPtr;
	typedef std::shared_ptr<Game> GameSharedPtr;

	static const float DEFAULT_SPAWN_TIME_MIN;
	static const float DEFAULT_SPAWN_TIME_MAX;
	static const float DEFAULT_ALIEN_SPEED;
	static const float DEFAULT_ALIEN_TOP_OFFSET;
	static const glm::vec3 DEFAULT_ALIEN_SIZE;

	Secret();

	float GetSpawnTimeMin() const;
	float GetSpawnTimeMax() const;
	float GetSelectedSpawnTime() const;
	float GetAlienSpeed() const;
	float GetTopOffset() const;
	glm::vec3 GetAlienSize() const;

	void SetSpawnTimeMax(float InSpawnTime);
	void SetSpawnTimeMin(float InSpawnTime);
	void SetAlienSpeed(float InSpeed);
	void SetTopOffset(float InTopOffset);
	void SetAlienSize(const glm::vec3& InSize);

	void LoadConfig() override;
	void Begin() override;
	void Update(const float Delta) override;

	void Reset();

private:
	void SelectSpawnTime();
	void UpdateSpawnTime(const float Delta);
	void UpdateAlien();
	void CreateAlien();
	void SpawnAlien();

	void PlaySpawnAudio();
	void StopSpawnAudio();

	GameSharedPtr GetGame() const;

	unsigned int SpawnAudioChannel;
	bool bAlienActive;
	float SpawnTimeMin;
	float SpawnTimeMax;
	float SelectedSpawnTime;
	float CurrentSpawnTime;
	float AlienSpeed;
	float TopOffset;
	glm::vec3 AlienSize;

	Alien::SharedPtr CurrentAlien;
	GameWeakPtr GamePtr;
};

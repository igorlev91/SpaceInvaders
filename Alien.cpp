#include "Alien.h"

#include <iostream>

#include "Assets.h"
#include "Projectile.h"
#include "ProjectilePool.h"
#include "TeamComponent.h"
#include "pk/Scene.h"
#include "pk/ClassSettingsReader.h"
#include "pk/SoundEngine.h"

Alien::Alien(AlienType InType)
	: Score(0), Type(InType)
{
	HasCollision(true);

	TeamPtr = std::make_shared<TeamComponent>(weak_from_this());
	TeamPtr->SetTeam(Team::Alien);
	AddComponent(TeamPtr);
}

Alien::Alien(const Transform& InTransform, AlienType InAlienType)
	: Alien(InAlienType)
{
	SetLocation(InTransform.Location);
	SetSize(InTransform.Size);
}

Alien::Alien(const glm::vec3& InLocation, const glm::vec3& InSize, AlienType InAlienType)
	: Alien(Transform(InLocation, InSize), InAlienType)
{
}

void Alien::SetProjectilePool(const ProjectilePoolPtr& InProjectilePool)
{
	CurrentProjectilePool = InProjectilePool;
}

int Alien::GetScore() const
{
	return Score;
}

AlienType Alien::GetType() const
{
	return Type;
}

void Alien::LoadConfig()
{
	Actor::LoadConfig();

	ClassSettings::SharedConstPtr AlienSettings = ClassSettingsReader::Load(GetConfigFile());
	if (AlienSettings == nullptr)
	{
		return;
	}

	AlienSettings->Get("Score", 0, Score);
	glm::vec4 SettingColor(Colors::White);
	AlienSettings->Get("Color", SettingColor);
	SetColor(SettingColor);
}

bool Alien::TakeDamage(float InDamage)
{
	SoundEngine::Get().Play(Assets::Sounds::AlienExplosion, 1.f);
	Destroy();
	return true;
}

void Alien::Shoot() const
{
	if (CurrentProjectilePool == nullptr)
	{
		std::cout << "[Alien] - Unable to shoot, no pool obtained.\n";
		return;
	}

	const Scene::SharedPtr CurrentScene = GetScene();

	glm::vec3 SpawnLocation(GetLocation());
	SpawnLocation.y += (GetSize().y + 5.f);

	Projectile::SharedPtr NewProjectile = CurrentProjectilePool->Create(SpawnLocation, TeamPtr->GetTeam());
	CurrentScene->Add(NewProjectile);
}

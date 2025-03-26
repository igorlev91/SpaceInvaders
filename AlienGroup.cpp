#include "AlienGroup.h"

#include <iostream>

#include "Assets.h"
#include "pk/Random.h"
#include "pk/Scene.h"
#include "pk/SettingsReader.h"

const int AlienGroup::DEFAULT_NUM_ROWS_PER_TYPE = 2;
const int AlienGroup::DEFAULT_ALIEN_PER_ROW = 11;
const float AlienGroup::DEFAULT_TOP_OFFSET = 60.f;
const float AlienGroup::DEFAULT_MOVE_DELAY = 2.f;
const float AlienGroup::DEFAULT_SHOOT_MAX_COOLDOWN = 2.f;
const float AlienGroup::DEFAULT_SHOOT_MIN_COOLDOWN = 0.5f;
const float AlienGroup::DEFAULT_H_MOVE_STEP = 10.f;
const float AlienGroup::DEFAULT_V_MOVE_STEP = 5.f;
const float AlienGroup::DEFAULT_H_DISTANCE = 20.f;
const float AlienGroup::DEFAULT_V_DISTANCE = 20.f;
const glm::vec3 AlienGroup::DEFAULT_ALIEN_SIZE = glm::vec3(10.f, 10.f, 1.f);

AlienGroup::AlienGroup()
	: bRightDirection(true), bGoDown(false),
		NumRowsPerType(DEFAULT_NUM_ROWS_PER_TYPE), NumAlienPerRow(DEFAULT_ALIEN_PER_ROW),
		OuterLeftCol(0), OuterRightCol(DEFAULT_ALIEN_PER_ROW - 1), LastRow(0),
		TopOffset(DEFAULT_TOP_OFFSET), MoveDelay(DEFAULT_MOVE_DELAY), CurrentDelay(0.f),
		ShootMaxCooldown(DEFAULT_SHOOT_MAX_COOLDOWN), ShootMinCooldown(DEFAULT_SHOOT_MIN_COOLDOWN), SelectedShootCooldown(DEFAULT_SHOOT_MAX_COOLDOWN), CurrentShootCooldown(0.f),
		HorizontalMoveStep(DEFAULT_H_MOVE_STEP), VerticalMoveStep(DEFAULT_V_MOVE_STEP),
		HorizontalDistance(DEFAULT_H_DISTANCE), VerticalDistance(DEFAULT_V_DISTANCE),
		AlienSize(DEFAULT_ALIEN_SIZE),
		State(GroupState::None)
{
	ConfigTypeMapping.insert(ConfigMapPair(AlienType::Squid, Assets::Config::SquidFile));
	ConfigTypeMapping.insert(ConfigMapPair(AlienType::Crab, Assets::Config::CrabFile));
	ConfigTypeMapping.insert(ConfigMapPair(AlienType::Octopus, Assets::Config::OctopusFile));
}

GroupState AlienGroup::GetState() const
{
	return State;
}

int AlienGroup::GetNumRowsPerType() const
{
	return NumRowsPerType;
}

int AlienGroup::GetNumRowsTotal() const
{
	return NumRowsPerType * static_cast<int>(ConfigTypeMapping.size());
}

int AlienGroup::GetNumAlienPerRow() const
{
	return NumAlienPerRow;
}

float AlienGroup::GetTopOffset() const
{
	return TopOffset;
}

float AlienGroup::GetMoveDelay() const
{
	return MoveDelay;
}

float AlienGroup::GetShootMaxCooldown() const
{
	return ShootMaxCooldown;
}

float AlienGroup::GetShootMinCooldown() const
{
	return ShootMinCooldown;
}

float AlienGroup::GetHorizontalMoveStep() const
{
	return HorizontalMoveStep;
}

float AlienGroup::GetVerticalMoveStep() const
{
	return VerticalMoveStep;
}

float AlienGroup::GetHorizontalDistance() const
{
	return HorizontalDistance;
}

float AlienGroup::GetVerticalDistance() const
{
	return VerticalDistance;
}

glm::vec3 AlienGroup::GetAlienSize() const
{
	return AlienSize;
}

void AlienGroup::SetNumRowsPerType(int InNum)
{
	NumRowsPerType = std::abs(InNum);
}

void AlienGroup::SetNumAlienPerRow(int InNum)
{
	NumAlienPerRow = std::abs(InNum);
}

void AlienGroup::SetTopOffset(float InOffset)
{
	TopOffset = std::abs(InOffset);
}

void AlienGroup::SetMoveDelay(float InMoveDelay)
{
	MoveDelay = std::abs(InMoveDelay);
}

void AlienGroup::SetShootMaxCooldown(float InShootMaxCooldown)
{
	ShootMaxCooldown = std::abs(InShootMaxCooldown);
	if (ShootMaxCooldown <= ShootMinCooldown)
	{
		ShootMaxCooldown += ShootMinCooldown;
	}
}

void AlienGroup::SetShootMinCooldown(float InShootMinCooldown)
{
	ShootMinCooldown = std::max(DEFAULT_SHOOT_MIN_COOLDOWN, InShootMinCooldown);
}

void AlienGroup::SetHorizontalMoveStep(float InMoveStep)
{
	HorizontalMoveStep = std::abs(InMoveStep);
}

void AlienGroup::SetVerticalMoveStep(float InMoveStep)
{
	VerticalMoveStep = std::abs(InMoveStep);
}

void AlienGroup::SetHorizontalDistance(float InDistance)
{
	HorizontalDistance = std::abs(InDistance);
}

void AlienGroup::SetVerticalDistance(float InDistance)
{
	VerticalDistance = std::abs(InDistance);
}

void AlienGroup::SetAlienSize(const glm::vec3& InAlienSize)
{
	AlienSize = glm::abs(InAlienSize);
}

void AlienGroup::SetProjectilePool(const std::shared_ptr<ProjectilePool>& InProjectilePool)
{
	ProjectilePoolPtr = InProjectilePool;
}

void AlienGroup::LoadConfig()
{
	Actor::LoadConfig();

	Settings::SharedConstPtr GroupSettings = SettingsReader::Load(GetConfigFile());
	if (GroupSettings == nullptr)
	{
		return;
	}

	int InNumRows, InNumAlien;
	float InTopOffset, InMoveDelay, InShootMaxCooldown, InShootMinCooldown, InHMoveStep, InVMoveStep, InHDistance, InVDistance;
	glm::vec3 InAlienSize(DEFAULT_ALIEN_SIZE);
	GroupSettings->Get("NumRowsPerType", DEFAULT_NUM_ROWS_PER_TYPE, InNumRows);
	GroupSettings->Get("NumAlienPerRow", DEFAULT_ALIEN_PER_ROW, InNumAlien);
	GroupSettings->Get("TopOffset", DEFAULT_TOP_OFFSET, InTopOffset);
	GroupSettings->Get("MoveDelay", DEFAULT_MOVE_DELAY, InMoveDelay);
	GroupSettings->Get("ShootMaxCooldown", DEFAULT_SHOOT_MAX_COOLDOWN, InShootMaxCooldown);
	GroupSettings->Get("ShootMinCooldown", DEFAULT_SHOOT_MIN_COOLDOWN, InShootMinCooldown);
	GroupSettings->Get("HorizontalMoveStep", DEFAULT_H_MOVE_STEP, InHMoveStep);
	GroupSettings->Get("VerticalMoveStep", DEFAULT_V_MOVE_STEP, InVMoveStep);
	GroupSettings->Get("HorizontalDistance", DEFAULT_H_DISTANCE, InHDistance);
	GroupSettings->Get("VerticalDistance", DEFAULT_V_DISTANCE, InVDistance);
	GroupSettings->Get("AlienSize", InAlienSize);

	SetNumRowsPerType(InNumRows);
	SetNumAlienPerRow(InNumAlien);
	SetTopOffset(InTopOffset);
	SetMoveDelay(InMoveDelay);
	SetShootMinCooldown(InShootMinCooldown);
	SetShootMaxCooldown(InShootMaxCooldown);
	SetHorizontalMoveStep(InHMoveStep);
	SetVerticalMoveStep(InVMoveStep);
	SetHorizontalDistance(InHDistance);
	SetVerticalDistance(InVDistance);
	SetAlienSize(InAlienSize);
}

void AlienGroup::Begin()
{
	Actor::Begin();

	BuildMatrix();
	StartGroup();

	GenerateShootCooldown();
}

void AlienGroup::Update(const float Delta)
{
	Actor::Update(Delta);
	if (State != GroupState::Moving)
	{
		return;
	}

	UpdateShootCooldown(Delta);
	UpdateMoveDelay(Delta);
	if (ReachedPlayer())
	{
		State = GroupState::Stopped;
		NotifyReachedPlayer();
	}

	UpdateAliveAliens();
}

void AlienGroup::StartGroup()
{
	Scene::SharedPtr CurrentScene = GetScene();
	if (CurrentScene == nullptr)
	{
		return;
	}

	bRightDirection = true;
	bGoDown = false;
	CurrentShootCooldown = 0.f;
	CurrentDelay = 0.f;
	OuterLeftCol = 0;
	OuterRightCol = NumAlienPerRow - 1;
	LastRow = 0;

	const float Width = static_cast<float>(CurrentScene->GetScreenWidth());

	const float AlienPerRow = static_cast<float>(NumAlienPerRow);

	const float GroupRectangleWidth = (AlienSize.x * AlienPerRow) + (HorizontalDistance * AlienPerRow);
	const float StartX = (Width - GroupRectangleWidth) / 2;

	glm::vec3 CurrentLocation(0.f);
	CurrentLocation.y = TopOffset;
	CurrentLocation.x = StartX + (AlienSize.x / 2);

	AliveAliensIdx.clear();
	AliveAliensIdx.reserve(AllAliens.size());
	for (int i = 0; i < AllAliens.size(); ++i)
	{
		const Alien::SharedPtr& Alien = AllAliens[i];
		Alien->CancelDestroy();
		CurrentScene->Add(Alien);
		Alien->SetSize(AlienSize);
		Alien->SetLocation(CurrentLocation);
		AliveAliensIdx.push_back(i);

		CurrentLocation.x += HorizontalDistance + (AlienSize.x);

		if ((i + 1) % NumAlienPerRow == 0)
		{
			CurrentLocation.x = StartX + (AlienSize.x / 2);
			CurrentLocation.y += VerticalDistance + (AlienSize.y);
		}
	}

	State = GroupState::Moving;
}

void AlienGroup::AddOnReachedPlayerDelegate(const OnReachedPlayerDelegate& InFunction)
{
	OnReachedPlayerFunctions.push_back(InFunction);
}

void AlienGroup::AddOnDefeatDelegate(const OnDefeatDelegate& InFunction)
{
	OnDefeatFunctions.push_back(InFunction);
}

void AlienGroup::HideBoard() const
{
	for (const Alien::SharedPtr& Alien : AllAliens)
	{
		Alien->Destroy();
	}
}

void AlienGroup::BuildMatrix()
{
	BuildMatrixPerType(AlienType::Octopus);
	BuildMatrixPerType(AlienType::Crab);
	BuildMatrixPerType(AlienType::Squid);
}

void AlienGroup::BuildMatrixPerType(AlienType Type)
{
	const int AlienToSpawn = NumRowsPerType * NumAlienPerRow;
	for (int i = 0; i < AlienToSpawn; ++i)
	{
		Alien::SharedPtr NewAlien = std::make_shared<Alien>(Type);
		NewAlien->SetConfig(ConfigTypeMapping[Type]);
		NewAlien->SetShader(Assets::Shaders::ShapeName);
		NewAlien->SetProjectilePool(ProjectilePoolPtr);

		AllAliens.push_back(NewAlien);
	}
}

bool AlienGroup::ReachedEnd() const
{
	const Scene::SharedPtr CurrentScene = GetScene();
	if (CurrentScene == nullptr)
	{
		return false;
	}

	const float Width = static_cast<float>(CurrentScene->GetScreenWidth());
	const Alien::SharedPtr LeftAlien = AllAliens[OuterLeftCol];
	const Alien::SharedPtr RightAlien = AllAliens[OuterRightCol];
	const glm::vec3 LeftLocation = LeftAlien->GetLocation();
	const glm::vec3 RightLocation = RightAlien->GetLocation();

	if (!bRightDirection && LeftLocation.x - HorizontalMoveStep - (AlienSize.x) <= 0.f)
	{
		return true;
	}

	if (bRightDirection && RightLocation.x + HorizontalMoveStep + (AlienSize.x) >= Width)
	{
		return true;
	}

	return false;
}

bool AlienGroup::ReachedPlayer() const
{
	const Scene::SharedPtr CurrentScene = GetScene();
	if (CurrentScene == nullptr)
	{
		return false;
	}

	const float Height = static_cast<float>(CurrentScene->GetScreenHeight());
	const Alien::SharedPtr LastAlien = AllAliens[LastRow * NumAlienPerRow];
	if (LastAlien == nullptr)
	{
		return false;
	}

	const glm::vec3 LastLocation = LastAlien->GetLocation();
	if ((LastLocation.y + AlienSize.y) >= Height)
	{
		return true;
	}

	return false;
}

void AlienGroup::UpdateOuterColsAndRow()
{
	const int RowCount = GetNumRowsTotal();

	OuterLeftCol = NumAlienPerRow - 1;
	OuterRightCol = 0;

	for (int j = 0; j < NumAlienPerRow; ++j)
	{
		for (int i = 0; i < RowCount; ++i)
		{
			const int LeftCalcIndex = i * NumAlienPerRow + j;
			if (!AllAliens[LeftCalcIndex]->IsDestroyed() && j < OuterLeftCol)
			{
				OuterLeftCol = j;
			}

			const int RightIndex = (NumAlienPerRow - j - 1);
			const int RightCalcIndex = i * NumAlienPerRow + (RightIndex);
			if (!AllAliens[RightCalcIndex]->IsDestroyed() && RightIndex > OuterRightCol)
			{
				OuterRightCol = RightIndex;
			}

			if (!AllAliens[LeftCalcIndex]->IsDestroyed() && i >= LastRow)
			{
				LastRow = i;
			}
		}
	}
}

void AlienGroup::MoveAliens(const float Delta)
{
	glm::vec3 MoveOffset(0.f);
	if (bGoDown)
	{
		MoveOffset.y = VerticalMoveStep;
		bGoDown = false;
	}
	else if (bRightDirection)
	{
		MoveOffset.x = HorizontalMoveStep;
	}
	else
	{
		MoveOffset.x = -HorizontalMoveStep;
	}

	for (const Alien::SharedPtr& Alien : AllAliens)
	{
		const glm::vec3 NewLocation = Alien->GetLocation() + MoveOffset;
		Alien->SetLocation(NewLocation);
	}

	if (ReachedEnd())
	{
		bRightDirection = !bRightDirection;
		bGoDown = true;
	}
}

void AlienGroup::GenerateShootCooldown()
{
	SelectedShootCooldown = Random::Get(ShootMinCooldown, ShootMaxCooldown);
}

void AlienGroup::Shoot() const
{
	const int AliveCount = static_cast<int>(AliveAliensIdx.size()) - 1;
	const int RandomAlienIndex = Random::Get(0, AliveCount);
	const int AliveAlien = AliveAliensIdx[RandomAlienIndex];

	AllAliens[AliveAlien]->Shoot();
}

void AlienGroup::UpdateShootCooldown(const float Delta)
{
	CurrentShootCooldown += Delta;
	if (CurrentShootCooldown >= SelectedShootCooldown)
	{
		Shoot();
		CurrentShootCooldown = 0.f;
		GenerateShootCooldown();
	}
}

void AlienGroup::UpdateMoveDelay(const float Delta)
{
	CurrentDelay += Delta;
	if (CurrentDelay >= MoveDelay)
	{
		UpdateOuterColsAndRow();
		MoveAliens(Delta);
		CurrentDelay = 0.f;
	}
}

void AlienGroup::UpdateAliveAliens()
{
	AliveAliensIdx.erase(
		std::remove_if(AliveAliensIdx.begin(), AliveAliensIdx.end(), [this](int Index) { return AllAliens[Index]->IsDestroyed(); }),
		AliveAliensIdx.end()
	);

	if (AliveAliensIdx.empty())
	{
		State = GroupState::Stopped;
;		NotifyDefeat();
	}
}

void AlienGroup::NotifyReachedPlayer() const
{
	for (const OnReachedPlayerDelegate& Function : OnReachedPlayerFunctions)
	{
		Function();
	}
}

void AlienGroup::NotifyDefeat() const
{
	for (const OnDefeatDelegate& Function : OnDefeatFunctions)
	{
		Function();
	}
}

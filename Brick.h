#pragma once

#include "TeamComponent.h"
#include "pk/Actor.h"
#include "pk/IDamageable.h"

class Brick : public Actor, public IDamageable
{
public:
	typedef std::shared_ptr<Brick> SharedPtr;

	Brick();

	bool TakeDamage(float InDamage) override;

	~Brick() override = default;

private:
	TeamComponent::SharedPtr TeamPtr;
};

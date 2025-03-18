#include "Actor.h"

#include <glm/gtc/matrix_transform.hpp>

#include "AssetManager.h"
#include "Renderer.h"
#include "Scene.h"

Actor::Actor()
	: InitialLifeSpan(0.f), LifeSpan(0.f), Velocity(0.f), Color(Colors::Black), bPendingDestroy() {}

Actor::Actor(const ::Transform& InTransform)
	:Actor()
{
	mTransform = InTransform;
}

Actor::Actor(const glm::vec3& InLocation, const glm::vec3 InSize)
	: Actor(Transform(InLocation, InSize))
{
}

void Actor::SetScene(const Scene::WeakPtr& InScene)
{
	ScenePtr = InScene;
}

Scene::SharedPtr Actor::GetScene() const
{
	return ScenePtr.lock();
}

void Actor::SetShader(const std::string& InShader)
{
	ShaderName = InShader;
}

std::string Actor::GetShader() const
{
	return ShaderName;
}

void Actor::SetTexture(const std::string& InTexture)
{
	TextureName = InTexture;
}

std::string Actor::GetTexture() const
{
	return TextureName;
}

Transform Actor::GetTransform() const
{
	return mTransform;
}

void Actor::SetLocation(const glm::vec3& InLocation)
{
	mTransform.Location = InLocation;
}

glm::vec3 Actor::GetLocation() const
{
	return mTransform.Location;
}

void Actor::SetSize(const glm::vec3& InSize)
{
	mTransform.Size = InSize;
}

glm::vec3 Actor::GetSize() const
{
	return mTransform.Size;
}

void Actor::SetVelocity(const glm::vec3& InVelocity)
{
	Velocity = InVelocity;
}

glm::vec3 Actor::GetVelocity() const
{
	return Velocity;
}

void Actor::SetColor(const glm::vec4& InColor)
{
	Color = InColor;
}

glm::vec4 Actor::GetColor() const
{
	return Color;
}

float Actor::GetInitialLifeSpan() const
{
	return InitialLifeSpan;
}

void Actor::SetInitialLifeSpan(float InLifeSpan)
{
	InitialLifeSpan = std::max(0.f, InLifeSpan);
}

float Actor::GetLifeSpan() const
{
	return LifeSpan;
}

void Actor::SetConfig(const std::string& InConfigFile)
{
	ConfigFile = InConfigFile;
}

std::string Actor::GetConfigFile() const
{
	return ConfigFile;
}

void Actor::Move(const float Delta)
{
	mTransform.Location += Velocity * Delta;
}

void Actor::UpdateLifeSpan(const float Delta)
{
	if (InitialLifeSpan <= 0.f)
	{
		return;
	}

	LifeSpan += Delta;
	if (LifeSpan >= InitialLifeSpan)
	{
		Destroy();
	}
}


glm::mat4 Actor::GetRenderModel() const
{
	const glm::mat4 Identity(1.f);
	glm::mat4 RenderModel = glm::translate(Identity, mTransform.Location);
	RenderModel = glm::scale(RenderModel, mTransform.Size);

	return RenderModel;
}

BoundingBox Actor::GetBoundingBox() const
{
	BoundingBox Box(mTransform);
	return Box;
}

void Actor::BindTexture() const
{
	const Texture::SharedPtr Texture = AssetManager::Get().GetTexture(TextureName);
	if (Texture != nullptr)
	{
		Texture->Bind();
	}
}

void Actor::UnBindTexture() const
{
	const Texture::SharedPtr Texture = AssetManager::Get().GetTexture(TextureName);
	if (Texture != nullptr)
	{
		Texture->UnBind();
	}
}

bool Actor::Collide(const Actor& Other) const
{
	const BoundingBox Me(GetBoundingBox());
	const BoundingBox OtherBox(Other.GetBoundingBox());

	bool bCollidedX = (Me.Right() >= OtherBox.Left()  && OtherBox.Right() >= Me.Left());
	bool bCollidedY = (Me.Bottom() <= OtherBox.Top()  && OtherBox.Bottom() <= Me.Top());

	return bCollidedX && bCollidedY;
}

void Actor::LoadConfig()
{
}

void Actor::Begin()
{
	LoadConfig();
}

void Actor::Update(const float Delta)
{
	Move(Delta);
	UpdateLifeSpan(Delta);
}

void Actor::Input(const Window& Window, const float Delta)
{
}

void Actor::Render() const
{
	const Shader::SharedPtr Shader = AssetManager::Get().GetShader(ShaderName);
	const Texture::SharedPtr Texture = AssetManager::Get().GetTexture(TextureName);

	Renderer::Get().RenderSprite(
		Shader,
		Texture,
		GetRenderModel(),
		Color
	);
}

bool Actor::IsDestroyed() const
{
	return bPendingDestroy;
}

void Actor::Destroy()
{
	bPendingDestroy = true;
}

void Actor::CancelDestroy()
{
	bPendingDestroy = false;
}

bool Actor::IsInViewport() const
{
	const SceneSharedPtr CurrentScene = GetScene();
	if (CurrentScene == nullptr)
	{
		return false;
	}

	const Window::SharedPtr CurrentWindow = CurrentScene->GetWindow();
	if (CurrentWindow == nullptr)
	{
		return false;
	}

	const glm::vec3 Location = GetLocation();
	const glm::vec2 SizeOffset = GetBoundingBox().ScaleOffset;
	const float WindowWidth = static_cast<float>(CurrentWindow->GetWidth());
	const float WindowHeight = static_cast<float>(CurrentWindow->GetHeight());

	if (Location.x + SizeOffset.x <= 0.f 
		|| Location.x - SizeOffset.x >= WindowWidth)
	{
		return false;
	}

	if (Location.y + SizeOffset.y <= 0.f || 
		Location.y - SizeOffset.y >= WindowHeight)
	{
		return false;
	}

	return true;
}

#pragma once
#include "pk/Widget.h"

class Game;
class GameSave;

class MainMenu : public Widget
{
public:
	typedef std::shared_ptr<MainMenu> SharedPtr;
	typedef std::weak_ptr<Game> GameWeakPtr;
	typedef std::shared_ptr<Game> GameSharedPtr;

	MainMenu(const GameWeakPtr& InGame);

	void Input(const InputHandler& Handler, const float Delta) override;
	void Render() override;

private:
	GameSharedPtr GetGame() const;

	void OnChangeChoice() const;
	void HandleChoice();
	void StartGame();
	void ToggleMute() const;
	void QuitGame();

	void PlayNavSound() const;

	void RenderSelectArrows(const std::string& InText, const glm::vec2& OptionPos, const glm::vec2& OptionSize) const;

	int CurrentChoice;
	int MaxChoice;

	GameWeakPtr GamePtr;
};
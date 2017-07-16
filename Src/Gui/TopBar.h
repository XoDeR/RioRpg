#pragma once

#include <ctime>
#include <chrono>
#include <cstdlib>

#include "GuiWindow.h"

namespace RioGame
{
	class Game;

	// An info bar on the top of the screen displaying
	// the name of the game, player's gold, mana, units and the current time
	class TopBar : public GuiWindow
	{
	private:
		float timeSinceLastUpdate{ 0.0f };
		Game* game{nullptr};
	public:
		TopBar();
		~TopBar() = default;
		// Updates the current time on the top bar if a second passed since the last time update
		void updateTime(float timeSinceLastFrame);
		// Sets the given label's text to the given string
		void updateLabel(const std::string& labelToChange, const std::string& newText);
		void initWithGame(Game* game);
	protected:
		void init() override;
	};

} // namespace RioGame

#include "Tools/Player.h"
#include "TopBar.h"
#include "Game.h"
#include "ui/UIWidget.h"
#include "ui/UIText.h"

namespace RioGame
{

	void TopBar::updateTime(float delta)
	{
		using namespace RioEngine;

		this->timeSinceLastUpdate += delta;
		if (this->timeSinceLastUpdate > 1.0f)
		{
			this->timeSinceLastUpdate = 0.0f;
			time_t now = time(0);
			struct tm* tstruct = localtime(&now);
			char buf[80];
			std::strftime(buf, sizeof(buf), "%HH - %MM - %SS", tstruct);
			((ui::Text*)(this->window->getChildByName("FRAME/TIME")))->setText(buf);
		}
	}

	void TopBar::updateLabel(const std::string& label, const std::string& val)
	{
		using namespace RioEngine;

		((ui::Text*)(this->window->getChildByName("FRAME/" + label)))->setText(val);
	}

	void TopBar::init()
	{
		updateLabel("GOLD_VALUE", std::to_string(game->getPlayer()->getGold()));
		updateLabel("MANA_VALUE", std::to_string(game->getPlayer()->getMana()));
	}

	void TopBar::initWithGame(Game* game)
	{
		this->game = game;
	}

} // namespace RioGame
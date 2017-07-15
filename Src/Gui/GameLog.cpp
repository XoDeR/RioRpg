#include "GameLog.h"
#include "ui/UIWidget.h"
#include "ui/UIListView.h"
#include "ui/UIText.h"

namespace RioGame
{
	void GameLog::clear()
	{
		this->log->removeAllItems();
	}

	void GameLog::print(const std::string& msg)
	{
		using namespace RioEngine;

		ui::Text* text = nullptr;
		if (this->log->getItems().size() >= this->logHistory)
		{
			text = (ui::Text*)this->log->getItem(0);
			this->log->removeItem(0);
			text->setText(msg);
		}
		else
		{
			text = ui::Text::create(msg, "Arial", 22);
		}
		text->setTextColor(Color4B{ 0, 255, 0, 255 });
		this->log->addChild(text);
	}

	void GameLog::setHistory(uint32_t val)
	{
		this->logHistory = val;
	}

	uint32_t GameLog::getHistory() const
	{
		return this->logHistory;
	}

	void GameLog::init()
	{
		using namespace RioEngine;
		this->log = (ui::ListView*)this->window->getChildByName("FRAME/LOG");
	}

} // namespace RioGame
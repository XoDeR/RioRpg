#include "Console.h"

#include "ui/UIListView.h"
#include "ui/UIText.h"
#include "ui/UIButton.h"

namespace RioGame
{
	void ConsoleEditBoxDelegate::editBoxEditingDidBegin(RioEngine::ui::EditBox* editBox)
	{

	}
	void ConsoleEditBoxDelegate::editBoxEditingDidEnd(RioEngine::ui::EditBox* editBox)
	{
		console->handleText();
	}
	void ConsoleEditBoxDelegate::editBoxEditingDidEndWithAction(RioEngine::ui::EditBox* editBox, RioEngine::ui::EditBoxDelegate::EditBoxEndAction action)
	{

	}
	void ConsoleEditBoxDelegate::editBoxTextChanged(RioEngine::ui::EditBox* editBox, const std::string& text)
	{

	}
	void ConsoleEditBoxDelegate::editBoxReturn(RioEngine::ui::EditBox* editBox)
	{

	}

	using ::RioEngine::Color4B;

	void Console::init()
	{
		using namespace RioEngine;

		this->window->setVisible(false);

		this->consoleEditBoxDelegate = std::make_unique<ConsoleEditBoxDelegate>();
		this->consoleEditBoxDelegate->initWithConsole(this);

		// Registers event handlers
		((ui::EditBox*)(this->window->getChildByName("INPUT")))->setDelegate(this->consoleEditBoxDelegate.get());

		this->listView = (ui::ListView*)this->window->getChildByName("CONSOLE_LOG");
	}

	void Console::setIsVisible(bool visible)
	{
		using namespace RioEngine;

		this->window->setVisible(visible);
		if (visible)
		{
			((ui::EditBox*)(this->window->getChildByName("INPUT")))->setEnabled(true);
		}
	}

	bool Console::handleText()
	{
		using namespace RioEngine;

		std::string command = ((ui::EditBox*)(this->window->getChildByName("INPUT")))->getText();
		currentCommand += '\n' + command;
		printText(command);
		((ui::EditBox*)(this->window->getChildByName("INPUT")))->setText("");
		return true;
	}

	void Console::printText(const std::string& msg, Color4B col)
	{
		using namespace RioEngine;

		if (msg == "`") // Garbage value from toggling the console
			return;

		ui::Text* text;

		if (this->listView->getItems().size() >= this->consoleHistory)
		{ 
			// Little trick, reuse the oldest command entry
			text = (ui::Text*)this->listView->getItem(0);
			this->listView->removeItem(0);
			text->setText(msg + "\n");
		}
		else
		{
			text = ui::Text::create(msg + "\n", "Arial", 22);
		}
		text->setTextColor(col);
		this->listView->addChild(text);
		scrollDown();
	}

	void Console::scrollDown(uint32_t scrollsCount)
	{
		for (uint32_t i = 0; i < scrollsCount; ++i)
		{
			this->listView->jumpToPercentVertical(20);
		}
	}

	void Console::setHistory(uint32_t val)
	{
		this->consoleHistory = val;
	}

	uint32_t Console::getHistory() const
	{
		return this->consoleHistory;
	}

	void Console::clear()
	{
		this->listView->removeAllItems();
	}

} // namespace RioGame
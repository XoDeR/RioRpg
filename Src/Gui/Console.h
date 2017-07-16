#pragma once

#include <string>
#include <memory>
#include <cstdlib>

#include "GuiWindow.h"

#include "base/Types.h"
#include "ui/UIEditBox/UIEditBox.h"

namespace RioEngine
{
	class Color4F;

	namespace ui
	{
		class ListView;
	}
}

namespace RioGame
{
	// Aux, for edit box delegate
	class ConsoleEditBoxDelegate : public RioEngine::ui::EditBoxDelegate
	{
	private:
		Console* console{ nullptr };
	public:
		void initWithConsole(Console* console);
		virtual void editBoxEditingDidBegin(RioEngine::ui::EditBox* editBox) override;
		virtual void editBoxEditingDidEnd(RioEngine::ui::EditBox* editBox) override;
		virtual void editBoxEditingDidEndWithAction(RioEngine::ui::EditBox* editBox, RioEngine::ui::EditBoxDelegate::EditBoxEndAction action) override;
		virtual void editBoxTextChanged(RioEngine::ui::EditBox* editBox, const std::string& text) override;
		virtual void editBoxReturn(RioEngine::ui::EditBox* editBox) override;
	};

	class Console : public GuiWindow
	{
	private:
		// Pointer to the ListBox widget that serves as console output
		::RioEngine::ui::ListView* listView{ nullptr };
		// String containing the current command, allows to append more statements
		// to it until the EXECUTE button is pressed, which allows for multi-line code
		std::string currentCommand;
		// Limits the number of console entries that will be shown in it's history
		uint32_t consoleHistory{ 60 };

		std::unique_ptr<ConsoleEditBoxDelegate> consoleEditBoxDelegate;
	public:
		// Changes the visibility and text capturing of the console window
		void setIsVisible(bool) override;
		// Event handler that is called whenever a text is entered
		bool handleText();
		// Prints a given message into the console window
		void printText(const std::string& message, ::RioEngine::Color4B color = ::RioEngine::Color4B::WHITE);
		// Scrolls the console output down one line, used so that messages from the outside can scroll all the way down to the last line of the output
		void scrollDown(uint32_t amountOfLinesToScroll = 1);
		// Sets the number of entries that will be shown in the console's history
		void setHistory(uint32_t newEntryCount);
		// Returns the number of entries that will be shown in the console's history
		uint32_t getHistory() const;
		// Clears the console log
		void clear();
	protected:
		// Initializes the console and subscribes it to events
		void init() override;
	};

	

} // namespace RioGame
#pragma once

#include <cstdint>
#include <string>
#include <cstdlib>

#include "GuiWindow.h"

namespace RioEngine
{
	namespace ui
	{
		class ListView;
	}
}

namespace RioGame
{
	// Class representing the log window used to show messages to the player
	// (No space for gold, enemies attacking etc.)
	class GameLog : public GuiWindow
	{
	private:
		// Number of entires kept in the game log
		uint32_t logHistory{60};
		// Pointer to the log window for easy access (as it might get called quite often, this will avoid frequent lookups)
		::RioEngine::ui::ListView* log{nullptr};
	public:
		GameLog();
		~GameLog() = default;
		// Clears the game's log by deleting all it's entries
		void clear();
		// Prints a string to the game's log
		void print(const std::string&);
		// Sets the amount of entries kept in the game's log
		// The new log history.
		void setHistory(uint32_t);
		// Returns the amoung of entries kept in the game's log
		uint32_t getHistory() const;
	protected:
		// Initializes the game log (called by parent's init)
		void init() override;
	};
} // namespace RioGame
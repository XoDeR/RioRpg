// Copyright (c) 2012-2017 Volodymyr Syvochka
#pragma once

#include <vector>
#include <string>

#include "GuiWindow.h"

namespace RioGame
{
	class Spellcaster;

	// Class representing the spell selection window, allows the player to cast registered (unlocked) spells
	class SpellCastingWindow : public GuiWindow
	{
	private:
		// Names of all registered spells
		std::vector<std::string> spellNameList;
		// Number of the current rightmost selection
		// The window shows buildings with indices <selectionNumber - 3, selectionNumber>
		uint32_t selectionNumber = 3;
		// Does the actual spell casting once a spell is selected in this window
		Spellcaster* spellcaster = nullptr;
		// Keeps track of the spell that is being currently casted
		int currentActiveSpell = -1;
	public:
		// Appends a table name to the vector of all spell tables
		void registerSpell(const std::string& spellName);
		// Sets the caster instance used to cast the spells
		void setCaster(Spellcaster* newSpellCaster);
		// Hides the "active" label
		void deactivateCurrentSpell();
		// Returns a vector containing the names of all unlocked spells (Used for serialization)
		const std::vector<std::string>& getSpells() const;
		// Removes all unlocked spell
		void clearSpells();
		// Decrements selectionNumber by one and updates the window
		bool decreaseSelection();
		// Increments selectionNumber by one and updates the window
		bool increaseSelection();
		// Marks a given spell as active
		// Position of the spell in the current view (0-3)
		void setSpellActive(int);
		// Casts a spell at a given position
		// The position of the spell (1-4)
		void cast(int);
	protected:
		// Initializes the window and subscribes events
		void init() override;
	private:
		// Range checked this->buildingNameList index access, returns the name
		// of the building at a given index or "UNKNOWN" if the index is out of bounds
		// Index of the building in the buildings vector
		const std::string& getSpell(uint32_t);
		// Updates building names on the buttons
		void updateSelection();
	};

} // namespace RioGame
// Copyright (c) 2012-2017 Volodymyr Syvochka
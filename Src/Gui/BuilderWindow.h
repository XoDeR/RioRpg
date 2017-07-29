#pragma once

#include <vector>
#include <string>

#include "GuiWindow.h"

namespace RioGame
{

	class EntityPlacer;

	// Class representing the building selection window, allows the player to place registered (unlocked) buildings
	class BuilderWindow : public GuiWindow
	{
	private:
		// Names of all registered buildings
		std::vector<std::string> buildingNameList;
		// Number of the current rightmost selection
		// The window shows buildings with indices <selectionNumber - 3, selectionNumber>
		uint32_t selectionNumber = 3;
		EntityPlacer* entityPlacer = nullptr;
	public:
		BuilderWindow();
		~BuilderWindow() = default;
		// Appends a table name to the vector of all building tables
		void registerBuilding(const std::string& name);
		// Sets the placer that is used to build
		void setPlacer(EntityPlacer* newEntityPlacer);
		// Returns a vector containing all the names of the registered buildings (Used for serialization)
		const std::vector<std::string>& getBuildings() const;
		// Removes all unlocked buildings
		void clearBuildings();
		// Places the building on a given position
		// The button position (1-4)
		void build(int);
		// Decrements selection_number_ by one and updates the window
		void decreaseSelection();
		// Increments selection_number_ by one and updates the window
		void increaseSelection();
	protected:
		// Initializes the window and subscribes events
		void init() override;
	private:
		// Range checked buildings index access, returns the name
		// of the building at a given index or "UNKNOWN" if the index is out of bounds
		// Index of the building in the this->buildingNameList vector
		const std::string& getBuilding(uint32_t);
		// Updates building names on the buttons
		void updateSelection();
	};

} // namespace RioGame
// Copyright (c) 2012-2017 Volodymyr Syvochka
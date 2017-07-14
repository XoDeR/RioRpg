// Copyright (c) 2012-2017 Volodymyr Syvochka
#pragma once

#include <vector>
#include <string>
#include <cstdlib>

#define CACHE_ALLOWED 1

namespace RioGame
{
	class EntityManager;
	class Game;

	class Player
	{
	private:
		uint32_t gold = 2000;
		uint32_t mana_ = 200;
		uint32_t maxMana = 1000;
		// Amount of mana that is added to the player's mana pool on every regen tick
		uint32_t manaRegen = 1;
		// Amount of currently alive units
		uint32_t currentlyAliveUnitCount = 0;
		// Amount of all units (even those that are respawning)
		uint32_t maxUnitCount = 0;
		EntityManager* entityManager = nullptr;
		Game* game = nullptr;
		// Holds the names of the spells that are available to the player from the beggining
		std::vector<std::string> initialSpellUnlocks;
		// Holds the names of the buildings that are available to the player from the beggining
		std::vector<std::string> initialBuildingUnlocks;
	public:
		void init(Game* game, EntityManager* entityManager);
		// Adds gold to the player's gold stash
		void addGold(uint32_t amountToAdd);
		// Removes gold from the player's gold stash if possible
		// returns true if the player has enough, false otherwise
		bool subtractGold(uint32_t amountToRemove);
		// Adds mana to the player's mana pool
		void addMana(uint32_t amountToAdd);
		// Removes mana from the player's mana pool if possible,
		// returns true if the player has enough, false otherwise.
		bool subtractMana(uint32_t amountToRemove);
		// Increases the mana capacity of the player by a given amount
		void addMaxMana(uint32_t amountToAdd);
		// Decreases the mana capacity of the player by a given amount if possible
		// Returns true if the player has enough, false otherwise
		bool subtractMaxMana(uint32_t amountToDecreaseBy);
		// Increases the player's mana regeneration by a given amount
		void addManaRegen(uint32_t amountToIncreaseBy);
		// Decreases the player's mana regeneration by a given amount
		// if possible. Returns true if the player has enough, false otherwise
		bool subtractManaRegen(uint32_t amountToDecreaseBy);
		// Adds max units to the player's unit amount
		void addMaxUnit(uint32_t amountToAdd);
		// Removes max units from the player's unit amount if possible
		// returns true if the player has enough, false otherwise.
		bool subtractMaxUnit(uint32_t amountToRemove);
		// Adds current units to the player's unit amount
		void addCurrentUnit(uint32_t amountToAdd);
		// Removes current units from the player's unit amount if possible
		// returns true if the player has enough, false otherwise
		bool subtractCurrentUnit(uint32_t amountToRemove);
		// Returns the amount of gold the player currently has
		uint32_t getGold() const;
		// Returns the amount of mana the player currently has
		uint32_t getMana() const;
		// Returns the mana capacity of the player
		uint32_t getMaxMana() const;
		// Returns the value of the player's mana regeneration
		uint32_t getManaRegen() const;
		// Sets all of the player's stats to their default values
		void reset();
		// Sets all of the player's stats to zero (used for loading)
		void nulifyAllStats();
		
		// Sets the spells and buildings that are unlocked from the start
		void setInitialUnlocks(const std::vector<std::string>& initialSpellUnlocks, const std::vector<std::string>& initialBuildingUnlocks);
		// Returns a vector of all spells that are unlocked at the start of a new game
		const std::vector<std::string>& getInitialSpells() const;
		// Returns a vector of all buildings that are unlocked at the start of a new game
		const std::vector<std::string>& getInitialBuildings() const;
	
	};

} // namespace RioGame
// Copyright (c) 2012-2017 Volodymyr Syvochka
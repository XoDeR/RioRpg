// Copyright (c) 2012-2017 Volodymyr Syvochka
#pragma once

#include <memory>
#include <vector>

#include "Enums.h"
#include "Typedefs.h"
#include "Components.h"

#include "Gui/OptionsWindow.h"

#include "math/Vec2.h"
#include "math/Vec3.h"

#include "base/EventKeyboard.h"
#include "base/EventMouse.h"

namespace RioGame
{

	using ::RioEngine::Vec2;
	using ::RioEngine::Vec3;
	using ::RioEngine::EventKeyboard;
	using ::RioEngine::EventMouse;

	using ::std::unique_ptr;

	namespace LevelGenerators
	{
		class LevelGenerator;
	}

	class Player;
	class Gui;
	class Camera;
	class Spellcaster;
	class SelectionBox;
	class GameSerializer;
	class EntityPlacer;
	class EntityCreator;
	class LevelGenerator;
	class EntityManager;
	class World;

	class Game
	{
	private:
		friend class GameSerializer;
		friend class Gui;
		friend class NewGameDialog;

		friend void Action::quickLoad();
		friend void Action::quickSave();
		friend void Action::resetCamera();

	private:
		GameState state_ = GameState::INTRO_MENU;
		EntityManager* entityManager{ nullptr };
		unique_ptr<Camera> mainCamera;
		unique_ptr<GameSerializer> gameSerializer{ nullptr };
		unique_ptr<EntityPlacer> entityPlacer;
		uint32_t groundEntity;

		unique_ptr<SelectionBox> selectionBox;
		unique_ptr<EntityCreator> entityCreator;

		Vec2 mousePosition;
		unique_ptr<LevelGenerators::LevelGenerator> levelGenerator;
		std::unique_ptr<Spellcaster> spellCaster;
		// ID of the entity representing the Castle, losing which ends the game
		uint32_t castleId = Component::NO_ENTITY;

		unique_ptr<Player> player;
		unique_ptr<Gui> gui;
		unique_ptr<World> world;
	public:
		Game();
		~Game();
		// Starts the game
		void run();
		void update(float);
		void setState(GameState);
		// Creates a new game with the given dimensions
		void createNewGame(uint32_t width, uint32_t height);
		// Creates an empty level with the given dimensions
		void createEmptyLevel(uint32_t width, uint32_t height);
		// Resets the main camera's position to it's original state
		void resetCamera();
		// Restores the unlocks to their initial state
		void resetUnlocks();
		void setCastleId(uint32_t);
		uint32_t getCastleId() const;

		World* getWorld();
		Player* getPlayer();
		Gui* getGui();
		// Ends the game and shows the "YOU WON" message
		void win();
		// Ends the game and shows the "YOU LOST" message
		void lose();
	protected:

		// Global input callbacks
		bool keyPressed(const EventKeyboard::KeyCode&);
		bool keyReleased(const EventKeyboard::KeyCode&);
		bool mouseMoved(const EventMouse::MouseEventType&);
		bool mousePressed(const EventMouse::MouseEventType&, EventMouse::MouseButton);
		bool mouseReleased(const EventMouse::MouseEventType&, EventMouse::MouseButton);

	private:
		// Toggles the free camera movement mode
		void toggleCameraFreeMode();
		// Returns a pair consisting of the location of the point where the player
		// clicked on the ground plane and a boolean indicating if the click was indeed on the ground plane
		std::pair<bool, Vec2> getMouseClickPosition(const EventMouse::MouseEventType&) const;
	};

} // namespace RioGame
// Copyright (c) 2012-2017 Volodymyr Syvochka
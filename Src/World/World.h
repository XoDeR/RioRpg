// Copyright (c) 2012-2016 Volodymyr Syvochka
#pragma once
#include "Common.h"
#include "EntityManager.h"

namespace RioGame
{

	class AiSystem; // processing
	class AnimationSystem; // processing
	class CombatSystem;
	class InputSystem; // event based
	class MovementSystem; // processing

	class HealthSystem;
	class GridSystem;
	class TaskSystem;
	class ProductionSystem;
	class TimeSystem;
	class EventSystem;
	class GraphicsSystem;
	class TriggerSystem;
	class ManaSpellSystem;
	class WaveSystem;

	class Game;

	class World
	{
	public:
		World();
		World& operator=(const World& rhs) = delete;
		World(const World& rhs) = delete;
		World(World&& rhs);
		World& operator=(World&& rhs);
		~World();

		void init(Game* game);
		void initSystems();

		float getDelta();
		void setDelta(float delta);
		void process();
		EntityManager& getEntityManager();

		AiSystem& getAiSystem();
		AnimationSystem& getAnimationSystem();
		CombatSystem& getCombatSystem();
		EventSystem& getEventSystem();
		GridSystem& getGridSystem();
		InputSystem& getInputSystem();
		ManaSpellSystem& getManaSpellSystem();
		MovementSystem& getMovementSystem();

		ProductionSystem& getProductionSystem();
		TimeSystem& getTimeSystem();
		TriggerSystem& getTriggerSystem();

		WaveSystem& getWaveSystem();

		Game& getGame();
	private:
		Game* game = nullptr;

		// main manager
		EntityManager entityManager;

		// update interval
		float delta = 0.0f;

		// systems
		unique_ptr<HealthSystem> healthSystem;
		unique_ptr<MovementSystem> movementSystem;
		unique_ptr<AiSystem> aiSystem;
		unique_ptr<InputSystem> inputSystem;
		unique_ptr<GridSystem> gridSystem;
		unique_ptr<TaskSystem> taskSystem;
		unique_ptr<CombatSystem> combatSystem;
		unique_ptr<ProductionSystem> productionSystem;
		unique_ptr<TimeSystem> timeSystem;
		unique_ptr<EventSystem> eventSystem;
		unique_ptr<GraphicsSystem> graphicsSystem;
		unique_ptr<TriggerSystem> triggerSystem;
		unique_ptr<ManaSpellSystem> manaSpellSystem;
		unique_ptr<WaveSystem> waveSystem;
		unique_ptr<AnimationSystem> animationSystem;
	};

} // namespace RioGame
// Copyright (c) 2012-2016 Volodymyr Syvochka
// Copyright (c) 2012-2016 Volodymyr Syvochka
#include "World.h"

#include "base/Macros.h" // for RioAssert

#include "Game.h"

#include "Systems/HealthSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/AiSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/GridSystem.h"
#include "Systems/TaskSystem.h"
#include "Systems/CombatSystem.h"
#include "Systems/ProductionSystem.h"
#include "Systems/TimeSystem.h"
#include "Systems/EventSystem.h"
#include "Systems/GraphicsSystem.h"
#include "Systems/TriggerSystem.h"
#include "Systems/ManaSpellSystem.h"
#include "Systems/WaveSystem.h"
#include "Systems/AnimationSystem.h"

namespace RioGame
{

	World::World()
	{

	}

	World::World(World&& rhs)
		: entityManager(std::move(rhs.entityManager))
		, delta(rhs.delta)
		, aiSystem(std::move(rhs.aiSystem))
		, animationSystem(std::move(rhs.animationSystem))
		, combatSystem(std::move(rhs.combatSystem))
		, inputSystem(std::move(rhs.inputSystem))
		, movementSystem(std::move(rhs.movementSystem))
	{

	}

	World& World::operator=(World&& rhs)
	{
#define DISABLE_TEMPORARILY 0
#if DISABLE_TEMPORARILY
		entityManager = std::move(rhs.entityManager);
		delta = rhs.delta;
		aiSystem = std::move(rhs.aiSystem);
		animationSystem = std::move(rhs.animationSystem);
		combatSystem = std::move(rhs.combatSystem);
		inputSystem = std::move(rhs.inputSystem);
		movementSystem = std::move(rhs.movementSystem);
#endif DISABLE_TEMPORARILY
		return *this;
	}

	World::~World()
	{

	}

	void World::initSystems()
	{
#define DISABLE_TEMPORARILY 0
#if DISABLE_TEMPORARILY
		entityManager.reset(new EntitySystem{});

		healthSystem.reset(new HealthSystem{ *this });
		movementSystem.reset(new MovementSystem{ *this });
		inputSystem.reset(new InputSystem{ *this, *game->keyboard, *(game->mainCamera->camera) });
		//inputSystem->init();
		gridSystem.reset(new GridSystem{ *this, *entityManager });
		combatSystem.reset(new CombatSystem{ *this, *entityManager, *gridSystem });
		eventSystem.reset(new EventSystem{ *this });
		taskSystem.reset(new TaskSystem{ *this, *gridSystem, *combatSystem });
		productionSystem.reset(new ProductionSystem{ *this });
		timeSystem.reset(new TimeSystem{ *this });
		aiSystem.reset(new AiSystem{ *this });
		graphicsSystem.reset(new GraphicsSystem{ *this });
		triggerSystem.reset(new TriggerSystem{ *this });
		manaSpellSystem.reset(new ManaSpellSystem{ *this });
		waveSystem.reset(new WaveSystem{ *this });
		animationSystem.reset(new AnimationSystem{ *this });
#endif DISABLE_TEMPORARILY
	}

	void World::init(Game* game)
	{
		this->game = game;
	}

	Game& World::getGame()
	{
		RioAssert(game != nullptr, "game == nullptr");
		return *game;
	}

	float World::getDelta()
	{
		return this->delta;
	}

	void World::setDelta(float delta)
	{
		this->delta = delta;
	}

	void World::process()
	{
		inputSystem->process();
		aiSystem->process();
		animationSystem->process();
		movementSystem->process();

		// after processing all systems
		entityManager.removeEntitiesScheduledToRemove();

		entityManager.process();
	}

	EntityManager& World::getEntityManager()
	{
		return entityManager;
	}

	AiSystem& World::getAiSystem()
	{
		RioAssert(aiSystem != nullptr, "aiSystem == nullptr");
		return *aiSystem.get();
	}

	AnimationSystem& World::getAnimationSystem()
	{
		RioAssert(animationSystem != nullptr, "animationSystem == nullptr");
		return *animationSystem.get();
	}

	CombatSystem& World::getCombatSystem()
	{
		RioAssert(combatSystem != nullptr, "combatSystem == nullptr");
		return *combatSystem.get();
	}

	MovementSystem& World::getMovementSystem()
	{
		RioAssert(movementSystem != nullptr, "movementSystem == nullptr");
		return *movementSystem.get();
	}

	ProductionSystem& World::getProductionSystem()
	{
		RioAssert(productionSystem != nullptr, "productionSystem == nullptr");
		return *productionSystem.get();
	}

	TimeSystem& World::getTimeSystem()
	{
		RioAssert(timeSystem != nullptr, "timeSystem == nullptr");
		return *timeSystem.get();
	}

	GridSystem& World::getGridSystem()
	{
		RioAssert(gridSystem != nullptr, "gridSystem == nullptr");
		return *gridSystem.get();
	}

	WaveSystem& World::getWaveSystem()
	{
		RioAssert(waveSystem != nullptr, "waveSystem == nullptr");
		return *waveSystem.get();
	}

	EventSystem& World::getEventSystem()
	{
		RioAssert(eventSystem != nullptr, "eventSystem == nullptr");
		return *eventSystem.get();
	}

	ManaSpellSystem& World::getManaSpellSystem()
	{
		RioAssert(manaSpellSystem != nullptr, "manaSpellSystem == nullptr");
		return *manaSpellSystem.get();
	}

	TriggerSystem& World::getTriggerSystem()
	{
		RioAssert(triggerSystem != nullptr, "triggerSystem == nullptr");
		return *triggerSystem.get();
	}

} // namespace RioGame
// Copyright (c) 2012-2016 Volodymyr Syvochka
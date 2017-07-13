// Copyright (c) 2012-2017 Volodymyr Syvochka
#pragma once

#include <string>
#include <array>
#include <deque>
#include <bitset>
#include <memory>
#include <numeric>
#include <utility>
#include <map>
#include <functional>

#include <cstdlib>

#define CACHE_ALLOWED 1

#include "Enums.h"

#include "math/Vec2.h"
#include "math/Vec3.h"

#include "2d/CCNode.h"

namespace RioGame
{

	using ::RioEngine::Vec2;
	using ::RioEngine::Vec3;

	using ::RioEngine::Node;

	struct Component
	{
		static constexpr int count = 44;
		static constexpr uint32_t NO_ENTITY = std::numeric_limits<uint32_t>::max();
	};

	// To be able to manually create components without blueprints,
	// all components must have either default constructors or constructors with default values for all parameters
	// to be able to back components up, they need to provide a copy constructor
	
	// Allows an entity to be in two states -- activated and deactivated -- and
	// the player to switch between the two states of an entity using a button in the entity viewer
	struct ActivationComponent
	{
		static constexpr int type = 0;

		std::map<std::string, std::function<void()>> blueprint;
		bool activated = false;

		ActivationComponent(std::map<std::string, std::function<void()>>&& blueprint, bool a = false)
			: blueprint{ std::move(blueprint) }
			, activated{ a }
		{
		}
		ActivationComponent(const ActivationComponent&) = default;
		ActivationComponent(ActivationComponent&&) = default;
		ActivationComponent& operator=(const ActivationComponent&) = default;
		ActivationComponent& operator=(ActivationComponent&&) = default;
		~ActivationComponent() = default;
	};

	struct AiComponent
	{
		static constexpr int type = 1;

		std::map<std::string, std::function<void()>> blueprint;
		EntityState::ENUM state;

		AiComponent(std::map<std::string, std::function<void()>>&& blueprint, EntityState::ENUM entityState = EntityState::NORMAL)
			: blueprint{ std::move(blueprint) }
			, state{ entityState }
		{
		}
		AiComponent(const AiComponent&) = default;
		AiComponent(AiComponent&&) = default;
		AiComponent& operator=(const AiComponent&) = default;
		AiComponent& operator=(AiComponent&&) = default;
		~AiComponent() = default;
	};

	// Align states: scale, sprite, etc for the different alignments of blocks (e.g. walls)
	struct AlignComponent
	{
		static constexpr int type = 2;
		static constexpr int stateCount = 6;

		struct AlignState
		{
			Vec2 scale;
			Vec2 positionOffset;
			std::string sprite;
		};

		std::array<AlignState, stateCount> states;

		AlignComponent() = default;
		AlignComponent(const AlignComponent&) = default;
		AlignComponent(AlignComponent&&) = default;
		AlignComponent& operator=(const AlignComponent&) = default;
		AlignComponent& operator=(AlignComponent&&) = default;
		~AlignComponent() = default;
	};

	struct AnimationState
	{
		// Dummy
	};

	struct AnimationComponent
	{
		static constexpr int type = 3;

		AnimationState* currentAnimation = nullptr;
		std::bitset<AnimationType::COUNT> possibleAnimationList;
		bool stopCurrentAnimation = true;

		AnimationComponent() = default;
		AnimationComponent(const AnimationComponent&) = default;
		AnimationComponent(AnimationComponent&&) = default;
		AnimationComponent& operator=(const AnimationComponent&) = default;
		AnimationComponent& operator=(AnimationComponent&&) = default;
		~AnimationComponent() = default;
	};

	// Entity's attack types and damage
	struct CombatComponent
	{
		static constexpr int type = 4;

		uint32_t currentTarget;
		uint32_t minDamage;
		uint32_t maxDamage;
		float cooldownTime;
		float cooldown;
		float range;
		AttackType attackType;
		bool pursue;
		std::string projectileBlueprint;

		CombatComponent(uint32_t target = Component::NO_ENTITY
			, uint32_t mi = 0
			, uint32_t ma = 0
			, float cd = 0.0f
			, float r = 0.0f
			, int type = 0
			, bool p = false
			, std::string&& proj = "ERROR"
		)
			: currentTarget{ target }
			, minDamage{ mi }
			, maxDamage{ ma }
			, cooldown{ cd }
			, cooldownTime{ cd }
			, range{ r }
			, attackType((AttackType)type)
			, pursue{ p }
			, projectileBlueprint{ std::move(proj) }
		{
		}
		CombatComponent(const CombatComponent&) = default;
		CombatComponent(CombatComponent&&) = default;
		CombatComponent& operator=(const CombatComponent&) = default;
		CombatComponent& operator=(CombatComponent&&) = default;
		~CombatComponent() = default;
	};

	// Contains a list of commands an entity can respond to
	struct CommandComponent
	{
		static constexpr int type = 5;

		std::bitset<(uint32_t)CommandType::COUNT> possibleCommandList;

		CommandComponent() = default;
		CommandComponent(const CommandComponent&) = default;
		CommandComponent(CommandComponent&&) = default;
		CommandComponent& operator=(const CommandComponent&) = default;
		CommandComponent& operator=(CommandComponent&&) = default;
		~CommandComponent() = default;
	};

	// A simple incrementing counter
	// The max value is not enforced and serves only for manual checking
	struct CounterComponent
	{
		static constexpr int type = 6;

		uint32_t currentValue = (uint32_t)(-1);
		uint32_t maxValue;

		CounterComponent(uint32_t max = 0)
			: maxValue{ max }
		{
		}
		CounterComponent(const CounterComponent&) = default;
		CounterComponent(CounterComponent&&) = default;
		CounterComponent& operator=(const CounterComponent&) = default;
		CounterComponent& operator=(CounterComponent&&) = default;
		~CounterComponent() = default;
	};

	// Contains the blueprint that gets called when an entity that has this component is created
	struct ConstructorComponent
	{
		static constexpr int type = 7;

		std::map<std::string, std::function<void()>> blueprint;

		ConstructorComponent(std::map<std::string, std::function<void()>>&& blueprint)
			: blueprint{ std::move(blueprint) }
		{
		}
		ConstructorComponent(const ConstructorComponent&) = default;
		ConstructorComponent(ConstructorComponent&&) = default;
		ConstructorComponent& operator=(const ConstructorComponent&) = default;
		ConstructorComponent& operator=(ConstructorComponent&&) = default;
		~ConstructorComponent() = default;
	};

	// Allows an entity to increase the player's mana capacity and regeneration rate while it's alive
	struct CrystalManaComponent
	{
		static constexpr int type = 8;

		uint32_t capIncrease;
		uint32_t regenIncrease;

		CrystalManaComponent(uint32_t cap = 0, uint32_t regen = 0)
			: capIncrease{ cap }
			, regenIncrease{ regen }
		{
		}
		CrystalManaComponent(const CrystalManaComponent&) = default;
		CrystalManaComponent(CrystalManaComponent&&) = default;
		CrystalManaComponent& operator=(const CrystalManaComponent&) = default;
		CrystalManaComponent& operator=(CrystalManaComponent&&) = default;
		~CrystalManaComponent() = default;
	};

	// Contains name of the table that contains the function
	// (called "dtor") which is called when an entity is destroyed
	struct DestructorComponent
	{
		static constexpr int type = 9;

		std::map<std::string, std::function<void()>> blueprint;

		DestructorComponent(std::map<std::string, std::function<void()>>&& blueprint)
			: blueprint{ std::move(blueprint) }
		{
		}
		DestructorComponent(const DestructorComponent&) = default;
		DestructorComponent(DestructorComponent&&) = default;
		DestructorComponent& operator=(const DestructorComponent&) = default;
		DestructorComponent& operator=(DestructorComponent&&) = default;
		~DestructorComponent() = default;
	};

	// An entity with this component causes others to align to it, but also forces them
	// to use the full geometry e.g. for doors to avoid artefacts on the neighbour blocks
	struct DummyAlignComponent
	{
		static constexpr int type = 10;
	};

	// Represents events that happen in the game, like dropping gold,
	// curing an entity of poisoning or triggers from traps, etc
	struct EventComponent
	{
		static constexpr int type = 11;

		EventType eventType;
		uint32_t target;
		uint32_t handler;
		float radius;
		bool active;

		EventComponent(EventType ev = EventType::NONE, uint32_t t = Component::NO_ENTITY,
			float r = 0.f, bool a = true)
			: eventType{ ev }
			, target{ t }
			, handler{ Component::NO_ENTITY }
			, radius{ r }
			, active{ a }
		{
		}
		EventComponent(const EventComponent&) = default;
		EventComponent(EventComponent&&) = default;
		EventComponent& operator=(const EventComponent&) = default;
		EventComponent& operator=(EventComponent&&) = default;
		~EventComponent() = default;
	};

	// Allows to cherry pink when it comes to event handling and handle only certain events 
	// (Also, only entities with this component will react to events)
	struct EventHandlerComponent
	{
		static constexpr int type = 12;

		std::string handler;
		std::bitset<(uint32_t)EventType::COUNT> possibleEventList;

		EventHandlerComponent(std::string&& h = "ERROR")
			: handler{ std::move(h) }
			, possibleEventList{}
		{
		}
		EventHandlerComponent(const EventHandlerComponent&) = default;
		EventHandlerComponent(EventHandlerComponent&&) = default;
		EventHandlerComponent& operator=(const EventHandlerComponent&) = default;
		EventHandlerComponent& operator=(EventHandlerComponent&&) = default;
		~EventHandlerComponent() = default;
	};

	// The amount of experience the entity yields when killed
	struct ExperienceValueComponent
	{
		static constexpr int type = 13;

		uint32_t value;

		ExperienceValueComponent(uint32_t v = 0)
			: value{ v }
		{
		}
		ExperienceValueComponent(const ExperienceValueComponent&) = default;
		ExperienceValueComponent(ExperienceValueComponent&&) = default;
		ExperienceValueComponent& operator=(const ExperienceValueComponent&) = default;
		ExperienceValueComponent& operator=(ExperienceValueComponent&&) = default;
		~ExperienceValueComponent() = default;
	};

	// Component used to create the visual effect of an explosion
	// the damage should be done in the explosion's constructor so that it's not applied on each frame
	struct ExplosionComponent
	{
		static constexpr int type = 14;

		float delta;
		float maxRadius;
		float currentRadius = 0.0f;

		ExplosionComponent(float d = 0.f, float rad = 0.f)
			: delta{ d }
			, maxRadius{ rad }
		{
		}
		ExplosionComponent(const ExplosionComponent&) = default;
		ExplosionComponent(ExplosionComponent&&) = default;
		ExplosionComponent& operator=(const ExplosionComponent&) = default;
		ExplosionComponent& operator=(ExplosionComponent&&) = default;
		~ExplosionComponent() = default;
	};
	
	// Health and regeneration
	struct HealthComponent
	{
		static constexpr int type = 15;

		uint32_t currentHealthPoints;
		uint32_t maxHealthPoints;
		uint32_t regen;
		uint32_t defense;
		bool alive;

		HealthComponent(uint32_t max = 0
			, uint32_t reg = 0
			, uint32_t def = 0
			, bool a = true
		)
			: currentHealthPoints{ max }
			, maxHealthPoints{ max }
			, regen{ reg }
			, defense{ def }
			, alive{ a }
		{
		}
		HealthComponent(const HealthComponent&) = default;
		HealthComponent(HealthComponent&&) = default;
		HealthComponent& operator=(const HealthComponent&) = default;
		HealthComponent& operator=(HealthComponent&&) = default;
		~HealthComponent() = default;
	};

	// Used for projectiles that are supposed to follow a target and deal damage when they hit it
	struct HomingComponent
	{
		static constexpr int type = 16;

		uint32_t source;
		uint32_t target;
		uint32_t dmg;

		HomingComponent(uint32_t s = Component::NO_ENTITY,
			uint32_t t = Component::NO_ENTITY,
			uint32_t d = 0)
			: source{ s }
			, target{ t }
			, dmg{ d }
		{
		}
		HomingComponent(const HomingComponent&) = default;
		HomingComponent(HomingComponent&&) = default;
		HomingComponent& operator=(const HomingComponent&) = default;
		HomingComponent& operator=(HomingComponent&&) = default;
		~HomingComponent() = default;
	};

	// Represents a gold amount an entity is holding, be it a gold seam, worker minion or gold depository
	struct GoldComponent
	{
		static constexpr int type = 17;

		uint32_t maxAmount;
		uint32_t currentAmount;

		GoldComponent(uint32_t max = 0, uint32_t curr = 0)
			: maxAmount{ max }
			, currentAmount{ curr }
		{
		}
		GoldComponent(const GoldComponent&) = default;
		GoldComponent(GoldComponent&&) = default;
		GoldComponent& operator=(const GoldComponent&) = default;
		GoldComponent& operator=(GoldComponent&&) = default;
		~GoldComponent() = default;
	};

	struct GraphicsComponent
	{
		static constexpr int type = 18;

		std::string sprite;
		bool visible;
		Node* node = nullptr;
		uint32_t entity = uint32_t(-1);
		bool isManualScaling;
		Vec2 scale;

		GraphicsComponent(std::string&& spriteName = ""
			, bool visible = true
			, bool manual = false
			, Vec2 scale = Vec2{ 0.0f, 0.0f }
		)
			: sprite{ std::move(spriteName) }
			, visible{ visible }
			, isManualScaling{ manual }
			, scale{ scale }
		{
		}

		GraphicsComponent(const GraphicsComponent&) = default;
		GraphicsComponent(GraphicsComponent&&) = default;
		GraphicsComponent& operator=(const GraphicsComponent&) = default;
		GraphicsComponent& operator=(GraphicsComponent&&) = default;
		~GraphicsComponent() = default;
	};

	// Holds GridNode's neighbour nodes
	// The neighbours are set to the maximum value of uint32_t to
	// fix a state when one or more neighbours weren't set (won't have that many
	// nodes so the A* algorithm will ignore them)
	struct GridNodeComponent
	{
		static constexpr int type = 19;
		static constexpr uint32_t neighbourCount = 9;

		std::array<uint32_t, neighbourCount> neighbours;
		bool free;
		// Position in the grid
		uint32_t x;
		uint32_t y;
		uint32_t resident;

		GridNodeComponent(std::array<uint32_t
			, neighbourCount> neigh = std::array<uint32_t, neighbourCount>{}
			, bool f = true
			, uint32_t positionX = 0
			, uint32_t positionY = 0
			, uint32_t res = Component::NO_ENTITY
		)
			: neighbours(neigh)
			, free{ f }
			, x{ positionX }
			, y{ positionY }
			, resident{ res }
		{
			neighbours.fill(Component::NO_ENTITY);
		}
		GridNodeComponent(const GridNodeComponent&) = default;
		GridNodeComponent(GridNodeComponent&&) = default;
		GridNodeComponent& operator=(const GridNodeComponent&) = default;
		GridNodeComponent& operator=(GridNodeComponent&&) = default;
		~GridNodeComponent() = default;
	};

	// Represents the faction an entity that has this component if a member of
	struct FactionComponent
	{
		static constexpr int type = 20;

		Faction faction;

		FactionComponent(Faction f = Faction::NEUTRAL)
			: faction{ f }
		{
		}
		FactionComponent(const FactionComponent&) = default;
		FactionComponent(FactionComponent&&) = default;
		FactionComponent& operator=(const FactionComponent&) = default;
		FactionComponent& operator=(FactionComponent&&) = default;
		~FactionComponent() = default;
	};

	// Direct player input applied to an entity
	struct InputComponent
	{
		static constexpr int type = 21;

		std::string inputHandler;

		InputComponent(std::string&& handler = "ERROR.inputHandler")
			: inputHandler{ std::move(handler) }
		{
		}
		InputComponent(const InputComponent&) = default;
		InputComponent(InputComponent&&) = default;
		InputComponent& operator=(const InputComponent&) = default;
		InputComponent& operator=(InputComponent&&) = default;
		~InputComponent() = default;
	};

	// Allows to create entities that are automatically killed (summons)
	// after a certain amount of time has passed (lifespan)
	struct LimitedLifeSpanComponent
	{
		static constexpr int type = 22;

		float currentTime = 0.0f;
		float maxTime;

		LimitedLifeSpanComponent(float max = 0.0f)
			: maxTime{ max }
		{
		}
		LimitedLifeSpanComponent(const LimitedLifeSpanComponent&) = default;
		LimitedLifeSpanComponent(LimitedLifeSpanComponent&&) = default;
		LimitedLifeSpanComponent& operator=(const LimitedLifeSpanComponent&) = default;
		LimitedLifeSpanComponent& operator=(LimitedLifeSpanComponent&&) = default;
		~LimitedLifeSpanComponent() = default;
	};

	// Allows an entity to cast spell by providing the mana resource
	struct ManaComponent
	{
		static constexpr int type = 23;

		uint32_t currentMana;
		uint32_t maxMana;
		uint32_t manaRegen;

		ManaComponent(uint32_t max = 0, uint32_t regen = 0)
			: currentMana{ max }
			, maxMana{ max }
			, manaRegen{ regen }
		{
		}
		ManaComponent(const ManaComponent&) = default;
		ManaComponent(ManaComponent&&) = default;
		ManaComponent& operator=(const ManaComponent&) = default;
		ManaComponent& operator=(ManaComponent&&) = default;
		~ManaComponent() = default;
	};

	// Dummy component that signals that an entity having it can be mined
	struct MineComponent
	{
		static constexpr int type = 24;
	};

	// Holds info related to movement, if an entity has this component it should also
	// have a Physics component (containing the entity's position), otherwise the
	// MovementSystem might not work correctly
	struct MovementComponent
	{
		static constexpr int type = 25;

		float speedModifier;
		float originalSpeed;

		MovementComponent(float speed = 0.0f)
			: speedModifier{ speed }
			, originalSpeed{ speed }
		{
		}
		MovementComponent(const MovementComponent&) = default;
		MovementComponent(MovementComponent&&) = default;
		MovementComponent& operator=(const MovementComponent&) = default;
		MovementComponent& operator=(MovementComponent&&) = default;
		~MovementComponent() = default;
	};

	// Name of the entity shown in the entity viewer
	struct NameComponent
	{
		static constexpr int type = 26;

		std::string name;

		NameComponent(std::string&& n = "ERROR")
			: name{ std::move(n) }
		{
		}
		NameComponent(const NameComponent&) = default;
		NameComponent(NameComponent&&) = default;
		NameComponent& operator=(const NameComponent&) = default;
		NameComponent& operator=(NameComponent&&) = default;
		~NameComponent() = default;
	};

	// Allows to keep track about notification cooldown, so that an entity
	// doesn't spam the player with messages on reoccuring events in a short time period
	struct NotificationComponent
	{
		static constexpr int type = 27;

		float currentTime = 0.0f;
		float cooldown;

		NotificationComponent(float cooldown = 0.f)
			: cooldown{ cooldown }
		{
		}
		NotificationComponent(const NotificationComponent&) = default;
		NotificationComponent(NotificationComponent&&) = default;
		NotificationComponent& operator=(const NotificationComponent&) = default;
		NotificationComponent& operator=(NotificationComponent&&) = default;
		~NotificationComponent() = default;
	};

	// Contains the blueprint table which gets called when an entity that has this component gets hit
	struct OnHitComponent
	{
		static constexpr int type = 28;

		std::map<std::string, std::function<void()>> blueprint;
		float currentTime;
		float cooldown;

		OnHitComponent(std::map<std::string, std::function<void()>>&& blueprint, float cooldown = 0.f)
			: blueprint{ std::move(blueprint) }
			, currentTime{ cooldown }
			, cooldown{ cooldown }
		{
		}
		OnHitComponent(const OnHitComponent&) = default;
		OnHitComponent(OnHitComponent&&) = default;
		OnHitComponent& operator=(const OnHitComponent&) = default;
		OnHitComponent& operator=(OnHitComponent&&) = default;
		~OnHitComponent() = default;
	};

	// Holds data related to the entity's current path
	struct PathfindingComponent
	{
		static constexpr int type = 29;

		uint32_t targetId;
		uint32_t lastId;
		std::deque<uint32_t> pathQueue;
		// Name of the table the getCost(id1, id2) function is in
		std::map<std::string, std::function<void()>> blueprint; 

		PathfindingComponent(std::map<std::string, std::function<void()>>&& blueprint, uint32_t tar = 0, uint32_t last = 0)
			: targetId{ tar }
			, lastId{ last }
			, pathQueue{}
			, blueprint{ std::move(blueprint) }
		{
		}
		PathfindingComponent(const PathfindingComponent&) = default;
		PathfindingComponent(PathfindingComponent&&) = default;
		PathfindingComponent& operator=(const PathfindingComponent&) = default;
		PathfindingComponent& operator=(PathfindingComponent&&) = default;
		~PathfindingComponent() = default;
	};

	struct PhysicsComponent
	{
		static constexpr int type = 30;

		bool solid;
		Vec2 position;
		float halfHeight;

		PhysicsComponent(bool s = false, Vec2 pos = Vec2{ 0.0f, 0.0f }, float hh = 0.0f)
			: solid{ s }
			, position{ pos }
			, halfHeight{ hh }
		{
		}
		PhysicsComponent(const PhysicsComponent&) = default;
		PhysicsComponent(PhysicsComponent&&) = default;
		PhysicsComponent& operator=(const PhysicsComponent&) = default;
		PhysicsComponent& operator=(PhysicsComponent&&) = default;
		~PhysicsComponent() = default;
	};

	// An entity having it is a portal, used in pathfinding
	struct PortalComponent
	{
		static constexpr int type = 31;
	};

	// Represents either gold or mana cost of an entity.
	struct PriceComponent
	{
		static constexpr int type = 32;

		uint32_t price;

		PriceComponent(uint32_t p = 0)
			: price{ p }
		{
		}
		PriceComponent(const PriceComponent&) = default;
		PriceComponent(PriceComponent&&) = default;
		PriceComponent& operator=(const PriceComponent&) = default;
		PriceComponent& operator=(PriceComponent&&) = default;
		~PriceComponent() = default;
	};

	// References the producer of the entity that has this component
	// (Producer is the building/tile that spawned it)
	struct ProductComponent
	{
		static constexpr int type = 33;

		uint32_t producer;

		ProductComponent(uint32_t producerId = Component::NO_ENTITY)
			: producer{ producerId }
		{
		}
		ProductComponent(const ProductComponent&) = default;
		ProductComponent(ProductComponent&&) = default;
		ProductComponent& operator=(const ProductComponent&) = default;
		ProductComponent& operator=(ProductComponent&&) = default;
		~ProductComponent() = default;
	};

	// Allows scheduled production of new entities (spawners) of a given type up to a maximum amount
	struct ProductionComponent
	{
		static constexpr int type = 34;

		std::string productBlueprint;
		uint32_t currentProduced = 0;
		uint32_t maxProduced;
		float cooldown;
		float currentCooldown = 0.0f;

		ProductionComponent(std::string&& b = "ERROR", uint32_t maxProduced = 1, float cooldown = 0.0f)
			: productBlueprint{ std::move(b) }
			, maxProduced{ maxProduced }
			, cooldown{ cooldown }
		{ 
		}
		ProductionComponent(const ProductionComponent&) = default;
		ProductionComponent(ProductionComponent&&) = default;
		ProductionComponent& operator=(const ProductionComponent&) = default;
		ProductionComponent& operator=(ProductionComponent&&) = default;
		~ProductionComponent() = default;
	};

	// Allows an entity to be selected and select/deselect handler blueprint
	struct SelectionComponent
	{
		static constexpr int type = 35;

		std::map<std::string, std::function<void()>> blueprint;
		Vec2 scale;
		uint32_t entity = uint32_t(-1);
		SelectionMarkerType markerType;
		float rotation;

		SelectionComponent(std::map<std::string, std::function<void()>>&& blueprint
			, std::string&& m = "NONE"
			, Vec2 scale = Vec2{}
			, SelectionMarkerType t = SelectionMarkerType::CIRCLE
		)
			: blueprint{ std::move(blueprint) }
			, scale{ scale }
			, markerType{ t }
			, rotation{}
		{
		}
		SelectionComponent(const SelectionComponent&) = default;
		SelectionComponent(SelectionComponent&&) = default;
		SelectionComponent& operator=(const SelectionComponent&) = default;
		SelectionComponent& operator=(SelectionComponent&&) = default;
		~SelectionComponent() = default;
	};

	// Allows an entity to periodically cast a spell
	struct SpellComponent
	{
		static constexpr int type = 36;

		std::map<std::string, std::function<void()>> blueprint;
		float cooldownTime = 0.0f;
		float cooldown;

		SpellComponent(std::map<std::string, std::function<void()>>&& blueprint, float cooldown = 0.0f)
			: blueprint{ std::move(blueprint) }
			, cooldown{ cooldown }
		{
		}
		SpellComponent(const SpellComponent&) = default;
		SpellComponent(SpellComponent&&) = default;
		SpellComponent& operator=(const SpellComponent&) = default;
		SpellComponent& operator=(SpellComponent&&) = default;
		~SpellComponent() = default;
	};

	// Defines a building (or a wall), by holding it's radius (of the area it takes
	// in the grid) and vector of nodes that it sits on
	struct StructureComponent
	{
		static constexpr int type = 37;

		uint32_t radius;
		bool isWalkThrough;
		std::vector<uint32_t> residences;

		StructureComponent(uint32_t r = 1, bool wt = false)
			: radius{ r }
			, isWalkThrough{ wt }
			, residences{}
		{
		}
		StructureComponent(const StructureComponent&) = default;
		StructureComponent(StructureComponent&&) = default;
		StructureComponent& operator=(const StructureComponent&) = default;
		StructureComponent& operator=(StructureComponent&&) = default;
		~StructureComponent() = default;
	};

	// Defines a task by giving it a type, source (the task handler) and a target (subject of the task)
	// Handling of these tasks is done via the TaskHandlerComponent below
	struct TaskComponent
	{
		static constexpr int type = 38;

		TaskType taskType;
		uint32_t source;
		uint32_t target;
		bool complete = false;

		TaskComponent(uint32_t targetId = Component::NO_ENTITY
			, uint32_t sourceId = Component::NO_ENTITY
			, TaskType taskType = TaskType::NONE
		)
			: taskType{ taskType }
			, source{ sourceId }
			, target{ targetId }
		{  
		}
		TaskComponent(const TaskComponent&) = default;
		TaskComponent(TaskComponent&&) = default;
		TaskComponent& operator=(const TaskComponent&) = default;
		TaskComponent& operator=(TaskComponent&&) = default;
		~TaskComponent() = default;
	};

	// Task queue and register of possible tasks, every entity that is
	// able to actually do something on it's own should have it.
	struct TaskHandlerComponent
	{
		static constexpr int type = 39;

		uint32_t currentTask = Component::NO_ENTITY;
		std::bitset<(uint32_t)TaskType::COUNT> possibleTaskList;
		std::deque<uint32_t> taskQueue;
		bool busy = false;
		std::map<std::string, std::function<void()>> blueprint;

		TaskHandlerComponent(std::map<std::string, std::function<void()>>&& blueprint)
			: blueprint{ std::move(blueprint) }
		{  
		}
		TaskHandlerComponent(const TaskHandlerComponent&) = default;
		TaskHandlerComponent(TaskHandlerComponent&&) = default;
		TaskHandlerComponent& operator=(const TaskHandlerComponent&) = default;
		TaskHandlerComponent& operator=(TaskHandlerComponent&&) = default;
		~TaskHandlerComponent() = default;
	};

	// Represents a timer that after a certain amount of time can start end an event (it's target)
	struct TimeComponent
	{
		static constexpr int type = 40;

		float currentTime = 0.0f;
		float timeLimit;
		uint32_t target;
		TimeEvent eventType;

		TimeComponent(TimeEvent ev = TimeEvent::NONE
			, float limit = 0.0f
			, uint32_t t = Component::NO_ENTITY
		)
			: timeLimit{ limit }
			, target{ t }
			, eventType{ ev }
		{
		}
		TimeComponent(const TimeComponent&) = default;
		TimeComponent(TimeComponent&&) = default;
		TimeComponent& operator=(const TimeComponent&) = default;
		TimeComponent& operator=(TimeComponent&&) = default;
		~TimeComponent() = default;
	};

	// Allows an entity to cause an effect (by calling it's blueprint) when
	// its triggered (stepped on) or can notify a linked entity which causes the effect
	struct TriggerComponent
	{
		static constexpr int type = 41;

		std::map<std::string, std::function<void()>> blueprint;
		uint32_t linkedEntity = Component::NO_ENTITY;
		float currentTime = 0.0f;
		float cooldown;
		float radius;

		TriggerComponent(std::map<std::string, std::function<void()>>&& blueprint, float cooldown = 0.0f, float rad = 0.0f)
			: blueprint{ std::move(blueprint) }
			, cooldown{ cooldown }
			, radius{ rad }
		{  
		}
		TriggerComponent(const TriggerComponent&) = default;
		TriggerComponent(TriggerComponent&&) = default;
		TriggerComponent& operator=(const TriggerComponent&) = default;
		TriggerComponent& operator=(TriggerComponent&&) = default;
		~TriggerComponent() = default;
	};

	// Represents the game's leveling system component, contains info about experience
	// and leveling progression as well as the blueprint that gets called on level up
	struct UpgradeComponent
	{
		static constexpr int type = 42;

		std::map<std::string, std::function<void()>> blueprint;
		uint32_t experience = 0;
		uint32_t experienceNeeded;
		uint32_t level = 0;
		uint32_t levelCap;

		UpgradeComponent(std::map<std::string, std::function<void()>>&& blueprint, uint32_t exp = 100, uint32_t cap = 5)
			: blueprint{ std::move(blueprint) }
			, experienceNeeded{ exp }
			, levelCap{ cap }
		{
		}
		UpgradeComponent(const UpgradeComponent&) = default;
		UpgradeComponent(UpgradeComponent&&) = default;
		UpgradeComponent& operator=(const UpgradeComponent&) = default;
		UpgradeComponent& operator=(UpgradeComponent&&) = default;
		~UpgradeComponent() = default;
	};

} // namespace RioGame
// Copyright (c) 2012-2017 Volodymyr Syvochka
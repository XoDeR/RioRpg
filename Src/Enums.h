// Copyright (c) 2012-2017 Volodymyr Syvochka
#pragma once

namespace RioGame
{

	enum class GameState
	{
		RUNNING = 0,
		ENDED,
		PAUSED,
		MENU,
		INTRO_MENU
	};

	enum class EntityType
	{
		NONE = 0,
		WALL = 1 << 0,
		MINION = 1 << 1,
		ENEMY = 1 << 2,
		BUILDING = 1 << 3,
		MISC = 1 << 4
	};

	namespace EntityState
	{
		enum ENUM
		{
			NONE = 0,
			NORMAL,
			COUNT
		};
	};

	enum class Faction
	{
		FRIENDLY = 0,
		ENEMY = 1,
		NEUTRAL = 2
	};

	enum class EventType
	{
		NONE = 0,
		KILL_ENTITY = 1,
		GOLD_DROPPED = 2,
		RESTORE_SPEED = 3,
		METEOR_FALLING = 4,
		COUNT
	};

	enum class TaskType
	{
		NONE = 0,
		GO_TO,
		GO_NEAR,
		GO_KILL,
		KILL,
		GET_IN_RANGE,
		GO_PICK_UP_GOLD,
		PICK_UP_GOLD,
		GO_DEPOSIT_GOLD,
		DEPOSIT_GOLD,
		COUNT
	};

	enum class AttackType
	{
		NONE = 0,
		MELEE = 1,
		RANGED = 2,
		COUNT
	};

	enum class TimeEvent
	{
		NONE = 0,
		START_EVENT,
		END_EVENT,
		CALL_FUNCTION,
		COUNT
	};

	namespace Direction
	{
		enum ENUM
		{
			UP = 0,
			DOWN,
			LEFT,
			RIGHT,
			UP_LEFT,
			UP_RIGHT,
			DOWN_LEFT,
			DOWN_RIGHT,
			PORTAL,
			NONE
		};
	}

	enum class SpellType
	{
		NONE = 0,
		TARGETED,
		POSITIONAL,
		GLOBAL,
		PLACING
	};

	enum class CommandType
	{
		MINE = 0,
		ATTACK = 1,
		REPOSITION = 2,
		RETURN_GOLD = 3,
		FALL_BACK = 4,
		COUNT
	};

	namespace KeyBindAction
	{
		enum ENUM
		{
			NONE = 0,
			SPELL_BUILD_1,
			SPELL_BUILD_2,
			SPELL_BUILD_3,
			SPELL_BUILD_4,
			NEXT,
			PREV,
			SPELL_TAB,
			BUILD_TAB,
			MENU_TAB,
			RESET_CAMERA,
			QUICK_SAVE,
			QUICK_LOAD,
			COUNT
		};
	}

	enum class WaveState
	{
		ACTIVE = 0,
		WAITING,
		INACTIVE
	};

	namespace AnimationType
	{
		enum ENUM
		{
			WALK = 0,
			IDLE,
			HIT,
			ACTIVATE,
			DEACTIVATE,
			COUNT
		};
	}

	enum class SelectionMarkerType
	{
		CIRCLE = 0,
		SQUARE,
		HALF_SQUARE
	};

	enum class ComponentType 
	{
		NONE =					-1,
		ACTIVATION =			0,
		AI =					1,
		ALIGN =					2,
		ANIMATION =				3,
		COMBAT =				4,
		COMMAND =				5,
		COUNTER =				6,
		CONSTRUCTOR =			7,
		CRYSTAL_MANA =			8,
		DESTRUCTOR =			9,
		DUMMY_ALIGN_COMPONENT = 10,
		EVENT =					11,
		EVENT_HANDLER =			12,
		EXPERIENCE_VALUE =		13,
		EXPLOSION =				14,
		HEALTH =				15,
		HOMING =				16,
		GOLD =					17,
		GRAPHICS =				18,
		GRID_NODE =				19,
		FACTION =				20,
		INPUT =					21,
		LIMITED_LIFE_SPAN =		22,
		MANA =					23,
		MINE =					24,
		MOVEMENT =				25,
		NAME =					26,
		NOTIFICATION =			27,
		ON_HIT =				28,
		PATHFINDING =			29,
		PHYSICS =				30,
		PORTAL =				31,
		PRICE =					32,
		PRODUCT =				33,
		PRODUCTION =			34,
		SELECTION =				35,
		SPELL =					36,
		STRUCTURE =				37,
		TASK =					38,
		TASK_HANDLER =			39,
		TIME =					40,
		TRIGGER =				41,
		UPGRADE =				42,
	};

	enum class InputKeyType 
	{
		KEY_UP = 0,
		KEY_DOWN = 1,
		KEY_LEFT = 2,
		KEY_RIGHT = 3,
	};

} // namespace RioGame
// Copyright (c) 2012-2017 Volodymyr Syvochka
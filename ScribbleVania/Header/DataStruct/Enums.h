#pragma once
#define WIN32_LEAN_AND_MEAN

//Typoes  =======================================================================
typedef enum class ObjectType
{
	Player = 0,
	Level=1,
	Background = 2,
	EnvironmentObject=3,
	Boss=4,
	Enemy=5,
	Projectile=6,
	Other
} ObjecType;

enum CollidableType
{
	Box,
	Circle,
	Other,
};


typedef enum class EnvSubType{
	Wall,
	Floor,
	Ceiling,
	Ledge,
	Door,
	Background,
	Other
} EnvSubType;

typedef enum class EnemyType
{
	RedSnail,
	GraySnail,
	FatFrog,
	BombFrog,
	Other
} EnemyType;

typedef enum class BossType
{
	Snail,
	Other
} BossType;

typedef enum class ProjectileType
{
	Basic,
	other
} ProjectileType;

//STATES =======================================================================
typedef enum class PlayerState
{
	Walking,
	Sliding,
	Jumping,
	Hanging
} PlayerState;

typedef enum class RedSnailState
{
	Patrol,
	Attack,
	Falling,
	Dead
} RedSnailState;

typedef enum class SnailBossState
{
	Falling,
	Bouncing,
	Attack,
	Defend,
	Dead
} SnailBossState;

typedef enum class FatFrogState
{
	Patrolling,
	Jumping,
	Falling,
	Dead
} FatFrogState;

//OTHER  =======================================================================
typedef enum class Direction
{
	Up,
	Right,
	Down,
	Left
} Direction;
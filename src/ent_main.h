#pragma once
#include "g_pathing.h"
#include "pt_draw.h"
#include <map>

class Entity;
class EntityTemplate;

struct ProjectileInfo{
	ProjectileInfo();
	ProjectileInfo(unsigned int tex, color col, int w, int h, float spd, bool guided);

	unsigned int tex;
	color col;
	int w, h;
	float vel;
	bool guided;
	bool retarget;
	double turnrate;
};

struct Projectile{
	Projectile();
	Projectile(float x, float y, ProjectileInfo* inf, double ang);

	float x, y;
	ProjectileInfo* inf;
	double ang;
	Entity* target;
};

struct ProjectileList{
	ProjectileList();

	Projectile val;
	ProjectileList* prv;
	ProjectileList* nxt;
};

struct AttackInfo{
	AttackInfo();
	AttackInfo(float dmg, float rng, float spd);
	AttackInfo(float dmg, float rng, float spd, ProjectileInfo proj);
	float range;
	float damage;
	float rate;
	bool projectile;
	ProjectileInfo proj;
	ProjectileList* projlist;

	float lastAtk;
};

//Texture Info
struct TextureInfo{
	TextureInfo();
	TextureInfo(int base);
	TextureInfo(int base, int move, int attack);
	
	int base;
	int move;
	int attack;
	int die;
	int misc1;
	int misc2;
};

//Default Entity Class
class Entity {
public:
	float x, y;
	int w, h;
	TextureInfo tex;
	int activetex;
	color col;
	int zone;
	char* name;
	char* tooltip;
	float hp;
	float hpmax;
	float armor;
	float speed;
	double ang;
	bool enemy;

	int rescost;
	EntityTemplate* upgradeEnt;

	bool active;

	AttackInfo atk;

	int dest;
	Entity* target;

	Entity();
	Entity(EntityTemplate* et, int x, int y);
	~Entity();

	//METHODS

	//Returns data from 'dat'
	float Get(char* dat);
	//Sets data at 'loc' to 'dat'
	void Set(char* loc, float dat);
	//Returns current zone
	Zone* GetZone();

	//Set ents health to 'amt'
	void SetHealth(float amt);
	//returns position as a point
	Point GetPos();
	//sets ent's posiiton to (x, y)
	void SetPos(int x, int y);
	void SetPos(float x, float y);
	//sets ent's position to a point
	void SetPos(Point p);

	//variable event methods

	//Draw Entity
	void Draw(float scalex, float scaley, int panx, int pany);
	void (*OnDraw)(Entity*, float, float, int, int);
	//Takes Damage
	float Damage(Entity* attacker, float amt);
	float (*OnTakeDamage)(Entity*, Entity*, float);
	//Performs an Attack
	void Attack(Entity* target);
	void (*OnAttack)(Entity*, Entity*);
	//Is Healed
	void Heal(Entity* healer, float amt);
	void (*OnTakeHeal)(Entity*, Entity*, float);
	//Deals Damage
	void DealsDamage(Entity* ent, float amt);
	void (*OnDealDamage)(Entity*, Entity*, float);
	//Kills
	void KillsEnt(Entity* victim);
	void (*OnKillEnt)(Entity*, Entity*);
	//Death
	void Death(Entity* killer);
	void (*OnDeath)(Entity*, Entity*);
	//Think
	void Think();
	void (*OnThink)(Entity*);

	void ProcessProjectiles();

	//Get new destination
	void FindDest();

	//Finds closest enemy
	void FindTarget();

	//Calculate current zone
	void CalcZone();

	//Delete Entity
	void Delete();

private:
	std::map<char*, float> data;
};

//ENTITY TEMPLATE
class EntityTemplate {
public:
	EntityTemplate();

	int w, h;
	TextureInfo tex;
	int activetex;
	color col;
	char* name;
	char* tooltip;
	float hp;
	float hpmax;
	float armor;
	float speed;
	double ang;
	bool enemy;

	int rescost;
	EntityTemplate* upgradeEnt;

	AttackInfo atk;

	void (*OnDraw)(Entity*, float, float, int, int);

	float (*OnTakeDamage)(Entity*, Entity*, float);

	void (*OnAttack)(Entity*, Entity*);

	void (*OnTakeHeal)(Entity*, Entity*, float);

	void (*OnDealDamage)(Entity*, Entity*, float);

	void (*OnKillEnt)(Entity*, Entity*);

	void (*OnDeath)(Entity*, Entity*);

	void (*OnThink)(Entity*);

	std::map<char*, float> data;
};

EntityTemplate* loadEntity(char* path);

void UpgradeEntity(Entity* ent, EntityTemplate* to);
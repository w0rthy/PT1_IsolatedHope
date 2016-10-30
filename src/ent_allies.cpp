#include "ent_allies.h"
#include "ent_methods.h"

namespace ENTS_ALLIES {
	EntityTemplate builder = EntityTemplate();
	EntityTemplate arrowTower1 = EntityTemplate();
	EntityTemplate basicWall1 = EntityTemplate();
	void ConstructTemplates(){
		//BUILDER
		builder.name = "Builder";
		builder.w = 32;
		builder.h = 32;
		builder.hp = 1000.0f;
		builder.hpmax = 1000.0f;
		builder.speed = 35.0f;
		builder.armor = 0.0f;
		builder.enemy = false;
		builder.tex = TextureInfo(loadTexture("servobot.png"));
		builder.atk.range = 30.0f;
		builder.OnThink = &ENT_THINKS::DefaultBuilder;

		//ARROW TOWERS
		arrowTower1.name = "Arrow Tower Lv. 1";
		arrowTower1.tooltip = "The most basic tower.";
		arrowTower1.w = 32;
		arrowTower1.h = 32;
		arrowTower1.hp = 100.0f;
		arrowTower1.hpmax = 100.0f;
		arrowTower1.speed = 0.0f;
		arrowTower1.armor = 0.0f;
		arrowTower1.enemy = false;
		arrowTower1.upgradeEnt = &basicWall1;
		arrowTower1.tex = TextureInfo(loadTexture("badtower.png"));
		arrowTower1.atk = AttackInfo(15.0f,150.0f,1.0f,ProjectileInfo(loadTexture("arrow.png"),color(1.0f,1.0f,1.0f),6,16,25.0f,false));
		arrowTower1.OnThink = &ENT_THINKS::DefaultTower;
		
		//BASIC WALLS
		basicWall1.name = "Barricade (Simple Wall Lv. 1)";
		basicWall1.tooltip = "A simple wall. It's great at keeping stuff out!";
		basicWall1.w = 32;
		basicWall1.h = 32;
		basicWall1.hp = 1000.0f;
		basicWall1.hpmax = 1000.0f;
		basicWall1.speed = 0.0f;
		basicWall1.armor = 10.0f;
		basicWall1.enemy = false;
		basicWall1.tex = TextureInfo(loadTexture("ooze.png"));
		basicWall1.OnThink = nullptr;
	}
}
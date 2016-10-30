#include "ent_enemies.h"
#include "ent_methods.h"

namespace ENTS_ENEMIES {
	EntityTemplate mouse = EntityTemplate();
	void ConstructTemplates(){
		mouse.name = "Mouse";
		mouse.w = 16;
		mouse.h = 16;
		mouse.hp = 50.0f;
		mouse.hpmax = 50.0f;
		mouse.speed = 25.0f;
		mouse.armor = 0.0f;
		mouse.enemy = true;
		mouse.tex = TextureInfo(loadTexture("content/art/enemies/mouse/idle.png"),
			loadTexture("content/art/enemies/mouse/walk.png"),
			loadTexture("content/art/enemies/mouse/atk.png"));
		mouse.atk =  AttackInfo(3.0f,20.0f,0.5f);
		mouse.OnThink = &ENT_THINKS::DefaultEnemy;
	}
}
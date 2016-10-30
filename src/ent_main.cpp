#include "ent_main.h"
#include "ent_list.h"
#include "ent_methods.h"
#include "pt_io.h"
#include "g_vars.h"
#include "g_resources.h"
#include <list>
#include <fstream>

//PROJECTILE INFO
ProjectileInfo::ProjectileInfo(){

}

ProjectileInfo::ProjectileInfo(unsigned int text, color colo, int w1, int h1, float speed, bool guid){
	tex = text;
	col = colo;
	w = w1;
	h = h1;
	vel = speed;
	guided = guid;
	turnrate = 2.0*PI;
	retarget = false;
}

Projectile::Projectile(){

}

Projectile::Projectile(float x1, float y1, ProjectileInfo* info, double angle){
	x = x1;
	y = y1;
	inf = info;
	ang = angle;
}

ProjectileList::ProjectileList(){
	nxt = nullptr;
	prv = nullptr;
}

//ATTACK INFO
AttackInfo::AttackInfo(){
	lastAtk = 0.0f;
	projlist = nullptr;
}

AttackInfo::AttackInfo(float dmg, float rng, float spd){
	lastAtk = 0.0f;
	projlist = nullptr;
	damage = dmg;
	range = rng;
	rate = spd;
	projectile = false;
}

AttackInfo::AttackInfo(float dmg, float rng, float spd, ProjectileInfo projinf) {
	damage = dmg;
	range = rng;
	rate = spd;
	lastAtk = 0.0f;
	projlist = nullptr;
	projectile = true;
	proj = projinf;
}

//TEXUTRES
TextureInfo::TextureInfo(){
	base = -1;
	move = -1;
	attack = -1;
	die = -1;
	misc1 = -1;
	misc2 = -1;
}

TextureInfo::TextureInfo(int bs){
	base = bs;
	move = -1;
	attack = -1;
	die = -1;
	misc1 = -1;
	misc2 = -1;
}

TextureInfo::TextureInfo(int bs, int mv, int atk){
	base = bs;
	move = mv;
	attack = atk;
	die = -1;
	misc1 = -1;
	misc2 = -1;
}

//ENTITY
Entity::Entity(){
	ent_list->add(this);
	name = "unnamed";
	tooltip = "no tooltip";
	x = 0;
	y = 0;
	w = 10;
	h = 10;
	tex = TextureInfo();
	activetex = -1;
	col = color(1.0f,1.0f,1.0f);
	hp = 100.0f;
	hpmax = 100.0f;
	armor = 0.0f;
	speed = 1.0f;
	zone = -1;
	dest = -1;
	enemy = true;

	upgradeEnt = nullptr;

	active = true;

	atk = AttackInfo(10.0f,30.0f,2.0f);

	OnDraw = &ENT_DRAWS::Default;
	OnThink = &ENT_THINKS::DefaultEnemy;
	OnAttack = &ENT_ATTACKS::Default;
	OnTakeDamage = &ENT_TAKEDAMAGES::Default;
	OnTakeHeal = nullptr;
	OnDealDamage = nullptr;
	OnKillEnt = nullptr;
	OnDeath = nullptr;

	data = std::map<char*, float>();
}

Entity::~Entity(){
	ent_list->del(this);
}

void Entity::Set(char* a, float dat){
	data[a] = dat;
}

float Entity::Get(char* dat){
	return data[dat];
}

Zone* Entity::GetZone(){
	return pointCurZone(x,y);
}

void Entity::SetHealth(float amt){
	hp = min(amt,hpmax);
}

Point Entity::GetPos(){
	return Point((int)x,(int)y);
}

void Entity::SetPos(int x1, int y1){
	x = (float)x1;
	y = (float)y1;
}

void Entity::SetPos(float x1, float y1){
	x = x1;
	y = y1;
}

void Entity::SetPos(Point p){
	x = (float)p.x;
	y = (float)p.y;
}

//void Entity::Think(){
//	//if distance between target and this is not in all attack ranges, move, else attack
//	if(zone != dest && dest >= 0 && zone >= 0){
//		Path* p = getPath(&map->zones[zone],&map->zones[dest]);
//		Point po = getNextPoint(p,Point(map->zones[dest].x,map->zones[dest].y),0);
//		if((int)x == po.x && (int)y == po.y){
//			zone = ZoneIndex(p->path[0]->con2);
//			return;
//		}
//		double angl = AngleBetweenRad((int)x,(int)y,po.x,po.y);
//		ang = (float)(angl*180.0/PI)+90.0;
//		Zone* z = &map->zones[zone];
//		float spd = ScaleTime(speed);
//		SetPos(clamp((float)(x+cos(angl)*spd),(float)z->x,(float)z->x+z->w),clamp((float)(y+sin(angl)*spd),(float)z->y,(float)z->y+z->h));
//	}
//}

//void Entity::FindDest(){
//	int closestZone = -1;
//	float closestDist = FLT_MAX;
//	for(int i = 0; i < ent_listslen; i++){
//		if(ent_lists[i].node == nullptr)
//			continue;
//		
//		linkedEnt* le = ent_lists[i].node;
//		while(le != nullptr && le->val->enemy == enemy)
//			le = le->nxt;
//		if(le == nullptr)
//			continue;
//		if(zone == i){
//			dest = zone;
//			return;
//		}
//
//		Path* p = getPath(&map->zones[zone],&map->zones[i]);
//		if(p->dist < closestDist){
//			closestZone = i;
//			closestDist = p->dist;
//		}
//	}
//	dest = closestZone;
//}
//
//void Entity::FindTarget(){
//	FindDest();
//	if(dest < 0)
//		return;
//
//	Entity* closestEnt = nullptr;
//	float closestDist = FLT_MAX;
//
//	linkedEnt* le = ent_lists[dest].node;
//	if(le == nullptr)
//		return;
//	while(le != nullptr){
//		if(le->val->enemy == enemy){
//			le = le->nxt;
//			continue;
//		}
//		float dis = dist(GetPos(),le->val->GetPos());
//		if(dis < closestDist){
//			closestEnt = le->val;
//			closestDist = dis;
//		}
//		le = le->nxt;
//	}
//	target = closestEnt;
//}

void Entity::FindTarget(){
	Entity* closestEnt = nullptr;
	float closestDist = FLT_MAX;

	for(int i = 0; i < ent_listslen; i++){
		linkedEnt* le = ent_lists[i].node;
		while(le != nullptr){
			Entity* ent = le->val;
			if(ent->enemy != enemy){
				float dis = dist(GetPos(),ent->GetPos());
				if(dis < closestDist){
					closestEnt = ent;
					closestDist = dis;
				}
			}
			le = le->nxt;
		}
	}

	target = closestEnt;
	if(target == nullptr)
		dest = -1;
	else
		dest = target->zone;
}

void Entity::CalcZone(){
	int z = ZoneIndex(GetZone());
	if(zone >= 0)
		ent_lists[zone].del(this);
	if(z >= 0)
		ent_lists[z].add(this);
	zone = z;
}

void Entity::Draw(float scalex, float scaley, int panx, int pany){
	if(OnDraw != nullptr)
		OnDraw(this,scalex,scaley,panx,pany);
}

float Entity::Damage(Entity* attacker, float amt){
	if(OnTakeDamage != nullptr)
		return OnTakeDamage(this,attacker,amt);
	return 0;
}

void Entity::Attack(Entity* target){
	if(OnAttack != nullptr)
		OnAttack(this,target);
}

void Entity::Heal(Entity* healer, float amt){
	if(OnTakeHeal != nullptr)
		OnTakeHeal(this,healer,amt);
}

void Entity::DealsDamage(Entity* ent, float amt){
	if(OnDealDamage != nullptr)
		OnDealDamage(this,ent,amt);
}

void Entity::KillsEnt(Entity* victim){
	if(OnKillEnt != nullptr)
		OnKillEnt(this,victim);
}

void Entity::Death(Entity* killer){
	if(OnDeath != nullptr)
		OnDeath(this,killer);
	Delete();
}

void Entity::ProcessProjectiles(){
	ProjectileList* lp = atk.projlist;
	while(lp != nullptr){
		Projectile* p = &lp->val;
		if(p->inf->guided && target != nullptr){
			if(target != p->target && !p->inf->retarget || (dist(x,y,p->x,p->y) > atk.range && dist(x,y,target->x,target->y) > atk.range))
				goto del;
			//MOVE IT
			double ang = AngleBetweenRad(p->x,p->y,target->x,target->y);
			//p->ang = clamp(p->ang + (ang-p->ang),p->ang - ScaleTime(p->inf->turnrate), p->ang + ScaleTime(p->inf->turnrate));
			p->ang = (ang*180.0/PI);
			p->x = clamp(p->x+(float)sin(ang)*ScaleTime(p->inf->vel),p->x,target->x);
			p->y = clamp(p->y-(float)cos(ang)*ScaleTime(p->inf->vel),p->y,target->y);

			if(dist(p->x,p->y,target->x,target->y) < (target->w+target->h)/4.0f){//HIT TARGET AS GUIDED
				target->Damage(this,atk.damage);
				goto del;
				}

		}
		else{//DUMBFIRE
			if(p->x < 0 || p->x > map->width || p->y < 0 || p->y > map->height || dist(x,y,p->x,p->y) > atk.range){
				goto del;
			}
			p->x = p->x+(float)sin(p->ang*PI/180.0)*ScaleTime(p->inf->vel);
			p->y = p->y-(float)cos(p->ang*PI/180.0)*ScaleTime(p->inf->vel);
			int zon = ZoneIndex(pointCurZone(p->x,p->y));
			if(zon >= 0){
				linkedEnt* le = ent_lists[zon].node;
				Entity* ent;
				while(le != nullptr){
					ent = le->val;
					if(ent->enemy != enemy && dist(p->x,p->y,ent->x,ent->y) <= (ent->w+ent->h)/4.0f){
						ent->Damage(this,atk.damage);
						goto del;
					}
					le = le->nxt;
				}
			}
		}

		lp = lp->nxt;
		continue;
del:
		if(lp->prv != nullptr)
			lp->prv->nxt = lp->nxt;
		if(lp->nxt != nullptr)
			lp->nxt->prv = lp->prv;
		if(atk.projlist == lp)
			if(lp->nxt != nullptr)
				atk.projlist = lp->nxt;
			else
				atk.projlist = nullptr;
		ProjectileList* lptmp = lp;
		lp = lp->nxt;
		delete lptmp;
		continue;
	}
}

void Entity::Think(){
	//PROCESS PROJECTILES
	ProcessProjectiles();

	if(!active)
		if(hp == hpmax)
			active = true;
		else
			return;

	if(OnThink != nullptr)
		OnThink(this);
}

void Entity::Delete(){
	//REMOVE ALL TRACES OF EXISTENCE
	if(zone >= 0)
		ent_lists[zone].del(this);

	ent_list->del(this);

	linkedEnt* le = ent_list->node;
	while(le != nullptr){
		if(le->val->target == this)
			le->val->target = nullptr;
		le = le->nxt;
	}

	delete this;
}

Entity::Entity(EntityTemplate* et, int xt, int yt){
	//DIFFICULTY
	float hpmul = 1.0f;
	float dmgmul = 1.0f;
	float spdmul = 1.0f;

	if(et->enemy){
		hpmul = getVar("hpmul");
		dmgmul = getVar("dmgmul");
		spdmul = getVar("spdmul");
	}
	ent_list->add(this);
	name = et->name;
	tooltip = et->tooltip;
	x = (float)xt;
	y = (float)yt;
	w = et->w;
	h = et->h;
	ang = et->ang;
	tex = et->tex;
	activetex = et->activetex;
	col = et->col;
	hp = et->hp*hpmul;
	hpmax = et->hpmax*hpmul;
	armor = et->armor;
	speed = et->speed*spdmul;
	zone = -1;
	dest = -1;
	target = nullptr;
	enemy = et->enemy;

	upgradeEnt = et->upgradeEnt;

	active = true;

	atk = et->atk;
	atk.damage *= dmgmul;

	OnDraw = et->OnDraw;
	OnThink = et->OnThink;
	OnAttack = et->OnAttack;
	OnTakeDamage = et->OnTakeDamage;
	OnTakeHeal = et->OnTakeHeal;
	OnDealDamage = et->OnDealDamage;
	OnKillEnt = et->OnKillEnt;
	OnDeath = et->OnDeath;
	CalcZone();

	data = et->data;
}

EntityTemplate::EntityTemplate(){
	name = "unnamed";
	tooltip = "no tooltip";
	w = 10;
	h = 10;
	tex = TextureInfo();
	activetex = -1;
	col = color(1.0f,1.0f,1.0f);
	hp = 100.0f;
	hpmax = 100.0f;
	ang = 0.0;
	armor = 0.0f;
	speed = 1.0f;
	enemy = true;

	upgradeEnt = nullptr;

	atk = AttackInfo(10.0f,30.0f,2.0f);

	OnDraw = &ENT_DRAWS::Default;
	OnThink = &ENT_THINKS::DefaultEnemy;
	OnAttack = &ENT_ATTACKS::Default;
	OnTakeDamage = &ENT_TAKEDAMAGES::Default;
	OnTakeHeal = nullptr;
	OnDealDamage = nullptr;
	OnKillEnt = nullptr;
	OnDeath = nullptr;

	data = std::map<char*, float>();
}

EntityTemplate* loadEntity(char* path){
	std::ifstream ifs = std::ifstream();
	EntityTemplate* tmp = new EntityTemplate();
	ifs.open(path,ifs.in|ifs.binary);

	tmp->name = readString(&ifs);
	tmp->tooltip = readString(&ifs); //UNIMPLIMENTED IN CREATOR
	tmp->w = readCmpInt(&ifs);
	tmp->h = readCmpInt(&ifs);
	tmp->hp = (float)readCmpFlt(&ifs);
	tmp->hpmax = (float)readCmpFlt(&ifs);
	tmp->armor = (float)readCmpFlt(&ifs);
	tmp->speed = (float)readCmpFlt(&ifs);
	tmp->enemy = ifs.get() != 0;
	tmp->tex.base = loadTexture(readString(&ifs));
	if(ifs.get()!=0)
		tmp->tex.attack = loadTexture(readString(&ifs));
	if(ifs.get()!=0)
		tmp->tex.move = loadTexture(readString(&ifs));
	if(ifs.get()!=0)
		tmp->tex.die = loadTexture(readString(&ifs));
	if(ifs.get()!=0)
		tmp->tex.misc1 = loadTexture(readString(&ifs));
	if(ifs.get()!=0)
		tmp->tex.misc2 = loadTexture(readString(&ifs));
	tmp->col.r = (float)readCmpFlt(&ifs);
	tmp->col.g = (float)readCmpFlt(&ifs);
	tmp->col.b = (float)readCmpFlt(&ifs);
	tmp->col.a = (float)readCmpFlt(&ifs);
	tmp->OnDraw = ENT_DRAWS::list[ifs.get()];
	tmp->OnTakeDamage = ENT_TAKEDAMAGES::list[ifs.get()];
	tmp->OnAttack = ENT_ATTACKS::list[ifs.get()];
	tmp->OnTakeHeal = ENT_TAKEHEALS::list[ifs.get()];
	tmp->OnDealDamage = ENT_DEALDAMAGES::list[ifs.get()];
	tmp->OnKillEnt = ENT_KILLENTS::list[ifs.get()];
	tmp->OnDeath = ENT_DEATHS::list[ifs.get()];
	tmp->OnThink = ENT_THINKS::list[ifs.get()];

	ifs.close();
	return tmp;
}

void UpgradeEntity(Entity* e, EntityTemplate* et){
	if(!canAfford(et->rescost))
		return;

	deductResource1(et->rescost);

	float hpmul = 1.0f;
	float dmgmul = 1.0f;
	float spdmul = 1.0f;

	if(et->enemy){
		hpmul = getVar("hpmul");
		dmgmul = getVar("dmgmul");
		spdmul = getVar("spdmul");
	}

	e->name = et->name;
	e->tooltip = et->tooltip;
	e->w = et->w;
	e->h = et->h;
	e->ang = et->ang;
	e->tex = et->tex;
	e->activetex = et->activetex;
	e->col = et->col;
	e->hp = et->hp*hpmul*(e->hp/e->hpmax);
	e->hpmax = et->hpmax*hpmul;
	e->armor = et->armor;
	e->speed = et->speed*spdmul;
	e->target = nullptr;
	e->enemy = et->enemy;

	e->upgradeEnt = et->upgradeEnt;

	e->active = true;

	e->atk = et->atk;
	e->atk.damage *= dmgmul;

	e->OnDraw = et->OnDraw;
	e->OnThink = et->OnThink;
	e->OnAttack = et->OnAttack;
	e->OnTakeDamage = et->OnTakeDamage;
	e->OnTakeHeal = et->OnTakeHeal;
	e->OnDealDamage = et->OnDealDamage;
	e->OnKillEnt = et->OnKillEnt;
	e->OnDeath = et->OnDeath;
}
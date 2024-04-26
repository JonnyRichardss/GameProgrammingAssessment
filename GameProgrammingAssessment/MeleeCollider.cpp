#include "MeleeCollider.h"
#include "GameScene.h"
int MeleeCollider::nextID = 0;
MeleeCollider::MeleeCollider(GameObject* _parent,std::string _name,float _offset, int w, int h, float lifetimeSeconds,float _damage)
{
	parent = _parent;
	name = _name;
	facing = parent->GetFacing();
	offset = _offset;
	position = parent->GetPos() + Vector2::RotateAroundOrigin(Vector2::up(), facing);
	BoundingBox = Vector2(w, h);
	lifetime = FRAME_CAP * lifetimeSeconds;
	damage = _damage;
	ID = nextID++;
}

void MeleeCollider::Init()
{
	collisionTags.push_back("MeleeAttack");
	shown = false;
}

void MeleeCollider::InitVisuals()
{
	if (DEBUG_DRAW_MELEES) {
		visuals->LoadTexture("MeleeDebug", ".png");
		SDL_Texture* Tex = visuals->GetTexture();
		SDL_Rect DefaultRect = BBtoDestRect();
		visuals->UpdateDestPos(&DefaultRect);
		shown = true;
	}
}

GameObject* MeleeCollider::GetParent()
{
	return parent;
}

float MeleeCollider::GetDamage()
{
	return damage;
}

int MeleeCollider::GetID()
{
	//ID is used by the damage receiver to check if it has already taken damage from this attack
	return ID;
}

bool MeleeCollider::Update()
{
	//post-decrement accesses THEN decrements so if lifetime == 1 it will be alive this frame and gone the next
	//not likely to be important but it WILL register collision on the frame that it is destroyed since collision is in preupdate (for mainscene)
	if (lifetime-- <= 0) {
		//this very well may crash idk what happens if an object calls code that deletes it
		scene->DeferredDeregister(this);
		return false;
	}
	//else exist
	facing = parent->GetFacing();
	Vector2 offsetVec = Vector2::RotateAroundOrigin(Vector2::up(), facing) * offset;
	offsetVec.x *= -1;
	position = parent->GetPos() + offsetVec;
	return true;
}

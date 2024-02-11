#include "RenderableComponent.h"

RenderableComponent::RenderableComponent()
{
	texture = nullptr;
	destination_pos = nullptr;
	source_pos = nullptr;
}

RenderableComponent::RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos) : RenderableComponent()
{
	//might want to make these into copies so the renderableComponent "owns" the data so they can be safely deleted whenever
	//that WOULD mean the texture has to be re-rendered into a new texture which is fun
	texture = _texture;
	destination_pos = _destination_pos;
	//source pos can be optionally null - dest pos can too but at that point itd render fullscreen so prob best to just get a rect of the screen instead
}

RenderableComponent::RenderableComponent(SDL_Texture* _texture, SDL_Rect* _destination_pos, SDL_Rect* _source_pos) : RenderableComponent(_texture,_destination_pos)
{
	source_pos = _source_pos;
}

RenderableComponent::~RenderableComponent()
{
	//this makes sense to me but apparently something is wrong with it - i might be leaking memory atm
	// 
	//SDL_DestroyTexture(texture);
	//delete destination_pos;
	//delete source_pos;
}

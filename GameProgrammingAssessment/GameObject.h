#ifndef USE_GAMEOBJECT
#define USE_GAMEOBJECT
#include "RenderableComponent.h"
#include "RenderEngine.h"
#include "GameMath.h"
#include "GameClock.h"
#include "ColourRGBA.h"
#include <string>
class GameEngine; //forward definition to prevent circular includes in header
class GameScene;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	bool UpdateAndRender(RenderableComponent*& render);
	
	void Hide();
	void Show();
	void ToggleVisibility();
	virtual void Init() = 0;
	virtual void InitVisuals() = 0;
	void SetOwner(GameScene* owner);
	float GetFacing();
	void DrawBoundingBox();
	bool GetStaticStatus();
	void MoveVisuals();
	std::string GetName();
	Vector2 GetPos();
	Vector2 GetVelo();
	Vector2 GetBB();
	JRrect GetCorners();
protected:
	virtual void Update() = 0;
	
	int windowWidth, windowHeight;
	std::string name;
	float facing;
	Vector2 position;
	Vector2 velocity;
	Vector2 BoundingBox;
	JRrect corners;
	SDL_Rect BBtoDestRect();
	JRrect BBtoGameRect();
	void GetWindowParams();
	bool shown;
	bool is_static = false;
	GameLogging* logging;
	RenderEngine* renderer;
	//GameEngine* engine;
	GameScene* scene;
	GameClock* clock;
	SDL_Window* window;
	SDL_Renderer* renderContext;
	RenderableComponent* visuals;
};
#endif // !USE_GAMEOBJECT


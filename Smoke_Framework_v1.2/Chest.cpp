#include "Chest.h"
#include "Engine_Core.h"

Chest::Chest()
{
	_itemType = ITEM_TYPES::DEFAULT_NONE;
	_inInventory = false;

	// Default hitbox
	hitBox.Initialize(0, 0, 0, 0);
}


Chest::~Chest()
{

}


void Chest::Initialize(float posX, float posY, float rotationInRadians)
{
	_itemType = ITEM_TYPES::CHEST;

	// Set up renderer
	Renderer.Initialize(1.0f, 1.0f, 16, 16, 12, 7, 7, 0, 0, rotationInRadians, posX, posY, "misc_things.png");

	// Initialize hitbox
	hitBox.Initialize(posX, posY, Renderer.GetAdjustedWidth(), Renderer.GetAdjustedHeight());
}


void Chest::Update(float deltaTime)
{

}


void Chest::HandleEvent(IEvent *e)
{

}


void Chest::Render()
{
	if (!_inInventory)
		Renderer.Render();
}


Vector2 Chest::GetTilePos()
{
	int currentCol = Renderer.GetPos().GetX() / TILE_SIZE_X;
	int currentRow = Renderer.GetPos().GetY() / TILE_SIZE_Y;

	Vector2 tilePos = Vector2(currentCol, currentRow);

	return tilePos;
}
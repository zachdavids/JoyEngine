#include "Level.h"
#include "Tile.h"

Engine::Level::Level()
{
	//TODO remove placeholder level
	Editor::Tile test;
	test.m_Type = 1;
	test.m_Decor = 0;
	test.m_Actor = 0;
	m_CurrentMap.AddTile(test);
}

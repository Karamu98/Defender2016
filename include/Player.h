////////////////////////////////////////////////////////////
// File: <Player.h>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "UI.h"
#include "Enemy.h"

class oPlayer
{

private:

	float fRespawnTimer = 3.f; // To be subtracted from with Delta Time
	float fRespawnTime = 3.f; // Time in seconds until the player is respawned



public:

	int iSprite = 0; // Hold Sprite ID
	bool bIsLeft = false; // Holds directional state
	bool bIsAlive = true; // Holds players life state

	void MovePlayer(int *a_iBackground, oEnemy *a_ClassEnemy, int *a_iEnemyAmount); // Passing the correct sprite to manipulate with input from the player
	void InitialisePlayer(int a_iScreenWidth, int a_iScreenHeight); // Initialises player
	void Die(); // Self explanitory...
	int Respawn(oUI *a_UI); // Respawns player
	float GetPlayerPosition(bool bXpos);

};


#endif
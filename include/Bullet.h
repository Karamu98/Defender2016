////////////////////////////////////////////////////////////
// File: <CBullet.h>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#ifndef _BULLET_H_
#define _BULLET_H_
#include "Player.h"


class oBullet
{



private:

	struct Bullet
	{
		float fxPos = 512.f; // Holds xPos of the bullet
		float fyPos = 512.f; // Holds yPos of the bullet
		bool bActive = false; // Holds the bullets state
		bool bDrawn = false; // Holds the bullets draw state
		int iSpriteID = 0; // Holds Sprite ID
		bool bGoingLeft = false; // Holds direction state
	};

	int iSpeed = 20; // How much to add to the bullet when update is called
	float iFireDelayTimer = 0.f; // This will be subtracted from to give delay
	float iFireDelayTime = 0.2f; // Time between shots in seconds


public:

	void Initialise(); // Initialise bullets
	void Update(oBullet *a_Bullet, oPlayer *a_Player); // Used to check if the bullet is on screen and move any visible bullets
	void Draw(); // Used to draw active bullets in their position
	void Fire(oPlayer *a_Player); // Used to reposition and set a bullets state to the player
	void StopAll();

	Bullet Bullets[10]; // Array of bullets [NEEDS TO BE CHANGED]
};




#endif
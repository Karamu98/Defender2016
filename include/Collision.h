////////////////////////////////////////////////////////////
// File: <Collision.h>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "Enemy.h"
#include "Bullet.h"
#include "UI.h"

class oCollision
{
public:
	void TestPhysicalCollision(oPlayer *a_Player, oEnemy *a_Enemy, int a_iEnemyAmount); // Comparing position of two sprites to test for collision
	void TestBulletCollision(oBullet *a_Bullets, oEnemy *a_Enemy, int a_iEnemyAmount, oPlayer *a_Player, oUI *a_UI); // COMPARE BULLET X & Y TO SHIP/ ENEMY AND TRIGGER APPROPIATE FUNCTIONS. NEEDS ANOTHER INPUT
};



#endif
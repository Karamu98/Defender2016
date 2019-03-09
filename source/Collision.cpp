////////////////////////////////////////////////////////////
// File: <Collision.cpp>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#include "Collision.h"
#include "UGFW.h"
#include <iostream>


void oCollision::TestPhysicalCollision(oPlayer *a_Player, oEnemy *a_Enemy, int a_iEnemyAmount)
{
	for (int i = 0; i <= a_iEnemyAmount; i++)
	{
		float enemyX, enemyY = 0; // Our varibles that update each frame
		UG::GetSpritePosition(a_Enemy->EnemyArray[i].iSpriteID, enemyX, enemyY); // Setting the varibles with the x and y position of the sprite "iShip"


		if ((a_Player->GetPlayerPosition(true) + 32) > (enemyX - 15) && (a_Player->GetPlayerPosition(true) - 32) < (enemyX + 15)) // Test X first as it will happen less frequent (Map is longer on the x axis than it is taller on the y axis)
		{
			if ((a_Player->GetPlayerPosition(false) + 10) > (enemyY - 15) && (a_Player->GetPlayerPosition(false) - 10) < (enemyY + 15)) // Test Y 
			{
				if (a_Player->bIsAlive)
				{
					a_Enemy->Die(i); // Call Die in Enemy class
					a_Player->Die(); // Call Die in Player class
				}


				// Both tests succeed
			}
			else
			{
				// First test pass, second test failed
			}
		}
		else
		{
			// First test failed, don't run second test
		}
	}

}

void oCollision::TestBulletCollision(oBullet *a_Bullets, oEnemy *a_Enemy, int a_iEnemyAmount, oPlayer *a_Player, oUI *a_UI)
{
	for (int i = 0; i <= 9; i++) // Loop 10 times
	{
		if (a_Bullets->Bullets[i].bActive == true) // Check if the bullets active state is true
		{
			for (int j = 0; j <= a_iEnemyAmount; j++) // Loop though enemies
			{
				if (a_Bullets->Bullets[i].fxPos > (a_Enemy->EnemyArray[j].xPos - 31) && a_Bullets->Bullets[i].fxPos < (a_Enemy->EnemyArray[j].xPos + 31)) // If active bullets x pos is within range of enemies x pos
				{
					if (a_Bullets->Bullets[i].fyPos > (a_Enemy->EnemyArray[j].yPos - 31) && a_Bullets->Bullets[i].fyPos < (a_Enemy->EnemyArray[j].yPos + 31))  // If active bullets y pos is within range of enemies y pos
					{
						// Both test pass
						a_Enemy->Die(j); // Call Die in enemy class
						a_UI->AddScore(100); // Award 100 score to player
						a_Bullets->Bullets[i].bActive = false; // Set active bullet to not active
					}
					else
					{
						// First test pass second fail
					}
				}
				else
				{
					// Both fail
				}
			}
		}
	}
	// Test collision of bullets against the enemies and players

}


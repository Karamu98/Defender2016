////////////////////////////////////////////////////////////
// File: <Enemy.h>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Directions.h"


class oEnemy
{
private:
	
	struct Sprite
	{
		int iSpriteID = 0; // Holds sprite ID
		float xPos = -100.0f; // Holds X position
		float yPos = -100.0f; // Holds Y position

		int iSpeed = 2; // Speed of enemies

		bool bIsOnScreen = false; // Holds position state

		float fTimer = 2.f; // The varible that will be manipulated with delta time
		float fFrequency = 2.f; // The minimum value the timer can be
		float fBuffer = 5.f; // Random value between 0 and this number will be added to the timer

		RandomDirections Direction = NORTH; // Initialise which direction each ship moves



	};


public:



	void Die(int a_index); // Does appopiate actions to remove the enemy
	void Move(bool a_bIsLeft, int a_amount); // Check if on screen and then move based on player position
	void Spawn(int a_amount); // Spawns given amount of ships within map boundries
	void SetAllEnemySpeed(int a_iSpeed, int a_amount); // Sets all sprites speed to a given index 
	int GetEnemySpeed(int a_index); // Takes index and returns speed
	void RenderCheck(int a_iEnemyAmount); // Called each frame to check if an enemy should be rendered
	void Destroy(int a_enemyCount); // Destroy all enemies and positional data
	void AIMove(int a_amount); // Moves ships around randomly
	void AIUpdateDirection(int a_amount); // Updates the directions ships will move
	void AIInitialiseInitialDirection(int a_amount);

	Sprite EnemyArray[50]; // FIND ANOTHER WAY OF STORING. Arrays size can't be changed  // Array to store enemies


};
#endif
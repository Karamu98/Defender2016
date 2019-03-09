////////////////////////////////////////////////////////////
// File: <Enemy.cpp>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#include "Enemy.h"
#include "UGFW.h"
#include <iostream>
#include <math.h>
#include <ctime>


#include "windows.h"
#pragma comment(lib, "winmm.lib")



void oEnemy::Die(int a_index)
{
	UG::MoveSprite(EnemyArray[a_index].iSpriteID, -100, -100); // Move enemy out of the way [Crude, I know. I'm thinking of another way]
	EnemyArray[a_index].xPos = 0; // Set Position varibles [Also Crude]
	EnemyArray[a_index].yPos = 0; // Set Position varibles [Also Crude]
	UG::DestroySprite(EnemyArray[a_index].iSpriteID); // Destroy specific enemy
	PlaySound(TEXT("./sounds/EnemyDie.wav"), NULL, SND_NOSTOP | SND_ASYNC);
}

void oEnemy::Move(bool a_bIsLeft, int a_amount) 
{
	if (a_bIsLeft == true) // If is true ('Player moving left')
	{
		for (int i = 0; i < a_amount; i++) // Loop equal to enemy amount
		{
			UG::MoveSprite(EnemyArray[i].iSpriteID, EnemyArray[i].xPos += 15, EnemyArray[i].yPos); // Move all spites in array + 15 on the x axis
		}
	}
	else
	{
		for (int i = 0; i < a_amount; i++)
		{
			UG::MoveSprite(EnemyArray[i].iSpriteID, EnemyArray[i].xPos -= 15, EnemyArray[i].yPos); // Move all spites in array + 15 on the x axis
		}
	}
}

void oEnemy::Spawn(int a_amount) // Will be called once at the start of a round
{
	srand(time(0));
	for (int i = 0; i < a_amount; i++) 
	{
		if (i == 0)
		{
			EnemyArray[i].xPos = 64.0f + (rand() % 3968); // Sets a random number between 64 and 4032 (Border of 64px)
			EnemyArray[i].yPos = 64.0f + (rand() % 640); // Sets a random number between 64 and 704 (Border of 64px)

			EnemyArray[i].iSpriteID = UG::CreateSprite("./images/Enemy.png", 64, 64, true); // Creates and asigns sprites with ID's through the array
			UG::MoveSprite(EnemyArray[i].iSpriteID, EnemyArray[i].xPos, EnemyArray[i].yPos); // Moves all sprite's in array to their X and Y position randomly generated
			UG::SetSpriteLayer(EnemyArray[i].iSpriteID, 2);

			if (EnemyArray[i].xPos <= (0 - 70) || EnemyArray[i].xPos >= (1024 + 70))
			{
				EnemyArray[i].bIsOnScreen = false; // Sets boolean value to false to indicate if sprite needs to be rendered
			}
			else
			{
				UG::DrawSprite(EnemyArray[i].iSpriteID); // Draws all sprites on screen
				EnemyArray[i].bIsOnScreen = true; // Sets boolean value to false to indicate if sprite needs to be rendered
			}


			std::cout << "Sprite ID: " << EnemyArray[i].iSpriteID << std::endl << "Sprite X: " << EnemyArray[i].xPos << std::endl << "Sprite Y: " << EnemyArray[i].yPos << std::endl << std::endl; // [DEBUG]
		}

		EnemyArray[i].xPos = 64.0f + (rand() % 3968); // Sets a random number between 64 and 4032 (Border of 64px)
		EnemyArray[i].yPos = 64.0f + (rand() % 640); // Sets a random number between 64 and 704 (Border of 64px)

		EnemyArray[i].iSpriteID = UG::DuplicateSprite(EnemyArray[0].iSpriteID); // Creates and asigns sprites with ID's through the array
		UG::MoveSprite(EnemyArray[i].iSpriteID, EnemyArray[i].xPos, EnemyArray[i].yPos); // Moves all sprite's in array to their X and Y position randomly generated
		UG::SetSpriteLayer(EnemyArray[i].iSpriteID, 2);

		if (EnemyArray[i].xPos <= (0 - 70) || EnemyArray[i].xPos >= (1024 + 70))
		{
			EnemyArray[i].bIsOnScreen = false; // Sets boolean value to false to indicate if sprite needs to be rendered
		}
		else
		{
			UG::DrawSprite(EnemyArray[i].iSpriteID); // Draws all sprites on screen
			EnemyArray[i].bIsOnScreen = true; // Sets boolean value to false to indicate if sprite needs to be rendered
		}


		std::cout << "Sprite ID: " << EnemyArray[i].iSpriteID << std::endl << "Sprite X: " << EnemyArray[i].xPos << std::endl << "Sprite Y: " << EnemyArray[i].yPos << std::endl << std::endl; // [DEBUG]

	}

}

void oEnemy::SetAllEnemySpeed(int a_iSpeed, int a_amount) // Takes speed to be set and applies it to given number of enemies in the array
{
	for (int i = 0; i <= a_amount; i++)
	{
		EnemyArray[i].iSpeed = a_iSpeed; // Sets speed of all sprites in array to given value
	}
	std::cout << "Speed set to: " << a_iSpeed; // [DEBUG]
}

int oEnemy::GetEnemySpeed(int a_index) // Requires index
{
	return EnemyArray[a_index].iSpeed; // Uses value to point to index in array and sets speed to that sprite
}

void oEnemy::RenderCheck(int a_iEnemyAmount) 
{
	for (int i = 0; i < a_iEnemyAmount; i++) // Loop equal to the amount of enemies
	{
		if (EnemyArray[i].xPos <= -70 || EnemyArray[i].xPos >= 1094) // Check if the enemies x pos is equal to or lower/higher than -70/1094 (OFF SCREEN)
		{
			if (EnemyArray[i].bIsOnScreen == true) // If they are currently set as active too
			{
				EnemyArray[i].bIsOnScreen = false; // Set inactive
				UG::StopDrawingSprite(EnemyArray[i].iSpriteID); // And stop drawing them
				std::cout << "Stop" << std::endl; // [DEBUG]
			}
		}
		else if (EnemyArray[i].xPos > -70 || EnemyArray[i].xPos < 1094) // Check if the enemies x pos is reverse to previous (ON SCREEN)
		{
			if (EnemyArray[i].bIsOnScreen == false) // If they're not active
			{
				EnemyArray[i].bIsOnScreen = true; // Set active
				UG::DrawSprite(EnemyArray[i].iSpriteID); // And Draw them
				std::cout << "Draw" << std::endl; // [DEBUG]
			}
		}
	}
}

void oEnemy::Destroy(int a_enemyCount)
{
	for (int i = 0; i <= a_enemyCount; i++) // Loop equal to the amount of enemies
	{
		UG::StopDrawingSprite(EnemyArray[i].iSpriteID); // Stop drawing each enemy
		UG::DestroySprite(EnemyArray[i].iSpriteID); // Destroy Sprites
	}
}

void oEnemy::AIUpdateDirection(int a_amount)
{
	for (int i = 0; i < a_amount; i++) // Loop 
	{
		srand(time(0)); // Seed random time

		if (EnemyArray[i].bIsOnScreen) // Check if the enemy is on screen
		{
			EnemyArray[i].fTimer -= UG::GetDeltaTime(); // If it is, start reducing the timer with delta time
			if (EnemyArray[i].fTimer <= 0.f) // When the timer reaches zero
			{
				EnemyArray[i].fTimer = EnemyArray[i].fFrequency + (rand() % 5); // Reset the timer to a time between 5 and 10 seconds

				float ex, ey = 0.f; // Varibles to store enemy position
				UG::GetSpritePosition(EnemyArray[i].iSpriteID, ex, ey); // Setting the varibles

				EnemyArray[i].Direction = static_cast<RandomDirections>(rand() % 8); // Get a random number between 0 and 7

				
			}
		}
	}
}

void oEnemy::AIInitialiseInitialDirection(int a_amount)
{
	srand(time(0));
	for (int i = 0; i < (a_amount); i++)
	{
		EnemyArray[i].Direction = static_cast<RandomDirections>(rand() % 8); // Get a random number between 0 and 7
	}
}

void oEnemy::AIMove(int a_amount)
{
	for (int i = 0; i < a_amount; i++) // Loop though all enemies
	{
		if (EnemyArray[i].bIsOnScreen) // If enemy is on screen
		{
			UG::GetSpritePosition(EnemyArray[i].iSpriteID, EnemyArray[i].xPos, EnemyArray[i].yPos); // Get their position and set to Variable
			switch (EnemyArray[i].Direction) // Based on the enemies direction variable
			{


			case NORTH:
			{
				if (EnemyArray[i].yPos > (768 - 32)) // If Enemies y pos is higher than 1024-32
				{
					EnemyArray[i].Direction = static_cast<RandomDirections>((rand() % 3) + 4); // Set a new direction with numbers between 4 and 6 [SOUTHEAST, SOUTH, SOUTHWEST]
					break;
				}
				else
				{
					UG::MoveSprite(EnemyArray[i].iSpriteID, EnemyArray[i].xPos, (EnemyArray[i].yPos + EnemyArray[i].iSpeed)); // Move enemy based on speed and state
				}

					break; // We don't want to do all cases so break here
			}

			case NORTHEAST:
			{
				if (EnemyArray[i].yPos > (768 - 32)) // If Enemies y pos is higher than 1024-32
				{
					EnemyArray[i].Direction = static_cast<RandomDirections>((rand() % 3) + 4); // Set a new direction with numbers between 4 and 6 [SOUTHEAST, SOUTH, SOUTHWEST]
					break;
				}
				else
				{
					UG::MoveSprite(EnemyArray[i].iSpriteID, (EnemyArray[i].xPos + EnemyArray[i].iSpeed), (EnemyArray[i].yPos + EnemyArray[i].iSpeed)); // Move enemy based on speed and state
				}


				break; // We don't want to do all cases so break here
			}

			case EAST:
			{
				UG::MoveSprite(EnemyArray[i].iSpriteID, (EnemyArray[i].xPos + EnemyArray[i].iSpeed), EnemyArray[i].yPos); // Move enemy based on speed and state

				break; // We don't want to do all cases so break here
			}

			case SOUTHEAST:
			{
				if (EnemyArray[i].yPos < (0 + 32)) // If Enemies y pos is lower than 0 + 32
				{
					EnemyArray[i].Direction = static_cast<RandomDirections>(rand() % 3); // Set a new direction with numbers between 0 and 2 [NORTHWEST, NORTH, NORTHEAST]
					break;
				}
				else
				{
					UG::MoveSprite(EnemyArray[i].iSpriteID, (EnemyArray[i].xPos + EnemyArray[i].iSpeed), (EnemyArray[i].yPos - EnemyArray[i].iSpeed)); // Move enemy based on speed and state
				}

				break; // We don't want to do all cases so break here
			}

			case SOUTH:
			{
				if (EnemyArray[i].yPos < (0 + 32)) // If Enemies y pos is lower than 0 + 32
				{
					EnemyArray[i].Direction = static_cast<RandomDirections>(rand() % 3); // Set a new direction with numbers between 0 and 2 [NORTHWEST, NORTH, NORTHEAST]
					break;
				}
				else
				{
					UG::MoveSprite(EnemyArray[i].iSpriteID, EnemyArray[i].xPos, (EnemyArray[i].yPos - EnemyArray[i].iSpeed)); // Move enemy based on speed and state
				}

				break; // We don't want to do all cases so break here
			}

			case SOUTHWEST:
			{
				if (EnemyArray[i].yPos < (0 + 32)) // If Enemies y pos is lower than 0 + 32
				{
					EnemyArray[i].Direction = static_cast<RandomDirections>(rand() % 3); // Set a new direction with numbers between 0 and 2 [NORTHWEST, NORTH, NORTHEAST]
					break;
				}
				else
				{
					UG::MoveSprite(EnemyArray[i].iSpriteID, (EnemyArray[i].xPos - EnemyArray[i].iSpeed), (EnemyArray[i].yPos - EnemyArray[i].iSpeed)); // Move enemy based on speed and state
				}
				break; // We don't want to do all cases so break here
			}

			case WEST:
			{
				UG::MoveSprite(EnemyArray[i].iSpriteID, (EnemyArray[i].xPos - EnemyArray[i].iSpeed), EnemyArray[i].yPos); // Move enemy based on speed and state

				break; // We don't want to do all cases so break here
			}

			case NORTHWEST:
			{
				if (EnemyArray[i].yPos > (768 - 32)) // If Enemies y pos is higher than 1024-32
				{
					EnemyArray[i].Direction = static_cast<RandomDirections>((rand() % 3) + 4); // Set a new direction with numbers between 4 and 6 [SOUTHEAST, SOUTH, SOUTHWEST]
					break;
				}
				else
				{
					UG::MoveSprite(EnemyArray[i].iSpriteID, (EnemyArray[i].xPos - EnemyArray[i].iSpeed), (EnemyArray[i].yPos + EnemyArray[i].iSpeed)); // Move enemy based on speed and state
				}
				
				break; // We don't want to do all cases so break here
			}

			}
		}
		
	}
	
}

////////////////////////////////////////////////////////////
// File: <Player.cpp>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#include "Player.h"
#include "UGFW.h"
#include "Enumerations.h"
#include <iostream>

#include "windows.h"
#pragma comment(lib, "winmm.lib")



void oPlayer::MovePlayer(int *a_iBackground, oEnemy *a_ClassEnemy, int *a_iEnemyAmount)
{

	float xPos = 0; float yPos = 0; // The varibles we set each frame
	UG::GetSpritePosition(iSprite, xPos, yPos); // Gets ship position


	float fMapXStart = 0.0f; // The start percentage of the background image to render
	float fMapXEnd = 0.0f; // The end percentage of the background image to render
	float fMapYStart = 0.0f; // The start percentage of the background image to render
	float fMapYEnd = 0.0f; // The end percentage of the background image to render

	float fMapJump = 0.0036621; // For a new value do (0.25 / 1024) * SPEED         Current: 15


	UG::GetSpriteUVCoordinates((*a_iBackground), fMapXStart, fMapYStart, fMapXEnd, fMapYEnd); // Updates the varibles above each frame

	if (bIsAlive == true) // If player is alive, then we can move
	{

		if (UG::IsKeyDown(UG::KEY_RIGHT)) // Right Key
		{
			UG::SetSpriteUVCoordinates(iSprite, 0, 0, 0.5, 1); // Makes the ship "Flip" to face the right
			UG::SetSpriteUVCoordinates((*a_iBackground), fMapXStart + fMapJump, 0, fMapXEnd + fMapJump, 1); // "Shifting" the position of the image to render
			a_ClassEnemy->Move(false, *a_iEnemyAmount); // Called each frame to move enemies
			a_ClassEnemy->AIMove((*a_iEnemyAmount));
			bIsLeft = false; // Set directional state


		}
		else if (UG::IsKeyDown(UG::KEY_LEFT)) // Left Key
		{
			UG::SetSpriteUVCoordinates(iSprite, 0.5, 0, 1, 1); // Makes the ship "Flip" to face the right
			UG::SetSpriteUVCoordinates((*a_iBackground), fMapXStart - fMapJump, 0, fMapXEnd - fMapJump, 1); // "Shifting" the position of the image to render
			a_ClassEnemy->Move(true, (*a_iEnemyAmount)); // Called each frame to move enemies
			a_ClassEnemy->AIMove((*a_iEnemyAmount));
			bIsLeft = true; // Set directional state
		}

		if (UG::IsKeyDown(UG::KEY_UP)) // Key Up
		{
			if (yPos >= 753)
			{

			}
			else
			{
				UG::MoveSprite(iSprite, xPos, yPos + 10.f); // Move player sprite on the y axis
			}
		}

		if (UG::IsKeyDown(UG::KEY_DOWN)) // Key Down
		{
			if (yPos <= 15)
			{

			}
			else 
			{
				UG::MoveSprite(iSprite, xPos, yPos - 10.f); // Move player sprite on the y axis
			}
			
		}

		if (UG::IsKeyDown(UG::KEY_DOWN) && UG::IsKeyDown(UG::KEY_LEFT)) // Down and Left
		{
			UG::SetSpriteUVCoordinates(iSprite, 0.5, 0, 1, 1); // Makes the ship "Flip" to face the right
			UG::SetSpriteUVCoordinates((*a_iBackground), fMapXStart - fMapJump, 0, fMapXEnd - fMapJump, 1); // "Shifting" the position of the image to render
		}

		if (UG::IsKeyDown(UG::KEY_DOWN) && UG::IsKeyDown(UG::KEY_RIGHT)) // Down and Right
		{
			UG::SetSpriteUVCoordinates(iSprite, 0, 0, 0.5, 1); // Makes the ship "Flip" to face the right
			UG::SetSpriteUVCoordinates((*a_iBackground), fMapXStart + fMapJump, 0, fMapXEnd + fMapJump, 1); // "Shifting" the position of the image to render
		}

		if (UG::IsKeyDown(UG::KEY_UP) && UG::IsKeyDown(UG::KEY_LEFT)) // Up and Left
		{
			UG::SetSpriteUVCoordinates(iSprite, 0.5, 0, 1, 1); // Makes the ship "Flip" to face the right
			UG::SetSpriteUVCoordinates((*a_iBackground), fMapXStart - fMapJump, 0, fMapXEnd - fMapJump, 1); // "Shifting" the position of the image to render

		}

		if (UG::IsKeyDown(UG::KEY_UP) && UG::IsKeyDown(UG::KEY_RIGHT)) // Up and Right	
		{
			UG::SetSpriteUVCoordinates(iSprite, 0, 0, 0.5, 1); // Makes the ship "Flip" to face the right
			UG::SetSpriteUVCoordinates((*a_iBackground), fMapXStart + fMapJump, 0, fMapXEnd + fMapJump, 1); // "Shifting" the position of the image to render

		}
	}
		// End of Function
}

void oPlayer::InitialisePlayer(int a_iScreenWidth, int a_iScreenHeight)
{
	iSprite = UG::CreateSprite("./images/ShipSpriteSheet.png", 64, 64, true); // Creating the sprite for the ship 
	UG::SetSpriteUVCoordinates(iSprite, 0, 0, 0.5, 1); // Setting what part of the sprite sheet we want to use
	UG::SetSpriteLayer(iSprite, 3); // [Testing] Learning to use layers

	std::cout << "Ship ID: " << iSprite << std::endl << std::endl; // [DEBUG]

	UG::MoveSprite(iSprite, a_iScreenWidth * 0.5f, a_iScreenHeight * 0.5f); // Moving the ship to the center of the screen
}

void oPlayer::Die()
{
	bIsAlive = false; // Set alive state to false
	UG::StopDrawingSprite(iSprite); // Stop drawin player sprite
	PlaySound(TEXT("./sounds/PlayerDie.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

int oPlayer::Respawn(oUI *a_UI)
{
	if (a_UI->iPlayerLives > 0 && bIsAlive == false) // If player lives is greater than zero and they're dead, respawn them
	{
		fRespawnTimer -= UG::GetDeltaTime(); // Deduce timer

		if (fRespawnTimer < 0.f) // When timer reaches zero
		{
			UG::DrawSprite(iSprite); // Draw the sprite
			bIsAlive = true; // Set alive state to true
			fRespawnTimer = fRespawnTime; // Reset the timer
			a_UI->iPlayerLives = a_UI->iPlayerLives - 1; // Reduce player lives
		}
		return -1;
	}
	else if (a_UI->iPlayerLives <= 0 && bIsAlive == false)
	{
		return 0;
	}
	return -1;
}

float oPlayer::GetPlayerPosition(bool bXpos)
{
	float x, y = 0.f;
	UG::GetSpritePosition(iSprite, x, y);
	if (bXpos)
	{
		return x;
	}
	else
	{
		return y;
	}


}

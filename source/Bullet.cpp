////////////////////////////////////////////////////////////
// File: <Bullet.cpp>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#include "UGFW.h"
#include "Bullet.h"
#include <iostream>

#include "windows.h"
#pragma comment(lib, "winmm.lib")


void oBullet::Initialise()
{
	for (int i = 0; i <= 10; i++) // Loop 10 times
	{
		Bullets[i].iSpriteID = UG::CreateSprite("./images/Bullet.png", 16, 16); // Create sprites and sprite ID's for our bullets
		UG::MoveSprite(Bullets[i].iSpriteID, 512, 512); // Move sprites to center of the screen (Just to stop any possible bugs with bullets exiting the screen)
	}
}

void oBullet::Update(oBullet *a_Bullet, oPlayer *a_Player)
{
	iFireDelayTimer -= UG::GetDeltaTime(); // Set timer to it's current value - the delta time 

	float fplayerX = 0; // Player position x
	float fplayerY = 0; // Player position y

	UG::GetSpritePosition(a_Player->iSprite, fplayerX, fplayerY); // Set varibles above so we can move the bullet back on screen if it goes off

	for (int i = 0; i <= 10; i++) // Loop throught bullet array
	{

		if (Bullets[i].bActive == true) // Test if Bullet is active
		{

			if (a_Bullet->Bullets[i].bGoingLeft == true) // Check whoch direction the bullet will fire in
			{
				UG::MoveSprite(a_Bullet->Bullets[i].iSpriteID, (a_Bullet->Bullets[i].fxPos -= a_Bullet->iSpeed), a_Bullet->Bullets[i].fyPos); // Set the xposition to it's current - speed
			}
			else 
			{
				UG::MoveSprite(a_Bullet->Bullets[i].iSpriteID, (a_Bullet->Bullets[i].fxPos += a_Bullet->iSpeed), a_Bullet->Bullets[i].fyPos); // Set the xposition to it's current + speed
			}


			if (a_Bullet->Bullets[i].fxPos > (1024 + 70) || a_Bullet->Bullets[i].fxPos < (0 - 70)) // Check if the active bullet is still on screen
			{
				std::cout << "Bullet off screen" << std::endl << std::endl; // [DEBUG]

				UG::MoveSprite(Bullets[i].iSpriteID, fplayerX, fplayerY); // Move the bullet back to the center to stop triggering this statement
				a_Bullet->Bullets[i].bActive = false; // Notify that bullet is not active
			}
		}
	}

}

void oBullet::Draw()
{
	for(int i = 0; i <= 10; i++) // Loop throught bullet array
	if (Bullets[i].bActive == true && Bullets[i].bDrawn == false) // Draw any active bullets that haven't been drawn [DO ONCE]
	{
		Bullets[i].bDrawn = true; // Set that the bullet is now being drawn
		UG::DrawSprite(Bullets[i].iSpriteID); // Draw the bullet
	}
	else if (Bullets[i].bActive == false && Bullets[i].bDrawn == true) // Stop drawing any bullets that are being drawn but aren't acive [DO ONCE]
	{
		Bullets[i].bDrawn = false; // Notify that it's no longer being drawn
		Bullets[i].bActive = false; // Notify that it's no longer active
		UG::StopDrawingSprite(Bullets[i].iSpriteID); // Stop drawing bullet
	}
}

void oBullet::Fire(oPlayer *a_Player)
{
	if (a_Player->bIsAlive == true)
	{
		if (iFireDelayTimer < 0.f) // When it reaches below zero
		{
			iFireDelayTimer = iFireDelayTime; // Set the counter back up to its original value be subtracted from again

			for (int i = 0; i <= 10; ++i) // Loop though the array 10 times
			{
				if (Bullets[i].bActive == false) // Look for an inactive bullet in the array
				{
					if (a_Player->bIsLeft == true) // Check what direction the player is facing
					{
						Bullets[i].bGoingLeft = true; // Notify which direction the bullet will go
					}
					else
					{
						Bullets[i].bGoingLeft = false; // Notify which direction the bullet will go
					}

					float x, y = 0; // Varibles to move the bullet back to the player

					UG::GetSpritePosition(a_Player->iSprite, x, y); // Sets our variables defined above to the players x and y
					UG::MoveSprite(Bullets[i].iSpriteID, x, y); // Moves inactive bullet to player

					Bullets[i].fxPos = x; // Sets bullets x...
					Bullets[i].fyPos = y; // ... And y position 

					Bullets[i].bActive = true; // Set the inactive bullet to active...

					PlaySound(TEXT("./sounds/PlayerShoot.wav"), NULL, SND_FILENAME | SND_ASYNC);


					std::cout << "Fire!" << std::endl << std::endl; // [DEBUG]
					break; // We only want to do this once so break from the for loop
				}
			}
		}
	}
	
}

void oBullet::StopAll()
{
	for (int i = 0; i < 11; i++)
	{
		UG::StopDrawingSprite(Bullets[i].iSpriteID);
		Bullets[i].bActive = false;
		Bullets[i].bDrawn = false;
	}
}

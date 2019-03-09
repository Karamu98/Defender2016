////////////////////////////////////////////////////////////
// File: <main.cpp>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#include "Enumerations.h"
#include "Enemy.h"
#include "UGFW.h" 
#include "Player.h"
#include "Bullet.h"
#include "Collision.h"
#include "UI.h"
#include <iostream>

#include "windows.h"
#pragma comment(lib, "winmm.lib") // Needs work on all instances used (https://goo.gl/D8Qazx)

typedef enum GameStates
{

	MENUPLAY,
	MENUHIGHSCORE,
	MENUEXIT,
	HIGHSCORE,
	GAMEPLAY,
	GAMEOVER,
	SPLASHSCREEN
}GameState;



int g_iEnemyAmount = 10; // TEMP: Need to find another way of sorting enemies in an 'array' so that the size can be modified

int main(int argv, char* argc[])
{
	if (UG::Create(1024, 768, false, "Defender", 100, 100))
	{

		oEnemy ClassEnemy; // Creating an object of the class
		oPlayer ClassPlayer; // Creating an object of the class
		oBullet ClassBullet; // Creating an object of the class
		oCollision ClassCollision; // Creating an object of the class
		oUI ClassUI; // Creating an object of the class
		int iBackGround = 0;

		float fSplashTimer = 7.f;

		int iScreenWidth, iScreenHeight = 0; // Using the framework to create and set the varibles equal to the screen width and height
		UG::GetScreenSize(iScreenWidth, iScreenHeight); // Set the varibles here

		int iMenuScreen = UG::CreateSprite("./images/MenuScreenSpriteSheet.png", 1024, 768, false); // Initialises the menu screen 

		int iSpashScreen = UG::CreateSprite("./images/SplashScreen.png", 1024, 768, false); // Initialises the splash screen 
		UG::MoveSprite(iSpashScreen, 0, 768);
		UG::DrawSprite(iSpashScreen);


		GameState currentState = SPLASHSCREEN; // Set the menu state to MENUPLAY

		UG::AddFont("./fonts/invaders.fnt"); // Add the font to the game
			
		do
		{
			switch (currentState) // Switch depending on the "currentState"'s value is
			{

			case SPLASHSCREEN:
			{
				fSplashTimer -= UG::GetDeltaTime();

				if (fSplashTimer <= 0)
				{
					UG::StopDrawingSprite(iSpashScreen);
					UG::MoveSprite(iSpashScreen, -200, -200);
					UG::DestroySprite(iSpashScreen);
					currentState = MENUPLAY;
					UG::MoveSprite(iMenuScreen, 0, 768); // Moves the sprite to the top left
					UG::SetSpriteUVCoordinates(iMenuScreen, 0, 0, 0.5, 0.5); // Renders the bottom left portion of the image
					UG::DrawSprite(iMenuScreen); // Draw the menu
				}

			}

			case MENUPLAY:
			{


				if (UG::IsKeyDown(UG::KEY_ENTER))
				{
					UG::StopDrawingSprite(iMenuScreen); // Stop drawing the menu
					UG::DestroySprite(iMenuScreen);
					UG::ClearScreen(); // Clear the screen
					currentState = GAMEPLAY; // Set the currentState to GAMEPLAY

					iBackGround = UG::CreateSprite("./images/Background.png", 1024, 768, false); // Creates a sprite ID for the background image at size (1024, 768) Doesn't draw from center
					UG::SetSpriteLayer(iBackGround, 0);
					UG::MoveSprite(iBackGround, 0, 768); // Moves image to top left
					UG::DrawSprite(iBackGround); // Draw the game background
					UG::SetSpriteUVCoordinates(iBackGround, 0, 0, 0.25, 1); // Set UVCoords to render a quater of the image

					ClassBullet.Initialise(); // Initialises player bullets
					ClassPlayer.InitialisePlayer(iScreenWidth, iScreenHeight); // Initialises the player

					UG::DrawSprite(ClassPlayer.iSprite); // Draw the ship
					ClassEnemy.Spawn(g_iEnemyAmount); // Spawn the amount of enemies defined in g_iEnemyAmount
					ClassEnemy.AIInitialiseInitialDirection(g_iEnemyAmount);
					ClassUI.iPlayerLives = ClassUI.iMaxLives; // Set lives back to maximum
					ClassPlayer.bIsAlive = true; // Notifies that the player is alive
					PlaySound(TEXT("./sounds/Confirm.wav"), NULL, SND_FILENAME | SND_SYNC); 
				}


				if (UG::IsKeyDown(UG::KEY_DOWN))
				{
					UG::SetSpriteUVCoordinates(iMenuScreen, 0.5, 0, 1, 0.5); // Displays the bottom right potion of the image
					currentState = MENUHIGHSCORE; // Set the state to MENUHIGHSCORE
					PlaySound(TEXT("./sounds/Select.wav"), NULL, SND_FILENAME | SND_SYNC);

				}


				if (UG::IsKeyDown(UG::KEY_UP))
				{
					UG::SetSpriteUVCoordinates(iMenuScreen, 0, 0.5, 0.5, 1); // Displays the top left potion of the image
					currentState = MENUEXIT; // Set currentState to MENUEXIT
					PlaySound(TEXT("./sounds/Select.wav"), NULL, SND_FILENAME | SND_SYNC);
				}


				UG::ClearScreen(); // Clear all drawn sprites
				break; // Break so we don't continue down the statements
			}

			case MENUHIGHSCORE:
			{

				if (UG::IsKeyDown(UG::KEY_ENTER))
				{
					UG::SetSpriteUVCoordinates(iMenuScreen, 0.5, 0.5, 1, 1); // Displays top right portion of the image
					ClassUI.ReadScores();
					ClassUI.DrawHighScores();
					currentState = HIGHSCORE; // Set currentState to HIGHSCORE
					PlaySound(TEXT("./sounds/Confirm.wav"), NULL, SND_FILENAME | SND_SYNC);
				}

				if (UG::IsKeyDown(UG::KEY_DOWN))
				{
					UG::SetSpriteUVCoordinates(iMenuScreen, 0, 0.5, 0.5, 1); // Displays the bottom right portion of the image
					currentState = MENUEXIT; // Set currentState to MENUEXIT
					PlaySound(TEXT("./sounds/Select.wav"), NULL, SND_FILENAME | SND_SYNC);

				}

				if (UG::IsKeyDown(UG::KEY_UP))
				{
					UG::SetSpriteUVCoordinates(iMenuScreen, 0, 0, 0.5, 0.5); // Displays the bottom left portion of the image
					currentState = MENUPLAY; // Set currentState to MENUPLAY
					PlaySound(TEXT("./sounds/Select.wav"), NULL, SND_FILENAME | SND_SYNC);
				}


				UG::ClearScreen(); // Clears all drawn sprites
				break; // Break so we don't continue down the statements
			}

			case HIGHSCORE:
			{
				ClassUI.DrawHighScores();

				if (UG::IsKeyDown(UG::KEY_ESCAPE))
				{
					UG::SetSpriteUVCoordinates(iMenuScreen, 0.5, 0, 1, 0.5); // Displays the bottom right of the image
					currentState = MENUHIGHSCORE; // Set currentState to MENUHIGHSCORE
					PlaySound(TEXT("./sounds/Cancel.wav"), NULL, SND_FILENAME | SND_SYNC);
				}

				UG::ClearScreen(); // Clears all drawn sprites
				break; // Break so we don't continue down the statements
			}

			case MENUEXIT:
			{


				if (UG::IsKeyDown(UG::KEY_ENTER))
				{
					UG::StopDrawingSprite(iMenuScreen); // Stops drawing the main menu
					PlaySound(TEXT("./sounds/Confirm.wav"), NULL, SND_FILENAME | SND_SYNC);
					UG::Close(); // Closes the game

				}

				if (UG::IsKeyDown(UG::KEY_DOWN))
				{
					UG::SetSpriteUVCoordinates(iMenuScreen, 0, 0, 0.5, 0.5); // Displays the bottom left portion of the image
					currentState = MENUPLAY;  // Set currentState to MENUPLAY
					PlaySound(TEXT("./sounds/Select.wav"), NULL, SND_FILENAME | SND_SYNC);

				}

				if (UG::IsKeyDown(UG::KEY_UP))
				{
					UG::SetSpriteUVCoordinates(iMenuScreen, 0.5, 0, 1, 0.5); // Displays the bottom right portion of the image
					currentState = MENUHIGHSCORE; // Set currentState to MENUHIGHSCORE
					PlaySound(TEXT("./sounds/Select.wav"), NULL, SND_FILENAME | SND_SYNC);
				}


				UG::ClearScreen(); // Clears all drawn sprites
				break; // Break so we don't continue down the statements
			}
			case GAMEPLAY:
			{
				if (ClassUI.iPlayerLives <= 0 && ClassPlayer.bIsAlive == false) // Before anything else, check the player still has lives and is alive
				{
					currentState = MENUPLAY; // If that fails, return the player to the menu
					ClassUI.iPlayerLives = ClassUI.iMaxLives; // Set player lives back to max
				} 
				else
				{
					if (UG::IsKeyDown(UG::KEY_SPACE))
					{
						ClassBullet.Fire(&ClassPlayer); // When space is pressed call this function
					}


					if (UG::IsKeyDown(UG::KEY_ESCAPE)) // Quit our application when escape is pressed
					{

						UG::StopDrawingSprite(ClassPlayer.iSprite); // Stops drawing the player

						UG::StopDrawingSprite(iBackGround); // Stops drawing the background
						UG::DestroySprite(iBackGround); // Destroys the sprite

						ClassBullet.StopAll();
						ClassEnemy.Destroy(g_iEnemyAmount); // Destroys all enemy data
						ClassUI.UpdateHighScores(); // Update the Highscores
						ClassUI.ClearScore(); // Clear the players score
						UG::ClearScreen(); // Clears all drawn sprites
						currentState = MENUPLAY; // Sets currentState to MENUPLAY
						iMenuScreen = UG::CreateSprite("./images/MenuScreenSpriteSheet.png", 1024, 768, false); // Initialises the menu screen 
						UG::DrawSprite(iMenuScreen); // Draw the menu screen
						UG::MoveSprite(iMenuScreen, 0, 768); // Move to top left of the screen
						UG::SetSpriteUVCoordinates(iMenuScreen, 0, 0, 0.5, 0.5); // Display the bottom left portion of the image
						break;
					}


					/* ==================================================== Do Every Frame ==================================================== */

					ClassPlayer.MovePlayer(&iBackGround, &ClassEnemy, &g_iEnemyAmount); // Moves all assets to simulate the player moving
					ClassPlayer.Respawn(&ClassUI); // Checks player state and respawns if needed
					ClassEnemy.RenderCheck(g_iEnemyAmount); // Checks if the enemies need to be rendered or not
					ClassEnemy.AIUpdateDirection(g_iEnemyAmount);
					ClassEnemy.AIMove(g_iEnemyAmount);
					ClassBullet.Update(&ClassBullet, &ClassPlayer); //  Updates bullet positions
					ClassBullet.Draw(); // Checks if the bullet needs to be drawn and draws accordingly
					ClassUI.DrawPlayerInfo(); // Draws "Player Score: VARIBLE" and "Player Lives: VARIBLE" in the top left
					ClassCollision.TestPhysicalCollision(&ClassPlayer, &ClassEnemy, g_iEnemyAmount); // Checks if player is colliding with any enemies
					ClassCollision.TestBulletCollision(&ClassBullet, &ClassEnemy, g_iEnemyAmount, &ClassPlayer, &ClassUI); // Checks if player bullets are colliding with any enemies




					if (ClassPlayer.Respawn(&ClassUI) == 0) // If player is out of lives and dead (ClassPlayer.Respawn return's 0 on fail) 
					{
						UG::StopDrawingSprite(ClassPlayer.iSprite); // Stops drawing the player

						UG::StopDrawingSprite(iBackGround); // Stops drawing the background
						UG::DestroySprite(iBackGround); // Destroys the sprite

						ClassBullet.StopAll();
						ClassEnemy.Destroy(g_iEnemyAmount); // Destroys all enemy data
						ClassUI.UpdateHighScores(); // Update the Highscores
						ClassUI.ClearScore(); // Clear the players score
						UG::ClearScreen(); // Clears all drawn sprites
						currentState = MENUPLAY; // Sets currentState to MENUPLAY
						iMenuScreen = UG::CreateSprite("./images/MenuScreenSpriteSheet.png", 1024, 768, false); // Initialises the menu screen 
						UG::DrawSprite(iMenuScreen); // Draw the menu screen
						UG::MoveSprite(iMenuScreen, 0, 768); // Move to top left of the screen
						UG::SetSpriteUVCoordinates(iMenuScreen, 0, 0, 0.5, 0.5); // Display the bottom left portion of the image
						break;
					}


					UG::ClearScreen(); // Clears all drawn sprites
					break; // Break so we don't continue down the statements
				}
			}
			}

		} while (UG::Process());

		
		UG::Dispose();


	}
	return 0;
}
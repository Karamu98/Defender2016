////////////////////////////////////////////////////////////
// File: <main.cpp>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#include "UI.h"
#include "UGFW.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>

void oUI::AddScore(int a_amount)
{
	iPlayerScore += a_amount; // Set iPlayerScore to the sum of itself + a_amount
}

void oUI::DrawPlayerInfo()
{
	std::stringstream ssScore; // Make a stringstream called ssScore

	std::stringstream ssLives; // Make a stringstream called ssLives

	ssScore << "Player Score: " << iPlayerScore; // Stream string and variable into stringstream
	ssLives << "Player Lives: " << iPlayerLives; // Stream string and variable into stringstream

	UG::SetFont("./fonts/invaders.fnt"); // Set the font
	UG::DrawString(ssScore.str().c_str(), 20, 750); // Tbh, idek [Need's Googl'ing)
	UG::DrawString(ssLives.str().c_str(), 20, 715); // Tbh, idek [Need's Googl'ing)
}

void oUI::DrawHighScores()
{
	float iScreenHeightModifer = 0.9f;
	std::stringstream ssHighScores;

	for (int i = 0; i < 5; i++)
	{
		ssHighScores.str(std::string()); //Clears the String Stream
		ssHighScores << i + 1 << ". " << iPlayerBestScores[i];
		UG::DrawString(ssHighScores.str().c_str(), 200, 500 * iScreenHeightModifer);
		iScreenHeightModifer -= 0.1f;
	}
}

void oUI::UpdateHighScores()
{
	for (int i = 0; i < 5; i++)
	{
		if (iPlayerScore == iPlayerBestScores[i])
		{

		}
		else
		{
			if (iPlayerScore > iPlayerBestScores[i])
			{
				iPlayerBestScores[4] = iPlayerScore;
				break;
			}
		}


	}
	std::sort(std::begin(iPlayerBestScores), std::end(iPlayerBestScores));


	std::fstream highscores;
	highscores.open("Highscores", std::ios_base::out);

	for (int i = 4; i > -1; i--)
	{
		highscores << iPlayerBestScores[i] << std::endl;
	}
	highscores.close();

}

void oUI::ClearScore()
{
	iPlayerScore = 0;
}

void oUI::ReadScores()
{
	std::fstream highscores;
	highscores.open("Highscores", std::ios_base::in);

	if (highscores.is_open() == false)
	{
		highscores.open("Highscores", std::ios_base::out);
		highscores << "0" << std::endl;
		highscores << "0" << std::endl;
		highscores << "0" << std::endl;
		highscores << "0" << std::endl;
		highscores << "0" << std::endl;
		highscores.close();
		highscores.open("Highscores", std::ios_base::in);
	}

	for (int i = 0; i < 5; i++)
	{
		highscores >> iPlayerBestScores[i];
	}
}

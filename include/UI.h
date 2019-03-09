////////////////////////////////////////////////////////////
// File: <UI.h>
// Author: <Callum PJ Haines>
// Date Created: <24/11/2016>
// Brief: <Recreation of retro game "defender" for CT4019>
////////////////////////////////////////////////////////////

#ifndef _UI_H_
#define _UI_H_


class oUI
{
private:

	int iPlayerScore = 0; // Holds player score
	int iPlayerBestScores[5] = {0, 0, 0, 0, 0}; // Holds highest scores


public:

	int iPlayerLives = 3; // Holds player lives
	const int iMaxLives = 3; // Holds the max amount of lives the player can have
	void AddScore(int a_amount); // Adds a given amount to player score
	void DrawPlayerInfo(); // Draw player information
	void DrawHighScores();
	void UpdateHighScores();
	void ClearScore();
	void ReadScores();

};

#endif
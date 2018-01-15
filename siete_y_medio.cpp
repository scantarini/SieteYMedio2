#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "cards.h"
using namespace std;

bool Bust(Player p)
{
	if (p.GetHandPoints() > 7.5) return 1;
	return 0;
}

bool DrawAgain()
{
	char ans;

	do {
		cout << "Do you want another card (y/n)?";
		cin >> ans;
	} while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N');
	if (ans == 'y' || ans == 'Y') return 1;
	return 0;
}

int PlayTurn(Player& p, int playerNumber)
{
	bool draw = true;

	// Instructions for you to play the round (not the dealer)
	if (playerNumber == 1)
	{
		p.SetBet();
		while (draw)
		{
			if (draw)
			{
				p.GetCard();
				p.DisplayPlayerHand();
			}

			if (Bust(p))
			{
				cout << "\nYou bust. Dealer's turn.\n";
				p.SetBank(p.GetBank() - p.GetBet());
				return -1; // -1 is used as a value indicating that the round has been lost by this player
			}

			draw = DrawAgain();
		}
	}
	else
	{
		while (p.GetHandPoints() < 5.5)
		{
			p.GetCard();
			p.DisplayPlayerHand();
		}
		if (Bust(p)) return -1;  // -1 is used as a value indicating that the round has been lost by this player
	}
}

int main() {
	Player you(1);
	Player dealer(2);
	double score1;
	double score2;


	score1 = PlayTurn(you, 1);
	score2 = PlayTurn(dealer, 2);

	while (score1 != 0 && score1 < 1000)
	{
		if (score1 < score2 || (score1 == -1 && score2 == -1))
		{
			cout << "Too bad. You lose " << you.GetBet() << ".\n";
			you.SetBank(you.GetBank() - you.GetBet());
		}
		else if (score1 > score2)
		{
			cout << "You win " << you.GetBet() << ".\n";
			you.SetBank(you.GetBank() + you.GetBet());
		}
		else if (score1 == score2)
		{
			cout << "Nobody wins!\n";
		}
	}
}
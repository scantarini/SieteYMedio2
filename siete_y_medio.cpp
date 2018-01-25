#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "cards.h"
using namespace std;

const int BUST = -1; // -1 is used as a value indicating that the round has been lost by this player


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

double PlayTurn(Player& p, int playerNumber)
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
				return BUST;
			}

			draw = DrawAgain();
		}
		return p.GetHandPoints();
	}
	else
	{
		while (p.GetHandPoints() < 5.5)
		{
			p.GetCard();
			p.DisplayPlayerHand();
		}
		if (Bust(p)) return BUST; 
	}
	return p.GetHandPoints();
}

int main() {
	Player you(1);
	Player dealer(2);
	double score1 = 1;
	double score2 = 1;

	while (you.GetBank() != 0 && you.GetBank() < 1000)
	{
		score1 = PlayTurn(you, 1);
		score2 = PlayTurn(dealer, 2);
		if (score1 < score2 || score1 == BUST)
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
		you.Reset();
	}
	if (!you.GetBank())
	{
		cout << "You have $0. GAME OVER!\n";
		cout << "Come back when you have more money.\n\n";
		cout << "Bye!\n";
		return 0;
	}
	cout << "Congratulations. You beat the casino!\n\nBye!\n";
}
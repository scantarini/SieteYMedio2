#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "cards.h"
#include <iomanip>
using namespace std;

const int BUST = -1; // -1 is used as a value indicating that the round has been lost by this player

// This function returns whether or not the player's total hand points exceed 7.5 (BUST)
bool Bust(Player p)
{
	if (p.GetHandPoints() > 7.5) return 1;
	return 0;
}

// This function prompts the user if they would like to draw another card. If yes, return 1. If no, return 0.
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

// This function is where a player draws their card. The return value is the total number of points of a player's hand (-1 for a bust).
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

// This function sends relevant information to the output file stream
void FinalOutput(Player& p1, Player& p2, ofstream& out)
{
	string cardNameSpanish; // Used for convenience for setw formatting
	out << setw(12) << " ";
	out << "Money left: " << p1.GetBank() << endl;
	out << "Bet: " << p1.GetBet() << endl << endl;
	out << "Your cards:\n";

	for (int i = 0; i < p1.ReadCards()->size(); i++)
	{
		cardNameSpanish = (*p1.ReadCards())[i].get_spanish_rank() + " de " + (*p1.ReadCards())[i].get_spanish_suit();
		out << "	" << setw(20) << cardNameSpanish;
		out << "(" << (*p1.ReadCards())[i].get_english_rank() << " of " << (*p1.ReadCards())[i].get_english_suit() << ")." << endl;
	}

	out << "Your total is " << p1.GetHandPoints() << ". \n\n";


	out << "Dealer's cards:\n";
	for (int i = 0; i < p2.ReadCards()->size(); i++)
	{
		cardNameSpanish = (*p2.ReadCards())[i].get_spanish_rank() + " de " + (*p2.ReadCards())[i].get_spanish_suit();
		out << "	" << setw(20) << cardNameSpanish;
		out << "(" << (*p2.ReadCards())[i].get_english_rank() << " of " << (*p2.ReadCards())[i].get_english_suit() << ")." << endl;
	}
	out << "The dealer's total is " << p1.GetHandPoints() << ". " << endl << endl;

}


int main() {
	Player you(1);		// Declaration of the player. The (1) sets the player's number to 1.
	Player dealer(2);	// Declaration of the dealer
	double score1 = 1;	// The number of points between the player's cards (cards of the "you" player)
	double score2 = 1;	// The number of points between the dealer's cards
	int gameNumber = 1;	// The current game number
	ofstream output;	// The output file stream that outputs to gamelog.txt

	output.open("gamelog.txt");
	output << left;
	output << "-----------------------------------------------\n";

	// This loop runs each game and terminates when the player's balance is 0 or when the dealer has lost at least 900.
	while (you.GetBank() != 0 && you.GetBank() < 1000)
	{
		score1 = PlayTurn(you, 1);
		score2 = PlayTurn(dealer, 2);

		output << "Game number: " << gameNumber;

		// Sends relevant information to the output file.
		FinalOutput(you, dealer, output);

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


		output << "-----------------------------------------------\n";


		gameNumber++;
		
		// Resets the player's bet and clears their hand after a game.
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

	output.close();
}
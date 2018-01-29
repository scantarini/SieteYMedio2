/* *************************************
Ricardo Salazar, February 26, 2015

Interface of a simple Card class
************************************* */

#include <string>
#include <vector>
#include <fstream>

#ifndef CARDS_H
#define CARDS_H

using namespace std;

enum suit_t { OROS, COPAS, ESPADAS, BASTOS };

/*
The values for this type start at 0 and increase by one
afterwards until they get to SIETE.
The rank reported by the function Card::get_rank() below is
the value listed here plus one.
E.g:
The rank of AS is reported as    static_cast<int>(AS) + 1   = 0 + 1 =  1
The rank of SOTA is reported as  static_cast<int>(SOTA) + 1 = 9 + 1 = 10
*/
enum rank_t { AS, DOS, TRES, CUATRO, CINCO, SEIS, SIETE, SOTA = 9, CABALLO = 10, REY = 11 };

class Card {
public:
	// Constructor assigns random rank & suit to card.
	Card();

	// Accessors 
	string get_spanish_suit() const;
	string get_spanish_rank() const;

	/*
	These are the only functions you'll need to code
	for this class. See the implementations of the two
	functions above to get an idea of how to proceed.
	*/
	string get_english_suit() const;
	string get_english_rank() const;

	// Converts card rank to number.
	// The possible returns are: 1, 2, 3, 4, 5, 6, 7, 10, 11 and 12
	int get_rank() const;

	// Compare rank of two cards. E.g: Eight<Jack is true.
	// Assume Ace is always 1. 
	// Useful if you want to sort the cards.
	bool operator < (Card card2) const;

private:
	suit_t suit;
	rank_t rank;
};


class Hand {
public:
	Hand();
	void SetScoreTotal(double newValue);		// Modifies the total score
	double GetScoreTotal() const;				// Returns the cumulative score between the cards in the hand
	void InsertCard();							// Inserts a card into the hand
	void Clear();								// Resets the hand after the end of a game
	void Display(int playerNumber) const;		// Displays information about the cards in the hand
	vector<Card>* SeeCards();					// This allows the player to see their own cards

private:
	vector<Card> cards;	//The hand of cards
	double scoreTotal;	// The cumulative card value in the hand
};


class Player {
public:
	Player();							// Default Constructor
	Player(int playerNum);				// Constructor with playerNumber parameter.
	void SetBank(int newBankBalance);	// Modifies the amount of money the player has
	int GetBank() const;				// Returns the amount of money the player has
	int GetBet() const;					// Returns the amount of money the player bet
	void SetBet();						// This function allows the player to set the amount of money they want to bet.
	double GetHandPoints();				// Returns the total number of points in a player's hand
	void DisplayPlayerHand() const;		// This is used for convenience in displaying card information. It is built on Display() in the Hand class.
	void GetCard();						// This function adds a card to a player's hand
	void Reset();						// This function resets the player's information in case several games were to be played (not required)
	vector<Card>* ReadCards();			// This allows the player to access information about their own hand.

private:
	int bet;
	int money;
	Hand playerHand;  // This will be added after modification of the hand class.
	int playerNumber; // Distinguishes the player from the dealer
};

#endif
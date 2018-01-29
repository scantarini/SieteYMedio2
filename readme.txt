Note: There is thorough documentation in the files themselves,
but I will add an interface for all functions in the program
at the bottom of this file for good measure.


Notes:
Every time the player is prompted to enter information, there is error checking that prevents undesired alphanumeric and punctuation input.
All the following cases were tested (and worked properly):
1. The player wins a game in the following ways:
	-The player's final total is greater, and neither the player nor the dealer bust
	-The dealer busts and the player does not
2. The dealer wins a game in the following ways:
	-Both the player and the dealer bust
	-Only the player busts
	-The dealer has a higher point count, and neither the dealer nor the player bust
3. The game is a tie (neither the dealer nor the player bust, and the point count is the same)
4. The player hits (or exceeds) $1000, so the game ends.
5. The player's balance hits 0, and the game ends.


Function Interface: (Might not be necessary --  this information is also included in the files themselves):

siete_y_medio.cpp:
----------------------------------------------
bool Bust(Player p)										 // This function returns whether or not the player's total hand points exceed 7.5 (BUST)
bool DrawAgain()										 // This function prompts the user if they would like to draw another card.
														 // If yes, return 1. If no, return 0.

double PlayTurn(Player& p, int playerNumber);			 // This function is where a player draws their card. 
														 //The return value is the total number of points of a player's hand (-1 for a bust).

void FinalOutput(Player& p1, Player& p2, ofstream& out); // This function sends relevant information to the output file stream.
----------------------------------------------

Hand Class Member Functions:
----------------------------------------------
Hand();										// The default constructor
void SetScoreTotal(double newValue);		// Modifies the total score
double GetScoreTotal() const;				// Returns the cumulative score between the cards in the hand
void InsertCard();							// Inserts a card into the hand
void Clear();								// Resets the hand after the end of a game
void Display(int playerNumber) const;		// Displays information about the cards in the hand
vector<Card>* SeeCards();					// This allows the player to see their own cards
----------------------------------------------

Player Class Member Functions
----------------------------------------------
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
----------------------------------------------

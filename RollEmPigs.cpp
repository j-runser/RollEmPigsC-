// RollEmPigs.cpp
//
// Created by Joseph Runser on 10/5/17.
// The dice game Roll Em Pigs.

#include <iostream>
#include <time.h>
#include <string>

using namespace std;

// Minimum and maximum value for the die
static const int DIE_MAX = 6;
static const int DIE_MIN = 1;

// Function definitions, detailed comments at the implimentation
static bool playTurn(bool isHuman, string playerName, int &gameScore);
static int rollDie(void);
static bool isTurnScoreLost(int die1value, int die2value);
static bool isGameScoreLost(int die1value, int die2value);
static bool isGameScoreWin(int gameScore);
static char getUserInput(void);

int main() {
    
    srand((int)time(NULL));
    
    int humanScore = 0;
    int computerScore = 0;
    
    cout << "Welcome to Roll-Em-Pigs!" << endl;
    
	// Game loop
    while (true) {
        // human turn
        if (playTurn(true, "Player 1", humanScore))
            break;
        
        // computer turn
        if (playTurn(false, "Computer", computerScore))
            break;
    }
    
    system("pause");
    return 0;
    
}

// This plays the turn. Since the turns are the same, except one part, for the
// computer and the human it is one fucntion.
//
// gameScore: A pointer pointing to the gameScore of the player, if this goes over
//     if this goes over 100 and the turn the fucntion will return true.
// playerName: The name of the player for display purposes.
// isHuman: true if the player is human false if a computer.
//
// return: true if the the player wins, otherwise false.
// 
static bool playTurn(bool isHuman, string playerName, int &gameScore) {
    int turnScore = 0;
    int dieOne = 0;
    int dieTwo = 0;
    
    while (true) {
        cout << endl << playerName << ", your game score is " << gameScore;
        cout << ", and your turn score is " << turnScore << endl;
        
        if (isHuman && getUserInput() == 's') {
            gameScore += turnScore;
            break;
        }
        else if (turnScore >= 21 || isGameScoreWin(gameScore)) {
            gameScore += turnScore;
            break;
        }
        
        dieOne = rollDie();
        dieTwo = rollDie();
        cout << "Die one: " << dieOne << " Die two: " << dieTwo << endl;
        
        // Check for loss of turn
        if (isTurnScoreLost(dieOne, dieTwo)) {
            if (isGameScoreLost(dieOne, dieTwo))
                gameScore = 0;
            break;
        }
        
        turnScore += dieOne + dieTwo;
    }
    
    // Check for the end of the game
    cout << playerName << " has ended their turn with a score of " << gameScore << endl;
    if (isGameScoreWin(gameScore)) {
        cout << playerName << " has won the game." << endl << endl;
        return true;
    }
    return false;
}

// Rolls a die using the rand function.
//
// !! WARNING: It is not seeded as is. !!
//
// return: An integer value between the declared values of DIE_MIN and DIE_MAX
int rollDie() {
    return rand() % DIE_MAX + DIE_MIN;
}

// Checks to see if the turn score is either won or lost.
//
// die1value: The value of the first die.
// die2value: The value of the second die.
//
// return: true if the turn score is lost, false otherwise.
bool isTurnScoreLost(int die1value, int die2value) {
    if (die1value == 1 || die2value == 1) return true;
    return false;
}

// Checks to see if the game score is either won or lost.
//
// die1value: The value of the first die.
// die2value: The value of the second die.
//
// return: true if the game score is lost, false otherwise.
bool isGameScoreLost(int die1value, int die2value) {
    if (die1value == 1 && die2value == 1) return true;
    return false;
}

// Checks to see if the game is either won or lost.
//
// gameScore: The total game score.
//
// return: true if the game won, false otherwise.
bool isGameScoreWin(int gameScore) {
    if(gameScore >= 100) { return true; }
    return false;
}

// Get and clean the user input.
// 
// return: If the user inputs either 'S' or 's' it returns 's' and if the user
//     inputs either 'R' or 'r' it returns 'r'. If there is an error it will 
//     return an 'e'.
char getUserInput() {
    char input;
    cout << "Please input (r) if you would like to roll or (s) to stop: ";
    while(true) {
        cin >> input;
        
        if(input == 's' || input == 'S') return 's';
        if(input == 'r' || input == 'R') return 'r';
        
        cout << "That is not a valid input." << endl;
        cout << "Please input (r) if you would like to roll or (s) to stop";
    }
    
    return 'e'; // error
}

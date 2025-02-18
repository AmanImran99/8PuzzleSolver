#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP
#include "puzzle.hpp"

#include <deque>


struct PuzzleNode {
    Puzzle currentPuzzle;      // Stores puzzle object
    int f;              // Value to find best node
    int g;              // Value to find number of moves used
    PuzzleNode* parent; // Pointer to the parent node
    PuzzleNode* right;  // Pointer to child nodes
    PuzzleNode* left;
    PuzzleNode* up;
    PuzzleNode* down;

    PuzzleNode() : g(0), f(0), parent(nullptr), right(nullptr), left(nullptr), up(nullptr), down(nullptr) {}
};

void testFunction();

// Calculates the Heuristic value, (number of tiles that are in the wrong spot)
int calculateH1(Puzzle& puzzle);

// Calculates the Heursitic Value, (Manhattan Distance)
int calculateH2(Puzzle& puzzle);

//  Uses Heursitics to solve the puzzle
int solveH(Puzzle& puzzle, int (*heuristic)(Puzzle&));

// Function to check if a puzzle already exists in the closed list
bool isInClosed(const deque<PuzzleNode*>& closed, const Puzzle& puzzle);

// Finds the best F value in the puzzle structure
PuzzleNode* getBestNode(deque<PuzzleNode*>& open);




#endif
#include <iostream>
#include "heuristics.hpp"
using namespace std;




int calculateH1(Puzzle& puzzle){
    int num = 0;
    int h = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle.current[i][j] != 0){
                if (puzzle.current[i][j] == num){
                    h++;
                }
            }
            num++;
        }
    }
    return 8-h;
}

int calculateH2(Puzzle& puzzle){
    int h = 0; // Heuristic value (Manhattan distance)

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int tile = puzzle.current[i][j]; // Get the tile number
            if (tile != 0) { // Ignore the blank tile (0)
                // Compute the goal position
                int goalX = tile / 3; // Expected row index
                int goalY = tile % 3; // Expected column index

                // Add the Manhattan distance
                h += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    
    return h; // Return the total Manhattan distance
}

bool isInClosed(const deque<PuzzleNode*>& closed, const Puzzle& puzzle) {
    for (const auto& node : closed) {
        if (node->currentPuzzle == puzzle) { // Assuming `Puzzle` has an `operator==`
            return true;
        }
    }
    return false;
}

PuzzleNode* getBestNode(deque<PuzzleNode*>& open) {
    if (open.empty()) return nullptr;  // Avoid errors if open list is empty

    auto bestNode = open.front();  // Start with the first node
    auto bestIt = open.begin();    // Iterator to the best node

    for (auto it = open.begin(); it != open.end(); ++it) {
        if ((*it)->f < bestNode->f) {
            bestNode = *it;
            bestIt = it;
        }
    }

    open.erase(bestIt);  // Remove the best node from open list
    return bestNode;      // Return the best node
}


int solveH(Puzzle& puzzle, int (*heuristic)(Puzzle&)){

    int count = 0;
    int moves = 1;
    deque<PuzzleNode*> open;
    deque<PuzzleNode*> closed;
    deque<PuzzleNode*> solution;
    
    // Create the parent node, start state (scrambled);
    PuzzleNode* currentNode = new PuzzleNode();  // Allocate dynamically
    currentNode->currentPuzzle = puzzle;
    currentNode->g = 0;
    currentNode->f = (heuristic(currentNode->currentPuzzle) + 0);
    currentNode->parent = nullptr;
    currentNode->right = nullptr;
    currentNode->left = nullptr;
    currentNode->up = nullptr;
    currentNode->down = nullptr;

    // Create tempNode for neighbor storage
    PuzzleNode* tempNode = nullptr;

    while (true) {

        if (heuristic(currentNode->currentPuzzle) == 0) {  // Check if puzzle is solved

            while (currentNode->parent != nullptr){
                solution.push_front(currentNode);
                currentNode = currentNode->parent;   
            }
            for (const auto& PuzzleNode : solution) {
                cout << "move: " << moves << endl;
                PuzzleNode->currentPuzzle.print();
                moves++;
            }

            break;
        }

        closed.push_back(currentNode);  // Add currentNode to closed list
        
        // Store possible nodes in open (checking for possible moves)
        
        // Move Right
        Puzzle tempPuzzle = currentNode->currentPuzzle;
        if (tempPuzzle.moveRight() && !isInClosed(closed, tempPuzzle)) {  
            tempNode = new PuzzleNode();  
            tempNode->currentPuzzle = tempPuzzle;  
            tempNode->parent = currentNode;
            tempNode->g = currentNode->g + 1;
            tempNode->f = heuristic(tempNode->currentPuzzle) + tempNode->g;

            open.push_back(tempNode);  
        }

        // Move Left
        tempPuzzle = currentNode->currentPuzzle;
        if (tempPuzzle.moveLeft() && !isInClosed(closed, tempPuzzle)) {  
            tempNode = new PuzzleNode();  
            tempNode->currentPuzzle = tempPuzzle;  
            tempNode->parent = currentNode;
            tempNode->g = currentNode->g + 1;
            tempNode->f = heuristic(tempNode->currentPuzzle) + tempNode->g;

            open.push_back(tempNode);  
        }

        // Move Up
        tempPuzzle = currentNode->currentPuzzle;
        if (tempPuzzle.moveUp() && !isInClosed(closed, tempPuzzle)) {  
            tempNode = new PuzzleNode();  
            tempNode->currentPuzzle = tempPuzzle;  
            tempNode->parent = currentNode;
            tempNode->g = currentNode->g + 1;
            tempNode->f = heuristic(tempNode->currentPuzzle) + tempNode->g;

            open.push_back(tempNode);  
        }

        // Move Down
        tempPuzzle = currentNode->currentPuzzle;
        if (tempPuzzle.moveDown() && !isInClosed(closed, tempPuzzle)) {  
            tempNode = new PuzzleNode();  
            tempNode->currentPuzzle = tempPuzzle;  
            tempNode->parent = currentNode;
            tempNode->g = currentNode->g + 1;
            tempNode->f = heuristic(tempNode->currentPuzzle) + tempNode->g;

            open.push_back(tempNode);  
        }


        count++;
        // Increment count for iteration
        /* 
        cout << "Move: " << count << "    h value: " << heuristic(currentNode->currentPuzzle) << endl;
        currentNode->currentPuzzle.print();
        */

        // Pick the node with the best f value
        currentNode = getBestNode(open);
        if (!currentNode) {
            cout << "No solution found!" << endl;
            break;
        }
    }



    // Cleanup: delete all dynamically allocated nodes
    // All created nodes will be deleted if we delete open and closed


    for (PuzzleNode* node : closed) {
        delete node;
    }
    closed.clear();

    for (PuzzleNode* node : open) {
        delete node;
    }
    open.clear();

    return 0;
}


void testFunction(){
    Puzzle puzzle1;
    puzzle1.randomize();
    cout << "start state: " << endl;
    puzzle1.print();
    solveH(puzzle1, calculateH2);
}
#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <random>
#include <string>
using namespace std;


class Puzzle{
    public:
        // Holds the current state of the puzzle
        int current[3][3];

        // Postion of the empty slide
        int x,y;

        // Constructor, puzzle will start in the solved state
        Puzzle();

        // Prints the 'current' state of the puzzle
        void print();

        // Returns a reference to the 'current' array
        int (&getCurrent())[3][3];

        bool operator==(const Puzzle& other) const;

        // Scrambles the puzzle
        void randomize();

        // Set custom puzzle
        void setPuzzle(int arr[9]);

        // Checks if the puzzle is solvable
        bool isSolvable(int list[]);

        // Update the position of the empty slide
        void updateEmpty();

        // Converts puzzle in a string for easy storing
        string convertToString();

        // Shift the empty slide by 1 space,
        // Functions will return false if the empty slide is already at the end
        bool moveRight();
        bool moveLeft();
        bool moveDown();
        bool moveUp();
        
};


#endif // __PUZZLE_HPP
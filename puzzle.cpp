#include "puzzle.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>


// Constructor
Puzzle::Puzzle(){
    int counter = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            current[i][j] = counter;
            counter += 1;
        }
    }
    x = 0;
    y = 0;
}

void Puzzle::print(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cout << current[i][j]<<" ";
        }
        cout << endl;
    }
    cout << endl;
}


void Puzzle::updateEmpty(){
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){

            if (current[i][j] == 0)
            {
                x = j;
                y = i;
            }
            
        }
    }
}


int (&Puzzle::getCurrent())[3][3] {
    return current;
}


void Puzzle::randomize() {
    int list[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    // Create a random number generator
    random_device rd;
    mt19937 g(rd());

    // Shuffle the array once
    shuffle(list, list + 9, g);

    // Ensure the puzzle is solvable
    if (!isSolvable(list)) {
        // Swap any two non-zero numbers to change the parity of inversions
        for (int i = 0; i < 9; i++) {
            if (list[i] == 0) continue;
            for (int j = i + 1; j < 9; j++) {
                if (list[j] == 0) continue;
                swap(list[i], list[j]);  // Swap first two non-zero numbers
                goto fix_complete;  // Exit loop
            }
        }
    }
fix_complete:

    int counter = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            current[i][j] = list[counter];
            counter++;
        }
    }

    // Update where the empty slide is
    updateEmpty();
}


void Puzzle::setPuzzle(int arr[9]){
    int count = 0;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            current[i][j] = arr[count];
            count++;
        }
    }
    updateEmpty();
}


// Function to check if the puzzle is solvable
bool Puzzle::isSolvable(int list[]) {
    int inversions = 0;

    // Count inversions, ignoring the empty tile (0)
    for (int i = 0; i < 9; i++) {
        if (list[i] == 0) continue;
        for (int j = i + 1; j < 9; j++) {
            if (list[j] == 0) continue;
            if (list[i] > list[j]) inversions++;
        }
    }

    return (inversions % 2 == 0);
}

string Puzzle::convertToString(){
    string result;
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            result += to_string(current[i][j]);
        }
    }
    return result;
}

bool Puzzle::moveRight(){
    if (x == 2){
        return false;
    }
    current[y][x] = current[y][x+1];
    current[y][x+1] = 0;
    x++;
    return true;
}

bool Puzzle::moveLeft(){
    if (x == 0){
        return false;
    }
    current[y][x] = current[y][x-1];
    current[y][x-1] = 0;
    x--;
    return true;
}

bool Puzzle::moveDown(){
    if (y == 2){
        return false;
    }
    current[y][x] = current[y+1][x];
    current[y+1][x] = 0;
    y++;
    return true;
}

bool Puzzle::moveUp(){
    if (y == 0){
        return false;
    }
    current[y][x] = current[y-1][x];
    current[y-1][x] = 0;
    y--;
    return true;
}

// Define operator== to compare two Puzzle objects
bool Puzzle::operator==(const Puzzle& other) const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (current[i][j] != other.current[i][j]) {
                return false; // If any tile is different, return false
            }
        }
    }
    return true; // If all tiles match, return true
}
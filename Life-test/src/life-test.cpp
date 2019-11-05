/*
John Kolden, SCPD
Standford University CS106B
Project Name: Life.pro
Assignment 1
April 8, 2015
Section Leader: Sarah Spikes

Purpose of Program:
-------------------
The Game of Life is a simulation of living cell colonies. The game models the life cycle of bacteria using
a two-dimensional grid of cells. Given an initial pattern, the game simulates the birth and death of future
generations of cells using a set of simple rules.

This Game of Life program begins by prompting the user for a file name and using that file's contents to set
the initial state of your bacterial colony grid. Then it will allow the user to advance the colony through generations
of growth. The user can "tick" forward the bacteria simulation by one generation, or can initiate an
animation loop that ticks forward the simulation by several generations, once every 50 milliseconds.
 */

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
#include "stack.h"
#include "queue.h"

using namespace std;

//function prototypes:
void displayWelcomeMessages();
char getUserInput();
void populateFirstGeneration(Grid<char>&);
void populateNewGeneration(Grid<char>&);

int main() {




    return 0;
 }

void stutter (Queue<int> q) {
    Queue<int> q2;
    int size = q.size();

    while (!q.isEmpty()) {


    }

}

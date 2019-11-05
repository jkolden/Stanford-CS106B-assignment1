/*
John Kolden, SCPD
Standford University CS106B
Filename: life-extra.cpp
Assignment 1 (Extras File)
April 8, 2015
Section Leader: Sarah Spikes

Additions included in life-extra.cpp:
-- Random grid generation
-- GUI display

Purpose of Program:
-------------------
The Game of Life is a simulation of living cell colonies. The game models the life cycle of bacteria using
a two-dimensional grid. The simulation starts with an initial pattern and simulates the birth and death of future
generations of cells using a set of rules.

This program begins by prompting the user for a file name and using the contents of the file to set
the initial state of the colony. Then it will allow the user to advance the colony through generations
of cell growth. The user can tick forward the bacteria simulation by one generation, or can initiate an
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
using namespace std;

//function prototypes:
void displayWelcomeMessages();
char getUserInput();
void populateFirstGeneration(LifeGUI&, Grid<char>&);
void populateNewGeneration(LifeGUI&, Grid<char>&);
void populateRandomGeneration(LifeGUI&, Grid<char>&); //***new in extras file***
char randomCell();  //***new in extras file***

int main() {

    LifeGUI lifeGUIMatrix;
    Grid<char> lifeMatrix;
    char userSelection; //used to capture whether user wants to tick, animate or quit

    //begin user interaction:

    displayWelcomeMessages(); //displays welcome messages

    string fileOrRandom = toUpperCase(getLine("Would you like to choose an e)xisting file or generate a grid r)andonly: "));

    while (!((fileOrRandom == "R")||(fileOrRandom == "E"))) {
        cout << "Not a valid selection. Try again." << endl;
        fileOrRandom = toUpperCase(getLine("Would you like to choose an e)xisting file or generate a grid r)andonly: "));
    }

    if (fileOrRandom == "R") {
        populateRandomGeneration(lifeGUIMatrix, lifeMatrix);//displays initial grid based on random generation

    } else if (fileOrRandom == "E") {
    populateFirstGeneration(lifeGUIMatrix, lifeMatrix); //displays initial grid based on selected filename
  //  changeGuiDisplay(lifeGUIMatrix, lifeMatrix); //grid display ***new in extras file***
    }

    while (userSelection != 'Q') {//execute this loop while user chooses to tick or animate.
        userSelection = getUserInput();

        switch (userSelection) {
        case ('A'): {//animate new generations based on user input
            int numberOfGenerations = getInteger("How many frames? ");
            for (int i=0; i < numberOfGenerations; i++) {
                clearConsole() ;
                populateNewGeneration(lifeGUIMatrix, lifeMatrix);
                pause(50);
            };
        }
            break;
        case ('T'): {//tick one generation forward
           populateNewGeneration(lifeGUIMatrix, lifeMatrix);
        }
            break;
        case('Q'): //quit program
            break;
        }
    };// end while loop

    cout << "Have a nice Life!" << endl;
    return 0;
}

void displayWelcomeMessages()  {

    cout << "Welcome to the CS 106B Game of Life," << endl;
    cout << "a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "- A cell with 1 or fewer neighbors dies." << endl;
    cout << "- Locations with 2 neighbors remain stable." << endl;
    cout << "- Locations with 3 neighbors will create life." << endl;
    cout << "- A cell with 4 or more neighbors dies." << endl;
    cout << endl;
}

//This getUserInput method collects input from the user as they progress through the program.
char getUserInput() {

    string userInput = toUpperCase(( getLine ("a)nimate, t)ick, q)uit? ")));

    while (!(userInput == "A"||userInput == "T"||userInput == "Q")) {
        cout << "Invalid choice; please try again." << endl;
        userInput = toUpperCase(getLine ("a)nimate, t)ick, q)uit? "));
    }

    char userSelection = userInput.at(0); //convert string to char for use in the switch statement in main method
    return userSelection;

}

/*
 * This populateFirstGeneration method creates a life matrix based on user
 * selection of a file containing seeded data.
*/
void populateFirstGeneration(LifeGUI& lifeGUIMatrix, Grid<char>& lifeMatrix) {

    ifstream input;
    string line;
    string fileName;

    fileName   = getLine("Grid input file name? ");

    // validate that user-entered filename exists before continuing
    while (!fileExists(fileName)) {
        cout << "Unable to open that file.  Try again." << endl;
        fileName   = getLine("Grid input file name? ");
    }

    input.open(fileName);

    //get number of rows from input file:
    getLine(input,line);
    int rows = stringToInteger(line);

    //get number of columns from input file:
    getLine(input,line);
    int columns = stringToInteger(line);

    //resize grid variable
    lifeMatrix.resize(rows, columns);
    lifeGUIMatrix.resize(rows,columns);

    //populate grid with data from file:

    for (int r=0; r <rows; r++) {
        getLine(input, line);

        for (int c=0; c < columns; c++) {
            lifeMatrix[r][c] = line[c];     
           cout << lifeMatrix[r][c];    //display matrix row in console window

           if (line[c] == 'X') {
                  lifeGUIMatrix.drawCell(r, c, true);
        }

        }//end row loop
        cout << endl;
    }//end column loop


}//end populateFirstGeneration

/*
 * This populateNewGeneration method applies the game of life rules to a reference of the life matrix,
 * creates a new generation and displays the results to the console.
*/
void populateNewGeneration(LifeGUI& lifeGUIMatrix, Grid<char>& lifeMatrix) {

    int maxRows = lifeMatrix.numRows();
    int maxColumns = lifeMatrix.numCols();
    int livingNeighbors = 0;
    Grid<char> matrixCopy(maxRows,maxColumns);
    matrixCopy = lifeMatrix; //copy the matrix and use the copy to create the new generation

    lifeGUIMatrix.resize(maxRows,maxColumns);//to clear the GUI grid on each iteration. I wasn't sure how else to do this.

    //iterate over each location in the grid:
    for (int currentRow = 0; currentRow < maxRows; currentRow++) {
        for (int currentColumn = 0; currentColumn < maxColumns; currentColumn++) {

            //and then test each location's neighbors for a living cell

            for (int neighborRows = -1; neighborRows < 2; neighborRows++) {
                for (int neighborCols = -1; neighborCols < 2; neighborCols++ ) {
                    if (lifeMatrix.inBounds((currentRow - neighborRows),(currentColumn - neighborCols))
                            && lifeMatrix[currentRow - neighborRows][currentColumn - neighborCols] == 'X') {
                        livingNeighbors += 1;
                    }
                }

            }//end evaluation of neighbor cells

            //don't count the location itself!:

            if (lifeMatrix[currentRow][currentColumn]=='X') {
                livingNeighbors -= 1;
            }

            //apply rules to determine if the current location will have a living cell based on the number of living neighbors:

            switch (livingNeighbors) {
            case 0: //A location that has zero or one neighbors will be empty in the next generation. If a cell was there, it dies.
                matrixCopy[currentRow][currentColumn] = '-';
                break;
            case 1: //A location that has zero or one neighbors will be empty in the next generation. If a cell was there, it dies.
                matrixCopy[currentRow][currentColumn] = '-';
                break;
            case 2: //A location with two neighbors is stable. If it had a cell, it still contains a cell. If it was empty, it's still empty.
                matrixCopy[currentRow][currentColumn] = lifeMatrix[currentRow][currentColumn];
                break;
            case 3: //A location with three neighbors will contain a cell in the next generation. If it was unoccupied before, a
                //new cell is born. If it currently contains a cell, the cell remains.
                matrixCopy[currentRow][currentColumn] = 'X';
                break;
            default: //A location with four or more neighbors will be empty in the next generation. If there was a cell in that
                //location, it dies of overcrowding.
                matrixCopy[currentRow][currentColumn] = '-';
                break;
            }

            cout << matrixCopy[currentRow][currentColumn]; //print new generation to console
            livingNeighbors = 0;


            if (matrixCopy[currentRow][currentColumn] == 'X') {
                   lifeGUIMatrix.drawCell(currentRow, currentColumn, true);
         }

        } //end iteration over columns

        cout << endl;

    } //end iteration over rows

    lifeMatrix = matrixCopy;

}//end populateNewGeneration


/*
 * This populateRandomGeneration method generates a random life matrix based on user input
 * and prints it to the console.
*/
void populateRandomGeneration(LifeGUI& lifeGUIMatrix, Grid<char>& lifeMatrix) { //***new in extras file***

    cout << endl;
    cout << "Ok, I'll generate a random grid colony, but first tell me this:" << endl;

    int rows = getInteger("How many rows?: ");
    int columns = getInteger("How many columns?: ");

    cout << endl;
    cout << "Ok, here is your colony populated randomly:" << endl;
    cout << endl;

    lifeMatrix.resize(rows,columns);
    lifeGUIMatrix.resize(rows, columns);

    for (int r = 0; r < rows; r ++) {
        for (int c = 0; c < columns; c++) {
            lifeMatrix[r][c] = randomCell();
            cout << lifeMatrix[r][c];

            if (lifeMatrix[r][c] == 'X') {
                lifeGUIMatrix.drawCell(r, c, true);
            }
        }//end row loop

        cout << endl;

    }//end column loop

}

/*
 * This randomCell method generates an '-' or a 'X' randomly.
 * This code was copied from the textbook 'Programming Abstraction in C++' by Eric Roberts, p. 96
*/
char randomCell() {

    if (randomChance(0.50)){
        return 'X';
    } else {
        return '-';
    }
}



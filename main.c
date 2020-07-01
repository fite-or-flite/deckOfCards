#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int deck[52];
char hand[7][2];


char suit[4] = {'C', 'D', 'S', 'H'};
char face[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};

void initDeck();
void shuffleDeck();
void printDeck();
void printCard(int);
void dealHand();

int main() {

    int cardNum;
    char quit, junk;

    initDeck();

    while (quit != 'q') {
        printf("Your deck.");
        printDeck();

        shuffleDeck();
        printDeck();

        printf("Hit q to quit; any other key to continue.\n");
        quit = getchar();
        junk = getchar();
    }
    return 0;
}

void initDeck(){
//initialize deck starting at 0 for 2-clubs, 1 for 2-diamonds, 2 for 2-spades,...51 for Ace-Hearts
    for (int i = 0; i < 52; i++)
        deck[i] = i;
}

void shuffleDeck(){

    srand(time(NULL));
    int y, temp;

    printf("\n...shuffling...\n");

    for (int x = 51; x > 0; x--) {
            y = rand() % x; //gets rando num bet 0 & 52
            temp = deck[x];
            deck[x] = deck[y];
            deck[y] = temp;
    }
}

void printDeck(){
    printf("\n");
    for (int i = 0; i < 52; i++)
        printf(" %d ", deck[i]);
    printf("\n");

}

void printCard(int cardNum){

}

void dealHand() {

    for (int j = 0; j < 7; j++)

}

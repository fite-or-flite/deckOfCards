#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int deck[52];

void printDeck();
void printCard(int);
void shuffleDeck(); //giving me two 0s for some reason

int main() {

    int cardNum = 0;
    int value = 2;
    char suit, face;

    //initialize deck starting at 0 for 2-clubs, 1 for 2-diamonds, 2 for 2-spades,...51 for Ace-Hearts
    for (int i = 0; i < 52; i++)
        deck[i] = i;

    printf("Your deck has 52 cards.\n");
    printDeck();

    printf("\nShuffling...\n");
    shuffleDeck();
    printf("\n");
    printDeck();

    printf("\nfirst card listed is: \n");
    printCard(deck[0]);

    return 0;
}

void printDeck() {
    for (int i = 0; i < 52; i++)
        printf(" %d ", deck[i]);
}

void printCard(int cardNum) {

    int value = 2;
    char suit, face;
    //determine card value
    if (cardNum > 3) //else value = 2;
        value = (cardNum / 4) + 2;

    //determine suit
    if (cardNum % 4 == 0)
        suit = 'C';
    else if (cardNum % 4 == 1)
        suit = 'D';
    else if (cardNum % 4 == 2)
        suit = 'S';
    else if (cardNum % 4 == 3)
        suit = 'H';
    else printf("this isn't a card, wtf\n");

    //adjusting for face cards
    if (value <= 10) {
        printf("\nCard number %d is: %d-%c", cardNum, value, suit);
    }

    else if (value == 11){ //jack
        face = 'J';
        printf("\nCard number %d is: %c-%c", cardNum, face, suit);
    }

    else if (value == 12) {//queen
        face = 'Q';
        printf("\nCard number %d is: %c-%c", cardNum, face, suit);
    }

    else if (value == 13) {// king
        face = 'K';
        printf("\nCard number %d is: %c-%c", cardNum, face, suit);
    }

    else if (value == 14) {//ace
        face = 'A';
        printf("\nCard number %d is: %c-%c\n", cardNum, face, suit);
    }
}

void shuffleDeck() {
    srand(time(NULL));
    int y, temp;

    for (int x = 52; x > 0; x--) {
            y = rand() % x;
            temp = deck[x];
            deck[x] = deck[y];
            deck[y] = temp;
    }

}

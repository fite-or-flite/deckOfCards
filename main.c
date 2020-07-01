//yet another rewritten deck of cards program

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffleDeck(int*);
void printDeck(int*);
void printHand(int*, int);
void drawCard(int*, int, int*);
void sortCards(int*, int);

char suit[4] = {'C', 'D', 'S', 'H'};
char face[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};


int main()
{
    int deck[52] = {0};
    int pHand[52] = {0};
    int cHand[52] = {0};
    int pNumCards = 0;
    int cNumCards = 0;
    int *deckPosition = deck;

    //populate deck
    for (int i = 0; i < 52; i++)
        deck[i] = i;

    shuffleDeck(deck);
    printDeck(deck);

    //deal hands
    //could have made into function, but then can't change deckposition or xnumcards values
    printf("\nDealing 7 cards each.\n");
    for (int n = 0; n < 7; n++) {
        pHand[n] = *deckPosition;
        deckPosition++;
        pNumCards++;

        cHand[n] = *deckPosition;
        deckPosition++;
        cNumCards++;
    }

    //print hands
    printf("\nYou:");
    printHand(pHand, pNumCards);
    printf("\nComputer:");
    printHand(cHand, cNumCards);

    //draw a card
    drawCard(pHand, pNumCards, deckPosition);
    pNumCards++; //couldn't change value inside function
    deckPosition++; //maybe add some pointers to pass instead?

    printHand(pHand, pNumCards);

    return 0;
}

void shuffleDeck(int deck[]) {
    printf("\n...Shuffling...\n");
    srand(time(NULL));
    int y, temp;

    for (int x = 51; x > 0; x--) {
            y = rand() % x;
            temp = deck[x];
            deck[x] = deck[y];
            deck[y] = temp;
    }

}

void printDeck(int deck[]) {
    printf("Your deck: ");
    for (int j = 0; j < 52; j++){
        printf(" %d ", deck[j]);
    }

}

void printHand(int hand[], int numCards) {
    sortCards(hand, numCards);
    printf("\nHand: ");
    for (int i = 0; i < numCards; i++) {
        printf(" %c-%c ", face[hand[i] / 4], suit[hand[i] % 4]);

    }
    printf("\n");
}

void drawCard(int hand[], int numCards, int *deckPosition) {
    printf("\n...Drawing a card...\n");
    hand[numCards] = *deckPosition; //numCards is the next open space in the array, not last element
}

void sortCards(int hand[], int cardsInHand) {
    int temp;
    for (int i = 0; i < cardsInHand - 1; i++) {
        for (int j = 0; j < cardsInHand - i - 1; j++) {
            if (hand[j] > hand[j+1]) {
                temp = hand[j];
                hand[j] = hand[j+1];
                hand[j+1] = temp;
            }
        }
    }

}

#include <stdio.h>
#include <stdlib.h>

int deck[52];
int pDeck[52];
int cDeck[52];

int cardsInHand = 7;
int dcount = 0;
int cCardsInHand = 7;

void printDeck();
void dealHands();
int drawCard(int);
void printHand();


int main() {
    //initialize deck
    for (int i = 0; i < 52; i++){
        deck[i] = i;
    }

    int player = 1;

    printDeck();
    dealHands();
    printHand();
    printf("\ndcounter: %d\nvalue of deck[dcount]: %d", dcount, deck[dcount]);

    drawCard(player);
    printHand();
    printf("\ndcounter: %d\nvalue of deck[dcount]: %d", dcount, deck[dcount]);

    return 0;
}

void printDeck() {
    for (int i = 0; i < 52; i++)
            printf(" %d ", deck[i]);
}

void dealHands() {

    for (int j = 0; j < cardsInHand; j++) {
        pDeck[j] = deck[dcount];
        dcount++;
        cDeck[j] = deck[dcount];
        dcount++;
    }
    printf("\ndcount ends at: %d\n", dcount);
}

void printHand() {
    printf("Your hand: ");
    for (int k = 0; k < cardsInHand; k++)
        printf(" %d ", pDeck[k]);
    printf("\nComputer's hand: ");
    for (int n = 0; n < cCardsInHand; n++)
        printf(" %d ", cDeck[n]);
}

int drawCard(int player) {

    printf("\n\nDrawing a card...\n");

    if (player == 1) {
        cardsInHand++;
        pDeck[cardsInHand] = deck[dcount];
    }
    else if (player == 2) {
        cCardsInHand++;
        cDeck[cCardsInHand] = deck[dcount];
    }
    else printf("\nwhat the actual fuck\n");

    dcount++;
    return 0;
}

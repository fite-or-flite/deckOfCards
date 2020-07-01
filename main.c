//program to establish common card deck functions
//too many globals; need to rewrite using pointers


//sortcards using cardsinhand only; not ccardsinhand


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int deck[52];
int cardsInHand = 7;
int cCardsInHand = 7;
int dcounter = 0;


int hand[52];
int compHand[52];

char suit[4] = {'C', 'D', 'S', 'H'};
char face[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};

void initDeck();
void shuffleDeck();
void printDeck();
void printCard(int);
void dealHand();
void printHand(int []); //for printing player's hand; problems if comp and player dont have same no of cards
void drawCard(int []);
void cDrawCard(int []);
void sortCards(int [], int);

int main() {

    int cardNum;

    //getting deck ready
    initDeck();
    printDeck();
    shuffleDeck();
    printDeck();
    dealHand();

    printf("\n-----------------------\n");

    printf("\nYour hand:");
    printHand(hand);
    printf("\n\t   ");
    for (int n = 0; n < cardsInHand; n++)
        printf(" %d", hand[n]);

    sortCards(hand, cardsInHand);
    printf("\nYour hand:");
    printHand(hand);
    printf("\n\t   ");
    for (int n = 0; n < cardsInHand; n++)
        printf(" %d", hand[n]);


    printf("\nComputer's hand: ");
    printHand(compHand);
    printf("\n\t\t");
    for (int k = 0; k < cCardsInHand; k++)
        printf(" %d ", compHand[k]);
    sortCards(compHand, cCardsInHand);
    printf("\nComputer's hand: ");
    printHand(compHand);
    printf("\n\t\t");
    for (int k = 0; k < cCardsInHand; k++)
        printf(" %d ", compHand[k]);
    printf("\n-----------------------\n");
    cardNum = 51;
    printf("\nCard number %d is: ", cardNum);
    printCard(cardNum);
    printf("\n-----------------------\n");

    printf("\nDrawing a card\n");
    drawCard(hand);
    cDrawCard(compHand);

    printf("\nYour hand:");
    sortCards(hand, cardsInHand);
    printHand(hand);
    printf("\n\t   ");
    for (int n = 0; n < cardsInHand; n++)
        printf(" %d", hand[n]);
    printf("\nComputer's hand: ");
    sortCards(compHand, cCardsInHand);
    printHand(compHand);
    printf("\n\t\t");
    for (int p = 0; p < cCardsInHand; p++)
        printf(" %d", compHand[p]);

    printf("\n-----------------------\n");

    return 0;
}

void initDeck(){
//initialize deck
//starting at 0 for 2-clubs, 1 for 2-diamonds, 2 for 2-spades,...51 for Ace-Hearts
    for (int i = 0; i < 52; i++)
        deck[i] = i;
}

void shuffleDeck(){

    srand(time(NULL));
    int y, temp;

    printf("\n...shuffling...\n");

    for (int x = 51; x > 0; x--) { //x has to be numCards - 1; otherwise get two zeros
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
    printf("%c-%c", face[cardNum / 4], suit[cardNum % 4]);
}

void dealHand() {

    for (int j = 0; j < cardsInHand; j++) {
        hand[j] = deck[dcounter];
        dcounter++;
        compHand[j] = deck[dcounter];
        dcounter++;
    }
}

void printHand(int hand[]) {
    //sortCards(hand, cardsInHand);
    for (int i = 0; i < cardsInHand; i++)
        printf(" %c-%c ", face[hand[i] / 4], suit[hand[i] % 4]);
}

void drawCard(int hand[]) {
    hand[cardsInHand] = deck[dcounter];
    cardsInHand++;
    dcounter++;
 }

void cDrawCard(int compHand[]) {
    compHand[cCardsInHand] = deck[dcounter];
    cCardsInHand++;
    dcounter++;

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

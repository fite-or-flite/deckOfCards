//chris fite
//070220
//edited 071120

//yet another rewritten deck of cards program
//finishing poker hand ranking mechanisms (specifically, comparing hands with equal rank)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void mainMenu();
void shuffleDeck(int[]);
void printDeck(int[]);
void printHand(int[], int);
void drawCard(char);
void sortCards(int[], int);
void dealHands(int);
void blackJack();
int totalOfCards(int[], int);
void poker();
int rankPokerHand(int[]);
int checkNumPairs(int[]);
void compareEqualRanks();
int checkHighSuit(int, int);
void pWin();
void cWin();

char suit[4] = {'C', 'D', 'S', 'H'};
char face[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};
//stupid global variables
int deck[52] = {0};
int pHand[52] = {0};
int cHand[52] = {0};
int pNumCards = 0;
int cNumCards = 0;
int *deckPosition = deck;

int main()
{
    //populate deck
    for (int i = 0; i < 52; i++)
        deck[i] = i;

//    mainMenu();
    poker();
    return 0;
}

void mainMenu() {
    char choice, garbage;
    printf("\nWelcome to the Casino Royale");
    printf("\n\nWhich game would you like to play?");
    printf("\n(a) 5 card draw");
    printf("\n(b) Blackjack");
    printf("\n(q) Quit\n");
    scanf("%c%c", &choice, &garbage);
    switch(choice) {
        case 'a':
        poker();
            break;
        case 'b':
            blackJack();
            break;
        case 'q':
            printf("\nbye bye");
            break;
        default:
            break;
    }
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

void drawCard(char player) {
    printf("\n...Drawing a card...\n");
    if (player == 'p') {
        pHand[pNumCards] = *deckPosition; //numCards is the next open space in the array, not last element
        pNumCards++;
    }
    else if (player == 'c') {
        cHand[cNumCards] = *deckPosition;
        cNumCards++;
    }
    deckPosition++;
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

void dealHands(int numCardsInHand){
    printf("\nDealing %d cards each.\n", numCardsInHand);
    for (int n = 0; n < numCardsInHand; n++) {
        pHand[n] = *deckPosition;
        deckPosition++;
        pNumCards++;

        cHand[n] = *deckPosition;
        deckPosition++;
        cNumCards++;
    }
}

void blackJack() {
    char choice = 'd', garbage;
    printf("\nLet's play blackjack!");
    shuffleDeck(deck);
    dealHands(2);
    while ((choice != 'h') && (totalOfCards(pHand, pNumCards) < 21) && (totalOfCards(cHand, cNumCards) < 21)) {
        printf("\nYou:");
        printHand(pHand, pNumCards);
        printf("\ntotal of your cards: %d", totalOfCards(pHand, pNumCards));
        printf("\nWhat would you like to do? (d)raw or (h)old\n");
        scanf("%c%c", &choice, &garbage);
        if (choice == 'd') {
            drawCard('p');
            if (totalOfCards(cHand, cNumCards) < 17)
                drawCard('c');
        }
    }
    printHand(pHand, pNumCards);
    printHand(cHand, cNumCards);
    if (totalOfCards(pHand, pNumCards) > 21)
        printf("\nBusted!");
    else if ((totalOfCards(pHand, pNumCards) == 21)
        || (totalOfCards(pHand, pNumCards) >= totalOfCards(cHand, cNumCards))
        || (totalOfCards(cHand, cNumCards) > 21)) {
            pWin();
        }
    else if (totalOfCards(pHand, pNumCards) < totalOfCards(cHand, cNumCards)) cWin();
    printf("\nTotals:\nplayer: %d computer: %d", totalOfCards(pHand, pNumCards), totalOfCards(cHand, cNumCards));
}

int totalOfCards(int hand[], int numCards) {
    int total = 0;
    int cardValue = 0;
    for (int i = 0; i < numCards; i++) {
        cardValue = (hand[i] / 4) + 2;
        if (cardValue > 10) {
            if (cardValue == 14) cardValue = 11;
            else cardValue = 10;
        }
        total += cardValue;
    }
    return total;
}

void poker(){
    char choice = 'y', garbage;
    int choicePos[3] = {0}; //array to hold pass choices
    int choiceCtr = 0, changeMe = 0;
    char handNames[11][20] = {"nothing", "High card", "Pair", "Two pair", "Three of a kind", "Straight", "Flush", "Full house", "Four of a kind", "Straight flush", "Royal flush"};
    printf("\nLet's play poker!\n");
    shuffleDeck(deck);
    dealHands(5);

    //fake hands for testing
    //four aces
    //int x = 51; for (int i = 0; i<5;i++) {pHand[i] = x;x--;}
    //royal flush
    //int x = 51; for (int i=0;i<5;i++) {pHand[i]=x;x-=4;}
    //straight flush
    //int x=0; for (int i=0;i<5;i++){pHand[i]=x;x+=4;}
    //striaght
    //int x=0; for(int i=0;i<5;i++){pHand[i]=x;x+=5;} pHand[4]-=2;
    //full house
    //int x=0; for(int i=0;i<3;i++){pHand[i]=x;x++;} x=4; for(int i=3;i<5;i++){pHand[i]=x;x++;}
    //3of akind
    //int x=0; for(int i=0;i<3;i++){pHand[i]=x;x++;} pHand[3]=50;pHand[4]=45;
    //2pair
    //int x=0; for(int i=0;i<2;i++){pHand[i]=x;x++;} x=10; for(int i=2;i<4;i++){pHand[i]=x;x++;}
    //pair
    //int x=0; for(int i=0;i<2;i++){pHand[i]=x;x++;}

    //show phand with letters under to pass back if desired
    printHand(pHand, pNumCards);
    printf("\t0    1    2    3    4");
    printf("\nWould you like to pass back a card? (%d remaining)\n", (3 - choiceCtr));
    scanf("%c%c", &choice, &garbage);
    while ((choice == 'y') && ((3 - choiceCtr) > 0)) {
        printf("\nWhich card number?\n");
        scanf("%d%c", &choicePos[choiceCtr], &garbage);
        choiceCtr++;
        if ((3 - choiceCtr) > 0) {
            printf("\nWould you like to pass back a card? (%d remaining)\n", (3 - choiceCtr));
            scanf("%c%c", &choice, &garbage);
        }
    }
    //redeal cards to spots indicated
    for (int i = 0; i < (sizeof(choicePos)/sizeof(choicePos[0])); i++) {
        changeMe = choicePos[i];
        pHand[changeMe] = *deckPosition;
        deckPosition++;
    }
    printHand(pHand, pNumCards);

    //compare phand to chand; higher rankPokerHand() wins
    if (rankPokerHand(pHand) > rankPokerHand(cHand))
        pWin();
    else if (rankPokerHand(pHand) == rankPokerHand(cHand))
        compareEqualRanks();
    else cWin();
    //show both hands
    printf("\nYour hand: %s", handNames[rankPokerHand(pHand)]);
    printHand(pHand, pNumCards);
    printf("\nComputer's hand: %s", handNames[rankPokerHand(cHand)]);
    printHand(cHand, cNumCards);

}

int rankPokerHand(int hand[]) {
//only 5 cards in hand
    char bestHand;
    int returnValue = 0;
    bool flush = false;
    bool straight = false;
    bool pair = false;
    int pairCtr = 0;
    //convert hand into card struct
    struct card {
        char s;
        int f;
    };
    struct card Cards[5];
    for (int i = 0; i < 5; i++) {
        Cards[i].s = suit[hand[i] %4];
        Cards[i].f = hand[i] / 4 + 2;
    }
    //determine best hand
    //flushes
    for (int i = 1; i < 5; i++) {
        if (Cards[i - 1].s == Cards[i].s)
            flush = true;
        else {
            flush = false;
            break;
        }
    }

    //straights
    for (int i = 4; i > 0; i--) {
        if ((Cards[i].f - 1) == (Cards[i - 1].f))
            straight = true;
        else {
            straight = false;
            break;
        }
    }

    //pairs
    if (flush == false && straight == false && checkNumPairs(hand) > 0)
        pair = true;

    if (flush == true) {
        if (straight == true) {
            if (Cards[4].f == 14)
                bestHand = 'r';
            else bestHand = 'S';
        }
        else bestHand = 'f';
    }
    else if (straight == true) {
        bestHand = 's';
    }
    else if (pair == true) {
    //check num of pairs
/*  checkNumPairs() return values:
    0 - failure to detect pairs
    1 - one pair
    2 - two pairs
    3 - three of a kind
    4 - full house
    6 - four of a kind
*/
        pairCtr = checkNumPairs(hand);
        switch(pairCtr) {
            case 0: //should never happen
                bestHand = 'c';
                break;
            case 1:
                bestHand = 'p';
                break;
            case 2:
                bestHand = '2';
                break;
            case 3:
                bestHand = '3';
                break;
            case 4:
                bestHand = 'h';
                break;
            case 6:
                bestHand = '4';
                break;
            default:
                break; //error handling here?
        }
    }
    else { //high cards
        bestHand = 'c';
    }

    switch(bestHand) { //should this be an array instead?
        case 'r':
            //royal flush
            returnValue = 10;
            break;
        case 'S':
            //straight flush
            returnValue = 9;
            break;
        case '4':
            //four of a kind
            returnValue = 8;
            break;
        case 'h':
            //full house
            returnValue = 7;
            break;
        case 'f':
            //flush
            returnValue = 6;
            break;
        case 's':
            //straight
            returnValue = 5;
            break;
        case '3':
            //3 of a kind
            returnValue = 4;
            break;
        case '2':
            //two pair
            returnValue = 3;
            break;
        case 'p':
            //pair
            returnValue = 2;
            break;
        case 'c':
            //high card
            returnValue = 1;
            break;
        default:
            break;
    }
    return returnValue;
}

int checkNumPairs(int hand[]) {
/*  return values:
    0 - failure to detect pairs
    1 - one pair
    2 - two pairs
    3 - three of a kind
    4 - full house
    6 - four of a kind
*/
//convert hand into card struct
    struct card {
        char s;
        int f;
    };
    struct card Cards[5];
    for (int i = 0; i < 5; i++) {
        Cards[i].s = suit[hand[i] %4];
        Cards[i].f = hand[i] / 4 + 2;
    }

    int returnValue = 0, numPairs = 0, pairCtr = 0;
    int pairArray[5] = {0};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if ((Cards[i].f == Cards[j].f) && (i != j)) {
                numPairs++;
            }
        }
        pairArray[i] = numPairs;
        numPairs = 0;
    }

    for (int i = 0; i < 5; i++) {
        pairCtr += pairArray[i];
        }
    returnValue = pairCtr / 2;
    return returnValue;
}

void compareEqualRanks() {
    int pRank = rankPokerHand(pHand);
    int cRank = rankPokerHand(cHand);
    int pPairA, pPairB, cPairA, cPairB;
    //convert hands to structs
    struct card {
        char s;
        int f;
    };
    struct card pCards[5];
    struct card cCards[5];
    for (int i = 0; i < 5; i++) {
        pCards[i].s = suit[pHand[i] %4];
        pCards[i].f = pHand[i] / 4 + 2;
        cCards[i].s = suit[cHand[i] %4];
        cCards[i].f = cHand[i] / 4 + 2;
    }

    if (pRank != cRank) printf("\nIs there a problem here?");
    else {
        switch(pRank) {
            case 10:
                //royal flush
                //suits rank equal
                printf("\nYou tie!");
                printf("\n-\\/('_')\\/-");
                break;
            case 9:
            case 6:
            case 5:
                //straight flush, flush, straight
                //check highest card, suits rank equal
                if (pHand[4] > cHand[4])
                    pWin();
                else if (pHand[4] < cHand[4])
                    cWin();
                break;
            case 8:
            case 7:
            case 4:
                //four of a kind, full house, 3 of a kind
                //check high card in 3oak, cannot be equal
                //find 3ofak value (xCards[i].f = xPairA)
                //compare
                break;
            case 3:
                //two pair
                //check high card pair, then low card pair, then kicker
                //find pair values (xPairA, xPairB), compare
                //if equal, find highest card, not incl pair
                break;
            case 2:
                //pair
                //check high card pair, then high kicker, mid kicker, low kicker
                //find pair values (xPairA), compare
                //if equal, find highest card, not incl pair, etc
                break;
            case 1:
                //high card
                //highest card wins, the high kicker, etc
                for (int i = 4; i >= 0; i--) {
                    if (pHand[i] > cHand[i]) {
                        pWin();
                        printf("\nYou have the high card!");
                        break;
                    }
                    else if (pHand[i] < cHand[i]) {
                        cWin();
                        printf("\nComputer has the high card!");
                        break;
                    }
                }
                break;
            default:
                break;
        }
    }
}

int checkHighSuit (int pCard, int cCard) {
    int returnValue = 0;

}

void pWin() {
    printf("\nYou win!");
}

void cWin() {
    printf("\nYou lose!");
}

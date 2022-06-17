#include <iostream>
#include "americanCoinType.h"

using namespace std;

//---------------------------------------------------------------------------
// ShowMenu
//---------------------------------------------------------------------------
void showMenu()
{
    cout << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "|  Selection Menu                                            |" << endl;
    cout << "|  A:- +   (Addition)                                        |" << endl;
    cout << "|  B:- -   (Subtraction)                                     |" << endl;
    cout << "|  C:- *   (Multiplication)                                  |" << endl;
    cout << "|  D:- -=  (coinBox2 -= coinBox1)                            |" << endl;
    cout << "|  E:- x++ (coinBox1 postincrement; coinBox2 postincrement)  |" << endl;
    cout << "|  F:- ++x (coinBox1 preincrement; coinBox2 preincrement)    |" << endl;
    cout << "|  G:- x-- (coinBox1 postdecrement; coinBox2 postdecrement)  |" << endl;
    cout << "|  H:- --x (coinBox1 predecrement; coinBox2 predecrement)    |" << endl;
    cout << "|  I:- ==  (compare: if (coinBox1 == coinBox2))              |" << endl;
    cout << "|  J:- !=  (compare: if (coinBox1 != coinBox2))              |" << endl;
    cout << "|  K:- <   (compare: if (coinBox1 < coinBox2))               |" << endl;
    cout << "|  L:- >   (compare: if (coinBox1 > coinBox2))               |" << endl;
    cout << "|  M:- <=  (compare: if (coinBox1 <= coinBox2))              |" << endl;
    cout << "|  N:- >=  (compare: if (coinBox2 >= coinBox1))              |" << endl;
    cout << "|  O:- =   (Assignment operator; coinBox2 = coinBox1)        |" << endl;
    cout << "|  P:-     (Print CoinBoxs Value)                            |" << endl;
    cout << "|  R:-     (Insert Coins to Coinbox1)                        |" << endl;
    cout << "|  S:-     (Insert Coins to Coinbox2)                        |" << endl;
    cout << "|  Q:-     (Exit)                                            |" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << endl;
}

int main()
{
    char namecoinBox1[] = "coinBox1";
    char namecoinBox2[] = "coinBox2";
    char nameCoinBoxRes[] = "coinBoxRes";

    coinsBox coinBox1(10, 10, 10, 10, 10, namecoinBox1);
    coinsBox coinBox2(5, 5, 5, 5, 5, namecoinBox2); //12,10
    coinsBox coinBoxRes(0, 0, 0, 0, 0, nameCoinBoxRes);

    char choice;
    bool repeat = true;

    cout << coinBox1 << endl;
    cout << coinBox2 << endl;

    do
    {
        showMenu();
        cout << endl
             << "Make your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 'A':
        case 'a':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            coinBoxRes = (coinBox1 + coinBox2);
            coinBoxRes.setName(nameCoinBoxRes);
            cout << "ADD: coinBoxRes = coinBox1 + coinBox2 " << endl;
            cout << coinBoxRes << endl << endl;
            break;

        case 'B':
        case 'b':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            coinBoxRes = coinBox1 - coinBox2;
            coinBoxRes.setName(nameCoinBoxRes);
            cout << "SUBTRACT: coinBoxRes = coinBox1 - coinBox2 " << endl;
            cout << coinBoxRes << endl << endl;
            break;

        case 'C':
        case 'c':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            coinBoxRes = coinBox1 * coinBox2;
            coinBoxRes.setName(nameCoinBoxRes);
            cout << "MULTIPLICATION: coinBoxRes =  coinBox1 * coinBox2 " << endl;
            cout << coinBoxRes << endl << endl;
            break;

        case 'D':
        case 'd':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            coinBox2 -= coinBox1;
            coinBox2.setName(namecoinBox2);
            cout << "SUBTRACT: coinBox2 -= coinBox1" << endl;
            cout << coinBox2 << endl;
            break;

        case 'E':
        case 'e':
            cout << endl
                 << coinBox1 << endl;
            cout << "coinBox1 postincrement: " << endl;
            coinBox1++;
            cout << "After postincrement : " << endl;
            cout << coinBox1 << endl;

            cout << endl
                 << coinBox2 << endl;
            cout << "coinBox2 postincrement: " << endl;
            coinBox2++;
            cout << "After postincrement : " << endl;
            cout << coinBox2 << endl;
            break;
        case 'F':
        case 'f':
            cout << endl
                 << coinBox1 << endl;
            cout << "coinBox1 preincrement: " << endl;
            ++coinBox1;
            cout << "After preincrement : " << endl;
            cout << coinBox1 << endl;

            cout << endl
                 << coinBox2 << endl;
            cout << "coinBox2 preincrement: " << endl;
            ++coinBox2;
            cout << "After preincrement : " << endl;
            cout << coinBox2 << endl;
            break;
        case 'G':
        case 'g':
            cout << endl
                 << coinBox1 << endl;
            cout << "coinBox1 postdecrement: " << endl;
            coinBox1--;
            cout << "After postdecrement : " << endl;
            cout << coinBox1 << endl;

            cout << endl
                 << coinBox2 << endl;
            cout << "coinBox2 postdecrement: " << endl;
            coinBox2--;
            cout << "After postdecrement : " << endl;
            cout << coinBox2 << endl;
            break;
        case 'H':
        case 'h':
            cout << endl
                 << coinBox1 << endl;
            cout << "coinBox1 predecrement: " << endl;
            --coinBox1;
            cout << "After predecrement : " << endl;
            cout << coinBox1 << endl;

            cout << endl
                 << coinBox2 << endl;
            cout << "coinBox2 predecrement: " << endl;
            --coinBox2;
            cout << "After predecrement : " << endl;
            cout << coinBox2 << endl;
            break;
        case 'I':
        case 'i':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            cout << endl
                 << "compare: if (coinBox1 == coinBox2)" << endl;
            if (coinBox1 == coinBox2)
                cout << "coinBox1 and coinBox2 are equal." << endl;
            else
                cout << "coinBox1 and coinBox2 are not equal." << endl;
            break;
        case 'J':
        case 'j':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            cout << endl
                 << "compare: if (coinBox1 != coinBox2)" << endl;
            if (coinBox1 != coinBox2)
                cout << "coinBox1 and coinBox2 are not equal." << endl;
            else
                cout << "coinBox1 and coinBox2 are equal." << endl;
            break;
        case 'K':
        case 'k':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            cout << endl
                 << "compare: if (coinBox1 < coinBox2)" << endl;
            if (coinBox1 < coinBox2)
                cout << "coinBox1 is less than coinBox2." << endl;
            else
                cout << "coinBox1 is NOT less than coinBox2." << endl;
            break;
        case 'L':
        case 'l':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            cout << endl
                 << "compare: if (coinBox1 > coinBox2)" << endl;
            if (coinBox1 > coinBox2)
                cout << "coinBox1 is greater than coinBox2." << endl;
            else
                cout << "coinBox1 is NOT greater than coinBox2." << endl;
            break;
        case 'M':
        case 'm':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            cout << endl
                 << "compare: if (coinBox1 <= coinBox2)" << endl;
            if (coinBox1 <= coinBox2)
                cout << "coinBox1 is less than or equal to coinBox2." << endl;
            else
                cout << "coinBox1 is NOT less than or equal to coinBox2." << endl;
            break;
        case 'N':
        case 'n':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            cout << endl
                 << "compare: if (coinBox2 >= coinBox1)" << endl;
            if (coinBox2 >= coinBox1)
                cout << "coinBox2 is greater than or equal to coinBox1." << endl;
            else
                cout << "coinBox2 is NOT greater than or equal to coinBox1." << endl;
            break;
        case 'O':
        case 'o':
            cout << endl;
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            cout << "Assignment: coinBox2=coinBox1" << endl;
            coinBox2 = coinBox1;
            cout << coinBox2 << endl;
            break;
        case 'P':
        case 'p':
            cout << coinBox1 << endl;
            cout << coinBox2 << endl;
            break;
        case 'q':
        case 'Q':
            repeat = false;
            break;
        case 'r':
        case 'R':
            cout << "Insert Coins to CoinBox1 " << endl;
            cin >> coinBox1;
            cout << endl;
            break;
        case 's':
        case 'S':
            cout << "Insert Coins to CoinBox2 " << endl;
            cin >> coinBox2;
            cout << endl;
            break;

        default:
            showMenu();
            cout << endl
                 << "Make your choice: ";
            cin >> choice;

            break;
        }
    } while (repeat);

    return 0;
}

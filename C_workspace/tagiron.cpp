#include <iostream>
#include <ctime>
#include <stdlib.h>
// below header file is Required for sort function
#include <algorithm>
#include <windows.h>

using namespace std;

// type definition
struct user
{
    int rednum[5];
    int bluenum[5];
    int greennum[2];
    int redcount;
    int bluecount;
    int greencount;
    int mynumber[5];
    int oddNum;
    int maxDiff;
    int SumFirstThree;
    int SumMiddleThree;
    int SumRightThree;
    int numPos[5];
    int sequentialOrder[5];
    int NeighborSameColor[5];
    int color[5];
    int pairSameNum;
    int redSum;
    int blueSum;
    int TotalSum;
};

/* global variables definition*/
int question_index[6];
string questions[26];
int questionIdxRandom[26];

int q_Idx;

user Daisy;
user Melon;
user me;

/* Function declaration */
void question_Answer(int num);


/* Function implmentation below */
void SetColor(unsigned short ForeColor = 7, unsigned short BackGroundColor = 0)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, ForeColor | BackGroundColor);
}

void parseInfo(user *ptr)
{
    int i;
    int j;
    int num;
    int found;
    int NoSearch;

    for (i = 0; i < 5; i++)
    {
        if ((ptr->mynumber[i] == 5) || (ptr->mynumber[i] == 15))
        {
            ptr->greennum[ptr->greencount] = 5;
            ptr->mynumber[i] = 5;
            ptr->greencount++;
        }
        else if (ptr->mynumber[i] <= 9)
        {
            ptr->bluenum[ptr->bluecount] = ptr->mynumber[i];
            ptr->bluecount++;
        }
        else
        {
            ptr->rednum[ptr->redcount] = ptr->mynumber[i] - 10;
            ptr->redcount++;
            ptr->mynumber[i] -= 10;
        }
    }
    /* sort number from samll to large*/
    sort(ptr->mynumber, ptr->mynumber + 5);

    for (i = 0; i < 5; i++)
    {
        found = 0;
        NoSearch = 0;
        ptr->TotalSum += ptr->mynumber[i];
        if (ptr->mynumber[i] % 2 != 0)
        {
            ptr->oddNum++;
        }

        if (ptr->mynumber[i] == 5)
        {
            // set to Green color
            ptr->color[i] = 2;
        }
        else
        {
            if (i > 0)
            {
                if (ptr->mynumber[i] == ptr->mynumber[i - 1])
                {
                    // set to Blue Color
                    ptr->color[i] = 3;
                    NoSearch = 1;
                }
            }
            if (NoSearch == 0)
            {
                for (j = 0; j < ptr->redcount; j++)
                {
                    if (ptr->mynumber[i] == ptr->rednum[j])
                    {
                        found = 1;
                    }
                }
                if (found == 1)
                { // Set to Red Color
                    ptr->color[i] = 4;
                }
                else
                {
                    ptr->color[i] = 3;
                }
            }
        }
    }

    for (i = 0; i < 4; i++)
    {
        if (ptr->color[i] == ptr->color[i + 1])
        {
            ptr->NeighborSameColor[i] = 1;
            ptr->NeighborSameColor[i + 1] = 1;
        }
    }

    ptr->maxDiff = ptr->mynumber[4] - ptr->mynumber[0];
    ptr->SumFirstThree = ptr->mynumber[0] + ptr->mynumber[1] + ptr->mynumber[2];
    ptr->SumMiddleThree = ptr->mynumber[3] + ptr->mynumber[1] + ptr->mynumber[2];
    ptr->SumRightThree = ptr->mynumber[3] + ptr->mynumber[4] + ptr->mynumber[2];
    for (i = 0; i < 4; i++)
    {
        if (ptr->mynumber[i] == ptr->mynumber[i + 1])
        {
            ptr->pairSameNum++;
            i++;
        }
    }

    for (i = 0; i < 4; i++)
    {
        if (ptr->mynumber[i + 1] - ptr->mynumber[i] == 1)
        {
            ptr->sequentialOrder[i] = 1;
            ptr->sequentialOrder[i + 1] = 1;
        }
    }

    for (i = 0; i < 5; i++)
    {
        ptr->blueSum += ptr->bluenum[i];
    }

    for (i = 0; i < 5; i++)
    {
        ptr->redSum += ptr->rednum[i];
    }
}

void printFinalNum(user *ptr)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        SetColor(ptr->color[i]);
        cout << ptr->mynumber[i] << " ";
    }
    SetColor();
}

void get_randomNum()
{
    int i, j;
    int temp;
    int randomNum;
    int randomNumArrayN[20];
    int currentNum = 0;

    srand(time(0));
    /* intialize the Array*/
    for (j = 0; j < 20; j++)
    {
        randomNumArrayN[j] = j;
    }

    for (j = 0; j < 26; j++)
    {
        questionIdxRandom[j] = j;
    }

    for (i = 0; i < 20; i++)
    {
        // get the random number from 0 to 19
        randomNum = rand() % 20;
        temp = randomNumArrayN[i];
        randomNumArrayN[i] = randomNumArrayN[randomNum];
        randomNumArrayN[randomNum] = temp;
    }

    for (i = 0; i < 26; i++)
    {
        // get the random number from 0 to 19
        randomNum = rand() % 26;
        temp = questionIdxRandom[i];
        questionIdxRandom[i] = questionIdxRandom[randomNum];
        questionIdxRandom[randomNum] = temp;
    }

    cout << endl
         << "Start Number Allocation" << endl;
    for (i = 0; i < 15; i++)
    {
        if (i < 5)
        {
            me.mynumber[i] = randomNumArrayN[i];
        }
        else if (i < 10)
        {
            Daisy.mynumber[i - 5] = randomNumArrayN[i];
        }
        else
        {
            Melon.mynumber[i - 10] = randomNumArrayN[i];
        }
    }
}

void answer(void)
{
    char cond[10];
    int condNum;
    int i;
    int tryNum = 1;

    for (i = 0; i < 6; i++)
    {
        question_index[i] = questionIdxRandom[i];
    }
    q_Idx = 5;

    for (;;)
    {
        for (i = 0; i < 6; i++)
        {
            cout << i << "-" << questions[question_index[i]] << endl;
        }
        cout << "6-Exit Game" << endl <<" -----------------------------------------------------" << endl;
        SetColor(13);
        cout << "NO." << tryNum << " Try, Please choose : ";
        cin >> cond;
        condNum = atoi(cond);

        if (condNum > 6)
        {
            cout << " Not valid choice, please input again:  " << endl;
        }
        else if (condNum == 6)
        {
            return;
        }
        else
        {
            cout<< questions[question_index[condNum]]<<endl;
            question_Answer(question_index[condNum]);
            tryNum++;
            if (tryNum >= 20)
            {
                cout << " Try too many times, Game over :( " << endl;
                return;
            }
            q_Idx++;
            question_index[condNum] = questionIdxRandom[q_Idx];
        }
    }
}

void Question_Init(void)
{
    questions[0] = "What's the difference between largest and smallest number?";
    questions[1] = "What's the sum of your three left tiles?";
    questions[2] = "Where is 9?";
    questions[3] = "How many odd numbers do you have?";
    questions[4] = "How many even numbers do you have (including 0)?";
    questions[5] = "How many red tiles do you have?";
    questions[6] = "How many blue tiles do you have?";
    questions[7] = "How many pairs of the same number do you have?";
    questions[8] = "is the middle tile greater than 4?";
    questions[9] = "where do you have tiles in sequential order?";
    questions[10] = "What's the sum of your Red tiles?";
    questions[11] = "What's the sum of your three middle tiles?";
    questions[12] = "What's the sum of your three right tiles?";
    questions[13] = "What's the sum of your three left tiles?";
    questions[14] = "What's the sum of all of your tiles";
    questions[15] = "Where do you have neighboring tiles of the same color";
    questions[16] = "Where is 0?";
    questions[17] = "Where is 5?";
    questions[18] = "Where is 6?";
    questions[19] = "Where is 7?";
    questions[20] = "Where is 8 ?";
    questions[21] = "What is the sum of your blue tiles?";
    questions[22] = "Where is 3?";
    questions[23] = "Where is 4?";
    questions[24] = "Where is 1?";
    questions[25] = "Where is 2";
}

void SearchNumPos(user *ptr, int num)
{
    int i;
    int pos;
    pos = 0;
    ptr->numPos[0] = 0;
    ptr->numPos[1] = 0;
    for (i = 0; i < 5; i++)
    {
        if (ptr->mynumber[i] == num)
        {
            ptr->numPos[pos] = i + 1;
            pos++;
        }
    }
}

void question_Answer(int num)
{
    SetColor(12);
    switch (num)
    {
    case 0:
    {
        cout << "Daisy's answer is " << Daisy.maxDiff << endl;
        cout << "Melon's answer is " << Melon.maxDiff << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 1:
    {
        cout << "Daisy's answer is " << Daisy.SumFirstThree << endl;
        cout << "Melon's answer is " << Melon.SumFirstThree << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 2:
    {
        SearchNumPos(&Daisy, 9);
        cout << "Daisy's answer is " << Daisy.numPos[0] << "/" << Daisy.numPos[1] << endl;
        SearchNumPos(&Melon, 9);
        cout << "Melon's answer is " << Melon.numPos[0] << "/" << Melon.numPos[1] << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 3:
    {
        cout << "Daisy's answer is " << Daisy.oddNum << endl;
        cout << "Melon's answer is " << Melon.oddNum << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 4:
    {
        cout << "Daisy's answer is " << (5 - Daisy.oddNum) << endl;
        cout << "Melon's answer is " << (5 - Melon.oddNum) << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 5:
    {
        cout << "Daisy's answer is " << Daisy.redcount << endl;
        cout << "Melon's answer is " << Melon.redcount << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 6:
    {
        cout << "Daisy's answer is " << Daisy.bluecount << endl;
        cout << "Melon's answer is " << Melon.bluecount << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 7:
    {
        cout << "Daisy's answer is " << Daisy.pairSameNum << endl;
        cout << "Melon's answer is " << Melon.pairSameNum << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 8:
    {
        if (Daisy.mynumber[2] > 4)
        {
            cout << "Daisy's answer is YES" << endl;
        }

        else
        {
            cout << "Daisy's answer is NO" << endl;
        }
        if (Melon.mynumber[2] > 4)
        {
            cout << "Melon's answer is YES" << endl;
        }
        else
        {
            cout << "Melon's answer is NO" << endl;
        }
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 9:
    {
        int i;
        cout << "Daisy's answer is ";
        for (i = 0; i < 5; i++)
        {
            cout << Daisy.sequentialOrder[i] << "/";
        }
        cout << endl;
        cout << "Melon's answer is ";
        for (i = 0; i < 5; i++)
        {
            cout << Melon.sequentialOrder[i] << "/";
        }
        cout << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 10:
    {
        cout << "Daisy's answer is " << Daisy.redSum << endl;
        cout << "Melon's answer is " << Melon.redSum << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    case 11:
    {
        cout << "Daisy's answer is " << Daisy.SumMiddleThree << endl;
        cout << "Melon's answer is " << Melon.SumMiddleThree << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 12:
    {

        cout << "Daisy's answer is " << Daisy.SumRightThree << endl;

        cout << "Melon's answer is " << Melon.SumRightThree << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 13:
    {

        cout << "Daisy's answer is " << Daisy.SumFirstThree << endl;

        cout << "Melon's answer is " << Melon.SumFirstThree << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 14:
    {

        cout << "Daisy's answer is " << Daisy.TotalSum << endl;

        cout << "Melon's answer is " << Melon.TotalSum << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 15:
    {

        int i;
        cout << "Daisy's answer is ";
        for (i = 0; i < 5; i++)
        {
            cout << Daisy.NeighborSameColor[i] << "/";
        }
        cout << endl;
        cout << "Melon's answer is ";
        for (i = 0; i < 5; i++)
        {
            cout << Melon.NeighborSameColor[i] << "/";
        }
        cout << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 16:
    {
        SearchNumPos(&Daisy, 0);
        cout << "Daisy's answer is " << Daisy.numPos[0] << "/" << Daisy.numPos[1] << endl;
        SearchNumPos(&Melon, 0);
        cout << "Melon's answer is " << Melon.numPos[0] << "/" << Melon.numPos[1] << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 17:
    {
        SearchNumPos(&Daisy, 5);
        cout << "Daisy's answer is " << Daisy.numPos[0] << "/" << Daisy.numPos[1] << endl;
        SearchNumPos(&Melon, 5);
        cout << "Melon's answer is " << Melon.numPos[0] << "/" << Melon.numPos[1] << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 18:
    {
        SearchNumPos(&Daisy, 6);
        cout << "Daisy's answer is " << Daisy.numPos[0] << "/" << Daisy.numPos[1] << endl;
        SearchNumPos(&Melon, 6);
        cout << "Melon's answer is " << Melon.numPos[0] << "/" << Melon.numPos[1] << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 19:
    {
        SearchNumPos(&Daisy, 7);
        cout << "Daisy's answer is " << Daisy.numPos[0] << "/" << Daisy.numPos[1] << endl;
        SearchNumPos(&Melon, 7);
        cout << "Melon's answer is " << Melon.numPos[0] << "/" << Melon.numPos[1] << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 20:
    {
        SearchNumPos(&Daisy, 8);
        cout << "Daisy's answer is " << Daisy.numPos[0] << "/" << Daisy.numPos[1] << endl;
        SearchNumPos(&Melon, 8);
        cout << "Melon's answer is " << Melon.numPos[0] << "/" << Melon.numPos[1] << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 21:
    {
        cout << "Daisy's answer is " << Daisy.blueSum << endl;
        cout << "Melon's answer is " << Melon.blueSum << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 22:
    {
        SearchNumPos(&Daisy, 3);
        cout << "Daisy's answer is " << Daisy.numPos[0] << "/" << Daisy.numPos[1] << endl;
        SearchNumPos(&Melon, 3);
        cout << "Melon's answer is " << Melon.numPos[0] << "/" << Melon.numPos[1] << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 23:
    {
        SearchNumPos(&Daisy, 4);
        cout << "Daisy's answer is " << Daisy.numPos[0] << "/" << Daisy.numPos[1] << endl;
        SearchNumPos(&Melon, 4);
        cout << "Melon's answer is " << Melon.numPos[0] << "/" << Melon.numPos[1] << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 24:
    {
        SearchNumPos(&Daisy, 1);
        cout << "Daisy's answer is " << Daisy.numPos[0] << "/" << Daisy.numPos[1] << endl;
        SearchNumPos(&Melon, 1);
        cout << "Melon's answer is " << Melon.numPos[0] << "/" << Melon.numPos[1] << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;
    case 25:
    {
        SearchNumPos(&Daisy, 2);
        cout << "Daisy's answer is " << Daisy.numPos[0] << "/" << Daisy.numPos[1] << endl;
        SearchNumPos(&Melon, 2);
        cout << "Melon's answer is " << Melon.numPos[0] << "/" << Melon.numPos[1] << endl;
        cout << "----------------------------------------------" << endl;
    }
    break;

    default:
        break;
    }
    SetColor();
}

int main()
{
    Question_Init();
    get_randomNum();
    parseInfo(&me);
    parseInfo(&Daisy);
    parseInfo(&Melon);
    printFinalNum(&me);
    cout << endl
         << " Start to Play" << endl;
    answer();

    cout << " Game finish " << endl;
    cout << "Daisy" << endl;
    printFinalNum(&Daisy);
    cout << endl
         << "Melon" << endl;
    printFinalNum(&Melon);
    return 0;
}

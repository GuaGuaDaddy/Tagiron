#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;

#define LENGTH 30;

struct user
{
    int rednum[9];
    int bluenum[9];
    int greennum[2];
    int redcount;
    int bluecount;
    int greencount;
    int mynumber[5];
};

user usr1;
user Melon;
user me;

int user1_number[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int user2_number[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int user1[5];
int user2[5];
int my[5];

char condition1[10];
int con1;
int idx;
int length = 20;
int s_length = 5;
void print_currValidNum();

void check1()
{
    int diff;

    char char_diff[1];
    cout << "input max difference number";
    cin >> char_diff;
    diff = atoi(char_diff);
    for (idx = 0; idx < length; idx++)
    {
        if (user1_number[idx] - user1[0] > diff)
        {
            user1_number[idx] = 99;
        }
    }
}

void All_Conditions()
{
    cout << endl
         << "1. Input the max difference" << endl;
    cout << "Please inut your card number";
}

void Start_Game()
{
    int my_number;
    char my_char[1];
    cout << "***************************** Game Start *****************************" << endl;
    cout << "Please inut your number from small to large" << endl;
    for (idx = 0; idx < s_length; idx++)
    {
        cin >> my_char;
        my_number = atoi(my_char);
        my[idx] = my_number;
        user1_number[my_number] = 99;
        user2_number[my_number] = 99;
        if (idx < (s_length - 1))
        {
            cout << "please input next number" << endl;
        }
    }
    cout << "ok, input finished" << endl;

    print_currValidNum();
}

void print_currValidNum()
{
    for (idx = 0; idx < length; idx++)
    {
        cout << user1_number[idx] << "/";
    }
    cout << endl;

    for (idx = 0; idx < length; idx++)
    {
        cout << user2_number[idx] << "/";
    }
    cout << endl;
}

void parseInfo(user *ptr)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if ((ptr->mynumber[i] == 5) || (ptr->mynumber[i] == 15))
        {
            ptr->greennum[ptr->greencount] = 5;
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
        }
    }
}

void get_randomNum()
{
    int i, j;
    int randomNum;
    int randomNumArray[100];
    int randomNumArrayN[50];
    int currentNum = 0;
    int found;
    srand(time(0));
    /* intialize the Array*/
    for (j = 0; j < 50; j++)
    {
        randomNumArrayN[j] = 66;
    }

    for (int i = 0; i < 50; i++)
    {
        // get the random number from 0 to 19
        randomNum = rand() % 20;
        // cout << randomNum << "/";
        randomNumArray[i] = randomNum;
    }

    for (int i = 0; i < 50; i++)
    {
        found = 0;
        for (j = 0; j < 20; j++)
        {
            if (randomNumArray[i] == randomNumArrayN[j])
            {
                found = 1;
            }
        }
        if (i == 0)
        {
            randomNumArrayN[0] = randomNumArray[0];
        }
        else
        {
            if (found == 0)
            {
                currentNum++;
                randomNumArrayN[currentNum] = randomNumArray[i];
            }
        }
    }
    /*
    for (int i = 0; i < 50; i++)
    {
        cout << randomNumArray[i] << "/";
    }
    */
    // cout << endl << "next Array"<< endl;
    // for (int i = 0; i < 50; i++)
    // {
    // cout << randomNumArrayN[i] << "/";
    // }
    cout << endl
         << "Start Number Allocation" << endl;
    for (int i = 0; i < 15; i++)
    {
        if (i < 5)
        {
            me.mynumber[i] = randomNumArrayN[i];
            // cout << me.mynumber[i] << "/";
        }
        else if (i < 10)
        {
            usr1.mynumber[i - 5] = randomNumArrayN[i];
            // cout << usr1.mynumber[i-5] << "/";
        }
        else
        {
            Melon.mynumber[i - 10] = randomNumArrayN[i];
            // cout << Melon.mynumber[i-10] << "/";
        }
    }
    parseInfo(&me);
    parseInfo(&usr1);
    parseInfo(&Melon);

    if (me.bluecount == 0)
    {
        cout << " NO BLUE NUMBER ";
    }
    else
    {
        cout << "Blue Number:";
        for (i = 0; i < me.bluecount; i++)
            cout << me.bluenum[i] << " ";
    }

    if (me.redcount == 0)
    {
        cout << " / NO RED NUMBER /";
    }
    else
    {
        cout << "/ Red Number:";
        for (i = 0; i < me.redcount; i++)
            cout << me.rednum[i] << " ";
    }

    if (me.greencount == 0)
    {
        cout << " / NO Green NUMBER /";
    }
    else
    {
        cout << "/ Green Number:";
        for (i = 0; i < me.greencount; i++)
            cout << me.greennum[i] << " ";
    }
    cout << endl
         << " Start to Play" << endl;
}

void answer(void)
{
    char cond[10];
    int condNum;
    int i;
    for (;;)
    {

        for (i = 0; i < 6; i++)
        {
            cout << i << "-" << endl;
        }
        cout << "6- Exit Game" << endl;
        cout << "Please input your chose: ";
        cin >> cond;
        condNum = atoi(cond);
        switch (condNum)
        {
        case 6:
            return;
            break;

        case 1:
            break;

        default:
            cout << " Not valid choice, please input again:  "<<endl;
            break;
        }
    }
}

int main()
{
    get_randomNum();
    answer();
    // Start_Game();
    // length = sizeof(user1_number)/sizeof(user1_number[0]);
    /*     user1[0]=0;

        All_Conditions();
        cout<<endl;
        cin>>condition1;
        con1 =atoi(condition1);
        if (con1 == 1)
        {
            check1();
        }
        print_currValidNum();
        cin>>condition1; */

    cout << " Game finish ";
    return 0;
}

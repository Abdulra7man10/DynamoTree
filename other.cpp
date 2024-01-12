#pragma once
#include "other.h"

char IsChar(string msg)
{
    bool IsNotValid = false; string word;
    do
    {
        IsNotValid = false;
        cout << msg; cin >> word;
        try
        {
            if (word.size() > 1 || !isalpha(word[0]))
                IsNotValid = true;

            if (IsNotValid)
                throw "Error";
        }

        catch (...)
        {
            cerr << "Please, type only one letter :)\n";
        }
    } while (IsNotValid);

    return tolower(word[0]);
}

int IsNumber(string msg)
{
    bool IsNotValid = false; string num;
    do
    {
        IsNotValid = false;
        cout << msg; cin >> num;
        try
        {

            for (int i = 0; i < num.size(); i++)
                if (!isdigit(num[i]))
                {
                    IsNotValid = true;
                    throw "Error";
                }
        }

        catch (...)
        {
            cerr << "Please, type only positive numbers :)\n";
        }
    } while (IsNotValid);

    return stoi(num);
}

int IsValid(int sm, int big, string msg)
{
    bool IsNotValid = false; string num;
    do
    {
        IsNotValid = false;
        cout << msg; cin >> num;
        try
        {
            for (int i = 0; i < num.size(); i++)
                if (!isdigit(num[i]) && num[i] != '-')
                {
                    IsNotValid = true;
                    throw "Error";
                }

            if (stoi(num) < sm || stoi(num) > big)
            {
                IsNotValid = true;
                throw big;
            }
        }
        catch (int& i)
        {
            cerr << "please, Enter an avaialable number :)\n";
            IsNotValid = true;
        }

        catch (...)
        {
            cerr << "Please, don't write letters :)\n";
        }
    } while (IsNotValid);

    return stoi(num);
}





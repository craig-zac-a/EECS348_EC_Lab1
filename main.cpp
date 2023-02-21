// Zachary Craig
// EECS 348 Extra Credit Lab 1
// Date Created: 2/16/2023
// Last Modified: 2/16/2023
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

void readFile(int **departmentsPreferences, int **programmersPreferences)
{
    // Opens a file for reading
    ifstream inFile;
    inFile.open("matching-data.txt");

    // Reads file
    for (int i = 0; i < 10; i++)
    {
        if(i < 5)
        {
            for (int j = 0; j < 5; j++)
            {
                inFile >> departmentsPreferences[j][i];
            }
        }
        else
        {
            for (int j = 0; j < 5; j++)
            {
                inFile >> programmersPreferences[j][i-5];
            }
        }
    }
}

void printVariables(int **departmentsPreferences, int **programmersPreferences, int *departmentsMatched)
{
    // Prints out the departments array
    for (int i = 0; i < 5; i++)
    {
        cout << "Department #" << i+1 << ": ";;
        for (int j = 0; j < 5; j++)
        {
            cout << departmentsPreferences[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    // Prints out the programmers array
    for (int i = 0; i < 5; i++)
    {
        cout << "Programmer #" << i+1 << ": ";;
        for (int j = 0; j < 5; j++)
        {
            cout << programmersPreferences[i][j] << " ";
        }
        cout << endl;
    }

    // Prints out the departments matched array
    cout << "Departments Matched: ";
    for (int i = 0; i < 5; i++)
    {
        cout << "Department #" << i+1 << ": " <<  departmentsMatched[i] << " ";
    }
    cout << endl;
}

bool contains(int *departmentsMatched, int value)
{
    // Checks if the value is in the array
    for (int i = 0; i < 5; i++)
    {
        if(departmentsMatched[i] == value)
        {
            return false;
        }
    }
    return true;
}

void deleteVariables(int **departmentsPreferences, int **programmersPreferences, int *departmentsMatched)
{
    // Deletes the arrays
    for (int i = 0; i < 5; i++)
    {
        delete [] departmentsPreferences[i];
        delete [] programmersPreferences[i];
    }
    delete [] departmentsPreferences;
    delete [] programmersPreferences;
    delete [] departmentsMatched;
}

int main()
{
    // Declares variables
    int **departmentsPreferences;
    int **programmersPreferences;
    departmentsPreferences = new int*[5];
    programmersPreferences = new int*[5];

    for (int i = 0; i < 5; i++)
    {
        departmentsPreferences[i] = new int[5];
    }
    for (int i = 0; i < 5; i++)
    {
        programmersPreferences[i] = new int[5];
    }

    int *departmentsMatched = new int[5];

    // Sets the arrays to 0
    for (int i = 0; i < 5; i++)
    {
        departmentsMatched[i] = 0;
    }

    // Reads the file and stores the data in the arrays
    readFile(departmentsPreferences, programmersPreferences);

    // Matches the programmers and departments
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            for(int k = j; k < 5; k++)
            {
                if(departmentsPreferences[j][k] )
                {
                    departmentsMatched[i] = departmentsPreferences[i][j];
                    break;
                }
            }
            for(int k = 0; k < 5; k++)
            {
                if(departmentsPreferences[i][j] == programmersPreferences[k][i] && contains(departmentsMatched, departmentsPreferences[i][j]))
                {
                    departmentsMatched[i] = departmentsPreferences[i][j];
                    break;
                }
            }
            if(departmentsPreferences[i][j] != departmentsMatched[i] && contains(departmentsMatched, departmentsPreferences[i][j]))
            {
                departmentsMatched[i] = departmentsPreferences[i][j];
                break;
            }
        }
    }

    // Prints out the arrays
    printVariables(departmentsPreferences, programmersPreferences, departmentsMatched);

    // Deletes the arrays
    deleteVariables(departmentsPreferences, programmersPreferences, departmentsMatched);

    return 0;
}
/*******************************************************************
 *
 * Author:          sugarfreeoh
 * Date:            2016 Feb 25
 * Description:     First argument is a path to a file. Each line
 *                  includes a test casse which contains two playing
 *                  cards and a trump suit. Cards and a trump suit
 *                  are separated by '|'. The card deck includes 13
 *                  ranks from four suits.
 *                  Program prints the card that wins. If there is
 *                  no trump card then the higher card wins. If the
 *                  cards are equal print both cards.
 ******************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream inputFile;

    inputFile.open(argv[1]);

    if(inputFile.is_open())
    {
        string line;

        while(getline(inputFile,line))
        {
            cout << "Input: " << line << endl;
        }
    }
    else
    {
        cout << "Error opening input file" << endl;
    }

    return 0;
}

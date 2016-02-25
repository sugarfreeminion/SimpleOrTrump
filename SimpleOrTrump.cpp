/*******************************************************************
 *
 * Author:          sugarfreeoh
 * Date:            2016 Feb 25
 * Description:     First argument is a path to a file. Each line
 *                  includes a test case which contains two playing
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
#include <vector>

using namespace std;

void ParseLine(string inputLine, vector<string> &cards, char delimiter);
void ParsePlayingCards(string inputLine, vector<string> &cards, char delimiter);

int main(int argc, char *argv[])
{
    ifstream inputFile;

    char delimiter = '|';

    inputFile.open(argv[1]);

    if(inputFile.is_open())
    {
        string line;

        while(getline(inputFile,line))
        {
            vector<string> cards;
            cout << "Input: " << line << endl;

            ParseLine(line,cards,delimiter);

            for(vector<string>::const_iterator it=cards.begin();
                it!=cards.end();
                ++it)
            {
                cout << *it << endl;
            }
        }
    }
    else
    {
        cout << "Error opening input file" << endl;
    }

    return 0;
}


void ParseLine(string inputLine, vector<string> &cards, char delimiter)
{
    stringstream lineStream;

    string temp;

    bool separatedHands = false;

    char cardDelimiter = ' ';

    lineStream << inputLine;

    while(getline(lineStream,temp,delimiter))
    {
        if(separatedHands == false)
        {
            ParsePlayingCards(temp.substr(0,temp.size()-1),cards,cardDelimiter);

            separatedHands = true;
        }
        else
        {
            cards.push_back(temp.substr(1,temp.size()-1));
        }   
    }
}

void ParsePlayingCards(string inputLine, vector<string> &cards, char delimiter)
{
    stringstream lineStream;

    string temp;

    lineStream << inputLine;

    while(getline(lineStream,temp,' '))
    {
        cards.push_back(temp);
    }
}

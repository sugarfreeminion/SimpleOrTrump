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
void DetermineWinner(string handOne, string handTwo, string trump);
bool HasTrump(const string hand, const string trump);
int StringToInt(const string val);
int HandVal(const string handOne, const string handTwo);
int FaceCardToInt(const string card);

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
            //cout << "Input: " << line << endl;

            ParseLine(line,cards,delimiter);

            /*for(vector<string>::const_iterator it=cards.begin();
                it!=cards.end();
                ++it)
            {
                cout << *it << endl;
            }*/

            string handOne;
            string handTwo;
            string trump;

            //cout << "Number of objects parsed: " << cards.size() << endl;

            handOne = cards.at(0);
            handTwo = cards.at(1);

            if(cards.size() == 3)
            {
                trump = cards.at(2);
            }
            else
            {
                trump = "";
            }

            DetermineWinner(handOne,handTwo,trump);            
       }
    }
    else
    {
        cout << "Error opening input file" << endl;
    }

    return 0;
}

/************************************************************************
 * Function Name:   FaceCardToInt
 * Description:     Returns an integer representing a face card
 *                  Jack = 11
 *                  Queen = 12
 *                  King = 13
 *                  Ace = 14
 **********************************************************************/
int FaceCardToInt(const string card)
{
    int faceCardVal = 0;

    if(card.compare("J") == 0)
        faceCardVal = 11;
    else if(card.compare("Q") == 0)
        faceCardVal = 12;
    else if(card.compare("K") == 0)
        faceCardVal = 13;
    else if(card.compare("A") == 0)
        faceCardVal = 14;

    return faceCardVal;
}

/*******************************************************************
 * Function Name:   StringToInt
 * Description:     Transforms a string to an integer value
 *****************************************************************/
int StringToInt(const string val)
{
    int retVal;

    stringstream valStream(val);

    valStream >> retVal;

    return retVal;
}

/********************************************************************
 * Function Name:   HandVal
 * Description:     Determines an integer value of the players hand
 *******************************************************************/
int HandVal(const string hand)
{
    int handVal = 0;
    
    handVal = StringToInt(hand);

    if(handVal < 2 || handVal > 10)
    {
        //cout << "Hand has face card" << endl;

        handVal = FaceCardToInt(hand);

        //cout << "Hand value: " << handVal << endl;
    }
    else if(handVal >= 2 && handVal <= 10)
    {
        //cout << "Hand value: " << handVal << endl;
    }

     return handVal;
}

/***************************************************************
 * Function Name:   HasTrump
 * Description:     Determines if a player has a trump card
 **************************************************************/
bool HasTrump(const string hand, const string trump)
{
    bool hasTrump = false;

    string suit = hand.substr(hand.size() - 1);

    //cout << "Hand Suit: " << suit << endl;

    if(trump.compare(suit) == 0)
    {
        //cout << "hand has a trump card" << endl;
        hasTrump = true;
    }

    return hasTrump;
}

/*****************************************************************
 * Function Name:   DetermineWinner
 * Description:     Determines which hand is the winner
 ****************************************************************/
void DetermineWinner(string handOne,string handTwo,string trump)
{
    int handOneVal = 0;
    int handTwoVal = 0;

    bool handOneHasTrump = false;
    bool handTwoHasTrump = false;

    handOneHasTrump = HasTrump(handOne,trump);
    handTwoHasTrump = HasTrump(handTwo,trump);

    if(handOneHasTrump == true && handTwoHasTrump == false)
    {
        //cout << "Hand One Wins" << endl;
        cout << handOne << endl;
    }
    else if(handOneHasTrump == false && handTwoHasTrump == true)
    {
        //cout << "Hand Two Wins" << endl;
        cout << handTwo << endl;
    }
    else if((handOneHasTrump == false && handTwoHasTrump == false)
            || (handOneHasTrump == true && handTwoHasTrump == true)
            || trump.empty())
    {
        string handOneCard = handOne.substr(0,handOne.size()-1);
        string handTwoCard = handTwo.substr(0,handTwo.size()-1);

        //cout << "Hand one card: " << handOneCard << endl;
        //cout << "Hand two card: " << handTwoCard << endl;

        handOneVal = HandVal(handOneCard);
        handTwoVal = HandVal(handTwoCard);

        if(handOneVal > handTwoVal)
        {
            //cout << "Hand one wins: " << handOne << endl;
            cout << handOne << endl;
        }
        else if(handTwoVal > handOneVal)
        {
            //cout << "Hand two wins: " << handTwo << endl;
            cout << handTwo << endl;
        }
        else if(handOneVal == handTwoVal)
        {
            //cout << "TIE!: " << handOne << " " << handTwo << endl;
            cout << handOne << " " << handTwo << endl;
        }
    }
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
            if(temp.size() > 1)
            {
                //cout << "Found trump" << endl;
                cards.push_back(temp.substr(1,temp.size()-1));
            }
            else
            {
                //cout << "No trump" << endl;
                cards.push_back("");
            }
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

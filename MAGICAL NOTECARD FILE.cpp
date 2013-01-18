#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cmath>
#include<cstdlib>
using namespace std;

class Card
{
public:
    Card(string f, string b)
    {
        front = f;
        back = b;

    }
    string front,back;

    void addToDeck();


    string getFront()
    {
        return front;
    }
    string getBack()
    {
        return back;
    }
};
vector<Card> deck;
vector<Card> flagged,all;
void Card::addToDeck()
{
    deck.push_back(*this);
}

int main()
{
    bool randMode = true, flagMode = false;
    int index = -1;//will be incremented before use
    cout<<"Welcome to NoteCards!"<<endl;
    string input;
    cout<<"What do you want to do?"<<endl;
    getline(cin,input);
    while (input!="stop")
    {

        if(input.compare("add")==0)
        {
            string f, b;

            cout<<"Please enter the front."<<endl;
            getline(cin,f);
            cout<<"Please enter the back."<<endl;
            getline(cin,b);
            Card x(f,b);
            x.addToDeck();
        }
        else if(input.compare("get")==0||input=="")
        {
            if(deck.size()>0)
            {
                if(randMode)
                {
                    if(!flagMode)
                        index = rand()%deck.size();
                    else
                        index = rand()%flagged.size();
                }
                else
                {
                    index++;
                    if(!flagMode)
                    {
                        if(index==deck.size())
                        {
                            index = 0;
                        }
                    }
                    else if(index==flagged.size())
                    {
                        index = 0;
                    }
                }
                if(!flagMode)
                {
                    cout<<deck[index].getFront()<<endl;
                    system("pause");
                    cout<<deck[index].getBack()<<endl;
                }
                else
                {
                    cout<<flagged[index].getFront()<<endl;
                    system("pause");
                    cout<<flagged[index].getBack()<<endl;
                }
            }
            else
                cout<<"There are no cards yet!"<<endl;
        }
        else if(input.compare("export")==0||input.compare("save")==0)
        {
            cout<<"Enter File Name:"<<endl;
            string filename;
            cin.clear();
            getline(cin,filename);
            filename+=".txt";
            cout<<"Saving "<<filename<<endl;
            ofstream output;
            output.open(("notes\\"+filename).c_str());
            for(int x = 0; x< deck.size(); x++)
            {
                output<<deck[x].getFront()<<" - ";
                output<<deck[x].getBack()<<endl;
            }
        }
        else if(input.compare("import")==0||input=="open"||input == "load")
        {
            cout<<"Enter File Name:"<<endl;
            string filename;
            getline(cin,filename);
            filename+=".txt";
            cout<<"Opening "<<filename<<endl;
            ifstream input;
            input.open(("notes\\"+filename).c_str());
            while(!input.eof())
            {
                string x,y;
                getline(input,x,'-');
                getline(input,y);
                Card temp(x,y);
                temp.addToDeck();
            }

        }
        else if(input.compare("clear")==0)
        {
            deck.clear();
            flagged.clear();
            index = -1;
        }
        else if(input.compare("flip")==0)
        {
            vector<Card> temp;
            string box;
            for(int i = 0; i<deck.size(); i++)
            {
                Card x(deck[i].getBack(),deck[i].getFront());
                temp.push_back(x);
            }
            deck = temp;
        }
        else if (input == "remove")
        {
            if(index >=0)
            {
            deck.erase(deck.begin()+index);
            index = -1;
            }
            else cout<<"You have no card active."<<endl;
        }
        else if(input == "toFront")
        {
            index = -1;
        }
        else if(input == "change sort")
        {
            if(randMode)
            {
                randMode=false;
                cout<<"Mode Changed to Linear"<<endl;
            }
            else
            {
                randMode=true;
                cout<<"Mode Changed to Random"<<endl;
            }
        }
        else if(input=="flag")
        {
            if(!flagMode&&index>=0)
            {
                flagged.push_back(deck[index]);
                cout<<"Flag Successful"<<endl;

            }
            else
                cout<<"Can't flag"<<endl;


        }
        else if(input=="toggle flagged")
        {
            flagMode = !flagMode;
            index = -1;
            if(flagMode)
                cout<<"Flag Mode On"<<endl;
            else
                cout<<"Flag Mode Off"<<endl;

        }
        else if(input.compare("save flagged")==0)
        {
            cout<<"Enter File Name:"<<endl;
            string filename;
            cin.clear();
            getline(cin,filename);
            filename+=".txt";
            cout<<"Saving "<<filename<<endl;
            ofstream output;
            output.open(filename.c_str());
            for(int x = 0; x< flagged.size(); x++)
            {
                output<<flagged[x].getFront()<<endl;
                output<<flagged[x].getBack()<<endl;
            }
        }
        else if (input == "help")
        {
            cout<<"Command List:\n"
                <<"\t\nopen\t\nsave\t\nget"
                <<"\t\nflag\t\nsave flagged\t\ntoggle flagged"
                <<"\t\nchange sort\t\nclear\t\nadd\nremove\ntoFront\n";
        }
        else
            cout<<"I didn't understand"<<endl;

        cout<<endl;

        cout<<"What do you want to do now?"<<endl;
        getline(cin,input);
        system("cls");
    }



    return 0;
}


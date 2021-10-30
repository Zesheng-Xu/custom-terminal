#include <iostream>
#include <vector>
#include <stdio.h>
#include <filesystem>
#include<unistd.h>
#include <string>
#include <limits.h>
using namespace std;



//TODO: make the get_command more refined
//      make a command list
//      finish process
static const char *current_path;

static vector<string> get_command(string line)
{
    // intake a line
    string temp = line;
    int next_space = 0;
    int first_qoute = 0;
    int second_qoute = -1;

    vector<string> commands;
    // go through each char
    for(int x = 0; x < line.length(); x++)
    {
        // if they typed a space in the beginning of the line, we skip it
        if(line[x] == ' ' and x == 0)
        {
            x ++;
        }
        // if we meet a space we make it
        if(line[x] == ' ' and not(x > first_qoute and x < second_qoute) )
        {
            // locates a space that is not in the qoutes
            next_space = x;
            commands.push_back(line.substr(0, next_space));
            line=line.substr(next_space, line.size());
            x = 0;
        }
        else if(line[x] == ';' and not(x > first_qoute and x < second_qoute) )
        {
            // locates a space that is not in the qoutes
            next_space = x;
            commands.push_back(line.substr(0, next_space));
            line=line.substr(next_space, line.size());
            x = 0;
        }
        else if(line[x] == '|' and not(x > first_qoute and x < second_qoute) )
        {
            // locates a space that is not in the qoutes
            next_space = x;
            commands.push_back(line.substr(0, next_space));
            line=line.substr(next_space, line.size());
            x = 0;
        }
        // seperating the qoute parts
        else if(line[x] == '\"' or line[x]=='\'')
        {
            first_qoute = x ;
            for(int y = x + 1; y < line.length(); y++)
            {
                // locate next qoute mark
                if (line[y] == '\"' or line[y]=='\'')
                {
                    // add the qoute to the list
                    commands.push_back(line.substr(x, y));
                    line=line.substr(y + 1, line.length());
                    second_qoute = y;
                    x = y+1;
                    break;
                }
            }
        }

    }
    commands.push_back(line);


    return commands;
}
static void ls(string command)
{

    system(command.c_str());
}
static void grep(string command)
{

    system(command.c_str());
}
static void run_commands(vector<string> command)
{
    int x = 0;
    string input = "";
    string output = "";
    vector<string> sub_command;
    bool error = false;
    for(int x = 0; x < command.size()-1; x++)
    {
        if(command.at(x) == ";" or command.at(x) == "|"  and x < command.size()-1)
        {
            if(not (command.at(x+1) == "ls" or command.at(x+1) == "clear" or command.at(x+1) == "grep" or command.at(x+1) == "wc"))
            {
                cout<<"invalid command: "<<command.at(x+1)<<endl;
                error = true;
                break;
            }

        }

    }
    if (error)
    {return;}

    for( int x = 0; x < command.size(); x++)
    {

        if(command.at(x) == ";")
        {
            if(sub_command.at(0) == "ls")
            {
                basic_string<char> c="";
                for(int z = 0; z < sub_command.size(); z++)
                {
                    c = c +  sub_command.at(z);
                }

                ls(c);
            }
            else if (sub_command.at(0) == "grep")
            {
                if(sub_command.at(0) == "grep")
                {
                    basic_string<char> c="";
                    for(int z = 0; z < sub_command.size(); z++)
                    {
                        c = c + " " +sub_command.at(z);
                    }

                    grep(c);
                }
            }
            else if (sub_command.at(0) == "clear")
            {
                system("clear");
            }
            else if(command.at(x) == "|")
            {
                basic_string<char> c="";
                for(int z = 0; z < command.size(); z++)
                {
                    c = c + " "+ command.at(z);
                }
                system(c.c_str());
                break;

            }
            else if(command.at(x) == "<")
            {
                basic_string<char> c="";
                for(int z = 0; z < command.size(); z++)
                {
                    c = c + " "+ command.at(z);
                }
                system(c.c_str());
                break;

            }
            else if(command.at(x) == ">")
            {
                basic_string<char> c="";
                for(int z = 0; z < command.size(); z++)
                {
                    c = c + " "+ command.at(z);
                }
                system(c.c_str());
                break;

            }
            else if(command.at(x) == ">>")
            {
                basic_string<char> c="";
                for(int z = 0; z < command.size(); z++)
                {
                    c = c + " "+ command.at(z);
                }
                system(c.c_str());
                break;

            }

            else
            {
                cout<<"incorrect command " + sub_command.at(0)<<endl;
                break;
            }
        }
        else {
            sub_command.push_back(command.at(x));
        }
    }
}

static void print_commands(vector<string> command)
{
    for(int x =0 ; x < command.size(); x++)
    {
        cout<<command.at(x)<<"+";
    }
    cout<<endl;
}

int main() {
    char buffer[256];
    current_path = getcwd(buffer,256);
    cout<<"Hello World! - Welcome to this custom terminal - type exit to exit"<<endl;
    // readdir(
    cout<<"Enter your commands:"<<endl;

    while(true)
    {

        cout<<current_path <<  "$:";
        string line;
        getline(cin,line);
        cout<<line<<endl;
        if (line == "exit")
            exit(0);
        line = line +";";

        vector<string> commands = get_command(line);
        try {
            run_commands(commands);    
        }
        catch (system_error) {
            
        }
        
        print_commands(commands);

    }
    return 0;
}

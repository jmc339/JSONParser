/* This is the JSON Assignment

James Carnes              --

<jmc339@zips.uakron.edu>  --

ID: 2947845               --

This Assignment takes data from the url given (https://www.reddit.com/r/front.json) or any user specified file
and steps through to output the weight of the data.
Use in-line comments for information.

*/



#include <iostream> // cout cin
#include <fstream>  // For File input or output
#include <string>   //For strings
#include <vector>   // for using vectors

using namespace std;

int thewght = 0; //thewght = 'the weight'


//Start of Structs
struct Value
{
	virtual ~Value() = default;

};

struct Number : Value // Inherits from Value
{
	double val;
};


struct String : Value //Inherits from Value
{
	string val;
};

struct Null : Value // Inherits from Value
{
	string val;
};


struct Bool : Value //Inherits from Value
{
	bool val;

};




//END OF STRUCTS

//Begin main function...This is to find the weight of the data

void findWeight(ifstream & input) //takes input from the file
{
	string tag, _val, _empty;
    char    nxt, quotemark, colon, whtspc;

	input.get(nxt);

	while (!input.eof()) //as long as it is not the end of the file, this will trigger
	{
            while (true)
            {

                    if (nxt == '{') //checks for curly (open) bracket


                    {
                        char hold = input.peek(); // peek() returns the next value 'input' of a string but doesn't actually extract it.



                        if (hold == '}')

                        {

                            input.get(nxt);
                        }

                    }


                    if (nxt != ' ' && nxt != ',') //if the next character isn't a blank or a comma then break and get the next character
                        break;


                    input.get(nxt);
            }

		if (nxt == '{')
		{
                thewght= thewght +1;

                input.get(quotemark);

                getline(input, tag, '"'); // looking for a "

                input.get(whtspc);

                input.get(colon);


                //_____________

                //then find next


                input.get(nxt); // find next

                    if (nxt == '"')
                    {
                        thewght = thewght + 1;

                        getline(input, _val, '"');
                        input.get(nxt);

                    }
                    if (nxt == '{')
                    {
                        // object
                        thewght = thewght + 1;
                        char hold = input.peek();
                        input.putback(hold);
                            if (hold == '}')
                            input.get(nxt);

                            else
                            findWeight(input);

                }
                if (nxt == '}')
                {
                    input.get(nxt);
                }
                if (nxt == '[')
                {
                    thewght = thewght + 1;

                    char hold2 = input.peek();

                    input.putback(hold2);

                        if (hold2 == ']')
                        input.get(nxt);

                        else
                        input.get(nxt);

                }
                if (nxt == 't' || nxt == 'f')
                {
                    thewght = thewght + 1;

                    getline(input, _empty, 'e');
                }
                if (nxt == 'n')
                {
                    thewght = thewght + 1;
                    getline(input, _empty, ',');

                }
                if (isdigit(nxt))
                thewght = thewght + 1;




        }
		else if (nxt == '"')
		{

                getline(input, tag, '"');
                input.get(colon);
                input.get(whtspc);
                input.get(nxt);



                if (nxt == '"')
                {
                    string tmp;
                    thewght = thewght + 1;
                    getline(input, _val, '"');
                    input.get(nxt);


                    while (nxt != ',')
                    {
                        getline(input, tmp, '"');
                        _val = _val + tmp;
                        input.get(nxt);
                    }
                }
                if (nxt == '{')
                {
                    thewght = thewght + 1;

                    char tmpp = input.peek();
                    input.putback(tmpp);
                    if (tmpp == '}')
                    {
                        input.get(nxt);
                        input.get(nxt);
                    }
                    else
                    {
                        input.get(nxt);
                        findWeight(input);
                        input.get(nxt);
                    }
                }
                if (nxt == '}')
                {
                    input.get(nxt);
                }
                if (nxt == '[')
                {
                    thewght = thewght + 1;

                    char hold2 = input.peek();
                    if (hold2 == ']')
                    {
                        input.get(nxt);
                        input.get(nxt);
                    }
                    else
                        input.get(nxt);
                }
                if (nxt == 't' || nxt == 'f')
                {
                    thewght = thewght + 1;

                    getline(input, _empty, 'e');

                    input.get(nxt);
                }
                if (nxt == 'n')
                {
                    thewght = thewght + 1;
                    input.get(nxt);
                    input.get(nxt); //These multiple lines are needed for correct output, you can comment them out to check.
                    input.get(nxt);
                    input.get(nxt);
                }
                if (isdigit(nxt))
                {
                    thewght = thewght + 1;

                    while (isdigit(nxt) || nxt == '.')
                    {
                        input.get(nxt);
                    }
                }

		}
		else if (nxt == '}')
		{
			char temp = input.peek();

			if (temp == '}')
			{
				input.get(nxt);
			}
			return;
		}
		else if (nxt == ']')
		{
			input.get(nxt);
		}
		else
			return;
	}

}





double functions() //This is to control the output of the data and to get input from the user.
{
ifstream json;
	string response;
	string  _parsefile;





A:
cout<<"\t\t\tMAIN MENU\n\n"<<endl;
cout<<"Would you like to specify a file name (1)"<<endl;
cout<<"\nor use the default file given in the github repo (2)? \n\n(Please type 1 or 2 and then hit enter)"<<endl;
cout<<"Number: >";


cin>>response; //Response is a string so that a user can enter invalid options and the program will not crash...for instance if response was declared as an int
                // Then inputting something like 20.6 or 'g' would cause the program to enter into an loop until terminated.
cin.ignore(); //without this line the program will ignore what was entered and jump to "Error file not found"


            if(response=="1") //makes 1 a string and not an int for evaluation
            {
                cout<<"The file must be in the same directory as this program to be found!"<<endl;
                cout<<"Please input the file name that you would like to parse.\n\nExample: jsondata.txt\n"<<endl;

                cout<<"File Name > ";

                getline(cin,_parsefile);
                json.open(_parsefile.c_str() );

                findWeight(json);

            }

        else if(response== "2") //makes 2 a string and not an int for evaluation
        {

        json.open("jsondata.txt"); //This is the file to be read in, the file is included in the github repo but if there is a particular file for grading just change the name here.
                                    //OR use option 1 when executing the program
        findWeight(json);
        }
else
{

    cout<<"This is an invalid option please input 1 or 2 only"<<endl;
    goto A;
}


	if(json.is_open()) //just a simple check to make sure that the file is open
    {
        cout<<"Found File!"<<endl;
        cout << "Opening the file to parse...\n\n The Weight of the Json data is: "<<thewght<<endl;
    }

    else if(!json.is_open())
    {

        cout<<"ERROR! "<<_parsefile<<" couldn't be found!"<<endl;

        cout<<"Please check the file name that you have entered and try again."<<endl;

    }

	json.close();

}




double again() //This is called to see if the user wants to run the program again.
{
    string rep;
cout<<"Would you like to run the program again? (Y)es or (N)o"<<endl;
cin>>rep;
if(rep=="y"||rep=="Y")
{
    functions();

}
if(rep=="n"||rep=="N")
{
    cout<<"Program has ended"<<endl;
   return 0;

}
else
    cout<<"Invalid key press"<<endl;
    cout<<"You may only type Y or N"<<endl;
}






int main()
{
functions();
again();



	return 0;
}

//Alex Staley
//CS163 - Program 4
//February 23 - March 7, 2019

//This program is a dictionary of terms
//you might find while studying data structures
//in a computer science course--specifically,
//terms related to tables, trees, graphs and heaps.

//84 terms and their definitions are pre-loaded
//from the "program4_data.txt" file and stored
//in a binary search tree.

//The functionality of the program is described
//in more detail in the "tree.cpp" file, but
//the program maps in this way:

//MAIN MENU:
//	Add a term
//	Remove a term
//	Retrieve a term
//	Display data -> SUBMENU:
	//	Display terms within a range
	//	Display the whole dictionary
	//	Display the arrangement within the tree
//	Get info on the tree -> SUBMENU:
	//	Get the height of the tree
	//	Calculate the efficiency of the tree
	//	Count the number of entries in the tree

//If you want to increase the efficiency of the tree,
//you'll have to add more terms to the dictionary,
//or decrease the height of the tree.
//Try removing the term "subtree" from the dictionary!



#include "tree.h"
using namespace std;

int main()
{
	tree dictionary;	//Builds a BST from the "program4_data.txt" file
	term destination;	//Term object for insert/retrieve functions

	int height;		//The height of the tree
	int efficiency;		//A measure of the tree's efficiency
	int count;		//The number of items in the tree

	char choice;		//User's main menu selection
	char display_choice;	//User's display submenu selection
	char info_choice;	//User's info submenu selection

	char start[SIZE];	//Lower bound of display range
	char end[SIZE];		//Upper bound of display range
	char selection[SIZE];	//Term to be removed

	char word[SIZE];		//Temporary name
	char definition[SIZE * 6];	//Temporary definition
	char field[SIZE * 2];		//Temporary topic

	cout<<'\n'<<'\n'<<'\n'<<"Welcome."<<endl;

	do
	{
		cout<<'\n'<<'\t'<<'\t'<<"MAIN MENU"<<endl;

		//Display options:
		cout<<'\n'<<"You can:"<<endl;
		cout<<'\t'<<"Add a new term:"<<'\t'<<'\t'<<'\t'<<'\t';
		cout<<"(enter 'N')"<<endl;
		cout<<'\t'<<"Remove an existing term:"<<'\t'<<'\t';
		cout<<"(enter 'R')"<<endl;
		cout<<'\t'<<"Retrieve an existing term:"<<'\t'<<'\t';
		cout<<"(enter 'T')"<<endl;
		cout<<'\t'<<"Display your data:"<<'\t'<<'\t'<<'\t';
		cout<<"(enter 'D')"<<endl;
		cout<<'\t'<<"Get information about the tree:"<<'\t'<<'\t';
		cout<<"(enter 'I')"<<endl;
		cout<<'\t'<<"Save your data and exit the program:"<<'\t';
		cout<<"(enter 'X')"<<endl;

		//Get user's selection:
		cin>>choice;
		cin.ignore(100, '\n');
		choice = toupper(choice);

		//If adding a new term:
		if (choice == 'N')
		{
			//Get the term itself:
			cout<<'\n'<<"What is the term you'd like to add?"<<endl;
			cin.get(word, SIZE, '\n');
			cin.ignore(100, '\n');

			//Get the topic:
			cout<<'\n'<<"Under what topic should I file "<<word<<'?'<<endl;
			cin.get(field, SIZE * 2, '\n');
			cin.ignore(100, '\n');

			//Get the definition:
			cout<<'\n'<<"Define "<<word<<" in less than 200 characters."<<endl;
			cin.get(definition, SIZE * 6, '\n');
			cin.ignore(100, '\n');

			//Insert the term into the tree:
			if (dictionary.insert(word, field, definition))
				cout<<'\n'<<"Stored "<<word<<'.'<<endl;
		}

		//If removing a term:
		if (choice == 'R')
		{
			do
			{
				//Get the term to be removed:
				cout<<'\n'<<"What term would you like to remove?"<<endl;
				cin.get(selection, SIZE, '\n');
				cin.ignore(100, '\n');

				//Remove the term:
				if (dictionary.remove(selection))
					cout<<'\n'<<selection<<" removed."<<endl;
				else cout<<'\n'<<"Could not remove "<<selection<<'.'<<endl;

				//Prompt to continue:
				cout<<'\n'<<"Remove another term? Y/N"<<endl;
			} while (yn());
		}

		//If retrieving a term:
		if (choice == 'T')
		{
			do
			{
				//Get the term to be retrieved:
				cout<<'\n'<<"What term would you like to retrieve?"<<endl;
				cin.get(selection, SIZE, '\n');
				cin.ignore(100, '\n');

				//Retrieve and display the term:
				if (dictionary.retrieve(selection, destination))
					destination.display_term();
				else cout<<'\n'<<"Could not retrieve "<<selection<<'.'<<endl;

				//Prompt to continue:
				cout<<'\n'<<"Retrieve a different term? Y/N"<<endl;
			} while (yn());
		}

		//If displaying data:
		if (choice == 'D')
		{
			do
			{
				cout<<'\n'<<'\t'<<'\t'<<"DISPLAY MENU"<<endl;

				//Display options:
				cout<<'\n'<<"You can:"<<endl;
				cout<<'\t'<<"Display a range of terms"<<endl;
				cout<<'\t'<<"and their definitions:"<<'\t'<<'\t'<<'\t';
				cout<<"(enter 'R')"<<endl;
				cout<<'\n'<<'\t'<<"Display the entire tree"<<endl;
				cout<<'\t'<<"in alphabetical order:"<<'\t'<<'\t'<<'\t';
				cout<<"(enter 'A')"<<endl;
				cout<<'\n'<<'\t'<<"Display the position of the terms"<<endl;
				cout<<'\t'<<"as they are ordered in the tree:"<<'\t';
				cout<<"(enter 'T')"<<endl;
				cout<<'\n'<<'\n'<<'\t'<<"Return to the main menu:"<<'\t'<<'\t';
				cout<<"(enter 'M')"<<endl;

				//Get display submenu selection:
				cin>>display_choice;
				cin.ignore(100, '\n');
				display_choice = toupper(display_choice);

				//If displaying a range:
				if (display_choice == 'R')
				{
					//Get lower bound:
					cout<<'\n'<<"What character, word or phrase";
					cout<<'\n'<<"represents the lower bound";
					cout<<'\n'<<"of the range you want to display?"<<endl;
					cin.get(start, SIZE, '\n');
					cin.ignore(100, '\n');

					//Get upper bound:
					cout<<'\n'<<"What character, word or phrase";
					cout<<'\n'<<"represents your upper bound?"<<endl;
					cin.get(end, SIZE, '\n');
					cin.ignore(100, '\n');

					//Display range:
					cout<<'\n'<<"Displaying "
						<<start<<" - "<<end<<':'<<endl;
					if (!dictionary.display_range(start, end))
						cout<<'\n'<<"Could not display "
							<<start<<" - "<<end<<'.'<<endl;
				}

				//If displaying the whole tree:
				if (display_choice == 'A')
				{
					//Display the tree:
					if (!dictionary.display_all())
						cout<<'\n'<<"Could not display tree."<<endl;
				}

				//If displaying by level:
				if (display_choice == 'T')
				{
					//Display the tree:
					if (!dictionary.display_tree())
						cout<<'\n'<<"Could not display tree."<<endl;
				}

			//Return to the main menu:
			} while (display_choice != 'M');

		}

		//If requesting info:
		if (choice == 'I')
		{
			do
			{
				cout<<'\n'<<'\t'<<'\t'<<"INFORMATION MENU"<<endl;

				//Display options:
				cout<<'\n'<<"You can:"<<endl;
				cout<<'\t'<<"View the height of the tree:"<<'\t'<<'\t';
				cout<<"(enter 'H')"<<endl;
				cout<<'\t'<<"Calculate the efficiency of the tree:"<<'\t';
				cout<<"(enter 'E')"<<endl;
				cout<<'\t'<<"Get the number of items in the tree:"<<'\t';
				cout<<"(enter 'N')"<<endl;
				cout<<'\n'<<'\t'<<"Return to the main menu:"<<'\t'<<'\t';
				cout<<"(enter 'M')"<<endl;

				//Get info submenu selection:
				cin>>info_choice;
				cin.ignore(100, '\n');
				info_choice = toupper(info_choice);

				//If getting height:
				if (info_choice == 'H')
				{
					//Get the height:
					height = dictionary.get_height();
					cout<<'\n'<<"The current height of the tree is "
						<<height<<'.'<<endl;
				}
				
				//If calculating efficiency:
				if (info_choice == 'E')
				{
					//Determine if the tree is balanced:
					if (dictionary.is_balanced())
						cout<<'\n'<<"Your data tree is balanced!"<<endl;
					else cout<<'\n'<<"Your data tree is unbalanced."<<endl;

					//Calculate and display the efficiency rating:
					efficiency = dictionary.is_efficient();
					cout<<'\n'<<"Your data tree is currently operating at "
						<<efficiency<<"% efficiency."<<endl;
				}
				
				//If counting the items:
				if (info_choice == 'N')
				{
					//Count the items:
					count = dictionary.count_nodes();
					cout<<'\n'<<"There are currently "
						<<count<<" items in the tree."<<endl;
				}

			//Return to the main menu:
			} while (info_choice != 'M');
		}

	//Save and exit:
	} while (choice != 'X');

	cout<<'\n'<<'\n'<<'\n'<<"Have a nice day"<<endl;
	return 0;
}


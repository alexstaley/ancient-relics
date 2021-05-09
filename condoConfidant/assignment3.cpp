//Alex Staley
//astaley@pdx.edu
//CS 162 Program 3: The Condo Confidant
//November 6, 2018

//
	//		//		//		//     Smallest screen width for clean reading:	//
// **************************************************************************************************** //

//The Condo Confidant keeps track of the data
//acquired in the user's search for a condo,
//saving said data to secondary storage.

//The Confidant functions as follows:

	//DETERMINE IF USER HAS SAVED DATA:
//		If yes, external file --> master search array
//		If no, either:
//			user input --> master search array, or
//			alternate, existing file --> master search array

	//MAIN MENU:
//		Enter a new condo:
//			user input --> master search array
//		Look up a condo:
//			edit, or
//			remove it
//		Display the search array:
//			edit, or
//			remove a condo
//		Calculate monthly payments
//			and which condos user can afford
//			given user's financial data
//		Save and exit:
//			master search array --> external file

//

//Note:
	//While the fstream functions import() and save()
	//only read and write to a maximum of 10 elements in the search[] array,
	//the search array has size 31 because the remove() function
	//does not delete the last element of the array.
//
	//The extra indices of the array serve as a buffer,
	//and removed condos are tracked by the int variable "backlog",
	//which is used to prevent the user
	//from accessing outside memory.

//

//The Condo Confidant is sanitized
//against ambiguity in user capitalization.

//

//No finances were harmed during the making of this program.
							    // Smallest screen width for clean reading:	//
// **************************************************************************************************** //





// ************ //

//     PPDS	//
// ************ //



#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

const int SCALE = 26;





// ******************** //

//	  STRUCTS	//
// ******************** //



struct listing			//Condo data:
{
	char name[SCALE];	//User-defined name
	char address[SCALE*4];	//Street address
	char hood[SCALE];	//Neighborhood
	int commute;		//Commute time in minutes
	int size;		//Size in square feet
	int beds;		//Number of bedrooms
	int price;		//Listing price
	int hoa;		//Homeowners' Association fees in $/month
	int tax;		//Property tax in $/year
	bool parking;		//Off street parking space
	bool laundry;		//Laundry in the unit
	bool appliances;	//Newer appliances
};

struct loan			//Financial data:
{
	int down;		//Down payment
	float rate;		//Mortgage rate
	int insurance;		//Homeowner's insurance and PMI
};





// ******************************************** //

//	//	FUNCTION PROTOTYPES	//	//
// ******************************************** //



//Master functions that make up the main menu:

char menu			//Get user choice
	(int saved_condos, int backlog);
void input_option		//Enter a new condo
	(listing search[], int & saved_condos);
void lookup_option		//Look up a condo
	(listing search[], int & saved_condos, int & backlog);
void display_option		//Display all the condos
	(listing search[], int & saved_condos, int & backlog);
void calculate_option		//Calculate monthly costs
	(listing search[], int & saved_condos, loan & finances);



//Functions that operate at the member, struct or array level:

char edit_menu();		//Make edit() readable
void edit			//Edit a given parameter on a condo
	(listing & condo, char spec);
void remove			//Remove a condo from the search array
	(int selection, listing search[], int & saved_condos, int & backlog);
void input(listing & condo);	//Make input_option() readable
void display(listing & condo);	//Display data on a given condo
void awkward(loan & finances);	//Ask the user personal financial questions



//Functions that operate at the word level:

bool yes_no();			//Return valid user response to Y/N question
void caps(char phrase[]);	//Sanitize user capitalization



//Import/export functions:

int import		//Read: external file --> search array
	(char filename[], listing search[]);
void save		//Write: search array --> external file
	(char filename[], listing search[], int saved_condos);





// ************************************ //

//	//	MAIN()		//	//
// ************************************ //



int main()
{
	listing search[31];			//Array of condos in user's search (10 max)
	loan finances;				//User's financial data
	int saved_condos;			//Number of condos in array
	int i;					//Loop increment
	int backlog;				//Garbage data tracker
	char filename[11] = "condos.txt";	//External file name
	char alt_file[11] = "extant.txt";	//Existing data file
	char choice;				//Menu option

	backlog = 0;				//Initialize garbage data
						//caused by remove() function
	
	finances.down = 0;			//Initialize down payment
						//for awkward() function
	
	//Welcome the user:
	cout<<'\n'<<"Welcome to The Condo Confidant!"<<endl;
	cout<<'\n'<<"I'm here to help you organize your condo search";
	cout<<'\n'<<"with structs and external files."<<endl;
	cout<<'\n'<<"Once I have your condo data, I can:"<<endl;
	cout<<'\n'<<'\t'<<"Enter additional condos (up to 10 total),"<<endl;
	cout<<'\n'<<'\t'<<"Look up a condo by name,"<<endl;
	cout<<'\n'<<'\t'<<"Display all the data on all the condos in your search,"<<endl;
	cout<<'\n'<<'\t'<<"Read your financial information and tell you";
	cout<<'\n'<<'\t'<<"which condos you can afford, and"<<endl;
	cout<<'\n'<<'\t'<<"Save your search to an external file."<<endl;
	cout<<'\n'<<'\n'<<"I can also edit and remove existing condo data;";
	cout<<'\n'<<"those options can be found in the 'Lookup' and 'Display' menus."<<endl;
	cout<<'\n'<<'\n'<<"I am not case-sensitive."<<endl;
	cout<<'\n'<<'\n'<<'\n'<<'\t'<<"Are you ready???"<<endl;
	while (!yes_no()) cout<<'\n'<<'\n'<<"...are you ready yet?"<<endl;

	//Import the saved data
	//if the user has any:
	saved_condos = import(filename, search);

	//Obtain condo data from the user
	//if there is none to import:
	if (saved_condos == 0)
	{
		cout<<'\n'<<"To begin, we'll need to enter in data"<<endl;
		cout<<"on at least 1 condo."<<endl;

		//Offer existing data file:
		cout<<'\n'<<'\t'<<"...That is, unless you'd like to";
		cout<<'\n'<<"import someone else's preexisting condo data."<<endl;
		cout<<'\n'<<"That would be weird, but I understand";
		cout<<'\n'<<"if you're not in a data-entry mood."<<endl;
		cout<<'\n'<<'\n'<<'\t'<<"Would you like to import existing data? Y/N"<<endl;
		if (yes_no()) saved_condos = import(alt_file, search);
		else
		{
			cout<<'\n'<<"Great! Let's get started."<<endl;
			input_option(search, saved_condos);
		}
	}

//	//	MAIN	MENU	//	//

	do
	{
		choice = menu(saved_condos, backlog);

		if (choice == 'E')
			input_option(search, saved_condos);
		if (choice == 'L')
			lookup_option(search, saved_condos, backlog);
		if (choice == 'D')
			display_option(search, saved_condos, backlog);
		if (choice == 'C')
			calculate_option(search, saved_condos, finances);

		if (choice == 'X')
			save(filename, search, saved_condos);

	} while (choice != 'X');

//	//	//	//	//	//

	cout<<'\n'<<'\n'<<endl;
	cout<<'\t'<<"Your data is saved. Thanks for searching!"<<endl;
	cout<<'\n'<<'\n'<<'\n'<<'\n'<<'\n'<<endl;

	return 0;
}





// ************************************ //

//	MAIN	MENU	FUNCTIONS:	//

//	menu()
//	input_option()
//	lookup_option()
//	display_option()
//	calculate_option()
// ************************************ //



//The menu() function displays
//the user's options
//and returns the user's choice.
char menu(int saved_condos, int backlog)
{
	char response;		//Menu option

	cout<<'\n'<<'\n'<<'\n'<<endl;
	if ((backlog + saved_condos) < 21)
	{
		cout<<'\t'<<"What would you like to do with your condo search data?"<<endl;
		do
		{
			cout<<'\n'<<"You can:"<<endl;
			cout<<'\t'<<"Enter another condo"<<'\t'<<'\t'<<"(enter 'E')"<<endl;
			cout<<'\t'<<"Look up a condo"<<'\t'<<'\t'<<'\t'<<"(enter 'L')"<<endl;
			cout<<'\t'<<"Display all the condos"<<'\t'<<'\t'<<"(enter 'D')"<<endl;
			cout<<'\t'<<"Calculate which you can afford"<<'\t'<<"(enter 'C')"<<endl;
			cout<<'\t'<<"Save and exit the program"<<'\t'<<"(enter 'X')"<<endl;
			
			//Warn the user about junk data buildup:
			if ((backlog + saved_condos) > 15)
			{
				cout<<'\n'<<'\n'<<"Not for nothing, but you should";
				cout<<'\n'<<"save, exit, and restart the program soon.";
				cout<<'\n'<<"I take no responsibility for what could happen."<<endl;
			}

			//Ensure valid user choice:
			cin>>response;
			cin.ignore(100, '\n');
			response = toupper(response);
			if (response != 'E' &&
				response != 'L' &&
				response != 'D' &&
				response != 'C' &&
				response != 'X')
				cerr<<"Please choose from the given options."<<endl;
		} while (response != 'E' &&
			response != 'L' &&
			response != 'D' &&
			response != 'C' &&
			response != 'X');
	}

	//If user has "removed" enough condos
	//before adding to conceivably
	//fill up the entire size-31 array,
	//force them to save and exit:
	else
	{
		cout<<'\n'<<'\n'<<'\t'<<"DATA FIEND!!! You must save and exit the program";
		cout<<'\n'<<'\t'<<"before continuing. Adding and removing and removing and adding";
		cout<<'\n'<<'\t'<<"like some kind of condo contortionist... SHAME!!!"<<endl;
		do
		{
			cout<<'\n'<<"Repent and press 'X'!"<<endl;
			cin>>response;
			cin.ignore(100, '\n');
			response = toupper(response);
		} while (response != 'X');

		cout<<'\n'<<"Good. Now come back and just... save and exit";
		cout<<'\n'<<"and enter again after every few major changes, huh?";
		cout<<'\n'<<"We should all be so wise."<<endl;

	}

	return response;
}



//The input_option() function
//reads in and displays condo data from the user,
//and saves it in a master condo search array.
void input_option(listing search[], int & saved_condos)
{
	listing condo;	//Condo struct
	bool again;	//Enter another? Y/N
	
	//If user has 10 condos already saved,
	//prevent them from entering another:
	if (saved_condos == 10)
	{
		cout<<'\n'<<"You have 10 condos saved.";
		cout<<'\n'<<'\t'<<"Buy one already why dontcha!"<<endl;
	}
	else
	{

	//Loop if the user has less than 10 condos saved:
		do
		{
			//Obtain and display user input:
			input(condo);
			cout<<'\n'<<'\t'<<'\t'<<'\t'<<"..."<<'\n'<<endl;
			display(condo);

			//Add the data to the search array
			//and increment the associated variable:
			search[saved_condos++] = condo;
			cout<<'\n'<<"That's "<<saved_condos<<" condo";
			if (saved_condos != 1) cout<<'s';
			cout<<" so far recorded in your search."<<endl;
	
			//Prompt the user to continue or exit...
			cout<<'\n'<<"Would you like to enter another? Y/N"<<endl;
			again = yes_no();

			//...unless they've hit 10 condos:
			if (again && saved_condos == 10)
			{
				cout<<'\n'<<"You have 10 condos saved.";
				cout<<'\n'<<'\t'<<"Buy one already why dontcha!"<<endl;
			}

		} while (again && saved_condos < 10);
	}
}



//The lookup_option() function
//allows the user to view
//the data on a specific condo,
//and edit or remove it
//from the master search array.
void lookup_option(listing search[], int & saved_condos, int & backlog)
{
	int i;			//Loop increment
	int selection;		//Index of target condo
	int mismatch;		//Used to ensure valid condo name input
	char response;		//Menu choice
	char name[SCALE];	//Name of target condo

	if (saved_condos == 0) cout<<'\n'<<"You have no saved condos to look up."<<endl;
	else
	{
		do
		{
			//Prompt the user for the name
			//of the condo to be looked up:
			cout<<'\n'<<"What is the name of the condo you'd like to view?"<<endl;
			cin.get(name, SCALE, '\n');
			cin.ignore(100, '\n');

			//Compare the user's input
			//to the names of the condos
			//in the search array:
			caps(name);
			mismatch = 0;
			for (i=0; i<saved_condos; ++i)
			{
				if (strcmp(name, search[i].name) == 0)
				{
					selection = i;		//Index of selected condo
					display(search[i]);	//Display user's selection
				}
				else ++mismatch;
			}

			//Ensure the condo input
			//by the user is on the list:
			if (mismatch == i)
				cout<<'\n'<<name<<" does not match any condos on your list."<<endl;
		} while (mismatch == i);

		//LOOKUP MENU:
		do
		{
			do
			{
				cout<<'\n'<<"What would you like to do with "<<name<<"?";
				cout<<'\n'<<"You can:"<<endl;
				cout<<'\t'<<"Edit it"<<'\t'<<'\t'<<'\t';
				cout<<'\t'<<"(enter E')"<<endl;
				cout<<'\t'<<"Remove it from the list"<<'\t';
				cout<<'\t'<<"(enter 'R')"<<endl;
				cout<<'\t'<<"Return to the main menu"<<'\t';
				cout<<'\t'<<"(enter 'M')"<<endl;

				//Ensure valid user choice:
				cin>>response;
				cin.ignore(100, '\n');
				response = toupper(response);
				if (response != 'E' && response != 'R' && response != 'M')
					cerr<<'\n'<<"Please choose from the given options."<<endl;
			} while (response != 'E' && response != 'R' && response != 'M');

			if (response == 'E')		//User edits the condo
				edit(search[selection], edit_menu());

			if (response == 'R')		//User removes the condo
			{
				remove((selection+1), search, saved_condos, backlog);

				//Display the new total
				//and the new complete array:
				cout<<'\n'<<"Done! You now have "<<saved_condos<<" saved condo";
				if (saved_condos != 1) cout<<'s';
				cout<<'.'<<endl;
				for (i=0; i<saved_condos; ++i)
					display(search[i]);
			}
								//'R' or 'M' selection
		} while (response != 'R' && response != 'M');	//returns user to main menu
	}							//without the lookup loop
}



//The display_option() function
//displays the entire master array
//of the user's saved condos
//and allows the user
//to edit or remove one.
void display_option(listing search[], int & saved_condos, int & backlog)
{
	int i = 0;		//Loop increment
	int selection;		//Index of target condo
	char response;		//Menu choice

	//Display the number
	//of saved condos:
	cout<<'\n'<<'\n'<<'\t'<<"You have ";
	cout<<saved_condos<<" saved condo";
	if (saved_condos != 1) cout<<'s';
	cout<<'.'<<endl;

	if (saved_condos > 0)
	{

		//Display a numbered list
		//of all the condos
		//and all their data:
		for (i=0; i<saved_condos; ++i)
		{
			cout<<(i + 1)<<'.'<<endl;
			display(search[i]);
		}

		//DISPLAY MENU:
		do
		{
			do
			{
				cout<<'\n'<<'\n'<<'\t'<<"You can:"<<endl;
				cout<<'\t'<<"Edit a condo on the list";
				cout<<'\t'<<"(enter 'E')"<<endl;
				cout<<'\t'<<"Remove a condo from the list";
				cout<<'\t'<<"(enter 'R')"<<endl;
				cout<<'\t'<<"Return to the main menu"<<'\t';
				cout<<'\t'<<"(enter 'M')"<<endl;

				//Ensure valid user choice:
				cin>>response;
				cin.ignore(100, '\n');
				response = toupper(response);
				if (response != 'E' && response != 'R' && response != 'M')
					cerr<<'\n'<<"Please choose from the given options."<<endl;
			} while (response !='E' && response != 'R' && response != 'M');
		
			if (response == 'E')		//User edits a condo
			{				//By picking the corresponding number
				cout<<'\n'<<"Which condo would you like to edit? "
					<<"Enter the corresponding number."<<endl;
				cin>>selection;
				cin.ignore(100, '\n');
				display(search[selection-1]);		//Display selection
				edit(search[selection-1], edit_menu());	//Edit selection
			}

			if (response == 'R')		//User removes a condo
			{				//By picking the corresponding number
				cout<<'\n'<<"Which condo would you like to remove? "
					<<"Enter the corresponding number."<<endl;
				cin>>selection;
				cin.ignore(100, '\n');
				remove(selection, search, saved_condos, backlog);

				//Display the new number of condos
				//and new complete search array.
				cout<<'\n'<<"Done! You now have ";
				cout<<saved_condos<<" saved condo";
				if (saved_condos != 1) cout<<'s';
				cout<<'.'<<endl;

				for (i=0; i<saved_condos; ++i)
				{
					cout<<(i + 1)<<"."<<endl;
					display(search[i]);
				}
			}
		
		//User enters 'M' to return
		//to the main menu:
		} while (response != 'M' && saved_condos > 0);
	}


}



//The calculate_option() function allows
//the user to determine which condos
//they can afford, given a
//monthly housing budget.
void calculate_option(listing search[], int & saved_condos, loan & finances)
{
	int within[10];		//Indices of affordable condos
	int reach = 0;		//Counter of affordable condos
	int i;			//Loop increment
	int max;		//Maximum monthly housing cost
	int principal;		//Listing price less down payment
	int mortgage;		//Total monthly principal & interest payments
	int payment;		//Total monthly housing cost
	float rate;		//Expected monthly mortgage rate
	float exp;		//Exponential term in mortgage calculator

	//Get the user's financial data:
	awkward(finances);

	//Determine the user's maximum
	//affordable monthly housing cost:
	cout<<'\n'<<"Let's see which of these condos you can afford to live in.";
	cout<<'\n'<<"what monthly payment would you like to stay under?"<<'\n'<<'$';
	cin>>max;
	cin.ignore(100, '\n');
	cout<<'\n'<<'$'<<max<<", okay."<<endl;

	//Ensure the user is ready
	//to view the data:
	cout<<'\n'<<'\t'<<"... Just so you know,";
	cout<<'\n'<<"I'm about to display a bunch of data,";
	cout<<'\n'<<"so you should be prepared to scroll up.";
	do cout<<'\n'<<"Are you prepared to scroll up?"<<endl;
	while (!yes_no());

	//Calculate the monthly insurance rate
	//and process the exponential term
	//of the monthly loan payment equation:
	rate = finances.rate / 1200;	//(1200 = 12 months/year * 100 (%))

	exp = rate + 1;			//mortgage payment = principal*rate*(exp / (exp-1))
	for (i=1; i<360; ++i)		//where exp = (rate+1)^360
		exp *= (rate + 1);	//(360 = number of payments in a 30-yr mortgage)

	//Display a list of monthly costs
	//and totals for each condo:
	cout<<'\n'<<"Here we go!"<<'\n'<<endl;
	for (i=0; i<saved_condos; ++i)
	{
		cout<<'\n'<<"For "<<search[i].name<<':'<<endl;

		//Calculate the monthly mortgage payment:
		principal = search[i].price - finances.down;
		mortgage = principal * rate * (exp / (exp - 1));

		//Display the tabulated data:
		cout<<'\n'<<'\t'<<"Principal and interest";
		cout<<'\n'<<'\t'<<'\t'<<"on the loan:";
		cout<<'\t'<<'$'<<mortgage<<"/month";
		cout<<'\n'<<'\t'<<"Property taxes:"<<'\t';
		cout<<'\t'<<'$'<<search[i].tax / 12<<"/month";
		cout<<'\n'<<'\t'<<"HOA dues:"<<'\t';
		cout<<'\t'<<'$'<<search[i].hoa<<"/month";
		cout<<'\n'<<'\t'<<"Insurance:"<<'\t';
		cout<<'\t'<<'$'<<finances.insurance<<"/month"<<endl;

		//Calculate and display the user's
		//total monthly housing costs:
		payment = mortgage + search[i].hoa
			+ (search[i].tax / 12) + finances.insurance;
		cout<<'\n'<<'\t'<<search[i].name<<" will be";
		cout<<'\n'<<'$'<<payment<<"/month."<<'\n'<<endl;

		//If the user can afford the condo,
		//count it and record its index:
		if (payment <= max) within[reach++] = i;
	}

	if (reach == 0)	//If user can't afford any condos on their list:
	{
		cout<<'\n'<<"Looks like you'll need to reevaluate your budget";
		cout<<'\n'<<"... or find some cheaper condos!"<<endl;
	}
	else
	{
		//Display the condos
		//the user can afford:
		cout<<'\n'<<"Here are the condos you can live in";
		cout<<'\n'<<"for at or under $"<<max<<"/month:"<<'\n'<<endl;
		for (i=0; i<reach; ++i) display(search[within[i]]);
	}
}		//Return to the main menu.





// **************************************************** //

//	//	HIGH-LEVEL	FUNCTIONS	//	//

//	edit_menu()	edit()
//	remove()	input()
//	display()	awkward()
// **************************************************** //



//The edit_menu function determines
//which parameter the user would like to edit.
char edit_menu()
{
	char spec;	//Parameter targeted for edit

	cout<<'\n'<<"What parameter would you like to change?"<<endl;
	do
	{
		cout<<"You can choose any of the following:"<<endl;
		cout<<'\t'<<"Name:"<<'\t'<<'\t'<<"enter 'N'"<<endl;
		cout<<'\t'<<"Address:"<<'\t'<<"enter 'A'"<<endl;
		cout<<'\t'<<"Neighborhood:"<<'\t'<<"enter 'H'"<<endl;
		cout<<'\t'<<"Commute:"<<'\t'<<"enter 'C'"<<endl;
		cout<<'\t'<<"Size:"<<'\t'<<'\t'<<"enter 'S'"<<endl;
		cout<<'\t'<<"Beds:"<<'\t'<<'\t'<<"enter 'B'"<<endl;
		cout<<'\t'<<"Price:"<<'\t'<<'\t'<<"enter 'P'"<<endl;
		cout<<'\t'<<"HOA dues:"<<'\t'<<"enter 'D'"<<endl;
		cout<<'\t'<<"Tax:"<<'\t'<<'\t'<<"enter 'T'"<<endl;
		cout<<'\t'<<"Parking:"<<'\t'<<"enter 'K'"<<endl;
		cout<<'\t'<<"Laundry:"<<'\t'<<"enter 'L'"<<endl;
		cout<<'\t'<<"or Appliances:"<<'\t'<<"enter 'I'"<<endl;
		cout<<'\n'<<'\n'<<'\t';
		cout<<"(Remember, we're not case sensitive)"<<endl;

		cin>>spec;
		cin.ignore(100, '\n');
		spec = toupper(spec);
		
		if (spec != 'N' && spec != 'A' &&	//If spec is not a given option:
			spec != 'H' && spec != 'C' &&
			spec != 'S' && spec != 'B' &&
			spec != 'P' && spec != 'D' &&
			spec != 'T' && spec != 'K' &&
			spec != 'L' && spec != 'I')
			
			cerr<<'\n'<<"Please choose from the given options."<<endl;
	
	} while (spec != 'N' && spec != 'A' &&		//Loop while not an option
			spec != 'H' && spec != 'C' &&
			spec != 'S' && spec != 'B' &&
			spec != 'P' && spec != 'D' &&
			spec != 'T' && spec != 'K' &&
			spec != 'L' && spec != 'I');

	return spec;		//Return spec to edit() function
}


//The edit() function
//allows the user to change
//one datum on a given condo
//in their search.
void edit(listing & condo, char spec)
{
	if (spec == 'N')		//Name
	{
		cout<<'\n'<<"What is the condo's new name?"<<endl;
		cin.get(condo.name, SCALE, '\n');
		cin.ignore(100, '\n');
		caps(condo.name);		//Capitalize condo name
	}
	if (spec == 'A')		//Address
	{
		cout<<'\n'<<"What is the condo's real address?"<<endl;
		cin.get(condo.address, SCALE, '\n');
		cin.ignore(100, '\n');
		caps(condo.address);		//Capitalize street name & quadrant
	}
	if (spec == 'H')		//Neighborhood
	{
		cout<<'\n'<<"What neighborhood is the condo ACTUALLY in?"<<endl;
		cin.get(condo.hood, SCALE, '\n');
		cin.ignore(100, '\n');
		caps(condo.hood);		//Capitalize neighborhood name
	}
	if (spec == 'C')		//Commute
	{
		cout<<'\n'<<"How many minutes is your updated commute?"<<endl;
		cin>>condo.commute;
		cin.ignore(100, '\n');
	}
	if (spec == 'S')		//Size
	{
		cout<<'\n'<<"What is the updated square footage?"<<endl;
		cin>>condo.size;
		cin.ignore(100, '\n');
	}
	if (spec == 'B')		//Bedrooms
	{
		cout<<'\n'<<"What is the updated number of bedrooms?"<<endl;
		cin>>condo.beds;
		cin.ignore(100, '\n');
	}
	if (spec == 'P')		//Price
	{
		cout<<'\n'<<"What is the new price?"<<'\n'<<"$";
		cin>>condo.price;
		cin.ignore(100, '\n');
	}
	if (spec == 'D')		//HOA dues
	{
		cout<<'\n'<<"What are the updated monthly HOA dues?"<<'\n'<<"$";
		cin>>condo.hoa;
		cin.ignore(100, '\n');
	}
	if (spec == 'T')		//Property tax
	{
		cout<<'\n'<<"What is the updated property tax, yearly?"<<'\n'<<"$";
		cin>>condo.tax;
		cin.ignore(100, '\n');
	}
	if (spec == 'K')		//Parking
	{
		cout<<'\n'<<"OK, so... for real, does the unit have parking?"<<endl;
		if (yes_no()) condo.parking = true;
		else condo.parking = false;
	}
	if (spec == 'L')		//Laundry
	{
		cout<<'\n'<<"OK, so... for real, is there laundry in the unit?"<<endl;
		if (yes_no()) condo.laundry = true;
		else condo.laundry = false;
	}
	if (spec == 'I')		//Appliances
	{
		cout<<'\n'<<"OK, so... for real,";
		cout<<'\n'<<"is the stuff in there gonna break down on you?"<<endl;
		if (yes_no()) condo.appliances = false;
		else condo.appliances = true;
	}

	//Display edited condo profile:
	cout<<'\n'<<'\n'<<'\t'
		<<"Okay, here is your edited "<<condo.name<<" profile:"
		<<'\n'<<'\n'<<endl;
	display(condo);
}



//The remove() function
//removes a condo from the list
//of saved condos.
void remove(int selection, listing search[], int & saved_condos, int & backlog)
{
	int i;

	for (i=selection; i<saved_condos; ++i)
		search[i-1] = search[i];
	saved_condos -= 1;
	backlog += 1;
}



//The input() function
//reads in data on a single condo
//from the user.
void input(listing & condo)
{
	int i;		//Loop increment
	
	cout<<'\n'<<"What is the street address of the condo?"<<endl;
	cin.get(condo.address, SCALE*4, '\n');
	cin.ignore(100, '\n');		//Address
	caps(condo.address);		//Capitalize street names & quadrants
	
	cout<<'\n'<<"What neighborhood is the condo in?"<<endl;
	cin.get (condo.hood, SCALE, '\n');
	cin.ignore(100, '\n');		//Neighborhood
	caps(condo.hood);		//Capitalize neighborhood names

	cout<<'\n'<<"How many minutes will it take you to get to your daily life?"<<endl;
	cin>>condo.commute;		//Commute
	cin.ignore(100, '\n');

	cout<<'\n'<<"How many square feet does it have?"<<endl;
	cin>>condo.size;		//Size
	cin.ignore(100, '\n');

	cout<<'\n'<<"How many bedrooms does it have?"<<endl;
	cin>>condo.beds;		//Bedrooms
	cin.ignore(100, '\n');

	cout<<'\n'<<"What is the listing price?"<<endl;
	cin>>condo.price;		//Listing price
	cin.ignore(100, '\n');

	cout<<'\n'<<"What are they going to charge you per month for HOA dues?"<<endl;
	cin>>condo.hoa;			//HOA dues
	cin.ignore(100, '\n');

	cout<<'\n'<<"Per year, what will you be giving Uncle Sam in property taxes?"<<endl;
	cin>>condo.tax;			//Property tax
	cin.ignore(100, '\n');

	cout<<'\n'<<"Does the unit include off-street parking? Y/N"<<endl;
	if (yes_no()) condo.parking = true;
	else condo.parking = false;	//Parking

	cout<<'\n'<<"Is there laundry in the unit? Y/N"<<endl;
	if (yes_no()) condo.laundry = true;
	else condo.laundry = false;	//Laundry

	cout<<'\n'<<"Do any of the appliances seem likely"<<endl;
	cout<<"to quit their jobs in the next 5 years or so?"<<endl;
	if (!yes_no()) condo.appliances = true;
	else condo.appliances = false;	//Appliances

	cout<<'\n'<<"Last thing... please enter a name for this condo."<<endl;
	cin.get(condo.name, SCALE, '\n');
	cin.ignore(100, '\n');		//Name
	caps(condo.name);		//Capitalize condo name
}



//The display() function
//prints the tabulated data
//on a given condo.
void display(listing & condo)
{
	cout<<'\t'<<"CONDO:"<<'\t'<<'\t'<<'\t'<<condo.name<<'\n'<<endl;
	cout<<'\t'<<"Address:"<<'\t'<<'\t'<<condo.address<<endl;
	cout<<'\t'<<"Neighborhood:"<<'\t'<<'\t'<<condo.hood<<endl;
	cout<<'\t'<<"Listing price:"<<'\t'<<'\t'<<"$"<<condo.price<<endl;
	cout<<'\t'<<"HOA dues:"<<'\t'<<'\t'<<"$"<<condo.hoa<<"/mo."<<endl;
	cout<<'\t'<<"Property tax:"<<'\t'<<'\t'<<"$"<<condo.tax<<"/yr."<<endl;
	cout<<'\t'<<"Size:"<<'\t'<<'\t'<<'\t'<<condo.size<<" sq. ft."<<endl;
	cout<<'\t'<<"Bedrooms:"<<'\t'<<'\t'<<condo.beds<<endl;
	cout<<'\t'<<"Commute:"<<'\t'<<'\t'<<condo.commute<<" mins."<<endl;
	cout<<'\t'<<"Parking:"<<'\t'<<'\t';
		if (condo.parking) cout<<"YES"<<endl;
		if (!condo.parking) cout<<"NO"<<endl;
	cout<<'\t'<<"Laundry:"<<'\t'<<'\t';
		if (condo.laundry) cout<<"YES"<<endl;
		if (!condo.laundry) cout<<"NO"<<endl;
	cout<<'\t'<<"Halfway decent stuff:"<<'\t';
		if (condo.appliances) cout<<"YES"<<endl;
		if (!condo.appliances) cout<<"NO"<<endl;
	cout<<'\n'<<'\n'<<endl;
}



//The awkward() function asks the user
//personal financial questions.
void awkward(loan & finances)
{
	bool read;		//Read in data? Y/N

	if (finances.down == 0)	//User's first time in awkward() function
	{
		read = true;
		cout<<'\n'<<"First we'll need some data from you."<<endl;
	}
	else			//User is returning to awkward() function
	{
		cout<<'\n'<<"We have you making a down payment of $"<<finances.down;
		cout<<'\n'<<"on a 30-year mortgage at a rate of "<<finances.rate<<"%."<<endl;
		cout<<'\n'<<"Would you like to change this data? Y/N"<<endl;
		read = yes_no();
	}

	//Get the user's data:
	if (read)
	{
		//Get the user's down payment:
		cout<<'\n'<<'\t'<<"In US dollars, how much";
		cout<<'\n'<<"will you place as a down payment?"<<'\n'<<'$';
		cin>>finances.down;
		cin.ignore(100, '\n');

		//Establish a minimum down payment of $3000:
		while (finances.down < 3000)
		{
			cout<<'\n'<<"This isn't 2008 and that is not a good idea.";
			cout<<'\n'<<"Come on now, how much you got?"<<'\n'<<'$';
			cin>>finances.down;
			cin.ignore(100, '\n');
		}
		if (finances.down > 30000) cout<<'\n'<<"Nice.";
		cout<<'\n'<<'$'<<finances.down<<", okay."<<endl;

		//Get the user's expected mortgage rate:
		cout<<'\n'<<'\t'<<"And what rate do you expect";
		cout<<'\n'<<"to be offered on your mortgage?";
		cout<<'\n'<<'\n'<<"Looking for a percentage here,";
		cout<<'\n'<<"decimals are ok but no % symbols please."<<endl;
		cin>>finances.rate;
		cin.ignore(100, '\n');

		//Establish realistic bounds for the rate:
		while (finances.rate < 1.00 || finances.rate > 15.00)
		{
			if (finances.rate < 1.00)
			{
				cout<<'\n'<<"Bill Gates's credit isn't that good.";
				cout<<'\n'<<"For real, what rate are they giving you?"<<endl;
				cin>>finances.rate;
				cin.ignore(100, '\n');
			}
			if (finances.rate > 15.00)
			{
				cout<<'\n'<<'\t'<<"..."<<'\t'<<"..."<<endl;
				cout<<'\n'<<"You scared me for a second there, I thought";
				cout<<'\n'<<"you were serious! We're assuming a 30-year mortgage.";
				cout<<'\n'<<"No way it's more than 15%,";
				cout<<'\n'<<"and honestly more than 8% would be loan sharking.";
				cout<<'\n'<<"For real, what rate are they giving you?"<<endl;
				cin>>finances.rate;
				cin.ignore(100, '\n');
			}
		}
		if (finances.rate > 5.00) cout<<'\n'<<"Yeesh.";
		cout<<'\n'<<finances.rate<<"%, okay."<<endl;

		//Assume the user's insurance payments:
		cout<<'\n'<<'\n'<<'\t'<<"We're going to assume you're paying";
		cout<<'\n'<<"$35/month total for homeowners' insurance and";
		cout<<'\n'<<"partial mortgage insurance if you need it."<<endl;
		finances.insurance = 35;

		//Assume the user's mortgage terms:
		cout<<'\n'<<'\t'<<"We're also going to assume a fixed rate,";
		cout<<'\n'<<"30-year mortgage, because this assignment is due soon."<<endl;
	}

	else cout<<'\n'<<"Good. I hate asking those questions."<<endl;
}





// **************************************************** //

//	//	LOW-LEVEL	FUNCTIONS	//	//

//	yes_no()
//	caps()
// **************************************************** //



//The yes_no() function ensures valid user response
//to a yes or no question.
bool yes_no()
{
	char response;

	cin>>response;
	cin.ignore(100, '\n');
	response = toupper(response);
	while (response != 'Y' && response != 'N')
	{
		cout<<'\n'<<"I know sometimes it's tough to tell. "
			<<"Best guess, Y or N."<<endl;
		cin>>response;
		cin.ignore(100, '\n');
		response = toupper(response);
	}

	if (response == 'Y') return true;
	if (response == 'N') return false;
}



//The caps() function sanitizes user capitalization
//and optimizes it for address display.
void caps(char phrase[])
{
	int i;
	int length = strlen(phrase);

	//Erase user capitalization:
	for (i=0; i<length; ++i)
		phrase[i] = tolower(phrase[i]);

	//Capitalize first letter after
	//every space or hyphen:
	phrase[0] = toupper(phrase[0]);
	for (i=1; i<length; ++i)
		if (phrase[i-1] == ' ' || phrase[i-1] == '-')
			phrase[i] = toupper(phrase[i]);
	
	//Capitalize quadrants NE, SW, etc:
	for (i=0; i<length; ++i)
		if (phrase[i] == ' ' && phrase[i+3] == ' ' &&
		(phrase[i+1] == 'N' || phrase[i+1] == 'S') &&
		(phrase[i+2] == 'e' || phrase[i+2] == 'w'))
			phrase[i+2] = toupper(phrase[i+2]);
}





// **************************************************** //

//	//	IMPORT/EXPORT	FUNCTIONS	//	//

//	import()
//	save()
// **************************************************** //



//The import() function checks
//if the user has saved data, and
//if so reads it into the search array.
int import(char filename[], listing search[])
{
	ifstream in_file;	//Input stream variable
	int saved_condos;	//Number of structs in saved array
	int i;			//Loop increment
	char check[SCALE];	//End of file flag

	in_file.open(filename);
	if (!in_file)		//No file = new user
	{
		saved_condos = 0;
		cout<<'\n'<<"You have 0 saved condos."<<endl;
	}

	if (in_file)		//Import search array
	{
		//Import the user's condo search data,
		//starting with the number of saved condos
		//in the search array:
		in_file>>saved_condos;
		in_file.ignore(100, ':');
		do
		{
			for (i=0; i<saved_condos; ++i)
			{
				in_file.get(search[i].name, SCALE, ':');
				in_file.ignore(100, ':');
				in_file.get(search[i].address, SCALE*4, ':');
				in_file.ignore(120, ':');
				in_file.get(search[i].hood, SCALE, ':');
				in_file.ignore(100, ':');
				in_file>>search[i].commute;
				in_file.ignore();
				in_file>>search[i].size;
				in_file.ignore();
				in_file>>search[i].beds;
				in_file.ignore();
				in_file>>search[i].price;
				in_file.ignore();
				in_file>>search[i].hoa;
				in_file.ignore();
				in_file>>search[i].tax;
				in_file.ignore();
				in_file>>search[i].parking;
				in_file.ignore();
				in_file>>search[i].laundry;
				in_file.ignore();
				in_file>>search[i].appliances;
				in_file.ignore();
			}
			in_file.get(check, SCALE, ':');
			in_file.ignore(100, ':');
		} while (!in_file.eof());
		in_file.close();

		//Display the number
		//of saved condos:
		cout<<'\n'<<"You have "<<saved_condos<<" saved condo";
		if (saved_condos != 1) cout<<'s';
		cout<<'!'<<endl;
	}

	return saved_condos;
}



//The save() function writes
//the master condo search array
//to an external file.
void save(char filename[], listing search[], int saved_condos)
{
	ofstream out_file;	//Output stream variabe
	int i;			//Loop increment
	
	out_file.open(filename);

	//Ensure a good connection:
	if (!out_file)
		cerr<<'\n'<<'\t'<<"Error, file not connected..."<<endl;

	//Write the data:
	if (out_file)
	{
		//The 1st datum in the file
		//is the number of structs
		//in the array:
		out_file<<saved_condos<<':';

		//Write the rest of the data:
		for (i=0; i<saved_condos; ++i)
		{
			out_file<<search[i].name<<':'<<search[i].address<<':'
				<<search[i].hood<<':'<<search[i].commute<<':'
				<<search[i].size<<':'<<search[i].beds<<':'
				<<search[i].price<<':'<<search[i].hoa<<':'
				<<search[i].tax<<':'<<search[i].parking<<':'
				<<search[i].laundry<<':'<<search[i].appliances<<':';
		}

		out_file.close();
	}
}

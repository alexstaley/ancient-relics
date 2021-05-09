//Alex Staley
//CS163 - Program 4
//February 23 - March 7, 2019

//Program 4 is a set of computer science terms
//together with their definitions and categories
//arranged in a binary search tree.

//The "term" class has as data members
//the term itself, a category (e.g. "trees"),
//the term's definition, and a searching/sorting
//key (the term itself converted to upper case).

//Its member functions include two each for
//comparing and copying terms (one from a word
//and one from a term object), two for displaying
//terms (one for the term and its definition,
//one for the term alone), and one to write
//a term and its definition to an external file.

//The "tree" class is a binary search tree built
//on a "node" struct that contains a term object
//and two pointers, "left" and "right".

//Its member functions include insertion, removal
//and retrieval, in addition to three display functions:
//one to display a range of terms, one to display
//the entire tree, and a third to display the terms
//as they are arranged in the tree.

//Also implemented in the tree class are functions
//to calculate the height, efficiency and number
//of items in the tree, and to determine
//whether the tree is balanced.

//All tree navigation is executed recursively;
//most of the tree functionality is split between
//public wrapper functions and private recursive ones.



#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

const int SIZE = 33;	//Maximum length of a term
bool yn();		//Get user's response to a Y/N question



class term
{
	public:
		term();			//Constructors
		term(char * word, char * field, char * definition);

		~term();		//Destructor
		void write_term();	//Append the term to an external file

		int compare_term	//Compare a word with a term's name
			(char * to_compare);
		int compare_term	//Compare the key of two terms
			(term & to_compare);

		void copy_term		//Make a deep copy from statically allocated data
			(char * word, char * field, char * definition);
		void copy_term		//Make a deep copy of an existing term
			(term & to_copy);

		void display_term();	//Display a term's definition
		void display_name();	//Display just the term itself

	private:
		char * name;		//The term itself
		char * topic;		//The topic of the term
		char * about;		//The term's definition
		char * key;		//The term in caps (for sorting/searching)
};



struct node
{
	term data;			//Term object
	node * left;			//Terms less than the term
	node * right;			//Terms not less than the term
};



class tree
{
	public:
		tree();			//Constructor
		~tree();		//Destructor
		
		int insert		//Wrapper for the insert function
			(char * word, char * field, char * definition);
		int remove		//Wrapper for the remove function
			(char * selection);
		int retrieve		//Wrapper for the retrieve function
			(char * selection, term & found);

		int display_all();	//Wrapper for the display_all function
		int display_tree();	//Wrapper for the display_tree function
		int display_range	//Wrapper for the display_range function
			(char * start, char * end);

		int get_height();	//Wrapper for the get_height function
		int is_balanced();	//Wrapper for the is_balanced function
		float is_efficient();	//Wrapper for the is_efficient function
		int count_nodes();	//Wrapper for the count_nodes function
	private:
		node * root;		//The root of the tree

		node * write		//Save the data to an external file
			(node * root);
		node * destroy		//Deallocate the nodes of the tree
			(node * & root);

		node * insert		//Insert a new term
			(char * word, char * field, char * definition, node * & root);
		int retrieve		//Look up a term
			(char * selection, term & found, node * root);

		node * remove		//Remove an existing term
			(char * selection, node * & root, bool & found);
		node * eat_ios		//Delete IOS and return its data
			(term & successor, node * & root);

		node * display_all	//Display the entire tree in order
			(node * root);
		node * display_tree	//Display the tree by level
			(node * root, int level);
		node * display_range	//Display all terms in a given range
			(char * start, char * end, node * root);

		int get_height		//Get the height of the tree
			(node * root);
		int is_balanced		//Compare the height of the L & R subtrees
			(node * root, bool & even);
		int is_efficient	//Determine the efficiency rating
			(node * root, int height, int level);
		int count_nodes		//Return the number of nodes in the tree
			(node * root);
};





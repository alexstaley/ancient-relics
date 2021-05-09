//Alex Staley
//CS163 - Program 4
//February 23 - March 7, 2019

//Functions of Program 4 can be grouped into
//two categories: tree member functions and
//term member functions.

//Term member functions include two each for
//comparing and copying terms (one from a word
//and one from a term object), two for displaying
//terms (one for the term and its definition,
//one for the term alone), and one to write
//a term and its definition to an external file.

//Tree member functions include insertion,
//retrieval and removal. The removal function
//is entirely recursive, including the case
//in which the inorder successor is promoted
//to root (via the recursive "eat_ios" function).

//Also implemented in the tree are three
//display functions: display_range and display_all,
//plus a display_tree function that displays
//the terms (without their definitions)
//as they are arranged in the tree.

//The display_range function is sanitized
//against user ambiguity between the
//"top" and "bottom" of the range ("k-a"
//displays as "a-k", for example), and can
//accept any combination of characters, words
//or phrases to bound it (including the case
//in which a single character bounds the end
//of the range, which requires attention).

//Other tree member functions determine if
//the tree is balanced, calculate its height
//and number of nodes, and compute the
//efficiency of the tree, which is determined by
//assigning an inefficiency number to each node with
//less than two children at a level l < (h - 1),
//where h is the height of the tree. Nodes closer
//to the root are considered more inefficient.

//The inefficiency numbers are summed and compared to
//the maximum inefficiency sum of a tree of equal height,
//then scaled by a factor proportional to the height
//to yield a percent efficiency score for the tree.

//With this algorithm, adding items to the tree
//typically increases efficiency, until the height
//is incremented, at which point there will be an
//efficiency drop proportional to the number of
//inefficient nodes (those with less than two children
//at a level less than h - 1).

//When testing this program, the grader is
//encouraged to remove the term "subtree"
//from the tree in its default state--
//this will result in a drop in height and
//therefore an increase in efficiency.





#include "tree.h"
using namespace std;



// **************************** //
//    TREE MEMBER FUNCTIONS:	//
//    				//
// **************************** //

//The constructor builds the tree
//from the "program4_data.txt" file
tree::tree()
{
	root = NULL;			//Initialize root to NULL
	int error = 0;			//Insertion error flag
	
	ifstream flin;			//File input stream varaible

	char word[SIZE];		//Temporary name
	char field[SIZE * 2];		//Temporary topic
	char definition[SIZE * 6];	//Temporary definition

	//Read from the file:
	flin.open("program4_data.txt");
	if (flin)
	{
		do
		{
			//Read name:
			flin.get(word, SIZE, '|');
			flin.ignore(100, '|');

			//Read topic:
			flin.get(field, SIZE * 2, '|');
			flin.ignore(100, '|');

			//Read definition:
			flin.get(definition, SIZE * 6, '|');
			flin.ignore(100, '|');
			flin.ignore(100, '\n');
			flin.ignore(100, '\n');

			//Insert the term into the tree:
			if (!insert(word, field, definition))
				++error;

		//Check if the end of the file
		//has been reached:
		} while (flin.peek() != ';');

		flin.close();
	}
}



//The destructor deallocates dynamic memory
//and invokes the write function to save the data.
tree::~tree()
{
	if (root)
	{
		//Make sure the file is empty:
		ofstream flout;
		flout.open("program4_data.txt");
		if (flout) flout.close();

		//Write the data to the file
		//and deallocate the root:
		root = write(root);
		root = destroy(root);

		//Write an end-of-file delimiter:
		flout.open("program4_data.txt", ios::app);
		if (flout)
		{
			flout<<';';
			flout.close();
		}
	}
}



//The destroy function
//deallocates memory for
//all the nodes in the tree.
node * tree::destroy(node * & root)
{
	if (!root) return NULL;

	//Delete children:
	root->left = destroy(root->left);
	root->right = destroy(root->right);

	//Delete node:
	delete root;
	root = NULL;

	return root;
}



//The write function saves the data
//to the "program4_data.txt" file.
node * tree::write(node * root)
{
	//Write the data:
	root->data.write_term();

	//Write the left subtree:
	if (root->left)
		root->left = write(root->left);

	//Write the right subtree:
	if (root->right)
		root->right = write(root->right);

	return root;
}



//The insert function is a wrapper
//for the recursive insert function.
int tree::insert(char * word, char * field, char * definition)
{
	//Insert the term:
	root = insert(word, field, definition, root);

	//Return 1 if successful:
	if (!root) return 0;
	return 1;
}



//The insert function adds
//a new term to the tree.
node * tree::insert(char * word, char * field, char * definition, node * & root)
{
	//Insert at a leaf:
	if (!root)
	{
		//Allocate memory and make
		//a deep copy of the term:
		root = new node;
		root->data.copy_term(word, field, definition);
		root->left = NULL;
		root->right = NULL;
	}

	//Traverse the tree:
	else
	{
		//If the data is less than
		//that of the current node,
		//traverse left:
		if (root->data.compare_term(word) < 0)
			root->left = insert(word, field, definition, root->left);

		//If greater than or equal to,
		//traverse right:
		else root->right = insert(word, field, definition, root->right);
	}

	return root;
}



//The remove function
//is a wrapper for
//the remove function.
int tree::remove(char * selection)
{
	//Exit if the tree is empty:
	if (!root) return 0;

	bool found = false;		//Flag for a found match
	
	//Copy term and convert to caps:
	char temp[strlen(selection) + 1];
	strcpy(temp, selection);
	for (int i = 0; i < strlen(temp); ++i)
		temp[i] = toupper(temp[i]);

	//Call recursive function:
	root = remove(temp, root, found);

	//Return positive if found:
	if (!found) return 0;
	return 1;
}



//The remove function
//removes a node from the tree.
node * tree::remove(char * selection, node * & root, bool & found)
{
	//Base case - no match found:
	if (!root) return NULL;

	//Search left subtree:
	if (root->data.compare_term(selection) < 0)
		root->left = remove(selection, root->left, found);

	//Search right subtree:
	if (root->data.compare_term(selection) > 0)
		root->right = remove(selection, root->right, found);

	//If a match is found:
	if (root->data.compare_term(selection) == 0)
	{
		//Set found flag to positive:
		found = true;

		//If removing from a leaf:
		if (!root->left && !root->right)
		{
			//Delete data and node
			//and reset to NULL:
			delete root;
			root = NULL;
		}

		//If matching node has children:
		else
		{
			//If match has one child:
			if (!root->left || !root->right)
			{
				//Copy child node:
				node * temp;
				if (root->left) temp = root->left;
				else temp = root->right;

				//Delete node and
				//reconnect tree:
				delete root;
				root = temp;
			}

			//If match has two children:
			else
			{
				//If match's right child
				//is the inorder successor:
				if (!root->right->left)
				{
					//Copy IOS data to root:
					root->data.copy_term(root->right->data);

					//Delete IOS and reconnect tree:
					node * temp = root->right->right;
					delete root->right;
					root->right = temp;
				}

				//If the inorder successor
				//is elsewhere:
				else
				{
					term successor;		//Term object to replace root's data

					//Find, copy and delete IOS:
					root->right = eat_ios(successor, root->right);

					//Copy IOS data to root:
					root->data.copy_term(successor);
				}
			}
		}
	}
	return root;
}



//The eat_ios function finds
//the inorder successor, deallocates
//its memory and returns its data.
node * tree::eat_ios(term & successor, node * & root)
{
	//Base case - IOS found:
	if (!root->left)
	{
		//Make a deep copy of the IOS data:
		successor.copy_term(root->data);
		node * temp = root->right;

		//Delete the IOS and
		//reconnect the tree:
		delete root;
		root = temp;
	}

	//Find the IOS:
	else root->left = eat_ios(successor, root->left);

	return root;
}



//The retrieve function
//is a wrapper for the
//retrieve function.
int tree::retrieve(char * selection, term & found)
{
	//Exit if the tree is empty:
	if (!root) return 0;

	//Return positive if term retrieved:
	if (retrieve(selection, found, root))
		return 1;
	return 0;
}



//The retrieve function
//copies the data of a
//term requested by the user.
int tree::retrieve(char * selection, term & found, node * root)
{
	//Return 0 if no match is found:
	if (!root) return 0;

	int match = 0;		//Flag for found match

	//Compare selection to the current term:
	int difference = root->data.compare_term(selection);

	//If match is found, copy the data
	//and return positive:
	if (difference == 0)
	{
		found.copy_term(root->data);
		return 1;
	}

	//Search the left subtree:
	if (difference < 0)
		match = retrieve(selection, found, root->left);

	//Search the right subtree:
	if (difference > 0)
		match = retrieve(selection, found, root->right);

	return match;
}



//The get_height function
//is a wrapper for the
//get_height function.
int tree::get_height()
{
	if (!root) return 0;
	return (get_height(root));
}



//The get_height function
//returns the height of the tree.
int tree::get_height(node * root)
{
	int height_left = 0;	//Height of left subtree
	int height_right = 0;	//Height of right subtree

	//Begin counting at a leaf:
	if (!root->left && !root->right)
		return 1;

	//Check the left subtree:
	if (root->left)
		height_left = get_height(root->left) + 1;

	//Check the right subtree:
	if (root->right)
		height_right = get_height(root->right) + 1;

	//Return the height of the taller subtree:
	return max(height_left, height_right);
}



//The is_balanced function
//is the wrapper for the
//is_balanced function.
int tree::is_balanced()
{
	//An empty tree is balanced:
	if (!root) return 1;
	
	bool even = true;	//Flag for balanced tree

	//Return positive if the tree is balanced:
	if (is_balanced(root, even))
		return 1;
	return 0;
}



//The is_balanced function
//compares the height of the
//left and right subtrees to
//determine if the tree is balanced
int tree::is_balanced(node * root, bool & even)
{
	//Return positive if off a leaf,
	//negative if the flag shows unbalanced:
	if (!root) return 1;
	if (!even) return 0;

	//Calculate the height difference:
	int left_sub = get_height(root->left);
	int right_sub = get_height(root->right);
	int difference = max(left_sub, right_sub) - min(right_sub, left_sub);

	//If unbalanced, set the flag:
	if (difference > 1)
		even = false;

	//Check subtrees:
	if (!is_balanced(root->left, even)
	|| !is_balanced(root->right, even))
		even = false;
	
	//Return negative if the
	//tree is unbalanced:
	if (!even) return 0;
	return 1;

}



//The is_efficient function
//calculates the efficiency
//of the tree.
float tree::is_efficient()
{
	//If tree is empty, return 0:
	if (!root) return 0;

	int height;		//Height of the tree
	int inefficiency;	//Inefficiency factor
	int count;		//2 less than the number of nodes in the tree
	int worst;		//Maximum inefficiency factor
	int score;		//Calculated tree efficiency

	//Get the height:
	height = get_height();

	//Determine the inefficiency of the tree
	//by summing that of its nodes:
	inefficiency = is_efficient(root, height, 1);

	//Get the number of nodes in the tree and
	//determine the maximum possible inefficiency:
	count = count_nodes(root) - 2;		//Inefficiency begins at level h - 2
	worst = count * (count + 1);		//1 + 2 + 3 + ... + n = n(n + 1)/2
	worst = worst / 2;

	//Compute the maximum likely inefficiency:
	worst = worst / (height / 2);

	//Calculate and return efficiency score:
	if (inefficiency > worst) return 0;
	return 100 * (worst - inefficiency) / worst;
}



//The is_efficient function
//calculates the inefficiency
//of the tree.
int tree::is_efficient(node * root, int height, int level)
{
	int inefficiency = 0;	//inefficiency = tree height - node level - 1
				//for each node with less than 2 children

	//If a node has less than two children,
	//rate its inefficiency:
	if (!root->left || !root->right)
	{
		inefficiency = height - level - 1;
		if (inefficiency < 0) inefficiency = 0;
	}

	//Check the left subtree:
	if (root->left)
		inefficiency += is_efficient(root->left, height, level + 1);

	//Check the right subtree:
	if (root->right)
		inefficiency += is_efficient(root->right, height, level + 1);
	
	//Return the sum:
	return inefficiency;
}



//The count_nodes function
//is a wrapper function for
//the count_nodes function.
int tree::count_nodes()
{
	if (!root) return 0;
	return count_nodes(root);
}



//The count_nodes function returns
//the number of nodes in the tree.
int tree::count_nodes(node * root)
{
	//A tree has no nodes.
	if (!root) return 0;

	int count = 0;		//Number of nodes

	//Count left subtree:
	if (root->left)
		count += count_nodes(root->left);

	//Count right subtree:
	if (root->right)
		count += count_nodes(root->right);

	//Count parent:
	return ++count;
}



//The display_range function
//is a wrapper for the
//display_range function.
int tree::display_range(char * start, char * end)
{
	//Return 0 if the tree is empty:
	if (!root) return 0;

	//If the upper bound is a single character,
	//change it to the next character to ensure inclusivity:
	if (strlen(end) == 1)
		++end[0];

	//Display the range:
	root = display_range(start, end, root);

	return 1;
}



//The display_range function
//displays the terms in the tree
//within a given alphabetic range.
node * tree::display_range(char * start, char * end, node * root)
{
	//Return null if off a leaf:
	if (!root) return NULL;

	//Display left subtree:
	if (root->left)
		root->left = display_range(start, end, root->left);

	//Compare data to range:
	int top = root->data.compare_term(start);
	int bottom = root->data.compare_term(end);

	//If within range, display data:
	if (min(bottom, top) <= 0 && max(top, bottom) >= 0)
		root->data.display_term();

	//Display right subtree:
	if (root->right)
		root->right = display_range(start, end, root->right);

	return root;
}



//The display_all function
//is a wrapper for the
//display_all function.
int tree::display_all()
{
	//Return negative
	//if tree is empty:
	if (!root) return 0;

	//Call display_all function:
	root = display_all(root);

	return 1;
}



//The display_all function
//displays the entire tree.
node * tree::display_all(node * root)
{
	//Return 0 if off a leaf:
	if (!root) return NULL;

	//Display left subtree:
	if (root->left)
		root->left = display_all(root->left);

	//Display parent:
	root->data.display_term();

	//Display right subtree:
	if (root->right)
		root->right = display_all(root->right);

	return root;
}



//The display_tree function
//is a wrapper for the
//display_tree function.
int tree::display_tree()
{
	//If the tree is empty, return 0:
	if (!root) return 0;

	//Display the root:
	cout<<'\n'<<"Level 1:"<<'\t';
	root->data.display_name();
	cout<<'\n';

	//Display the tree:
	root = display_tree(root, 2);

	return 1;
}



//The display_tree function
//displays the tree by level.
node * tree::display_tree(node * root, int level)
{
	//Return 0 if off a leaf:
	if (!root) return NULL;

	//Display the left subtree:
	if (root->left)
	{
		//Print the level and term:
		cout<<'\n'<<"Level "<<level<<':'<<'\t';
		root->left->data.display_name();

		//If there are 2 children, print an 'and':
		if (root->right)
			cout<<" and ";
	}

	//Display the right subtree:
	if (root->right)
	{
		//If there is 1 child, announce the level:
		if (!root->left)
			cout<<'\n'<<"Level "<<level<<':'<<'\t';

		//Print the term:
		root->right->data.display_name();
		
	}

	cout<<'\n';

	//Traverse left:
	if (root->left)
		root->left = display_tree(root->left, 1 + level);

	//Traverse right:
	if (root->right)
		root->right = display_tree(root->right, 1 + level);

	return root;

}





// **************************** //
//    TERM MEMBER FUNCTIONS:	//
//    				//
// **************************** //

//The first constructor initializes
//the data members of the term to NULL.
term::term()
{
	name = NULL;
	topic = NULL;
	about = NULL;
	key = NULL;
}



//The second constructor initializes
//the data members of the term,
//given user input.
term::term
	(char * word, char * field, char * definition)
{
	//Copy name:
	name = new char[strlen(word) + 1];
	strcpy(name, word);

	//Copy topic:
	topic = new char[strlen(field) + 1];
	strcpy(topic, field);

	//Copy definition:
	about = new char[strlen(definition) + 1];
	strcpy(about, definition);

	//Take the topic name in caps
	//as the search/sort key:
	char temp[SIZE];
	strcpy(temp, word);
	for (int i = 0; i < strlen(word); ++i)
		temp[i] = toupper(temp[i]);

	//Copy search/sort key:
	key = new char[strlen(temp) + 1];
	strcpy(key, temp);
}



//The destructor deallocates
//dynamically allocated memory.
term::~term()
{
	//Deallocate data,
	//if they exist:
	if (name) delete [] name;
	name = NULL;
	if (topic) delete [] topic;
	topic = NULL;
	if (about) delete [] about;
	about = NULL;
	if (key) delete [] key;
	key = NULL;
}



//The display_term function displays
//the definition of a term.
void term::display_term()
{
	//Display name, (topic)
	//and definition:
	cout<<'\n'<<'\t'<<name;
	cout<<'\t'<<"(in topic "<<topic<<"):"<<endl;
	cout<<about<<'\n'<<endl;
}



//The display_name function
//displays just the term itself.
void term::display_name()
{
	//Yes this is the entire function:
	cout<<name;
}



//The copy_term function makes
//a deep copy of the term data.
//void term::copy_term(term & destination)
void term::copy_term(char * word, char * field, char * definition)
{
	//Copy name:
	if (name) delete name;
	name = new char[strlen(word) + 1];
	strcpy(name, word);

	//Copy topic:
	if (topic) delete topic;
	topic = new char[strlen(field) + 1];
	strcpy(topic, field);

	//Copy definition:
	if (about) delete about;
	about = new char[strlen(definition) + 1];
	strcpy(about, definition);
			
	//Define search key:
	char temp[SIZE];
	strcpy(temp, name);
	for (int i = 0; i < strlen(name); ++i)
		temp[i] = toupper(temp[i]);

	//Copy search key:
	if (key) delete key;
	key = new char[strlen(temp) + 1];
	strcpy(key, temp);
}



//The copy_term function
//makes a deep copy of
//an existing term object.
void term::copy_term(term & to_copy)
{
	//Copy term:
	if (name) delete name;
	name = new char[strlen(to_copy.name) + 1];
	strcpy(name, to_copy.name);
	
	//Copy topic:
	if (topic) delete topic;
	topic = new char[strlen(to_copy.topic) + 1];
	strcpy(topic, to_copy.topic);

	//Copy definition:
	if (about) delete about;
	about = new char[strlen(to_copy.about) + 1];
	strcpy(about, to_copy.about);

	//Copy search key:
	if (key) delete key;
	key = new char[strlen(to_copy.key) + 1];
	strcpy(key, to_copy.key);
}



//This compare_term function
//compares a word with
//the term's search key.
int term::compare_term(char * to_compare)
{
	//Copy the word:
	char temp[strlen(to_compare)];
	strcpy(temp, to_compare);

	//Convert the copy to caps:
	for (int i = 0; i < strlen(temp); ++i)
		temp[i] = toupper(temp[i]);

	//Compare the copy with the key:
	return strcmp(temp, key);
}



//This compare_term function
//compares the search keys
//of two distinct terms.
int term::compare_term(term & to_compare)
{
	return strcmp(to_compare.key, key);
}



//The write_term function saves
//the data to an external file.
void term::write_term()
{
	ofstream flout;		//File output stream variable

	//Open file:
	flout.open("program4_data.txt", ios::app);

	if (flout)
	{
		//Write the data:
		flout<<name<<'|'<<topic<<'|'<<about<<'|';
		flout<<'\n'<<'\n';

		//Close the file:
		flout.close();
	}
}





// **************************** //
//      UTILITY FUNCTIONS:	//
//    				//
// **************************** //

//The yn function returns the answer
//to a yes-or-no question.
bool yn()
{
	char response;		//User's response to a Y/N question

	do
	{
		//Get a one-character response
		//and convert it to caps:
		cin>>response;
		cin.ignore(100, '\n');
		response = toupper(response);

		//Ensure a valid response:
		if (response != 'Y' && response != 'N')
			cout<<'\n'<<"Looking for a Y or N here..."<<endl;

	} while (response != 'Y' && response != 'N');

	//Return true if "yes", false if "no":
	if (response == 'Y') return true;
	return false;
}


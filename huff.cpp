#include <fstream>
#include <string>
#include <iostream>
#include <queue>
#include <map>

using namespace std;


//Each node contains a character and a letter 
class Node{
public:
	Node(char ch, int freq) {
		left = right = nullptr;
		this->ch = ch;
		this->freq = freq;
	}
	Node* left;
	Node* right;
	int freq;
	char ch;
};

//The comparison declaration for the map
struct compare {
	bool operator()(Node* left, Node* right) {
		return(left->freq > right->freq);
	}
};


//print out the tree
void readIn(Node* root, string str)
{
	if (!root) {
		return;
	}

	//* never appears in the particular file being tested, this can be changed for various text files
	//this will print out the character being read and the place it lies in the tree
	if (root->ch != '*') {
		cout << root->ch << ": " << str << "\n";
	}

	//while the travesal of left is possible it will pring a 0, while right is possible it will print a 1
	readIn(root->left, str + "0");
	readIn(root->right, str + "1");
}



//reads in a "character map" which contains characters and their frequencies, and builds the code
void huffTree( map<char,int> &charMap) {
	//iterator for the map
	map <char, int>::iterator iter;

	class Node *left, *right, *top;
	//declaration of the priority queue, stores each node with the lowest frequency at the top
	priority_queue<Node*, vector<Node*>, compare> heap;
	for (iter = charMap.begin(); iter != charMap.end(); iter++) {
		heap.push(new Node(iter->first, iter->second));
	}

	while (heap.size() > 1) {
		left = heap.top();
		heap.pop();

		right = heap.top();
		heap.pop();

		//create a new node by combining the two nodes with the lowest frequencies from the heap, and then re-add that node
		top = new Node('%', left->freq + right->freq);
		top->left = left;
		top->right = right;
		heap.push(top);
	}
	 readIn(heap.top(), "");
}

void PressEnterToContinue()
{
	cout << "Press ENTER to continue... " << flush;
	cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}

int main() {
	string line;
	char ch;
	int length = 0;
	char charArr[20] = {};
	int lettCount[100] = { 0 };
	map <char, int> charFreq;
	map <char, int>::iterator iter;
	ifstream theRaven("C:/Users/randUser/Desktop/test.txt");

	
	if (theRaven.is_open()) {
		while (getline(theRaven,line)) {
			cout << line << endl;
			for (int i = 0; i < line.length(); ++i) {
				charFreq[line[i]]++;
			}
		}
	}
	

	for (iter = charFreq.begin(); iter != charFreq.end(); iter++) {
		cout << iter->first << " with frequency " << iter->second << endl;
	}

  huffTree(charFreq);

	PressEnterToContinue();
	return 0;
	
}
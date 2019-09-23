#include <iostream>
#include <fstream>
#include <string>
#define ARRAY_SIZE 8

using namespace std;


//strut to define each chunk
template <typename T>
struct ChunkNode
{
	T values[ARRAY_SIZE];

	int indiListLen;
	ChunkNode* next;
};

//chunklist class
template <typename T>
class ChunkList
{
private:
	ChunkNode<T>* head;
	ChunkNode<T>* tail;
	int wholeListLen;
	

public:

	//constructor for the class
	ChunkList();
	~ChunkList();
	int GetLength();// Get the total number of all the elements in the chunklist
	bool IsEmpty();//check if the whole list is empty.
	void Append(T elem);//Add the element to the end of the chunklist
	void Print();//Print all the elements in the chunklist from chunk to chunk;
	void Remove(T elem);//removes first instance of elem;
	T* GetIndex(int i);// get item at given index;
	T* Search(T elem);




};

template<typename T>
ChunkList<T>::ChunkList()
{
	head = NULL;
	tail = NULL;
	wholeListLen = 0;

}

template<typename T>
ChunkList<T>::~ChunkList()
{
	while (head != nullptr) {
		ChunkNode<T>* tmp = head;
		head = head->next;
		delete tmp;
	}
}

template<typename T>
int ChunkList<T>::GetLength()
{

	return wholeListLen;

}

template<typename T>
bool ChunkList<T>::IsEmpty()
{
	return head == NULL;
}

template<typename T>
void ChunkList<T>::Append(T elem)
{

	// If list is empty...
	if (IsEmpty()) {
		ChunkNode<T>* newChunkNode = new ChunkNode<T>;
		head = tail = newChunkNode;
		newChunkNode->indiListLen = 1;
		newChunkNode->values[newChunkNode->indiListLen - 1] = elem;
		newChunkNode->indiListLen++;
		wholeListLen++;

	}
	else if (tail->indiListLen < ARRAY_SIZE + 1)
	{
		tail->values[tail->indiListLen - 1] = elem;
		tail->indiListLen++;
		wholeListLen++;
	}
	else {
		ChunkNode<T>* newChunkNode = new ChunkNode<T>;

		newChunkNode->indiListLen = 1;
		newChunkNode->values[newChunkNode->indiListLen - 1] = elem;
		newChunkNode->next = nullptr;
		tail->next = newChunkNode;
		tail = newChunkNode;
		tail->indiListLen++;
		wholeListLen++;
	}

}

template<typename T>
void ChunkList<T>::Print()
{
	int Nb = 1;
	ChunkNode<T>* newChunkNode = new ChunkNode<T>;

	while (head != nullptr)
	{
		cout << "Chunk " << Nb << ": ";
		for (int i = 0; i < (head->indiListLen - 1); i++) {
			cout << head->values[i] << " ";
		}
		cout << endl;
		Nb++;
		head = head->next;


	}

}
template<typename T>
void ChunkList<T>::Remove(T elem)
{
	ChunkNode<T>* prevChunkNode = NULL;
	ChunkNode<T>* currChunkNode = head;
	while (currChunkNode != NULL)
	{
		for (int i = 0; i < (currChunkNode->indiListLen - 1); i++)
		{
			if (currChunkNode->values[i] == elem)
			{
				if (currChunkNode->indiListLen == 1 && currChunkNode->next == NULL)
				{
					head = tail = NULL;
					delete currChunkNode;
					currChunkNode->indiListLen--;
				
					
				}
				else if (currChunkNode->indiListLen == 1 && currChunkNode == tail)
				{
					tail = prevChunkNode;
					tail->next = NULL;
					delete currChunkNode;
					currChunkNode->indiListLen--;
				


				}
				else if (currChunkNode->indiListLen == 1 && currChunkNode->next != NULL)
				{
					currChunkNode->indiListLen--;
					head = currChunkNode->next;
					delete currChunkNode;
				
					

				}
				else
				{
					currChunkNode->values[i] = NULL;//set the value of the element to NULL;
					
					
				}


			}

			//prevChunkNode = currChunkNode;
			//currChunkNode = currChunkNode->next;
		}
		
		wholeListLen--;
		return;

	}

}

template<typename T>
T* ChunkList<T>::GetIndex(int i)
{
	ChunkNode<T>* currChunkNode = head;
	while (currChunkNode != NULL)
	{
		for (int j = 0; j < 8; j++) {
			if (j == i)
				return new T(currChunkNode->values[j]);

		}
		currChunkNode = currChunkNode->next;
	}
	return nullptr;
}

template<typename T>
T* ChunkList<T>::Search(T elem)
{
	ChunkNode<T>* currChunkNode = head;

	for (int i = 0; i < (currChunkNode->indiListLen-1); i++) {
		if (currChunkNode->values[i] == elem) {
			return new T(currChunkNode->values[i]);
		}
		currChunkNode = currChunkNode->next;
	}

	return nullptr;
}



int main()
{
	ChunkList<int> myList;
	ofstream outFile;
	ifstream inFile;

	outFile.open("output.txt");
	inFile.open("unit_test.txt");

	if (!inFile) {
		cout << "File not found!" << endl;
		exit(0);
	}

	string command;
	inFile >> command;
	while (command != "quit") {
		if (command == "append") {
			int num;
			inFile >> num;
			myList.Append(num);
			outFile << "Appending " << num << endl;
		}
		else if (command == "remove")
		{
			int num;
			inFile >> num;
			myList.Remove(num);
			outFile << "removing " << num << endl;
		}
		else if (command == "getindex") {
			int num;
			inFile >> num;	
			outFile << "Index " << num<<" is "<< *myList.GetIndex(num)<< endl;
		}
	
		
		else if (command == "print") {
			myList.Print();
			
			for (int i = 0; i < myList.GetLength(); i++) {
				int *val = myList.GetIndex(i);
				if (val != nullptr)
				{
					outFile << *val << " ";
					outFile << "\n";
				}


			}
				
		}
		else if (command == "search") {
			int num;
			inFile >> num;
			int *val = myList.Search(num);
			if (val == nullptr) {
				outFile << *val << " does not exist in list" << endl;
			}
			else {
				outFile << *val << " exists in list" << endl;
			}


		}
		else if (command == "getlength") {
			outFile << "Length: " << myList.GetLength() << endl;
		}
		inFile >> command;
	}
	outFile.close();
	inFile.close();


	myList.Append(11);
	myList.Append(12);
	myList.Append(13);
	myList.Append(14);
	myList.Append(15);
	myList.Append(16);
	myList.Append(17);
	myList.Append(18);
	myList.Append(19);
	myList.Append(20);
	myList.Append(21);
	myList.Append(22);
	myList.Append(23);
	myList.Append(24);
	myList.Append(25);
	myList.Append(26);
	//myList.Append(27);
	//myList.Append(28);
	myList.Remove(11);
	myList.Remove(18);
	myList.Remove(19);
	myList.Remove(25);

	myList.GetIndex(4);
	//myList.Search(22);


	myList.Print();
	cout << myList.GetLength();


	return 0;
}

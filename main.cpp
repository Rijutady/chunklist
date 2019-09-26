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
    int indiListLen = 0;
    ChunkNode<T>* next;
};

//chunklist class
template <typename T>
class ChunkList
{
private:
    ChunkNode<T>* head;
    ChunkNode<T>* tail;
    int chunkamount;
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
    int getSize()//extra point for check chunk amounts
    { return chunkamount;}
    int getIndilistlen()//extra point for check chunk amounts
    { return getIndilistlen();}
};

template<typename T>
ChunkList<T>::ChunkList()
{
    head = nullptr;
    tail = nullptr;
    wholeListLen = 0;
    chunkamount= 0;

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
{   return wholeListLen;}

template<typename T>
bool ChunkList<T>::IsEmpty()
{   return head == nullptr; }

template<typename T>
void ChunkList<T>::Append(T elem)
{
    // If list is empty...
    if (IsEmpty()) {
        ChunkNode<T>* newChunkNode = new ChunkNode<T>;
        
        head = tail = newChunkNode;
        chunkamount++;
        int index = newChunkNode->indiListLen;
        newChunkNode->values[index] = elem;
        newChunkNode->indiListLen++;
        wholeListLen++;
    }
    else if (tail->indiListLen < ARRAY_SIZE)
    {
        tail->values[tail->indiListLen] = elem;
        tail->indiListLen++;
        wholeListLen++;
    }
    else {
        ChunkNode<T>* newChunkNode = new ChunkNode<T>;
        int index = newChunkNode->indiListLen;
        newChunkNode->values[index] = elem;
        newChunkNode->indiListLen++;
        newChunkNode->next = nullptr;
        
        tail->next = newChunkNode;
        tail = newChunkNode;

        chunkamount++;
        wholeListLen++;
    }

}

template<typename T>
void ChunkList<T>::Print()
{
    int Nb = 1;
    ChunkNode<T>* ptr = head;

    while (ptr != nullptr)
    {
        cout << "Chunk " << Nb << ": ";
        for (int i = 0; i < (ptr->indiListLen); i++) {
            cout << ptr->values[i] << " ";
        }
        cout << endl;
        Nb++;
        ptr = ptr->next;
    }

}
template<typename T>
void ChunkList<T>::Remove(T elem)
{
    ChunkNode<T>* prevChunkNode = head;
    ChunkNode<T>* currChunkNode = head;
    for (int i=0; i<chunkamount; i++) {
        
        for (int j = 0; j<currChunkNode->indiListLen; j++) {
            if (currChunkNode->values[j]==elem) {
                
                
                if (j == currChunkNode->indiListLen-1) {
                    currChunkNode->indiListLen--;
                    wholeListLen--;
                }
                else{
                    for (int h=j; h < currChunkNode->indiListLen; h++) {
                        currChunkNode->values[h]=currChunkNode->values[h+1];
                    }
                    currChunkNode->indiListLen--;
                    wholeListLen--;
                }
                
                if (currChunkNode->indiListLen == 0) {
                    prevChunkNode->next=currChunkNode->next;
                    chunkamount--;
                    if (currChunkNode==head) {
                        head=currChunkNode->next;
                    
                    }
                    else if (currChunkNode==tail)
                    {   tail=prevChunkNode;
                        tail->next=nullptr;
                        
                    }
                    delete currChunkNode;
                    
                }
                return;
            }
        }
        
        
        prevChunkNode=currChunkNode;
        currChunkNode=currChunkNode->next;
    }
  }

template<typename T>
T* ChunkList<T>::GetIndex(int i)
{
    if(!IsEmpty()){
    ChunkNode<T>* currChunkNode = head;
  
    for (int c=0; c<chunkamount; c++) {
        if(i < (currChunkNode->indiListLen))
            return new T(currChunkNode->values[i]);
        i = i-(currChunkNode->indiListLen);
        currChunkNode = currChunkNode->next;
        
    }
    return nullptr;
    }
    else
        return nullptr;
}

template<typename T>
T* ChunkList<T>::Search(T elem)
{
    ChunkNode<T>* currChunkNode = head;
for (int c=0; c<chunkamount; c++) {
    for (int i = 0; i < currChunkNode->indiListLen; i++)
    {
        if (currChunkNode->values[i] == elem) {
            return new T(currChunkNode->values[i]);
        }
        
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
            int *val = myList.GetIndex(num);
            if (val != nullptr){
                outFile << "Index " << num<<" is "<< *val<< endl;
            }
            
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
    myList.Append(27);
    myList.Append(28);
    //myList.getSize();
    myList.Remove(11);
    //cout << myList.getSize()<< endl;
    myList.Remove(18);
    //cout << myList.getSize()<< endl;
    myList.Remove(19);
    //cout << myList.getSize()<< endl;
    myList.Remove(25);
    cout << myList.getSize()<< endl;
    cout << myList.GetLength()<< endl;

    myList.Print();
    
    cout<<*(myList.GetIndex(13))<<endl;
    cout<<*(myList.Search(26))<<endl;
    //myList.Search(22);

    cout << myList.GetLength();

    return 0;
}


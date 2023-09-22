// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Mahdi Beigahmadi>
// St.# : <301570853>
// Email: <mba188@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Wordlist : public Wordlist_base
{
    
    public:
    // Use this Node to implement the doubly-linked list for the word list.
    // Don't change it any way!
    //
    struct Node
    {
        string word;
        Node *next;
        Node *prev;
    };
   
   unsigned int counter = 0;

   Node *tailDLinkedList;

   Node *headDLinkedList = nullptr;
   
   bool freezeVar = false;

   Wordlist();

   Wordlist(const Wordlist& other);
    
   Wordlist(const string& filename);

   ~Wordlist();
  
   bool is_frozen() const override;

   bool contains(const string &w) const override;
 
   int length() const override;

   string get_word(int index) const override;

   void add_word(const string &w) override;

   void remove_word(const string &w) override;

   vector<string *> get_sorted_index() override;

   void freezeTheList() {
    freezeVar = true;
   }

   void unFreezeTheList() {
    freezeVar = false;
   }

}; 

Wordlist::Wordlist() {
    headDLinkedList = nullptr;
    tailDLinkedList = nullptr;
    counter = 0;
}

Wordlist::Wordlist(const Wordlist& other) {
 Node* currentPointer = other.headDLinkedList;
        while(currentPointer != nullptr) {
            this->add_word(currentPointer->word);
            currentPointer = currentPointer->next;
       }
}

// Source: chatGPT, my code did not read the first line of the txt file it skipped to the next line, I could fix it by one STL which is called #inlclude <sstream>. but Toby did not accept from me to add this header into the code
Wordlist::Wordlist(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error loading the file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t start = 0;
        size_t end = line.find(' ');

        while (end != string::npos) {
            string word = line.substr(start, end - start);
            if (!word.empty()) {
                add_word(word);
            }

            start = end + 1;
            end = line.find(' ', start);
        }

        
        string lastWord = line.substr(start);
        if (!lastWord.empty()) {
            add_word(lastWord);
        }
    }

    file.close();
}


Wordlist::~Wordlist() {
Node* current = headDLinkedList;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    headDLinkedList = nullptr;
    tailDLinkedList = nullptr;
}

bool Wordlist::is_frozen() const {
   return freezeVar;
}

void Wordlist::add_word(const string &w) { //inspired from textbook (Data Structures & Algorithms. Mount, Goodrich and Tamassia)
if (is_frozen()) {
    throw runtime_error("The list is frozen");
}
 else if (!is_frozen()) {
        Node* temp = new Node;
        temp->word = w;
        temp->next = nullptr;

        bool searchTarget = false;
        Node* current = headDLinkedList;
        while (current != nullptr) {
            if (current->word == w) {
                searchTarget = true;
                delete temp;
                break;
            }
            current = current->next;
        }

        if (!searchTarget) {
            temp->prev = tailDLinkedList;
            if (tailDLinkedList != nullptr) {
                tailDLinkedList->next = temp;
            }
            else {
                headDLinkedList = temp; 
            }
            tailDLinkedList = temp;
            counter++;
        }
    }
}

int Wordlist::length() const {
  return this->counter;
}

bool Wordlist::contains(const string &w) const {
    
    Node* current = headDLinkedList;
    while (current != nullptr) {
        if (current->word == w) {
            return true;
        }
        current = current->next;
    }
    
 return false;
}

   
void Wordlist::remove_word(const string &w) { //inspired from geeksforgeeks website, https://www.geeksforgeeks.org/remove-duplicates-unsorted-doubly-linked-list/
  if (is_frozen()) {
    throw runtime_error("The list is frozen\a");
  }
  else if (!is_frozen()) {
    Node* temp = headDLinkedList;
        while (temp) {
            if (temp->word == w) {
                if (temp->prev) {
                    temp->prev->next = temp->next;
                } else {
                    headDLinkedList = temp->next;
                }

                if (temp->next) {
                    temp->next->prev = temp->prev;
                } else {
                    tailDLinkedList = temp->prev;
                }

                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
                counter--;
              
            } else {
                temp = temp->next;
            }
        }
  }
  
}


string Wordlist::get_word(int index) const {
 if(index < 0 || index >= length()) {
        throw out_of_range("Index out of bounds");
    }

    unsigned int helperIndex = 1;
    Node* current = headDLinkedList;
    while (current != nullptr) {
        if (index == 0) {
            return current->word;
            break;
        }
        else if (index == helperIndex ) {
            return current->word;
        }
        helperIndex++;
        current = current->next;
    }

    throw runtime_error("Unexpected error");
}
  
vector<string*> Wordlist::get_sorted_index() {
      freezeTheList();

    bool doneOperation = false;
    vector<string*> pointerToEachWord;
    Node* helperPointer = headDLinkedList;

    while (helperPointer != nullptr) {
        pointerToEachWord.push_back(&helperPointer->word);
        helperPointer = helperPointer->next;
        doneOperation = true;
    }
    sort(pointerToEachWord.begin(), pointerToEachWord.end(), [](const string* firstElement, const string* secondElement) { return *firstElement < *secondElement; });

    if (doneOperation) {
        return pointerToEachWord;
    }
    else { 
        exit(0);
    }
}
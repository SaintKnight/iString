#include <iostream>
#include <cstring>
#include <locale>
#include "istring.h"

using namespace std;

/*********** iString() ***********
  Purpose: Constructor of Class iString
           using member initialization list to initialize all
           fields to zero(pointer to NULL).
  Return: this
************************************/
iString::iString():chars(NULL),length(0),capacity(0) {}


/*********** iString(const iString &other) ***********
  Purpose: Copy constructor of Class iString
           using member initialization list to initialize all
           fields(except the array char) to the corresponding Class iString other's fields.
           deep copy the array chars to other.chars
  return: this
************************************/
iString::iString(const iString &other):length(other.length),capacity(other.capacity){
	if(other.chars != NULL){					 						 // is other.chars NULL?
		chars = new char[other.length];
		for(int i = 0; i < other.length; i++){	 		 // copy content of array
			chars[i] = other.chars[i];
		} // for
	} else {
		chars = NULL;
	} // if
} //iString(other)


/*********** iString(const char &a) ***********
  Purpose: A method of Class iString
           copy an array of char to iString
  return: this
************************************/
iString::iString(const char *a){
	if(a == NULL){								 								 // is array a NULL?
		chars = NULL;
		length = 0;
		capacity = 0;
	} else {
		length = strlen(a);
		chars = new char[length];
		for(int i = 0; i < length; i++){		 				 // copy content of array
			chars[i] = a[i];
		} // for
		capacity = length;
	} // if
} // iString(a)


/*********** operator= ***********
  Purpose: overload assignment operator
           assign an iString to another iString
  return *this.
************************************/
iString &iString::operator=(const iString &other) {
	if(this == &other){							 							 // are this and other already the same?
		return *this;
	} else if(other.chars != NULL){				 				 // is other.chars NULL?
		delete [] chars;						 								 // free previous memory of chars
		chars = new char[other.length];
		for(int i = 0; i < other.length; i++){   		 // a loop to assign contents of chars
			chars[i] = other.chars[i];
		} // for
	} else {
		chars = NULL;
	} // if
	length = other.length;						 						 // assign length
	capacity = other.capacity;					 					 // assign capacity
	return *this;
} // operator=


/*********** ~iString ***********
  Purpose: Destructor of Class iString
           free the memory of chars
************************************/
iString::~iString(){ 
	delete [] chars; 
} // ~iString


/*********** operator+ ***********
  Purpose: overload + operator
           append two iStrings
  return iString
************************************/
iString operator+(const iString &s1, const iString &s2){
	iString s = iString();						 // call constructor
	s.chars = new char[s1.length + s2.length];	 	 // allocate new memory to s

	// A loop to store s1 content in s first
	for(int i = 0; i < s1.length; i++){
		s.chars[i] = s1.chars[i];
	} //for

	// A loop to store s2 content in s second
	for(int i = s1.length; i < s1.length + s2.length; i++){
		s.chars[i] = s2.chars[i - s1.length];
	} // for
	s.length = s1.length + s2.length;			 				 // update length of s
	s.capacity = s1.length + s2.length;			 			 // update capacity of s
	return s;
} // operator+

/*********** operator+ ***********
  Purpose: overload + operator
           append an iString and an array of char
  return iString
************************************/
iString operator+(const iString &s1, char *s2){
	iString s = iString();						 						 // call constructor
	int l = strlen(s2);
	s.chars = new char[s1.length + l];

	// A loop to store s1 content in s first
	for(int i = 0; i < s1.length; i++){
		s.chars[i] = s1.chars[i];
	} // for

	// A loop to store array s2 content in s second
	for(int i = s1.length; i < s1.length + l; i++){
		s.chars[i] = s2[i - s1.length];
	} // for
	s.length = s1.length + l;					 						 // update length of s
	s.capacity = s1.length + l;					 					 // update capacity of s
	return s;
}


/*********** operator/ ***********
  Purpose: overload / operator
  		   find iString
  returns the starting index where s2 appears
  within s1. Prints -1 if s1 not found in s1
  ************************************/
int operator/(const iString &s1, const iString &s2){
	if((s1.length == 0)||(s2.length == 0)||(s1.length < s2.length)){ // imposible cases?
		return -1;
	} else {

		// A loop to look up every possible starting index of s1
		for(int i = 0; i < s1.length - s2.length + 1; i++){
			int same = 100;
			char *temp = new char[s2.length];

			// A loop to set a temp array cutting the s1 with length of s2 at certain starting index
			for(int j = i; j < i + s2.length; j++){
				temp[j-i] = s1.chars[j];
			}

			// A loop to compare s2 and temp
			for(int k = 0; k < s2.length; k++){
				if(temp[k] != s2.chars[k]){
					same = -1;
				}
			}

			if(same == 100){					 								 // s2 and temp same?
				delete [] temp;					 								 // free temp
				return i;																 // find return index
			}
			delete [] temp;														 // not same free temp
		}
		return -1;																	 // not find return -1
	}
}


/*********** operator% ***********
  Purpose: overload % operator
           append an iString and an array of char
  return iString
************************************/
iString operator%(const iString &s2, const int i){
	iString s1 = iString();												 // call constructor
	if((s2.length == 0)||(i >= s2.length)) {			 // possible cases
		return s1;
	} else {
		s1.chars = new char[s2.length - i];

		// A loop to set s1 with cutting s2 starting at index i with the length of s2
		for(int j = i; j < s2.length; j++){
			s1.chars[j - i] = s2.chars[j];
		} // for
		s1.length = s2.length - i;									// update length of s1
		s1.capacity = s2.capacity - i;							// update length of s2
	}
	return s1;
}


/*********** operator>> ***********
  Purpose: overload input operator
           input iString
  return in
************************************/
istream &operator>>(istream &in, iString &s){
	s.capacity = 1;
	s.chars = new char[s.capacity];
	in >> s.chars[0];
	(s.length)++;

	// A loop to check whether the next of cin is a whitespace.
	while(!isspace(cin.peek())){
		if(s.length == s.capacity){									 // is length = capacity?
			s.capacity = s.capacity * 2;							 // update capacity
			char *c = new char[s.length];

			// A loop to temporary store current content
			for(int i = 0; i < s.length; i++){
				c[i] = s.chars[i];
			} // if
			delete [] s.chars;												 // free previous memory
			s.chars = NULL;
			s.chars = new char[s.capacity];						 // allocate updated capacity

			// A loop to store previous content from temp array
			for(int i = 0; i < s.length; i++){
				s.chars[i] = c[i];
			} // for
			delete [] c;															 // delete temp array
			c = NULL;
		} // if
		in >> s.chars[s.length];
		(s.length)++;																 // update length
	} // while
	return in;
}


/*********** operator<< ***********
  Purpose: overload output operator
           append an iString and an array of char
  return out
************************************/
ostream &operator<<(ostream &out, const iString &s){
	if(s.chars != NULL){													 // is s.chars NULL?

		// A loop to output every element of the array s.chars
		for(int i = 0; i < s.length; i++) {
			out << s.chars[i];
		} // for
	} // if 
	return out;
}



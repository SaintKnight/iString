#include "istring.h"
#include <iostream>
#include <string>
using namespace std;

/* NOTES
   Commands are given in a regex style, e.g. saba, p a 3, f a, etc
   Copy Constructor needs to work before operator/, operator%, and operator+ can be tested
   
   Note on commands: Spaces are not necessary but are used here for readability
   Command descriptions:
   s destination source1 source2 // operator+
   t destination source1 string // operator+
   r destination string // operator >>, read a string into an iString object
   / source1 source2 // operator/
   % destination source1 int // operator%
   n destination string // iString(char*) - create an iString object with given string as contents
   i destination source // copy constructor - copy an existing iString object (like strdup)
   = destination source // assignment operator - copy an existing iString object
   f destination // default constructor - create empty iString (basically, empty string)
   e source // delete source/call destructor - cleans up memory
   w source // print the contents of iString
   l source // print length of iString
   q exits the program - does not free memory
*/
int main() {  
  bool done = false;
  string temp;
  iString *a[4] = {0,0,0,0};
  while(!done) {
    char c;
    char which;
    char op1;
    char op2;
    int int_op;
    cerr << "Command?" << endl;  // Valid commands:  
                                 //                  r [a-d] string
                                 //                  w [a-d]
                                 //                  q
                                 //                  s [a-d][a-d][a-d]
                                 //                  t [a-d] [a-d] string
                                 //                  / [a-d] [a-d]
	         		                   //                  % [a-d] [a-d] int
                                 //                  n [a-d] string
                                 //                  i [a-d] [a-d]
                                 //                  = [a-d] [a-d]
                                 //                  f [a-d] 
                                 //                  e [a-d]
                                 //                  l [a-d]
    cin >> c;  // Reads r, s, t, /, %, w, n, i, e, f, l, =, q
    if (cin.eof()) break;
    switch(c) {
      case 'r':
	{
        cin >> which;  // Reads a, b, c, or d
        delete a[which-'a'];
        a[which-'a'] = new iString;
        cin >> *(a[which-'a']);
        break;
	}
      case 'w':
	{
        cin >> which;  // Reads a, b, c, or d
        cout << *(a[which-'a']) << endl;
        break;
	}
      case 'n':
	{
        cin >> which >> temp;
        delete a[which-'a'];
        a[which-'a'] = new iString(temp.c_str());
        break;
	}
      case 'i':
	{
        cin >> op1 >> op2;
        iString *tmp = new iString(*(a[op2-'a']));
        delete a[op1-'a'];
        a[op1-'a'] = tmp;
        break;
	}
      case '=':
	{
        cin >> op1 >> op2;
        *a[op1-'a'] = *a[op2-'a'];
        break;
	}
      case 's':
	{
        cin >> which >> op1 >> op2;
        iString *tmp = new iString(*(a[op1-'a']) + *(a[op2-'a']));
        delete a[which-'a'];
        a[which-'a'] = tmp;
        break;
	}
      case 't':
	{
        cin >> which >> op1 >> temp;
        iString *tmp = new iString(*(a[op1-'a']) + temp.c_str());
        delete a[which-'a'];
        a[which-'a'] = tmp;
        break;
	}
	case '/':
	{
         cin >> op1 >> op2;  
	cout << *a[op1-'a'] / *a[op2-'a'] << endl;
         break;
	}
	case '%':
	{
	cin >> which >> op1;
         cin >> int_op; //must be int, otherwise behaviour undefined
	iString *tmp = new iString(*(a[op1-'a']) % int_op);
	delete a[which-'a'];
	a[which-'a'] = tmp;
	break;
	}
	case 'e':
	{
        cin >> which;
        delete a[which-'a'];
        a[which-'a'] = 0;
        break;
	}
      case 'f':
	{
        cin >> which;
        delete a[which-'a'];
        a[which-'a'] = new iString();
        break;
	}
      case 'l':
	{
        cin >> which;
        cout << a[which-'a']->length << endl;
        break;
	}
      case 'q':
	{
        done = true;
	}
    }
  }
}

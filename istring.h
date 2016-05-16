#ifndef __ISTRING_H__
#define __ISTRING_H__
#include <iostream>
#include <cstring>
#include <locale>

struct iString{
  // array of chars to represent string
  char * chars;
  // actrual length of the array
  unsigned int length;
  // capacity of the array
  unsigned int capacity;
  // constructor of iString
  iString();
  // copy an array of char to iString
  iString(const char *a);
  // copy constructor of iString
  iString(const iString &a);
  // overload assignment operator
  iString &operator=(const iString &other);
  // destructor
  ~iString();
};

// overload input operator
std::istream &operator>>(std::istream &in, iString &s);

// overload output operator
std::ostream &operator<<(std::ostream &out, const iString &s);

// overload + operator
iString operator+(const iString &s1, const iString &s2);

// overload + operator
iString operator+(const iString &s1, char *s2);

// overload / operator
int operator/(const iString &s1, const iString &s2);

// overload % operator
iString operator%(const iString &s2, const int i);

#endif

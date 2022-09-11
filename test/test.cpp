#include <iostream>

struct A {
  int a;
  uint ua;
  float b;
  double db;
  char cc;
  bool isBool;
  std::string s;
  void funA(int x) { a = x; }
  void funB(const std::string &x) { s = x; }
};

/**
 * @meta-ignore-struct;
 * whole struct gets ignored
 */
struct B {
  int a;
  float b;
};

/**
 * @meta-ignore-members: b,c;
 * only specified members get ignored
 */
struct C {
  int a;
  // ignored
  float b;
  // ignored
  float c;
  // not ignored
  float d;

  B bB;
  A *pA;

  int alpha() { return 0; };

  void beta() { ; };
  int gamma(int a, int b, int c) { return a * b + c; };
};

void something(int a, bool b, std::string c) { std::cout << "print" << a << ", " << b << std::endl; }

bool something_else(int a, bool b, std::string c) { return true; }

int main() { std::cout << "hello" << std::endl; }
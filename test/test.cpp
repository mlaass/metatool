#include <iostream>

struct A {
  int a;
  uint ua;
  float b;
  double db;
  char cc;
  bool isBool;
  std::string s;
  void fun(int x) { ; }
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
  int dup(int a) { return a * 2; };
};

void something(int a, int b) {
  std::cout << "print" << a << ", " << b << std::endl;
}

int main() { std::cout << "hello" << std::endl; }
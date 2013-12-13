#include "pseudorandom.h"
#include <assert.h>
#include <iostream>

#define DEBUG false

PseudoRandom::PseudoRandom() {
  this->a = 48271;
  this->c = 0;
  this->m = 2147483647;
  this->rand = 1;
}

PseudoRandom::PseudoRandom(int seed) {
  this->a = 48271;
  this->c = 0;
  this->m = 2147483647;
  this->rand = seed;
}

PseudoRandom::PseudoRandom(int seed, int a0, int c0, int m0) {
  this->a = a0;
  this->c = c0;
  this->m = m0;
  this->rand = seed;
}

int PseudoRandom::pseudorand() {
  rand = (rand * a) % m;
  rand = (rand + c) % m;
  if (DEBUG) {std::cout << "pseudorand a : " << a << std::endl;}
  if (DEBUG) {std::cout << "pseudorand c : " << c << std::endl;}
  if (DEBUG) {std::cout << "pseudorand m : " << m << std::endl;}
  if (DEBUG) {std::cout << "pseudorand : " << rand << std::endl;}
  // Regarder préciser la spec de %
  if(rand<0){
    rand = rand + m;
  }
  assert(rand<m);
  assert(rand>=0);
  return rand;
}

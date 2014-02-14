#ifndef PSEUDORANDOM
#define PSEUDORANDOM

/**
 * @brief It's a generator of pseudo random numbers
 * It makes a sequence of the form: u_(n+1) = a * u_n + c mod m
 * @author: ChatanW
 */
class PseudoRandom {

 private:
  /**
   * the multiplier of the generator
   */
  int a;
  /**
   * the increment of the generator
   */
  int c;
  /**
   * the modulus of the generator
   */
  int m;
  /**
   * the current term of the generator
   */
  int rand;

 public:
  /**
   * @brief create the generator with default parameters and initialize it to 1
   * The default parameters are the parameters of minstd_rand
   */
  PseudoRandom();

  /**
   * @brief create the generator with default parameters and initialize it with the seed
   * The default parameters are the parameters of minstd_rand
   * @param seed : initialize the generator
   */
  PseudoRandom(int seed);

  /**
   * @brief create the generator with given parameters
   * @param seed : initialize the generator
   * @param a0 : the multiplier of the generator
   * @param c0 : the increment of the generator
   * @param m0 : the modulus of the generator
   */
  PseudoRandom(int seed, int a0, int c0, int m0);

  /**
   * @brief give the next term of the sequence
   * @return the term of the sequence, used like a random number
   */
  int pseudorand();

}
;

#endif 

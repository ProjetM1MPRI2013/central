#ifndef CSCENARIOI_H
#define CSCENARIOI_H
include "action.h";	
/**
 * @brief The cscenario class
 * Used by UI 
 */

class Cscenarioi {
 
 public :
  /**
   * @brief isPossible 
   * @param a : a reference to the action . 
   * Called by the UI answer 0 if he can do this action, and  an other int if he can't (which can explains why he can't)
   */
  static int isPossible (Action& a) {}
 /**
   * @brief apply
   * @param a : a reference to the action . 
   * Apply an action (sending the changes to the local state)
   */
  static void applyAction (Action& a ) {}
    };


#endif

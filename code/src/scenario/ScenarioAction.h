#IFNDEF SCENARIOACTION_H
#DEFINE SCENARIOACION_H


/**
 * All the elementary actions that the scenario can use. Each action implements a method run that performed an action.
 */

/**
 * @brief An elementary action.
 * Implement a method run to performed the action.
 */
class ScenarioAction {
 public :
  Simulation simulation;

  /**
   * @brief The time at when the action was performed.
   */
  long date;

  /**
   * @brief This method performed the action.
   */
  static void run () ;
} ;


/**
 * @brief The player changes of direction.
 */
class changeDirection: public ScenarioAction {
  PlayerID id;
  /**
   * The new direction of the player.
   * 0 stop, 1 up, 2 right, 3 down, 4 left 
   */
  int newMovement;
} ;


/**
 * @brief Create a new explosion.
 */
class explosion: public ScenarioAction {
  /**
   * The location of the explosion
   */
  Tile location;

  /**
   * The power of the explosion
   */
  int power;
} ;

/**
 * @brief Kill a NPC.
 */
class killNPC: public ScenarioAction {
  NPC* target;
} ;

class addObject: public ScenarioAction {
  Object* object;
  Position position;

  /**
   * Is the object visible to Terrorist (0 no, 1 yes)
   */
  int isVisibleT;

  /**
   * Is the object visible to PC (0 no, 1 yes)
   */
  int isVisiblePC ;
} ;

class removeObject: public ScenarioAction {
  Object* object;
}
#ENDIF

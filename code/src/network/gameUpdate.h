#ifndef GAMEUPDATE_H
#define GAMEUPDATE_H

#include <string>
#include <vector>
#include "abstractMessage.h"
#include "npcUpdate.h"
#include "playerUpdate.h"

/**
 * @brief The GameUpdate class
 * Will contain informations to transmit to the clients
 * Will be created from the GameState.
 */

class GameUpdate : public AbstractMessage{
public:
    static std::string getMsgType(){
      return "GameUpdt" ;
    }

    static GameUpdate& fromString(std::string& data) ;

    std::string toString() {
      return "" ;
    }
    GameUpdate * copy() ;

    /**
     * @brief GameUpdate :
     * creates a new GameUpdate. Initially all fields are empty.
     * Data that must be sent with this update are added through the
     * UpdateGenerator class.
     */
    GameUpdate();

    /**
     * Default destructor
     */
    ~GameUpdate() ;

    /**
     * @brief setPlayerUpdate
     * @param playerUpdate
     * Sets the player update associated to this GameUpdate
     */
    void setPlayerUpdate(const PlayerUpdate& playerUpdate) ;

    /**
     * @brief getPlayerUpdate : returns the player update associated to this message
     * @return
     */
    PlayerUpdate& getPlayerUpdate() ;

    /**
     * @brief addNpcUpdate : adds a NPC Update to this update.
     * @param npcUpdate : the NpcUpdate to add.
     */
    void addNpcUpdate(const NpcUpdate& npcUpdate) ;

    /**
     * @brief getNpcUpdates
     * @return all the NPC updates in the message
     */
    std::vector<NpcUpdate> getNpcUpdates() ;

private :
    PlayerUpdate p_update ;
    std::vector<NpcUpdate> npc_updates ;
};

#endif // GAMEUPDATE_H

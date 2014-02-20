/**
   @author: Remy
 */


#ifndef PREHUD_H
#define PREHUD_H

enum WaitFor {
	WF_NONE, WF_CLICK, WF_STUFF, WF_PICK, WF_ERROR
};

class PreHud {
public:
	virtual void setwf(WaitFor w) = 0;
  virtual void newMessage(std::string message) = 0;
  virtual void deleteMessage() = 0;

};

#endif

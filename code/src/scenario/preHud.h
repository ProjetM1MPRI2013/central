#ifndef PREHUD_H
#define PREHUD_H

enum WaitFor {
	WF_NONE, WF_CLICK
};

class PreHud {
public:
	virtual void setwf(WaitFor w) = 0;
};

#endif

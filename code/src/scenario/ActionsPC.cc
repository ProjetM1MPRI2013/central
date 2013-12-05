#include "ActionsPC.h"
#include "../simulation/simulation.h"

//AddCop :: AddCop (int number, Positon* positon) : Action"AddCop"

bool :: AddCop::IsActionPossible() {return (COST_COP2 <= (*simulation).getSous());};
bool :: AddCam::IsActionPossible() {return (COST_CAM2 <= (*simulation).getSous());};



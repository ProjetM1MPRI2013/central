/**
 * @author: MrKuluW
 */

#ifndef FOG_DISABLER
#define FOG_DISABLER

class FogDisabler{

 private:
  int radius;
  bool active;
  
 public:
  FogDisabler();
  FogDisabler(int rad, bool active_init);
  void setActive(bool act);
  void setRadius(int rad);
  bool getActive();
  int getRadius();
};


#endif

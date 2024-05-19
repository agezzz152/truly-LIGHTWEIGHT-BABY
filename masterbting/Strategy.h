#ifdef __STRATEGY__
#define __STRATEGY__
#include "motors.h"

#define OurGoal 0 //0 Is Blue. 1 Is yellow
#define EnemyGoal 1



class Strategy {
private: 
  motors driver;
public:   
  void Strategy();
  void Retreat();
  void Attack();
  void Detect();
};
#endif
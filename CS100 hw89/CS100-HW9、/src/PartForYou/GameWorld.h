#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__
using namespace std;
#include <list>

#include "WorldBase.h"
//#include "GameObjects.h"
class GameObject;
class Dawnbreaker;
class Star;
class Alphatron;
class Sigmatron;
class Omegatron;

enum class Fly{NONE,DOWN,RIGHT_DOWN,LEFT_DOWN};



class GameWorld : public WorldBase {
public:
	GameWorld();                                                                   //我不该在.cpp的文件中的init函数new Dawnbreaker,明天再改一下
  virtual ~GameWorld();   //只有GameWorld才能访问和储存这些变量

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

  void AddObject(GameObject* object);

  Dawnbreaker* GetDawnbreaker();
  
  int GetLifeNum();
  int GetEnemyOnscreen();

  list<GameObject*> m_game_object;

private:
	 //存放游戏对象的list    //不能让外界直接访问到，参考小提示的最后一条
	int m_life_number; //游戏开始时，会有三条生命值！并非关卡开始时  若在一个关卡中失败会少一条生命值，然后重开关卡。失去最后一条生命，游戏结束							 //一些游戏数据储存在了GameWorld的基类WorldBase中，例如：当前关卡、游戏分数 且WorldBase中有访问与修改函数，可以获取这些信息
	Dawnbreaker* m_real_dawnbreaker;						 //会需要用到WorldBase中的一些方法
	int m_enemies_onscreen;	

	
};

#endif // !GAMEWORLD_H__

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
	GameWorld();                                                                   //�Ҳ�����.cpp���ļ��е�init����new Dawnbreaker,�����ٸ�һ��
  virtual ~GameWorld();   //ֻ��GameWorld���ܷ��ʺʹ�����Щ����

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
	 //�����Ϸ�����list    //���������ֱ�ӷ��ʵ����ο�С��ʾ�����һ��
	int m_life_number; //��Ϸ��ʼʱ��������������ֵ�����ǹؿ���ʼʱ  ����һ���ؿ���ʧ�ܻ���һ������ֵ��Ȼ���ؿ��ؿ���ʧȥ���һ����������Ϸ����							 //һЩ��Ϸ���ݴ�������GameWorld�Ļ���WorldBase�У����磺��ǰ�ؿ�����Ϸ���� ��WorldBase���з������޸ĺ��������Ի�ȡ��Щ��Ϣ
	Dawnbreaker* m_real_dawnbreaker;						 //����Ҫ�õ�WorldBase�е�һЩ����
	int m_enemies_onscreen;	

	
};

#endif // !GAMEWORLD_H__

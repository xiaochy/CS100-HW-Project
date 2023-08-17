#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__
#include "GameWorld.h"
#include "ObjectBase.h"
#include "math.h"
using namespace std;


class GameObject : public ObjectBase {//如果GameObject是一个抽象类，无法在构造时知道自己五个属性的值
public:                   //可以将无法确定的部分放在抽象类的构造函数里，继续向下传给具体的子类，使用初始化列表
	GameObject(int imageID, int x, int y, int direction, int layer, double size, bool a,int hp,int hurt);
	virtual void Update() override;
	bool Get_is_dead() const;
	void Set_is_dead(bool a);
	int GetHp()const;
	void SetHp(int hp);
	int GetHurt() const;
	void SetHurt(int hurt);
	//virtual bool IsEnemy();
	
private:
	bool m_is_dead;
	int m_HP;
	int m_hurt;

};

/// //////////////////////////////////////////

class Dawnbreaker : public GameObject {
public:
	Dawnbreaker(GameWorld* ptr);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	int GetEnergy()const;
	void SetEnergy(int energy);
	GameWorld* GetPtr()const;
	int GetPowerGoodie() const;
	void SetPowerGoodie(int count);
	int GetMeteorGoodie() const;
	void SetMeteorGoodie(int count);
	int GetHasdestroyed() const;
	void SetHasdestroyed(int count);
private:
	int m_energy;
	GameWorld* m_ptr;  
	int m_has_destroyed_enermies;
	int m_Power_Goodie;
	int m_Meteor_Goodie;
};

 /////////////////////////////////

class Star : public GameObject {
public:
	Star(int y);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
};


 //////////////////////////////

class Blue_bullet : public GameObject {
public:
	Blue_bullet(int x, int y, double size, int hurt,Dawnbreaker* ptr);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	bool Check_collapse();
	Dawnbreaker* Get_Dawn_Ptr() const;
private:
	Dawnbreaker* m_dawn_ptr;
};

 ///////////////////////////////////////

class Red_bullet : public GameObject {
public:
	Red_bullet(int x,int y,int direction,int hurt, GameWorld* ptr);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	bool Check_collapse();
	GameWorld* Get_World_Ptr() const;
private:
	GameWorld* m_world_ptr;
};

 ///////////////////////////////////////////////////////////////////////

class Enemy : public GameObject {
public:
	Enemy(int image_ID,int x,int y,int hp,int aggressivity,int velocity,int energy, int direction, int layer, double size,GameWorld* ptr,Fly fly_way,int hurt);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	int GetAggress() const;
	int GetVelocity() const;
	int GetEnergy() const;
	int GetFlytime() const;
	Fly GetFlyway() const;
	void SetAggress(int aggress);
	void SetVelocity(int velocity);
	void SetEnergy(int energy);
	void SetFlytime(int time);
	void SetFlyway(Fly direct);
	void decide_dead();
	bool Check_collapse();
	virtual void attack();
	void Fly_generate();
	void Fly_move();
	virtual void Be_destroyed();


	GameWorld* Get_World_Ptr() const;
private:
	int m_aggressivity;
	int m_velocity;
	int m_energy;
	int m_fly_time;
	Fly m_fly_way;
	GameWorld* m_world_ptr;

};
////////////////////////////////////////////////////////////////
class Alphatron : public Enemy {
public:
	Alphatron(int x, int y, int hp, int aggressivity, int velocity, GameWorld* ptr, Fly fly_way,int hurt);
	virtual void Update() override;
	virtual void attack() override;
	virtual void Be_destroyed() override;
	
};

/// //////////////////////////////////////////////////////////

class Sigmatron : public Enemy {
public:
	Sigmatron(int x, int y, int hp, int aggressivity, int velocity, GameWorld* ptr, Fly fly_way, int hurt);
	virtual void Update() override;
	virtual void attack() override;
	virtual void Be_destroyed() override;
	
};

/// ////////////////////////////////////////////

class Omegatron : public Enemy {
public:
	Omegatron(int x, int y, int hp, int aggressivity, int velocity, GameWorld* ptr, Fly fly_way, int hurt);
	virtual void Update() override;
	virtual void attack() override;
	virtual void Be_destroyed() override;
	
};

/// ///////////////////////////////////////

class Explosion : public GameObject {
public:
	Explosion(int x,int y);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	int GetCount() const;
private:
	int m_count;
};


 ///////////////////////////////////////////

class Meteor : public GameObject {
public:
	Meteor(int x, int y,Dawnbreaker* ptr);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	void Check_collapse();
	Dawnbreaker* Get_Dawn_Ptr();
private:
	Dawnbreaker* m_ptr;
};
 //////////////////////////////////////////////

class Goodie : public GameObject {
public:
	Goodie(int image_ID, int x, int y, GameWorld* ptr2);
	virtual void Update() override;
	//virtual bool IsEnemy() override;
	virtual bool Check_collapse();
	
	//Enemy* Get_Enemy_Ptr() const;
	GameWorld* Get_Goodie_World_Ptr()const;

private:
	//Enemy* m_enemy_ptr;
	GameWorld* m_goodie_world_ptr;
};

 //////////////////////////////////////

class HP_Restore_Goodie : public Goodie {
public:
	HP_Restore_Goodie(int image_ID, int x, int y, GameWorld* ptr2); //这里我把Enemy* ptr去掉了
	virtual void Update() override;
	virtual bool Check_collapse() override;

};

/// ////////////////////////////////////////


class Power_Up_Goodie : public Goodie {
public:
	Power_Up_Goodie(int image_ID, int x, int y, GameWorld* ptr2);
	virtual void Update() override;
	virtual bool Check_collapse() override;
	
};

/// ///////////////////////////////////////////

class Meteor_Goodie : public Goodie {
public:
	Meteor_Goodie(int image_ID, int x,int y,  GameWorld* ptr2);
	virtual void Update() override;
	virtual bool Check_collapse() override;
	
};


#endif // GAMEOBJECTS_H__
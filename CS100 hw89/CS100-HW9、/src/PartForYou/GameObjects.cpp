#include "GameObjects.h"

//#include "GameWorld.h"
using namespace std;



/// ///////////////////////////
bool is_collapsed(int x1, int y1, int x2, int y2, double size1, double size2) {
	double d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	if (d < 30 * (size1 + size2)) {
		return true;
	}
	else {
		return false;
	}
}
GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size, bool a,int hp,int hurt):ObjectBase(imageID, x, y, direction, layer, size), m_is_dead(a),m_HP(hp),m_hurt(hurt) {

}
 void GameObject::Update(){

}


bool GameObject::Get_is_dead() const {
	return m_is_dead;
}

void GameObject::Set_is_dead(bool a) {
	m_is_dead = a;
}

int GameObject::GetHp()const {
	return m_HP;
}

void GameObject::SetHp(int hp) {
	m_HP = hp;
}

int GameObject::GetHurt()const {
	return m_hurt;
}

void GameObject::SetHurt(int hurt) {
	m_hurt = hurt;
}


///// //////////////////////////////
//
Dawnbreaker::Dawnbreaker(GameWorld* ptr) :GameObject(IMGID_DAWNBREAKER, 300, 100, 0, 0, 1.0, false,100,0), m_energy(10), m_ptr(ptr),m_Power_Goodie(0),m_Meteor_Goodie(0),m_has_destroyed_enermies(0) {

}

void Dawnbreaker::SetEnergy(int energy) {
	m_energy = energy;
}

int Dawnbreaker::GetEnergy() const {
	return m_energy;
}

GameWorld* Dawnbreaker::GetPtr() const {
	return m_ptr;
}


int Dawnbreaker::GetPowerGoodie() const {
	return m_Power_Goodie;
}

void Dawnbreaker::SetPowerGoodie(int count) {
	m_Power_Goodie = count;
}

int Dawnbreaker::GetMeteorGoodie() const {
	return m_Meteor_Goodie;
}

void Dawnbreaker::SetMeteorGoodie(int count) {
	m_Meteor_Goodie = count;
}

int Dawnbreaker:: GetHasdestroyed() const {
	return m_has_destroyed_enermies;
}

void Dawnbreaker::SetHasdestroyed(int count) {
	m_has_destroyed_enermies = count;
}


void Dawnbreaker::Update() {
	if (GetHp() == 0 || Get_is_dead()==true) {
		Set_is_dead(true);
		return;
	}
	else {								//注意玩家可以同时按下多个键！即要向斜方向移动
		if (GetPtr()->GetKey(KeyCode::UP)) {
			if ((GetY() + 4) >= 50 && (GetY() + 4) <= WINDOW_HEIGHT - 1) {
				MoveTo(GetX(), GetY() + 4);
			}
		}
		if (GetPtr()->GetKey(KeyCode::DOWN)) {
			if ((GetY() - 4) >= 50 && (GetY() - 4) <= WINDOW_HEIGHT - 1) {
				MoveTo(GetX(), GetY() - 4);
			}
		}
		if (GetPtr()->GetKey(KeyCode::RIGHT)) {
			if ((GetX() + 4) >= 0 && (GetX() + 4) <= WINDOW_WIDTH - 1) {
				MoveTo(GetX() + 4, GetY());
			}
		}
		if (GetPtr()->GetKey(KeyCode::LEFT)) {
			if ((GetX() - 4) >= 0 && (GetX() - 4) <= WINDOW_WIDTH - 1) {
				MoveTo(GetX() - 4, GetY());
			}
		}

		if (GetPtr()->GetKey(KeyCode::FIRE1)) {
			if (m_energy >= 10) {
				m_energy -= 10;
				Blue_bullet* real_blue_bullet = new Blue_bullet(GetX(), GetY() + 50, 0.5+0.1*GetPowerGoodie(), 5 + 3 * GetPowerGoodie(),this);
   				GetPtr()->AddObject(real_blue_bullet);
			}
		}

		if (GetPtr()->GetKeyDown(KeyCode::FIRE2)) {
			if (GetPtr()->GetDawnbreaker()->GetMeteorGoodie() > 0) {
				GetPtr()->GetDawnbreaker()->SetMeteorGoodie(GetPtr()->GetDawnbreaker()->GetMeteorGoodie() - 1);
				Meteor* real_meteor = new Meteor(GetX(), GetY() + 100,this);
				GetPtr()->AddObject(real_meteor);
			}
		}
		
		if (m_energy < 10) {
			m_energy += 1;
		}

		

	}
}

 /////////////////////////////////////////////////////

Star::Star(int y) :GameObject(IMGID_STAR, randInt(0, WINDOW_WIDTH - 1), y, 0, 4, double(randInt(10, 40)) / 100, false,0,0) {

}

void Star::Update() {
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}
	MoveTo(GetX(), GetY() - 1);
	
}



 //////////////////////////////////////////////

Blue_bullet::Blue_bullet(int x, int y, double size, int hurt,Dawnbreaker* ptr) :GameObject(IMGID_BLUE_BULLET, x, y, 0, 1, size, false,0,hurt),m_dawn_ptr(ptr) {

}

bool Blue_bullet::Check_collapse() {   //这里调用蓝色子弹的update要减去hp,调用敌机的update也要减去hp,那会不会重复减去啊
	bool a = false;
	for (auto& object : m_dawn_ptr->GetPtr()->m_game_object) {
		if (dynamic_cast<Alphatron*>(object)!=nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), 1.0, GetSize())) {
				if (object->GetHp() - GetHurt() <= 0) {
					object->SetHp(0);
					object->Set_is_dead(true);
					Explosion* real_explosion = new Explosion(object->GetX(), object->GetY());   //这里四行是新加的
					Get_Dawn_Ptr()->GetPtr()->AddObject(real_explosion);
					Get_Dawn_Ptr()->GetPtr()->IncreaseScore(50);
					Get_Dawn_Ptr()->SetHasdestroyed(Get_Dawn_Ptr()->GetHasdestroyed() + 1);
				}
				else {
					object->SetHp(object->GetHp() - GetHurt());
				}
				Set_is_dead(true);
				a = true;   //会不会有两颗蓝色子弹同时撞上？？？会不会有两颗陨石一起装上？
			}
		}
		else if (dynamic_cast<Sigmatron*>(object) != nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), 1.0, GetSize())) {
				if (object->GetHp() - GetHurt() <= 0) {
					object->SetHp(0);
					object->Set_is_dead(true);
					Explosion* real_explosion = new Explosion(object->GetX(), object->GetY());   //这里四行是新加的
					Get_Dawn_Ptr()->GetPtr()->AddObject(real_explosion);
					Get_Dawn_Ptr()->GetPtr()->IncreaseScore(100);
					Get_Dawn_Ptr()->SetHasdestroyed(Get_Dawn_Ptr()->GetHasdestroyed() + 1);


					if (randInt(1, 5) == 1) {//新加的
						HP_Restore_Goodie* real_hp_restore_goodie = new HP_Restore_Goodie(IMGID_HP_RESTORE_GOODIE, object->GetX(), object->GetY(), Get_Dawn_Ptr()->GetPtr());
						Get_Dawn_Ptr()->GetPtr()->AddObject(real_hp_restore_goodie);
					}
				}
				else {
					object->SetHp(object->GetHp() - GetHurt());
				}
				Set_is_dead(true);
				a = true;
			}
		}
		else if (dynamic_cast<Omegatron*>(object) != nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), 1.0, GetSize())) {
				if (object->GetHp() - GetHurt() <= 0) {
					object->SetHp(0);
					object->Set_is_dead(true);
					Explosion* real_explosion = new Explosion(object->GetX(), object->GetY());   //这里四行是新加的
					Get_Dawn_Ptr()->GetPtr()->AddObject(real_explosion);
					Get_Dawn_Ptr()->GetPtr()->IncreaseScore(200);
					Get_Dawn_Ptr()->SetHasdestroyed(Get_Dawn_Ptr()->GetHasdestroyed() + 1);

					int rand = randInt(1, 5);
					if (rand == 1 || rand == 2) {
						int rand2 = randInt(1, 5);
						if (rand2 >= 1 && rand2 <= 4) {
							Power_Up_Goodie* real_power_up_goodie = new Power_Up_Goodie(IMGID_POWERUP_GOODIE, object->GetX(), object->GetY(),  Get_Dawn_Ptr()->GetPtr());
							Get_Dawn_Ptr()->GetPtr()->AddObject(real_power_up_goodie);
						}
						else if (rand2 == 5) {
							Meteor_Goodie* real_meteor_goodie = new Meteor_Goodie(IMGID_METEOR_GOODIE, object->GetX(), object->GetY(), Get_Dawn_Ptr()->GetPtr());
							Get_Dawn_Ptr()->GetPtr()->AddObject(real_meteor_goodie);
						}
					}
				}
				else {
					object->SetHp(object->GetHp() - GetHurt());
				}
				Set_is_dead(true);
				a = true;
			}
		}
	}
	return a;	
}

void Blue_bullet::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() >= WINDOW_HEIGHT) {
		Set_is_dead(true);
		return;
	}

	//第一次检查碰撞
	if (Check_collapse()) {
		return;
	}

	MoveTo(GetX(), GetY() + 6);
	//第二次检查碰撞
	if (Check_collapse()) {
		return;
	}
}


Dawnbreaker* Blue_bullet::Get_Dawn_Ptr() const {
	return m_dawn_ptr;
}

 //////////////////////////////////////////////

Red_bullet::Red_bullet(int x, int y, int direction, int hurt,GameWorld* ptr):GameObject(IMGID_RED_BULLET,x,y,direction,1,0.5,false,0,hurt),m_world_ptr(ptr) {

}

bool Red_bullet::Check_collapse() {
	if (Get_World_Ptr()->GetDawnbreaker()->Get_is_dead() != true) {
		if (is_collapsed(Get_World_Ptr()->GetDawnbreaker()->GetX(), Get_World_Ptr()->GetDawnbreaker()->GetY(), GetX(), GetY(), 1.0, 0.5)) {
			if (Get_World_Ptr()->GetDawnbreaker()->GetHp() - GetHurt() <= 0) {
				Get_World_Ptr()->GetDawnbreaker()->SetHp(0);
				Get_World_Ptr()->GetDawnbreaker()->Set_is_dead(true);
			}
			else {
				Get_World_Ptr()->GetDawnbreaker()->SetHp(Get_World_Ptr()->GetDawnbreaker()->GetHp() - GetHurt());
			}
			Set_is_dead(true);
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Red_bullet::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}
	//红色子弹需要第一次检查自己是否正在与破晓号发生碰撞  写！
	if (Check_collapse()) {
		return;
	}
	

	if (GetDirection() == 180) {
		MoveTo(GetX(), GetY() - 6);
	}
	else if (GetDirection() == 162) {
		MoveTo(GetX() + 2, GetY() - 6);
	}
	else if (GetDirection() == 198) {
		MoveTo(GetX() - 2, GetY() - 6);
	}

	//移动后，红色子弹需要第二次检查自己是否正在与破晓号相撞  写！

	if (Check_collapse()) {
		return;
	}

}

GameWorld* Red_bullet::Get_World_Ptr() const {
	return m_world_ptr;
}



 ////////////////////////////////////////////////////////

Enemy::Enemy(int image_ID,int x, int y, int hp, int aggressivity, int velocity, int energy,int direction,int layer,double size,GameWorld* ptr, Fly fly_way,int hurt):GameObject(image_ID,x,y,direction,layer,size,false,hp,hurt),m_aggressivity(aggressivity),m_velocity(velocity),m_energy(energy),m_fly_time(0),m_world_ptr(ptr),m_fly_way(fly_way) {

}



int Enemy::GetEnergy() const{
	return m_energy;
}

int Enemy::GetAggress()const {
	return m_aggressivity;
}

int Enemy::GetVelocity()const {
	return m_velocity;
}

int Enemy::GetFlytime() const {
	return m_fly_time;
}

void Enemy::SetFlytime(int time) {
	m_fly_time = time;
}


void Enemy::SetAggress(int aggress) {
	m_aggressivity = aggress;
}

void Enemy::SetVelocity(int velocity) {
	m_velocity = velocity;
}

void Enemy::SetEnergy(int energy) {
	m_energy = energy;
}

GameWorld* Enemy::Get_World_Ptr() const{
	return m_world_ptr;
}

Fly Enemy::GetFlyway() const {
	return m_fly_way;
}

void Enemy::SetFlyway(Fly direct) {
	m_fly_way = direct;
}

void Enemy::decide_dead() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY()<0) {
		Set_is_dead(true);
		return;
	}
}



bool Enemy::Check_collapse() {
	bool a = false;
	if (Get_World_Ptr()->GetDawnbreaker()->Get_is_dead() != true) {
		if (is_collapsed(Get_World_Ptr()->GetDawnbreaker()->GetX(), Get_World_Ptr()->GetDawnbreaker()->GetY(), GetX(), GetY(), 1.0, 1.0)) {
			if (Get_World_Ptr()->GetDawnbreaker()->GetHp() - 20 <= 0) {
				Get_World_Ptr()->GetDawnbreaker()->SetHp(0);
				Get_World_Ptr()->GetDawnbreaker()->Set_is_dead(true);

			}
			else {
				Get_World_Ptr()->GetDawnbreaker()->SetHp(Get_World_Ptr()->GetDawnbreaker()->GetHp() - 20);
			}

			SetHp(0);
			Set_is_dead(true);
			a = true;
		}
	}


	for (auto& object : Get_World_Ptr()->m_game_object) {  //会不会是循环的问题？
		if (dynamic_cast<Blue_bullet*>(object)!=nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), object->GetSize(), 1.0)) {
				if (GetHp() - object->GetHurt() <= 0) {
					SetHp(0);
					Set_is_dead(true);        //如果要加也是把这个函数拆开来把爆炸和奖励写在这

				}
				else {
					SetHp(GetHp() - object->GetHurt());
				}
				object->Set_is_dead(true);
				a = true;
			}
		}
		else if (dynamic_cast<Meteor*>(object) != nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), 2.0, 1.0)) {
				Set_is_dead(true);
				a = true;
				//Get_World_Ptr()->GetDawnbreaker()->SetMeteorGoodie(Get_World_Ptr()->GetDawnbreaker()->GetMeteorGoodie() - 1);//新加的

			}
		}
	}

	
	return a;	  
}

void Enemy::Update() {//暂时什么都没有写，因为后面子类还要override掉的

}

void Enemy::attack() {

}

void Enemy::Be_destroyed() {

}

void Enemy::Fly_generate() {
	if (GetFlytime() == 0) {
		if (randInt(1, 3) == 1) {
			SetFlyway(Fly::DOWN);
		}
		else if (randInt(1, 3) == 2) {
			SetFlyway(Fly::LEFT_DOWN);
		}
		else if (randInt(1, 3) == 3) {
			SetFlyway(Fly::RIGHT_DOWN);
		}
		SetFlytime(randInt(10, 50));
	}
	
	if (GetX() < 0) {
		SetFlyway(Fly::RIGHT_DOWN);
		SetFlytime(randInt(10, 50));
	}

	if (GetX() >= WINDOW_WIDTH) {
		SetFlyway(Fly::LEFT_DOWN);
		SetFlytime(randInt(10, 50));
	}
}

void Enemy::Fly_move() {
	SetFlytime(GetFlytime() - 1);
	if (GetFlyway() == Fly::DOWN) {
		MoveTo(GetX(), GetY() - GetVelocity());
	}
	else if (GetFlyway() == Fly::LEFT_DOWN) {
		MoveTo(GetX()-GetVelocity(), GetY() - GetVelocity());
	}
	else if (GetFlyway() == Fly::RIGHT_DOWN) {
		MoveTo(GetX() + GetVelocity(), GetY() - GetVelocity());
	}
}

/// /////////////////////////////////////////////////////////

Alphatron::Alphatron(int x, int y, int hp, int aggressivity, int velocity,GameWorld* ptr,Fly fly_way,int hurt):Enemy(IMGID_ALPHATRON,x,y,hp,aggressivity,velocity, 25,180,0,1.0,ptr,fly_way,hurt) {
	
}

void Alphatron::Be_destroyed() {
		Explosion* real_explosion = new Explosion(GetX(), GetY());
		Get_World_Ptr()->AddObject(real_explosion);
		Get_World_Ptr()->IncreaseScore(50);
		Get_World_Ptr()->GetDawnbreaker()->SetHasdestroyed(Get_World_Ptr()->GetDawnbreaker()->GetHasdestroyed() + 1);
	
}

void Alphatron::attack() {
		if (abs(GetX() - Get_World_Ptr()->GetDawnbreaker()->GetX()) <= 10) {
			if (GetEnergy() < 25) {
				return;
			}
			else {
				if (randInt(1, 4) == 1) {
					SetEnergy(GetEnergy() - 25);
					Red_bullet* real_red_bullet = new Red_bullet(GetX(), GetY() - 50, 180, GetAggress(), Get_World_Ptr());//为啥红色子弹需要指向GameWorld的指针
					Get_World_Ptr()->AddObject(real_red_bullet);
				}				

			}
		}
	
}

void Alphatron::Update() {
	if (Get_is_dead() == true) {  //在blue bullet 之后才添加到list中的话，因为调用blue bullet的update()函数，已经把get_is_dead设置为true了
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}

	if (Check_collapse()) {
		if (Get_is_dead()) {
			Be_destroyed();
			return;
		}
	}

	attack();


	if (GetEnergy() < 25) {
		SetEnergy(GetEnergy() + 1);
	}
	Fly_generate();
	Fly_move();
	
	if (Check_collapse()) {
		if (Get_is_dead()) {
			Be_destroyed();
			return;
		}
	}







}





/// //////////////////////////////////////////////////

Sigmatron::Sigmatron(int x, int y, int hp, int aggressivity, int velocity, GameWorld* ptr,Fly fly_way, int hurt): Enemy(IMGID_SIGMATRON, x, y, hp, aggressivity, velocity, 0, 180, 0, 1.0,ptr,fly_way,hurt) {

}

void Sigmatron::Be_destroyed() {
		Explosion* real_explosion = new Explosion(GetX(), GetY());
		Get_World_Ptr()->AddObject(real_explosion);
		Get_World_Ptr()->IncreaseScore(100);
		Get_World_Ptr()->GetDawnbreaker()->SetHasdestroyed(Get_World_Ptr()->GetDawnbreaker()->GetHasdestroyed() + 1);

		if (randInt(1, 5) == 1) {
			HP_Restore_Goodie* real_hp_restore_goodie = new HP_Restore_Goodie(IMGID_HP_RESTORE_GOODIE, GetX(), GetY(),this->Get_World_Ptr());
			Get_World_Ptr()->AddObject(real_hp_restore_goodie);
		}
	
}

void Sigmatron::attack() {
		if (abs(GetX() - Get_World_Ptr()->GetDawnbreaker()->GetX()) <= 10) {
			SetFlyway(Fly::DOWN);
			SetFlytime(WINDOW_HEIGHT);
			SetVelocity(10);
		}
	
}


void Sigmatron::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}

	if (Check_collapse()) {
		if (Get_is_dead()) {
			Be_destroyed();
			return;
		}
	}
	attack();
	Fly_generate();
	Fly_move();


	if (Check_collapse()) {
		if (Get_is_dead()) {
			Be_destroyed();
			return;
		}
	}
}


/// ////////////////////////////////////////////

Omegatron::Omegatron(int x, int y, int hp, int aggressivity, int velocity, GameWorld* ptr,Fly fly_way, int hurt): Enemy(IMGID_OMEGATRON, x, y, hp, aggressivity, velocity, 50, 180, 0, 1.0,ptr,fly_way,hurt) {

}

void Omegatron::Be_destroyed() {
	Explosion* real_explosion = new Explosion(GetX(), GetY());
	Get_World_Ptr()->AddObject(real_explosion);
	Get_World_Ptr()->IncreaseScore(200);
	Get_World_Ptr()->GetDawnbreaker()->SetHasdestroyed(Get_World_Ptr()->GetDawnbreaker()->GetHasdestroyed() + 1);

	int rand = randInt(1, 5);
	if (rand == 1 || rand == 2) {
		int rand2 = randInt(1, 5);
		if (rand2 >= 1 && rand2 <= 4) {
			Power_Up_Goodie* real_power_up_goodie = new Power_Up_Goodie(IMGID_POWERUP_GOODIE, GetX(), GetY(), this->Get_World_Ptr());
			Get_World_Ptr()->AddObject(real_power_up_goodie);
		}
		else if (rand2 == 5) {
			Meteor_Goodie* real_meteor_goodie = new Meteor_Goodie(IMGID_METEOR_GOODIE, GetX(), GetY(), this->Get_World_Ptr());
			Get_World_Ptr()->AddObject(real_meteor_goodie);
		}
	}
}

void Omegatron::attack() {
	if (GetEnergy() < 50) {
		return;
	}
	else {
		SetEnergy(GetEnergy() - 50);
		Red_bullet* red_1 = new Red_bullet(GetX(), GetY() - 50, 162, GetAggress(),Get_World_Ptr());
		Red_bullet* red_2 = new Red_bullet(GetX(), GetY() - 50, 198, GetAggress(), Get_World_Ptr());
		Get_World_Ptr()->AddObject(red_1);
		Get_World_Ptr()->AddObject(red_2);
	}
}

void Omegatron::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}

	if (Check_collapse()) {
		if (Get_is_dead()) {
			Be_destroyed();
			return;
		}
	}
	attack();

	if (GetEnergy() < 50) {
		SetEnergy(GetEnergy() + 1);
	}

	Fly_generate();
	Fly_move();


	if (Check_collapse()) {
		if (Get_is_dead()) {
			Be_destroyed();
			return;
		}
	}
}

 /////////////////////////////////////////////

Explosion::Explosion(int x, int y):GameObject(IMGID_EXPLOSION,x,y,0,3,4.5,false,0,0),m_count(0) {

}

void Explosion::Update() {  //这里只在m_size上做减法会显示出正确的吗？还是说要生成很多个爆炸，一点点显示？
	m_count += 1;
	SetSize(4.5 - 0.2 * m_count);
	if (m_count == 20) {
		Set_is_dead(true);
		return;
	}
}

int Explosion::GetCount() const{
	return m_count;
}

 ////////////////////////////////////////////////////////////////


Meteor::Meteor(int x,int y, Dawnbreaker* ptr):GameObject(IMGID_METEOR,x,y,0,1,2.0,false,0,0),m_ptr(ptr) {

}

Dawnbreaker* Meteor::Get_Dawn_Ptr() {
	return m_ptr;
}

void Meteor::Check_collapse() {
	for (auto& object : Get_Dawn_Ptr()->GetPtr()->m_game_object) { //////循环
		if (dynamic_cast<Alphatron*>(object)!=nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), 1.0, 2.0)) {
				object->Set_is_dead(true);		   //会不会有两颗蓝色子弹同时撞上？？？会不会有两颗陨石一起装上？
				Get_Dawn_Ptr()->GetPtr()->IncreaseScore(50);//新加的
				Explosion* real_explosion = new Explosion(object->GetX(), object->GetY());   //这里四行是新加的
				Get_Dawn_Ptr()->GetPtr()->AddObject(real_explosion);
				Get_Dawn_Ptr()->SetHasdestroyed(Get_Dawn_Ptr()->GetHasdestroyed() + 1);
			}
		}
		else if (dynamic_cast<Sigmatron*>(object) != nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), 1.0, 2.0)) {
				object->Set_is_dead(true);
				Get_Dawn_Ptr()->GetPtr()->IncreaseScore(100);
				Explosion* real_explosion = new Explosion(object->GetX(), object->GetY());   //这里四行是新加的
				Get_Dawn_Ptr()->GetPtr()->AddObject(real_explosion);
				Get_Dawn_Ptr()->SetHasdestroyed(Get_Dawn_Ptr()->GetHasdestroyed() + 1);

				if (randInt(1, 5) == 1) {//新加的
					HP_Restore_Goodie* real_hp_restore_goodie = new HP_Restore_Goodie(IMGID_HP_RESTORE_GOODIE, object->GetX(), object->GetY(), Get_Dawn_Ptr()->GetPtr());
					Get_Dawn_Ptr()->GetPtr()->AddObject(real_hp_restore_goodie);
				}
			}
		}
		else if (dynamic_cast<Omegatron*>(object) != nullptr && object->Get_is_dead() != true) {
			if (is_collapsed(object->GetX(), object->GetY(), GetX(), GetY(), 1.0, 2.0)) {
				object->Set_is_dead(true);
				Get_Dawn_Ptr()->GetPtr()->IncreaseScore(200);
				Explosion* real_explosion = new Explosion(object->GetX(), object->GetY());   //这里四行是新加的
				Get_Dawn_Ptr()->GetPtr()->AddObject(real_explosion);
				Get_Dawn_Ptr()->SetHasdestroyed(Get_Dawn_Ptr()->GetHasdestroyed() + 1);

				int rand = randInt(1, 5);
				if (rand == 1 || rand == 2) {
					int rand2 = randInt(1, 5);
					if (rand2 >= 1 && rand2 <= 4) {
						Power_Up_Goodie* real_power_up_goodie = new Power_Up_Goodie(IMGID_POWERUP_GOODIE, object->GetX(), object->GetY(), Get_Dawn_Ptr()->GetPtr());
						Get_Dawn_Ptr()->GetPtr()->AddObject(real_power_up_goodie);
					}
					else if (rand2 == 5) {
						Meteor_Goodie* real_meteor_goodie = new Meteor_Goodie(IMGID_METEOR_GOODIE, object->GetX(), object->GetY(),  Get_Dawn_Ptr()->GetPtr());
						Get_Dawn_Ptr()->GetPtr()->AddObject(real_meteor_goodie);
					}
				}
			}
		}
	}	
}

void Meteor::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() >= WINDOW_HEIGHT) {
		Set_is_dead(true);
		return;
	}
	//陨石第一次检查自己是否在与一只敌机碰撞  写！
	Check_collapse();

	MoveTo(GetX(), GetY() + 2);
	SetDirection(GetDirection() + 5);

	//移动后，陨石需要第二次检查自己是否正在与一只敌机相撞  写！
	Check_collapse();

}

 /////////////////////////////////////////////////////////

Goodie::Goodie(int image_ID,int x,int y ,  GameWorld* ptr2):GameObject(image_ID,x,y,0,2,0.5,false,0,0),m_goodie_world_ptr(ptr2) {

}

void Goodie::Update() {

}

bool Goodie::Check_collapse() {
	return false;
}


//
//Enemy* Goodie::Get_Enemy_Ptr() const{
//	return m_enemy_ptr;
//}

GameWorld* Goodie::Get_Goodie_World_Ptr()const {
	return m_goodie_world_ptr;
}

/// ///////////////////////////////////////////

HP_Restore_Goodie::HP_Restore_Goodie(int image_ID,int x, int y, GameWorld* ptr2) :Goodie(IMGID_HP_RESTORE_GOODIE, x, y,ptr2) {

}

bool HP_Restore_Goodie::Check_collapse() {
	if (Get_Goodie_World_Ptr()->GetDawnbreaker()->Get_is_dead() != true) {
		if (is_collapsed(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetX(), Get_Goodie_World_Ptr()->GetDawnbreaker()->GetY(), GetX(), GetY(), 1.0, 0.5)) {  //第一二个位置统一写破晓号的位置
			if ((Get_Goodie_World_Ptr()->GetDawnbreaker()->GetHp() + 50) > 100) {
				Get_Goodie_World_Ptr()->GetDawnbreaker()->SetHp(100);
			}
			else {
				Get_Goodie_World_Ptr()->GetDawnbreaker()->SetHp(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetHp() + 50);
			}

			Get_Goodie_World_Ptr()->IncreaseScore(20);
			Set_is_dead(true);
			return true;
		}
		else {
			return false;
		}
	}
	return false;
	
}

void HP_Restore_Goodie::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}

	//HP道具需要第一次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

	MoveTo(GetX(), GetY() - 2);
	//HP道具需要第二次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

}
/// /////////////////////////////////////////////////

Power_Up_Goodie::Power_Up_Goodie(int image_ID,int x, int y,  GameWorld* ptr2) :Goodie(IMGID_POWERUP_GOODIE, x, y,ptr2) {

}

bool Power_Up_Goodie::Check_collapse() {
	if (Get_Goodie_World_Ptr()->GetDawnbreaker()->Get_is_dead() != true) {
		if (is_collapsed(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetX(), Get_Goodie_World_Ptr()->GetDawnbreaker()->GetY(), GetX(), GetY(), 1.0, 0.5)) {
			Get_Goodie_World_Ptr()->GetDawnbreaker()->SetPowerGoodie(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetPowerGoodie() + 1);
			Get_Goodie_World_Ptr()->IncreaseScore(20);
			Set_is_dead(true);
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void Power_Up_Goodie::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}

	//升级道具需要第一次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

	MoveTo(GetX(), GetY() - 2);
	//升级道具需要第二次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

}

/// ///////////////////////////////////////////////////////////


Meteor_Goodie::Meteor_Goodie(int image_ID,int x, int y,  GameWorld* ptr2) :Goodie(IMGID_METEOR_GOODIE, x, y,ptr2){

}

bool Meteor_Goodie::Check_collapse() {
	if (Get_Goodie_World_Ptr()->GetDawnbreaker()->Get_is_dead() != true) {
		if (is_collapsed(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetX(), Get_Goodie_World_Ptr()->GetDawnbreaker()->GetY(), GetX(), GetY(), 1.0, 0.5)) {
			Get_Goodie_World_Ptr()->GetDawnbreaker()->SetMeteorGoodie(Get_Goodie_World_Ptr()->GetDawnbreaker()->GetMeteorGoodie() + 1);
			Get_Goodie_World_Ptr()->IncreaseScore(20);
			Set_is_dead(true);
			return true;
		}
		else {
			return false;
		}
	}
	return false;
	
}

void Meteor_Goodie::Update() {
	if (Get_is_dead() == true) {
		return;
	}
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}
	//陨石道具需要第一次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

	MoveTo(GetX(), GetY() - 2);
	//陨石道具需要第一次检查自己是否正在与破晓号相撞   写！
	if (Check_collapse()) {
		return;
	}

}
/////////////////////////////////////////////
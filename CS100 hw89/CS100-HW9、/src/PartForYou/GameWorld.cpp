#include "GameWorld.h"
#include "GameObjects.h"
#include "string"
using namespace std;


bool null_ptr(GameObject* ptr) {
	return (ptr == nullptr);
}

GameWorld::GameWorld():m_life_number(3),m_real_dawnbreaker(nullptr),m_enemies_onscreen(0) {

}
GameWorld::~GameWorld() {

}

Dawnbreaker* GameWorld::GetDawnbreaker() {
	return m_real_dawnbreaker;
}

void GameWorld::Init() {   //关卡的初始化！ 每一关开始前都会调用该函数！//初始化任何用于记录关卡的数据！
	m_real_dawnbreaker = new Dawnbreaker(this);
	for (int i = 0; i < 30; i++) {
		m_game_object.push_back(new Star(randInt(0, WINDOW_HEIGHT - 1)));
	}

}

LevelStatus GameWorld::Update() {               //游戏过程中每一刻对游戏世界的更新 在关卡开始后，此函数每一刻均会被调用一次
	
	if (randInt(1, 30) == 1) {
		m_game_object.push_back(new Star(WINDOW_HEIGHT - 1));
	}

	//为GameWorld生成新的敌机
	int level = GetLevel();
	int required = 3 * level;
	int destroyed = GetDawnbreaker()->GetHasdestroyed();
	int toDestroy = required - destroyed;
	int maxOnScreen = (5 + level) / 2;
	int allowed = min(toDestroy, maxOnScreen);
	int onScreen = GetEnemyOnscreen();
	if (onScreen < allowed) {
		if (randInt(1, 100) <= allowed - onScreen) {
			int P1 = 6;
			int P2 = 2 * max(level - 1, 0);
			int P3 = 3 * max(level - 2, 0);
			int rand = randInt(1, P1 + P2 + P3);
			if (rand <= P1) {
				Alphatron* real_alphatron = new Alphatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT - 1, 20 + 2 * level, 4 + level, 2 + level / 5, this, Fly::NONE, 0);
				m_game_object.push_back(real_alphatron);
				m_enemies_onscreen += 1;
			}
			else if (rand > P1 && rand <= P1 + P2) {
				Sigmatron* real_sigmatron = new Sigmatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT - 1, 25 + 5 * level, 0, 2 + level / 5, this, Fly::NONE, 0);
				m_game_object.push_back(real_sigmatron);
				m_enemies_onscreen += 1;
			}
			else if (rand > P1 + P2) {
				Omegatron* real_omegatron = new Omegatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT - 1, 20 + level, 2 + 2 * level, 3 + level / 4, this, Fly::NONE, 0);
				m_game_object.push_back(real_omegatron);
				m_enemies_onscreen += 1;
			}
		}
	}

	if (m_real_dawnbreaker->Get_is_dead() != true) {
		m_real_dawnbreaker->Update();
	}
	
	for (auto& object : m_game_object) {
		if (object->Get_is_dead()!=true) {
			object->Update();//在这个地方会断
		}
	}
	

	

	

	if (m_real_dawnbreaker->Get_is_dead() == true) {
		m_life_number -= 1;
		delete m_real_dawnbreaker;
		m_real_dawnbreaker = nullptr;
		return LevelStatus::DAWNBREAKER_DESTROYED;     //这个返回值 LevelStatus 指的是运行状态  作为返回值给到游戏框架（因为是框架在调用函数）
	}													//LevelStatus 是一个enum类型

	if (m_real_dawnbreaker->GetHasdestroyed() == 3 * level) {
		return  LevelStatus::LEVEL_CLEARED;
	}

	for (auto& object : m_game_object) {           //实在不行的话这里改成hw8 reference中的写法
		if (object != nullptr) {
			if (object->Get_is_dead() == true) {
				if (dynamic_cast<Enemy*>(object) != nullptr) {//这个地方是要写的吗？好像是对的
					m_enemies_onscreen -= 1;
				}
				delete object;
				object = nullptr;
			}
		}
	}
	m_game_object.remove_if(null_ptr);



	SetStatusBarMessage("HP: " + to_string(GetDawnbreaker()->GetHp()) + "/100   Meteors: " + to_string(GetDawnbreaker()->GetMeteorGoodie()) + "   Lives: " + to_string(GetLifeNum()) + "   Level: " + to_string(GetLevel()) + "   Enemies: " + to_string(GetDawnbreaker()->GetHasdestroyed()) + "/" + to_string(required) + "   Score: " + to_string(GetScore()));
	return LevelStatus::ONGOING;
	
}													
void GameWorld::CleanUp() {
	for (auto& object : m_game_object) {
		if (object != nullptr) {
			if (dynamic_cast<Enemy*>(object) != nullptr) {//这个我是新加的
				m_enemies_onscreen -= 1;
			}
			delete object;
			object = nullptr;			
		}
	}
	if (m_real_dawnbreaker != nullptr) {
		delete m_real_dawnbreaker;
		m_real_dawnbreaker = nullptr;
	}
	m_game_object.remove_if(null_ptr);


}


bool GameWorld::IsGameOver() const {
	if (m_life_number == 0) {
		return true;
	}
	else {
		return false;
	}
}


void GameWorld::AddObject(GameObject* object) {
	m_game_object.push_back(object);
}





int GameWorld::GetLifeNum() {
	return m_life_number;
}

int GameWorld::GetEnemyOnscreen() {
	return m_enemies_onscreen;
}


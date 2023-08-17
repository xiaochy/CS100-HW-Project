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

void GameWorld::Init() {   //�ؿ��ĳ�ʼ���� ÿһ�ؿ�ʼǰ������øú�����//��ʼ���κ����ڼ�¼�ؿ������ݣ�
	m_real_dawnbreaker = new Dawnbreaker(this);
	for (int i = 0; i < 30; i++) {
		m_game_object.push_back(new Star(randInt(0, WINDOW_HEIGHT - 1)));
	}

}

LevelStatus GameWorld::Update() {               //��Ϸ������ÿһ�̶���Ϸ����ĸ��� �ڹؿ���ʼ�󣬴˺���ÿһ�̾��ᱻ����һ��
	
	if (randInt(1, 30) == 1) {
		m_game_object.push_back(new Star(WINDOW_HEIGHT - 1));
	}

	//ΪGameWorld�����µĵл�
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
			object->Update();//������ط����
		}
	}
	

	

	

	if (m_real_dawnbreaker->Get_is_dead() == true) {
		m_life_number -= 1;
		delete m_real_dawnbreaker;
		m_real_dawnbreaker = nullptr;
		return LevelStatus::DAWNBREAKER_DESTROYED;     //�������ֵ LevelStatus ָ��������״̬  ��Ϊ����ֵ������Ϸ��ܣ���Ϊ�ǿ���ڵ��ú�����
	}													//LevelStatus ��һ��enum����

	if (m_real_dawnbreaker->GetHasdestroyed() == 3 * level) {
		return  LevelStatus::LEVEL_CLEARED;
	}

	for (auto& object : m_game_object) {           //ʵ�ڲ��еĻ�����ĳ�hw8 reference�е�д��
		if (object != nullptr) {
			if (object->Get_is_dead() == true) {
				if (dynamic_cast<Enemy*>(object) != nullptr) {//����ط���Ҫд���𣿺����ǶԵ�
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
			if (dynamic_cast<Enemy*>(object) != nullptr) {//��������¼ӵ�
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


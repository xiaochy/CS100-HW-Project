#include "Star.h"
using namespace std;

Star::Star(int y) :GameObject(IMGID_STAR, randInt(0, WINDOW_WIDTH - 1), y, 0, 4, double(randInt(10, 40)) / 100, false, 0, 0) {

}

void Star::Update() {
	if (GetY() < 0) {
		Set_is_dead(true);
		return;
	}
	MoveTo(GetX(), GetY() - 1);

}
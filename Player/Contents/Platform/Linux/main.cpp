#include "Polycode.h"
#include "PolycodeView.h"
#include "PolycodeLinuxPlayer.h"

int main(int argc, char *argv[]) {
	PolycodeView *view = new PolycodeView("Polycode Player");
	if(argc < 2) {
		printf("Filename required!\n");
		return 1;
	}
	PolycodeLinuxPlayer *player = new PolycodeLinuxPlayer(view, argv[1], false, true);
	player->runPlayer();
	while(player->Update()) {}
	delete player;
	return 0;
}

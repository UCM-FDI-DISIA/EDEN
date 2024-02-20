#include "EdenMaster.h"

int main() {
	eden::Master* master = eden::Master::Instance();
	master->Loop();
	delete master;
	return 0;
}
#include "Engine/System/BlueJadeII.h"
#include <windows.h>  
#include <stdlib.h>  
#include <string.h>  
#include <tchar.h>	

BlueJadeII* mGameApp = nullptr;

int main(){
	mGameApp = new BlueJadeII();

	if (!mGameApp->InitializeEngine()) {
		cout << "Failed to initialize the instance" << endl;
		return 1;
	}
	mGameApp->Start();

	return 0;
}
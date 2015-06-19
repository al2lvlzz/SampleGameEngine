#include "GameWindow.h"
#include "GameObject.h"

GameWindow* bis;
GameObject* mc;

void Start()
{
	mc = new GameObject(bis->GetRenderer());
	mc->Load("source/SPtest.png");
}

void Update()
{
	mc->Render();
}

void Close()
{
	delete mc;
	mc = NULL;

	delete bis;
	bis = NULL;
}

int main(int argc, char* argv[])
{
	bis = new GameWindow();

	if(!bis->CreateWindow("Sample Game", 800, 600))
	{
		cerr << "Can't Create GameWindow" << endl;
	}else{
		bis->Run((void*)&Start, (void*)Update);
	}

	Close();

	return 0;
}
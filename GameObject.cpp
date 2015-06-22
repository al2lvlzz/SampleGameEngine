#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer)
{
	index = 0;

	x = 0;
	y = 0;
	width = 0;
	height = 0;

	this->tex = new GameTexture();
	this->renderer = NULL;
	
	if(renderer != NULL)
	{
		this->renderer = renderer;
		this->tex->SetRenderer(renderer);
	}

	isPlay = false;
}

GameObject::~GameObject()
{
	clipList.clear();

	delete tex;
	tex = NULL;
}

void GameObject::SetRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	tex->SetRenderer(renderer);
}

void GameObject::Load(string path)
{
	tex->Load(path);

	x = tex->GetX();
	y = tex->GetY();
	width = tex->GetWidth();
	height = tex->GetHeight();
}

void GameObject::AddClip(SDL_Rect* clip)
{
	for(int i = 0; i < sizeof(clip); i++)
	{
		clipList.push_back(clip[i]);
	}
}

void GameObject::LoadClip(string path)
{
	string line;

	ifstream in(path.c_str());
	if(!in.is_open())
	{
		cerr << "Can't Load File : " << path << endl;
	}else{
		while(in.good())
		{
			getline(in, line);
			int _x, _y, _w, _h;
			sscanf(line.c_str(), "%d/%d/%d/%d", &_x, &_y, &_w, &_h);

			SDL_Rect rect = {_x, _y, _w, _h};
			clipList.push_back(rect);
		}
	}
}

void GameObject::SetFrame(int index)
{
	this->index = index;
}

void GameObject::SetAnimation(int start, int end)
{
	this->start = start;
	this->end = end;
}

void GameObject::SetFlip(SDL_RendererFlip flip)
{
	tex->SetFlip(flip);
}

bool GameObject::HitTest(GameObject* hit)
{
	int upA, upB, downA, downB, leftA, leftB, rightA, rightB;

	upA = y;
	upB = hit->y;
	downA = y+height;
	downB = hit->y + hit->height;

	leftA = x;
	leftB = hit->x;
	rightA = x+width;
	rightB = hit->x + hit->width;

	if(upA >= downB)
	{
		return false;
	}

	if(downA <= upB)
	{
		return false;
	}

	if(leftA >= rightB)
	{
		return false;
	}

	if(rightA <= leftB)
	{
		return false;
	}

	return true;
}

void GameObject::Render()
{
	tex->SetX(x);
	tex->SetY(y);
	tex->SetWidth(width);
	tex->SetHeight(height);

	if(clipList.size() > 0)
	{
		tex->SetClip(clipList[index].x, clipList[index].y, clipList[index].w, clipList[index].h);

		if(isPlay)
		{
			index++;

			if(index >= end)
			{
				index = start;
			}
		}
	}

	tex->Render();
}

void GameObject::ClearClip()
{
	clipList.clear();
}

bool GameObject::IsPlay(){return isPlay;}
void GameObject::Play(){isPlay = true;};
void GameObject::Stop(){isPlay = false;};
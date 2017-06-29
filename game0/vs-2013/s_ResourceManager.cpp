#include "s_ResourceManager.h"
#include "Logmanager2.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace df;
s_ResourceManager::s_ResourceManager()
{
	sprite_count = 0;
	setType("ResourceManager");
}


s_ResourceManager &s_ResourceManager::getInstance()
{
	static s_ResourceManager *resource_manager = NULL;

	if (!resource_manager)
	{
		resource_manager = new s_ResourceManager;

	}
	return *resource_manager;
}

int s_ResourceManager::startUp()
{
	sprite_count = 0;
	sound_count = 0;
	music_count = 0;
	s_Manager::startUp();
	return 1;
}

void s_ResourceManager::shutDown()
{
	// delete the p_sprite[1]
	s_Manager::shutDown();
}

int s_ResourceManager::loadSprite(std::string filename, std::string label)
{
	std::ifstream file(filename);
	int t = 0;
	int * line_num = &t;
	char * tag = NULL;

	//read header
	int s_frames_count = readLintInt(&file,line_num,"frames");   // not able to use default token
	if (s_frames_count <= 0)
	{
		LogManager2::getInstance().writeLog("line:%d frame_count err", (*line_num));
	}
	else LogManager2::getInstance().writeLog("line:%d frame_count ok", (*line_num));
	int s_width = readLintInt(&file, line_num, "width");
	int s_height = readLintInt(&file, line_num, "height");
	std::string color = readLineString(&file, line_num, "color");
	df::s_Color df_color;
	if (strcmp(color.c_str(),"black") == 0){
		df_color = BLACK;
	}
	else if(strcmp(color.c_str(), "red") == 0){
		df_color = RED;
	}
	else if (strcmp(color.c_str(), "green") == 0) {
		df_color = GREEN;
	}
	else if (strcmp(color.c_str(), "yellow") == 0) {
		df_color = YELLOW;
	}
	else if (strcmp(color.c_str(), "blue") == 0) {
		df_color = BLUE;
	}
	else if (strcmp(color.c_str(), "magenta") == 0) {
		df_color = MAGENTA;
	}
	else if (strcmp(color.c_str(), "cyan") == 0) {
		df_color = CYAN;
	}
	else if (strcmp(color.c_str(), "white") == 0) {
		df_color = WHITE;
	}
	else df_color = df::S_COLOR_DEFAULT;
	LogManager2::getInstance().writeLog("load header success.");
	// new sprite
	s_Sprite *new_sprite = new s_Sprite(s_frames_count);
	new_sprite->setHeight(s_height);
	new_sprite->setWidth(s_width);
	new_sprite->setColor(df_color);
	while (!file.eof())
	{
		//LogManager2::getInstance().writeLog("while successfully");
		s_Frame s_frame = readFrame(&file, line_num, s_width, s_height);
		new_sprite->addFrame(s_frame);
		
	}
	file.close();
	new_sprite->setLabel(label);

	// should put the sprite into the array  ----3.16/2017
	
	return 1;   // ok
}

int s_ResourceManager::unloadSprite(std::string label)
{
	for (int i = 0; i < sprite_count ;i++)
	{
		if (label.compare(p_sprite[i]->getLabel()) == 0)
		{
			delete p_sprite[i];

			for (int j = i; j < sprite_count - 1; j++)
			{
				p_sprite[j] = p_sprite[j + 1];
			}
			sprite_count --;
			return 1;  // ok
		}
	}
	return 0; // not ok;
}

s_Sprite *s_ResourceManager::getSprite(std::string label) const
{
	for (int i = 0; i < sprite_count; i++)
	{
		if (label.compare(p_sprite[i]->getLabel())== 0)
		{
			return p_sprite[i];
		}
	}
	return NULL;  // not found
}

int df::readLintInt(std::ifstream *p_file, int *p_line_num, const char *tag)
{
	std::string line = "";
	if (p_file->is_open())
	{
		if (p_file->good())
		{
			std::getline(*p_file, line);

			if (line.compare(0,strlen(tag),tag) != 0)
			{

				//LogManager2::getInstance().writeLog("failed to compare %d", line.compare(0,strlen(tag),tag));
				return -1; // not found
			}
			int number = atoi(line.substr(strlen(tag) + 1).c_str());
			*p_line_num++;
			return number;
		}
		else return -2; // not good err
	}
	else return -3;  // is not open
}
std::string df::readLineString(std::ifstream *p_file, int *p_line_num, const char *tag)
{
	std::string line = "";
	if (p_file->is_open())
	{
		if (p_file->good())
		{
			std::getline(*p_file, line);

			if (line.compare(0, strlen(tag), tag) !=0)
			{
				return "-1";  // not found
			}
			std::string res = line.substr(strlen(tag) + 1);
			return res;
		}
		else return "-2";   // not good err
	}
	else return "-3";    // is not open
}

s_Frame df::readFrame(std::ifstream *p_file, int *p_line_number, int width, int height)
{
	std::string line, frame_str="";
	
	if (p_file->is_open())
	{
		if (p_file->good())
		{
			for (int i = 0; i < height; i++)
			{
				std::getline(*p_file, line);
				if (line.size() != width)
				{
					s_Frame *tmp_frame = new s_Frame();
					return *tmp_frame;    // return empty
				}
				frame_str += line;
			}

			std::getline(*p_file, line);

			if (line != END_FRAME_TOKEN)  // which is end
			{
				s_Frame *tmp_frame = new s_Frame();
				return *tmp_frame;     // error
			}
			int w = width;
			int h = height;
			//s_Frame res_frame(w,h,frame_str);  // there is the problem..--3.17
			s_Frame *res_frame = new s_Frame(w,h,frame_str);
			return *res_frame;
		}
	}
}
int s_ResourceManager::loadSound(std::string filename, std::string label)
{
	if (sound_count = MAX_SOUNDS)
	{	
		LogManager2::getInstance().writeLog("sound array full");
		return 0;
	}

	if (sound[sound_count].loadSound(filename) == -1)
	{
		LogManager2::getInstance().writeLog("unable to load sound from file");
		return -1;
	}

	sound[sound_count].setLabel(label);
	sound_count++;
	return 1; // 1 for ok

}

int s_ResourceManager::unloadSound(std::string label)
{
	for (int i = 0; i < sound_count;i++)
	{
		if (label.compare(sound[i].getLabel()) == 0 )
		{
			for (int j = i; j < sound_count - 1; j++)
			{
				sound[j] = sound[j + 1];
				
			}
			sound_count--;
		}
		return 1; // for ok
	}
	return -1; // not found
}

s_Sound *s_ResourceManager::getSound(std::string label)
{
	for (int i = 0; i < sound_count;i++)
	{
		if (label.compare(sound[i].getLabel()) == 0 )
		{
			return &(sound[i]);
		}
	}
	return NULL;
}

int s_ResourceManager::loadMusic(std::string filename, std::string label)
{
	if (music_count = MAX_MUSICS)
	{
		LogManager2::getInstance().writeLog("music array full");
		return 0;
	}

	if (music[music_count].loadMusic(filename) == -1)
	{
		LogManager2::getInstance().writeLog("unable to load music from file");
		return -1;
	}

	music[music_count].setLabel(label);
	music_count++;
	return 1; // 1 for ok
}

int s_ResourceManager::unloadMusic(std::string label)
{
	if (label == "")
	{
		return -2;// don't allow empty string
	}
	for (int i = 0; i <  music_count; i++)
	{
		if (label.compare(music[i].getLabel()) == 0)
		{
			music[i].setLabel("");
			music_count--;
		}
		return 1; // for ok
	}
	return -1; // not found
}

s_Music *s_ResourceManager::getMusic(std::string label)
{
	for (int i = 0; i < music_count; i++)
	{
		if (label.compare(music[i].getLabel()) == 0)
		{
			return &(music[i]);
		}
	}
	return NULL;
}

int df::s_ResourceManager::insertSprite(s_Sprite * p_s)
{
	if (sprite_count < MAX_SPRITES)
	{
		p_sprite[sprite_count] = p_s;
		sprite_count++;
		return 0;   // success
	}
	else return -1;  //full;
}

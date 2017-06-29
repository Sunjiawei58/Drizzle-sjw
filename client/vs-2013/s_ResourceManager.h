#ifndef S_MANAGER_H
#define S_MANAGER_H
#include "s_Manager.h"
#include "s_Sprite.h"
#include "s_Sound.h"
#include "s_Music.h"
#include <iostream>
#include <fstream>
#include <string>
namespace df
{


	const int MAX_SPRITES = 1000;
	const int MAX_SOUNDS = 128;
	const int MAX_MUSICS = 128;

	const std::string FRAMES_TOKEN = "frames";
	const std::string HEIGHT_TOKEN = "height";
	const std::string WIDTH_TOKEN = "width";
	const std::string COLOR_TOKEN = "color";
	const std::string END_FRAME_TOKEN = "end";
	const std::string END_SPRITE_TOKEN = "eof";


	class s_ResourceManager :public s_Manager
	{

	private:
		s_ResourceManager();
		s_ResourceManager(s_ResourceManager const&);
		void operator= (s_ResourceManager const&);
		s_Sprite *p_sprite[MAX_SPRITES];  // error?
		int sprite_count;
		s_Sound	sound[MAX_SOUNDS];
		int sound_count;
		s_Music music[MAX_SOUNDS];
		int music_count;

	public:
		static s_ResourceManager &getInstance();

		int startUp();

		void shutDown();

		int loadSprite(std::string filename, std::string label);

		int unloadSprite(std::string label);

		s_Sprite *getSprite(std::string label)const;

		int loadSound(std::string filename, std::string label);

		int unloadSound(std::string label);

		s_Sound *getSound(std::string label);

		int loadMusic(std::string filename, std::string label);

		int unloadMusic(std::string label);

		s_Music *getMusic(std::string label);
		int insertSprite(s_Sprite* p_s);

	};

	int readLintInt(std::ifstream *p_file, int *p_line_num, const char *tag);
	std::string readLineString(std::ifstream *p_file, int *p_line_num, const char *tag);

	s_Frame readFrame(std::ifstream *p_file, int *p_line_number, int width, int height);

}

#endif;

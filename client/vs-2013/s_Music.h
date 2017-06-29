
#ifndef s_Music_h__
#define s_Music_h__
#include <string>
#include <SFML/Audio.hpp>
namespace df
{
	class s_Music
	{
	private:
		sf::Music music;
		std::string label;
		s_Music(s_Music &const);
		void operator= (s_Music &const);
	public:
		s_Music();
		

		int loadMusic(std::string filename);

		void setLabel(std::string new_label);

		std::string getLabel() const;

		void play(bool loop=true);

		void pause();

	//	void setMusic(sf::Music new_music);
		sf::Music *getMusic();
	};
}
#endif // s_Music_h__


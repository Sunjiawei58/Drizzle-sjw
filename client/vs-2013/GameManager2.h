///
/// The game manager
///

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "s_Manager.h"

#define DF_VERSION 1.s		/// sjw version

namespace df {

	/// Dragonfly cofiguration file.
	const std::string CONFIG_FILENAME = "df-config.txt";

	/// Default frame time (game loop time) in milliseconds (33 ms == 30 f/s).
	const int FRAME_TIME_DEFAULT = 33;

	class GameManager2 : public s_Manager {
		//using s_Manager::startUp; // Remove warning about hidden virtual function.

	private:
		
		GameManager2();                      ///< Private since a singleton.
		GameManager2(GameManager2 const&);   ///< Don't allow copy.
		void operator=(GameManager2 const&); ///< Don't allow assignment.
		bool game_over;           ///< True -> game loop should stop.
		int frame_time;           ///< Target time per game loop, in millisec.
		int step_count;           ///< Count of game loop iterations.

	public:
		/// Get the singleton instance of the GameManager.
		static GameManager2 &getInstance();

		/// Startup all GameManager services.
		int startUp();

		/// Game manager only accepts step events.
		/// Return false if other event.
		bool isValid(std::string event_name) const;

		/// Shut down GameManager services.
		void shutDown();

		/// Run game loop.
		void run();

		/// Set game over status to indicated value.
		/// If true (default), will stop game loop.
		void setGameOver(bool game_over = true);

		/// Get game over status.
		bool getGameOver() const;

		/// Return frame time.  
		/// Frame time is target time for each game loop, in milliseconds.
		int getFrameTime() const;

		/// Return game loop step count.
		int getStepCount() const;
	};

} // end of namespace df
#endif // __GAME_MANAGER_H__


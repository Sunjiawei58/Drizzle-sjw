///
/// Colors for Dragonfly
///

#ifndef __S_COLOR_H__
#define __S_COLOR_H__

namespace df {

	
	enum s_Color {
		BLACK = 0,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
	}; 

	/// If color not specified, will use this.
	const s_Color S_COLOR_DEFAULT = WHITE;

} // end of namespace df
#endif //__COLOR_H__
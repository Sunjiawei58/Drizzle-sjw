///
/// The base manager
///

#ifndef __S_MANAGER_H__
#define __S_MANAGER_H__

// System includes.
#include <string>

// Engine includes.
#include "s_Event.h"
#include "s_Object.h"
#include "ObjectList2.h"

namespace df {

	const int MAX_EVENTS = 100;	      ///< Max number of different events.
	const int MAX_ALTITUDE = 5;

	class s_Manager {

	private:
		std::string type;			 ///< Manager type identifier.
		int event_count;                       ///< Number of events.
		std::string event_name[MAX_EVENTS];	 ///< List of events.      //? when to add the event to the list?
		ObjectList2 obj_list[MAX_EVENTS];       ///< Objects interested in event.
		bool is_started;                       ///< True if startUp() succeeded

		/// Check if event is handled by this Manager.
		/// If handled, return true else false.
		/// (Base Manager always returns false.)
//		virtual bool isValid(std::string event_type) const;

	protected:
		/// Set type identifier of Manager.
		void setType(std::string type);

	public:
		s_Manager();
		virtual ~s_Manager();

		/// Get type identifier of Manager.
		std::string getType() const;

		/// Startup Manager. 
		/// Return 1 if ok, else 0.
		virtual int startUp();

		/// Shutdown Manager.  
		virtual void shutDown();

		/// Return status of is_started (true when startUp() was successful).
		bool isStarted() const;

		/// Send event to all interested Objects.
		/// Return count of number of events sent.
		int onEvent(const s_Event *p_event) const;

		/// Indicate interest in event.
		/// Return 0 if ok, else -1.
		/// (Note, doesn't check to see if Object is already registered.)
		int registerInterest(s_Object *p_o, std::string event_type);

		/// Indicate no more interest in event. 
		/// Return 0 if ok, else -1.
		int unregisterInterest(s_Object *p_o, std::string event_type);

	};

} // end of namespace df
#endif /// __MANAGER_H__

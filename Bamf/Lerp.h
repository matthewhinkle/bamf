//
//  Lerp.h
//  Bamf
//
//  Created by Matthew Hinkle on 2/15/13.
//
//

#ifndef Bamf_Lerp_h
#define Bamf_Lerp_h

namespace bamf {

/**
	Common linear interpolation rountines
 */
class Lerp {
public:

	Lerp() { }
	virtual ~Lerp();
	
	/**
		See game engine gems page 144 for more information
		
		*can be found on google books
	 */
	template<typename T = float, typename U = unsigned>
	static inline T frameRateIndependent(
		T x_0,		/* intial position */
		T x,		/* current position */
		U t,		/* time elapsed since initial position */
		U t_f) {	/* duration of last frame */
		
		return x + t_f * ((x - x_0) * t);
	}
	
private:
	Lerp(const Lerp &);
	Lerp & operator=(const Lerp &);
};

}

#endif

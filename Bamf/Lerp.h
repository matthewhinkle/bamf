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
		Generic linear interpolation
		
		@return the interpolated value between the initial and
				current position
	 */
	template<typename T = float, typename R = float>
	static inline T lerp(
		T x_0,		/* initial position */
		T x,		/* current position */
		R t,		/* time of initial frame */
		R dt) {		/* time delta */
		
		R a = t / dt;
		
		return x * a + x_0 * (1 - a);
	}
	
private:
	Lerp(const Lerp &);
	Lerp & operator=(const Lerp &);
};

}

#endif

/*!
...
*/

#ifndef DRAWCOMPLEX_H_
#define DRAWCOMPLEX_H_

/*!
 * This class allows to connect a state with a draw item.
 *   For example
 *   STATE_STANDING : gif1.gif
 *   STATE_MOVING_RIGHT : gif2.gif
 */
class DrawComplex : public DrawItem
{
	std::map<Uint32, DrawItem*> items;

	public:
        /*!
         * Set state of animation
         */
		void setState(Uint32 aNewState);
        /*!
         * returns state of animation
         */
		Uint32 getState();
};

#endif // DRAWCOMPLEX_H_

#ifndef PATH_SMOOTH_H
#define PATH_SMOOTH_H

#include <Trackable.h>

class Path;
class Node;

//comment this out to remove path smoothing
//#define SMOOTH_PATH 117

class PathSmooth : public Trackable
{
	private:
		const int mNO_NEED_TO_SMOOTH = 2,
				  mRAY_ITERATORS = 50;
	public:
		PathSmooth();
		~PathSmooth();
		Path* smoothPath(Path* pathToSmooth);
		bool clearPathRaycast(Node* startCastNode, Node* nextNode);

};

#endif // !PATH_SMOOTH_H

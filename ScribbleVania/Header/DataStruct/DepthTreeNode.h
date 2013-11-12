#include "../GameObject/GameObject.h"
#include <vector>
class DepthTreeNode
{
public:
	DepthTreeNode(float depth, unsigned int ID);
	~DepthTreeNode();
	std::vector<unsigned int> objectIDs;
	DepthTreeNode *back;
	DepthTreeNode *front;
	void AddToNode(float depth, unsigned int ID);
	void Remove(float depth, unsigned int ID);
protected:
private:
	float _depth;
};
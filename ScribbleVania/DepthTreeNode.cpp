#include "DepthTreeNode.h"

DepthTreeNode::DepthTreeNode(float depth, unsigned int ID)
{
	this->_depth = depth;
	objectIDs.push_back(ID);
}

DepthTreeNode::~DepthTreeNode()
{
	objectIDs.clear();
	SAFE_DELETE(back);
	SAFE_DELETE(front);
}

void DepthTreeNode::AddToNode(float depth, unsigned int ID)
{
	if(this->_depth > depth)
	{
		if(back == NULL)
		{
			back = new DepthTreeNode(depth, ID);
		}
		else
		{
			back->AddToNode(depth, ID);
		}
	}
	else if (this->_depth < depth)
	{
		if(front == NULL)
		{
			front = new DepthTreeNode(depth, ID);
		}
		else
		{
			front->AddToNode(depth, ID);
		}
	}
	else
	{
		if(objectIDs.size() == 0)
		{
			objectIDs.push_back(ID);
		}
		else
		{
			std::vector<unsigned int>::iterator it;
			for(it = objectIDs.begin(); it!= objectIDs.end();it++)
			{
				if(*it <= ID)
				{
					break;
				}
			}
			objectIDs.insert(it,ID);
		}
	}
}

void DepthTreeNode::Remove(float depth, unsigned int ID)
{
	if(this->_depth > depth)
	{
		this->back->Remove(depth,ID);
	}
	else if (this->_depth < depth)
	{
		this->front->Remove(depth,ID);
	}
	else
	{
		for(unsigned int i=0; i < objectIDs.size(); i++)
		{
			if(objectIDs[i]==ID)
			{
				objectIDs.erase(objectIDs.begin()+i);
				break;
			}
		}
	}
}
#include "../../Header/DataStruct/DepthTreeNode.h"

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
			std::vector<unsigned int>::iterator it = objectIDs.begin();
			int i;
			for (i=objectIDs.size(); i>0; i--)
			{
				if(objectIDs[i-1] <=ID)
				{
					break;
				}
			}
			it = it+(i-1);
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
		/*for(std::vector<unsigned int>::iterator it = objectIDs.begin(); it != objectIDs.end(); ++it)
		{
			if(*it==ID)
			{
				objectIDs.erase(it);
				break;
			}
		}*/
		std::vector<unsigned int>::iterator it = objectIDs.begin();
		int low=0;
		int high=objectIDs.size()-1;
		int mid;

		while(low<=high)
		{
			mid = low+((high-low)/2);
			if(objectIDs[mid] > ID)
			{
				high = mid-1;
			}
			else if (objectIDs[mid]<ID)
			{
				low = mid+1;
			}
			else
			{
				it = it+mid;
				objectIDs.erase(it);
				return;
			}
		}
		//not found, nothing to remove
	}
}
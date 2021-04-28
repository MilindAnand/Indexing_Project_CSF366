#include<bits/stdc++.h>
using namespace std;

#define MAXorder 6

struct key_addr
{
	int key, addr;
	key_addr() {}
	key_addr(int _key, int _addr)
	{
		key = _key;
		addr = _addr;
	}
};

typedef struct key_addr kas;

struct ret_struct
{
	int key, addr, ht;
	ret_struct() {}
	ret_struct(kas k, int height)
	{
		key = k.key;
		addr = k.addr;
		ht = height;
	}
	ret_struct(int k, int a, int h)
	{
		key = k;
		addr = a;
		ht = h;
	}
};

typedef struct ret_struct ret;

class Node{
private:
	kas* vals;
	int size;
	Node** pointers;
	int order;
	bool isLeaf;
	friend class BPTree;

public:
	Node() 
	{
		vals = new kas[MAXorder];
		pointers = new Node*[MAXorder+1];
	}

	void display()
	{
		cout<<"||";
		for (int i = 0; i < size; i++)
		{
			cout<<vals[i].key<<" ";
		}
		cout<<"||";
	}
};

class BPTree{
private:
	Node* root;

public:
	BPTree(){
		root = NULL;
	}
	ret search(int _key);
	void BPinsert(int _key, int _addr);
	void insertInternal(kas val, Node* cursor, Node* child);
	Node* getParent(Node* cursor, Node* child);
	void remove(int _key, int _addr);
};

ret BPTree::search(int _key)
{
	// cout<<"Inside search\n\n";
	if(root == NULL)
	{
		ret res(-1, -1, 0);
		cout<<"Empty Tree";
		return res;
	}
	Node *cursor = root;
	int height = 0;
	//cout<<"Key: "<<_key<<endl;
	while(!(cursor->isLeaf))
	{
		for (int i = 0; i < cursor->size; ++i)
		{
			// cout<<"Key: "<<_key<<endl;
			// cout<<"Curr val: "<<cursor->vals[i].key<<endl;
			// cout<<"Before if\n\n";
			if(_key < (cursor->vals[i].key))
			{
				// cout<<"Inside if\n\n";
				cursor = cursor->pointers[i];
				height++;
				break;
			}
			if(i == (cursor->size-1))
			{
				// cout<<"Inside else\n\n";
				cursor = cursor->pointers[i+1];
				height++;
				break;
			}
		}
		// if(!(cursor->isLeaf))
		// 	cout<<"No more leaf\n";
		//cout<<"Height: "<<height<<endl;
	}
	for (int i = 0; i < cursor->size; ++i)
	{
		// cout<<"Inside for, Curr val: "<<cursor->vals[i].key<<endl;
		if(cursor->vals[i].key == _key)
		{
			return ret(cursor->vals[i], height);
		}
		else if(i == cursor->size-1)
		{
			return ret(cursor->vals[i], height);
		}
		else if(cursor->vals[i].key < _key && _key < cursor->vals[i+1].key)
		{
			return ret(cursor->vals[i], height);
		}
	}

}

void BPTree::BPinsert(int _key, int _addr)
{
	// cout<<"Inside BPinsert\n\n";
	if(root==NULL)
	{
		// cout<<"Inside if\n\n";
		root = new Node();
		kas x(_key, _addr);
		root->isLeaf = true;
		root->size = 1;
		root->vals[0] = x;
	}
	else
	{	
		// cout<<"Inside else\n\n";
		Node* cursor = root;
		Node* parent = NULL;
		while(!(cursor->isLeaf))
		{
			// cout<<"Inside while\n\n";
			parent = cursor;
			for (int i = 0; i < cursor->size; ++i)
			{
				// cout<<"Inside for\n\n";
				if (_key < cursor->vals[i].key)
				{
					// cout<<"Inside first for if \n\n";
					cursor = cursor->pointers[i];
					break;
				}
				if (i == cursor->size - 1)
				{
					// cout<<"Inside second for if \n\n";
					cursor = cursor->pointers[i+1];
					break;
				}
				// cout<<"Outside for ifs\n\n";
			}
			// cout<<"Outside for\n\n";
		}
		// cout<<"Outside while \n\n";

		if (cursor->size < MAXorder)
		{
			// cout<<"Inside if\n\n";
			int pos=0;
			while(_key > cursor->vals[pos].key && pos < cursor->size)
				pos++;
			kas x(_key, _addr);
			for (int i = cursor->size; i > pos; i--)
			{
				cursor->vals[i] = cursor->vals[i-1];
			}
			cursor->vals[pos] = x;
			cursor->size += 1;
			cursor->pointers[cursor->size] = cursor->pointers[cursor->size - 1];
			cursor->pointers[cursor->size - 1] = NULL;
		}
		else
		{
			// cout<<"Inside else\n\n";
			Node *newLeaf = new Node();
			// cout<<"After new\n\n";
			kas tempNode[MAXorder+1];
			for (int i = 0; i < MAXorder; i++)
			{
				tempNode[i] = cursor->vals[i];
			}

			int pos=0;
			// cout<<"Before while\n\n";
			while(_key > tempNode[pos].key && pos < MAXorder)
				pos++;
			kas x(_key, _addr);
			for (int i = MAXorder+1; i > pos; i--)
			{
				tempNode[i] = tempNode[i-1];
			}
			// cout<<"afteer tempnode for\n\n";
			tempNode[pos] = x;
			newLeaf->isLeaf = true;
			cursor->size = (MAXorder+1)/2;
			newLeaf->size = MAXorder - (MAXorder+1)/2;
			cursor->pointers[cursor->size] = newLeaf;
			newLeaf->pointers[newLeaf->size] = cursor->pointers[MAXorder];
			cursor->pointers[MAXorder] = NULL;
			// cout<<"Aftyer pointer stuff\n\n";
			for(int i = 0; i < cursor->size; i++)
			{
				cursor->vals[i] = tempNode[i];
			}

			for(int i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
			{
				newLeaf->vals[i] = tempNode[j];
			}
			// cout<<"After fors\n\n";
			if(cursor == root)
			{
				// cout<<"Inside lolif\n\n";
				Node* newRoot = new Node();
				newRoot->vals[0] = newLeaf->vals[0];
				// cout<<"After vals[0]\n\n";
				newRoot->pointers[0] = cursor;
				newRoot->pointers[1] = newLeaf;
				// cout<<"Safe after?\n\n";
				newRoot->isLeaf = false;
				newRoot->size = 1;
				root = newRoot;
			}
			else
			{
				// cout<<"Calling insert internal\n\n";
				insertInternal(newLeaf->vals[0], parent, newLeaf);
			}
			// cout<<"After ifelse1\n\n";
		}
		// cout<<"After ifelse2\n\n";
	}
	// cout<<"After ifelse3\n\n";
}

void BPTree::insertInternal(kas val, Node* cursor, Node* child)
{
	// cout<<"Inside insert Internal\n\n";
	int _key = val.key;
	int _addr = val.addr;
	if(cursor->size < MAXorder)
	{
		// cout<<"Inside if\n\n";
		int pos=0;
		while(_key > cursor->vals[pos].key && pos < cursor->size)
			pos++;
		kas x(_key, _addr);
		for (int i = cursor->size; i > pos; i--)
		{
			cursor->vals[i] = cursor->vals[i-1];
			cursor->pointers[i+1] = cursor->pointers[i];
		}
		cursor->vals[pos] = x;
		cursor->pointers[pos+1] = child;
		cursor->size += 1;
	}
	else
	{
		// cout<<"Inside else\n\n";
		Node* newInternal = new Node();
		// cout<<"After new\n\n";
		kas tempVals[MAXorder+1];
		Node* tempPtrs[MAXorder+2];
		for(int i = 0; i < MAXorder; i++)
		{
			tempVals[i] = cursor->vals[i];
			tempPtrs[i] = cursor->pointers[i];
		}
		tempPtrs[MAXorder] = cursor->pointers[MAXorder];
		int pos=0;
		// cout<<"Before ehilwsdhfj\n\n";
		while(_key > tempVals[pos].key && pos < MAXorder)
				pos++;
		for (int i = MAXorder+1; i > pos; i--)
		{
			tempVals[i] = tempVals[i-1];
			tempPtrs[i+1] = tempPtrs[i];
		}
		kas x(_key, _addr);
		tempVals[pos] = x;
		tempPtrs[pos+1] = child;

		newInternal->isLeaf = false;
		cursor->size = (MAXorder+1)/2;
		newInternal->size = MAXorder-(MAXorder+1)/2;
		
		for(int i = 0, j = cursor->size+1; i < newInternal->size; i++, j++)
		{
			newInternal->vals[i] = tempVals[j];
		}
		for(int i = 0, j = cursor->size+1; i < newInternal->size+1; i++, j++)
		{
			newInternal->pointers[i] = tempPtrs[j];
		}

		if(cursor == root)
		{
			// cout<<"Inside lelif\n\n";
			Node* newRoot = new Node;
			newRoot->vals[0] = cursor->vals[cursor->size];
			newRoot->pointers[0] = cursor;
			newRoot->pointers[1] = newInternal;
			newRoot->isLeaf = false;
			newRoot->size = 1;
			root = newRoot;
		}
		else
		{
			// cout<<"Inside lel else\n\n";
			insertInternal(cursor->vals[cursor->size], getParent(root, cursor), newInternal);
		}
	}
}

Node* BPTree::getParent(Node* cursor, Node* child)
{
	// cout<<"Inside getparent\n\n";
	Node* parent = NULL;
	//cout<<"Before if par\n\n";
	if(cursor->isLeaf || (cursor->pointers[0])->isLeaf)
	{
		//cout<<"Inside if lala\n\n";
		return NULL;
	}
	for (int i = 0; i < cursor->size + 1; ++i)
	{
		//cout<<"Inside for\n\n";
		if(cursor->pointers[i] == child)
		{
			//cout<<"Inside if kek\n\n";
			parent = cursor;
			return parent;
		}
		else
		{
			//cout<<"Inside else kek\n\n";
			parent = getParent(cursor->pointers[i], child);
			if (parent != NULL)
			{
				return parent;
			}
		}
	}
	return parent;
}
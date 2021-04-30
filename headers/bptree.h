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
	bool isLeaf;
	friend class BPTree;

public:
	Node() 
	{
		vals = new kas[MAXorder];
		pointers = new Node*[MAXorder+1];
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
};

ret BPTree::search(int _key)
{
	if(root == NULL)
	{
		ret res(-1, -1, 0);
		cout<<"Empty Tree";
		return res;
	}
	Node *cursor = root;
	int height = 0;
	while(!(cursor->isLeaf))
	{
		for (int i = 0; i < cursor->size; ++i)
		{
			// cout<<"Key: "<<_key<<endl;
			// cout<<"Curr val: "<<cursor->vals[i].key<<endl;
			if(_key < (cursor->vals[i].key))
			{
				cursor = cursor->pointers[i];
				height++;
				break;
			}
			if(i == (cursor->size-1))
			{
				cursor = cursor->pointers[i+1];
				height++;
				break;
			}
		}
		//cout<<"Height: "<<height<<endl;
	}
	for (int i = 0; i < cursor->size; ++i)
	{
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
	if(root==NULL)
	{
		root = new Node();
		kas x(_key, _addr);
		root->isLeaf = true;
		root->size = 1;
		root->vals[0] = x;
	}
	else
	{
		Node* cursor = root;
		Node* parent = NULL;
		while(!(cursor->isLeaf))
		{
			parent = cursor;
			for (int i = 0; i < cursor->size; ++i)
			{
				if (_key < cursor->vals[i].key)
				{
					cursor = cursor->pointers[i];
					break;
				}
				if (i == cursor->size - 1)
				{
					cursor = cursor->pointers[i+1];
					break;
				}
			}
		}

		if (cursor->size < MAXorder)
		{
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
			Node *newLeaf = new Node();
			kas tempNode[MAXorder+1];
			for (int i = 0; i < MAXorder; i++)
			{
				tempNode[i] = cursor->vals[i];
			}

			int pos=0;
			while(_key > tempNode[pos].key && pos < MAXorder)
				pos++;
			kas x(_key, _addr);
			for (int i = MAXorder+1; i > pos; i--)
			{
				tempNode[i] = tempNode[i-1];
			}
			tempNode[pos] = x;
			newLeaf->isLeaf = true;
			cursor->size = (MAXorder+1)/2;
			newLeaf->size = MAXorder - (MAXorder+1)/2;
			cursor->pointers[cursor->size] = newLeaf;
			newLeaf->pointers[newLeaf->size] = cursor->pointers[MAXorder];
			cursor->pointers[MAXorder] = NULL;
			for(int i = 0; i < cursor->size; i++)
			{
				cursor->vals[i] = tempNode[i];
			}

			for(int i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
			{
				newLeaf->vals[i] = tempNode[j];
			}
			if(cursor == root)
			{
				Node* newRoot = new Node();
				newRoot->vals[0] = newLeaf->vals[0];
				newRoot->pointers[0] = cursor;
				newRoot->pointers[1] = newLeaf;
				newRoot->isLeaf = false;
				newRoot->size = 1;
				root = newRoot;
			}
			else
			{
				insertInternal(newLeaf->vals[0], parent, newLeaf);
			}
		}
	}
}

void BPTree::insertInternal(kas val, Node* cursor, Node* child)
{
	int _key = val.key;
	int _addr = val.addr;
	if(cursor->size < MAXorder)
	{
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
		Node* newInternal = new Node();
		kas tempVals[MAXorder+1];
		Node* tempPtrs[MAXorder+2];
		for(int i = 0; i < MAXorder; i++)
		{
			tempVals[i] = cursor->vals[i];
			tempPtrs[i] = cursor->pointers[i];
		}
		tempPtrs[MAXorder] = cursor->pointers[MAXorder];
		int pos=0;
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
			insertInternal(cursor->vals[cursor->size], getParent(root, cursor), newInternal);
		}
	}
}

Node* BPTree::getParent(Node* cursor, Node* child)
{
	Node* parent = NULL;
	if(cursor->isLeaf || (cursor->pointers[0])->isLeaf)
	{
		return NULL;
	}
	for (int i = 0; i < cursor->size + 1; ++i)
	{
		if(cursor->pointers[i] == child)
		{
			parent = cursor;
			return parent;
		}
		else
		{
			parent = getParent(cursor->pointers[i], child);
			if (parent != NULL)
			{
				return parent;
			}
		}
	}
	return parent;
}
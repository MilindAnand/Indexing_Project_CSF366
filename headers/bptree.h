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

class Node{
private:
	vector<kas> vals;
	vector<Node*> pointers;
	int order;
	bool isLeaf;
	friend class BPTree;

public:
	Node() {}

	Node(int _order, bool leaf)
	{
		order = _order;
		vals.resize(order);
		vals.clear();
		//cout<<"Inside Node decln\n\n";
		pointers.resize(_order+1);
		pointers.clear();
		//cout<<"Post resize\n\n";
		for (int i = 0; i < _order+1; ++i)
		{
			pointers.push_back(NULL);
		}
		//cout<<"Before isLeaf\n\n";
		isLeaf = leaf;
		//cout<<"Good init\n\n";
		//*parent = NULL;
	}

};

class BPTree{
private:
	Node* root;

public:
	BPTree(){
		root = NULL;
	}
	kas search(int _key);
	void BPinsert(int _key, int _addr);
	void insertInternal(kas val, Node* cursor, Node* child);
	Node* getParent(Node* cursor, Node* child);
	void remove(int _key, int _addr);
};

kas BPTree::search(int _key)
{
	if(root == NULL)
	{
		kas res(-1, -1);
		cout<<"Empty Tree";
		return res;
	}
	Node *cursor = root;
	while(!(cursor->isLeaf))
	{
		for (int i = 0; i < cursor->vals.size(); ++i)
		{
			if(_key < cursor->vals[i].key)
			{
				cursor = cursor->pointers[i];
				break;
			}
			if(i == cursor->vals.size()-1)
			{
				cursor = cursor->pointers[i+1];
				break;
			}
		}
	}
	for (int i = 0; i < cursor->vals.size(); ++i)
	{
		if(cursor->vals[i].key == _key)
		{
			return cursor->vals[i];
		}
		else if(i == cursor->vals.size()-1)
		{
			return cursor->vals[i];
		}
		else if(cursor->vals[i].key < _key && _key < cursor->vals[i+1].key)
		{
			return cursor->vals[i];
		}
	}

}

void BPTree::BPinsert(int _key, int _addr)
{
	if(root==NULL)
	{
		root = new Node(MAXorder, true);
		kas x(_key, _addr);
		root->vals.push_back(x);
	}
	else
	{
		Node* cursor = root;
		Node* parent = NULL;
		while(!(cursor->isLeaf))
		{
			parent = cursor;
			for (int i = 0; i < cursor->vals.size(); ++i)
			{
				if (_key < cursor->vals[i].key)
				{
					cursor = cursor->pointers[i];
					break;
				}
				if (i == cursor->vals.size() - 1)
				{
					cursor = cursor->pointers[i+1];
					break;
				}
			}
		}

		if (cursor->vals.size() < MAXorder)
		{
			int pos=0;
			while(_key > cursor->vals[pos].key && pos < cursor->vals.size())
				pos++;
			kas x(_key, _addr);
			cursor->vals.insert(cursor->vals.begin() + pos, x);
			int size = cursor->vals.size();
			cursor->pointers[size] = cursor->pointers[size - 1];
			cursor->pointers[size - 1] = NULL;
		}
		else
		{
			//cout<<"Inside overflow sfgpart\n";
			//cout<<"Before node decln\n\n";
			Node *newLeaf = new Node(MAXorder, true);
			//cout<<"Before vector decln\n\n";
			vector<kas> modvec(cursor->vals);
			//cout<<"After vec devln\n\n";
			int pos=0;
			while(_key > modvec[pos].key && pos < modvec.size())
				pos++;
			//cout<<"After while\n\n";
			kas x(_key, _addr);
			//cout<<"Before insert\n\n"<<cursor->vals.size()<<" "<<pos<<"\n\n";
			modvec.insert(modvec.begin() + pos, x);
			//cout<<"After mid\n\n";
			int mid = (MAXorder+1)/2;
			cursor->pointers[mid] = newLeaf;
			newLeaf->pointers[MAXorder + 1 - mid] = cursor->pointers[MAXorder];
			cursor->pointers[MAXorder] = NULL;
			cursor->vals.clear();
			vector<kas> temp1(modvec.begin(), modvec.begin() + mid);
			cursor->vals = temp1;
			vector<kas> temp2(modvec.begin() + mid, modvec.end());
			newLeaf->vals = temp2;
			if(cursor == root)
			{
				Node* newRoot = new Node(MAXorder, false);
				newRoot->vals.push_back(newLeaf->vals[0]);
				newRoot->pointers[0] = cursor;
				newRoot->pointers[1] = newLeaf;
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
	if(cursor->vals.size() < MAXorder)
	{
		int pos=0;
		while(_key > cursor->vals[pos].key && pos < cursor->vals.size())
			pos++;
		kas x(_key, _addr);
		cursor->vals.insert(cursor->vals.begin() + pos, x);
		cursor->pointers[pos+1] = child;
	}
	else
	{
		Node* newInternal = new Node(MAXorder, false);
		vector<kas> modkeys(cursor->vals);
		vector<Node*> modNodes(cursor->pointers);
		int pos=0;
		while(_key > modkeys[pos].key && pos < modkeys.size())
				pos++;
		kas x(_key, _addr);
		modkeys.insert(modkeys.begin() + pos, x);
		modNodes.insert(modNodes.begin() + pos + 1, child);
		int mid = (MAXorder + 1)/2;
		cursor->vals.clear();
		cursor->pointers.clear();
		vector<kas> temp1(modkeys.begin(), modkeys.begin() + mid);
		cursor->vals = temp1;
		vector<Node*> temp2(modNodes.begin(), modNodes.begin() + mid);
		cursor->pointers = temp2;
		vector<kas> temp3(modkeys.begin() + mid, modkeys.end());
		newInternal->vals = temp3;
		vector<Node*> temp4(modNodes.begin() + mid, modNodes.end());
		newInternal->pointers = temp4;

		if(cursor==root)
		{
			Node* newRoot = new Node(MAXorder, false);
			newRoot->vals.push_back(newInternal->vals[0]);
			newRoot->pointers[0] = cursor;
			newRoot->pointers[1] = newInternal;
			root = newRoot;
		}
		else
		{
			insertInternal(newInternal->vals[0], getParent(root, cursor), newInternal);
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
	for (int i = 0; i < cursor->vals.size() + 1; ++i)
	{
		if(cursor->pointers[i] == child)
		{
			parent = cursor;
			break;
		}
		else
		{
			getParent(cursor->pointers[i], child);
			if (parent != NULL)
			{
				return parent;
			}
		}
	}
	return parent;
}
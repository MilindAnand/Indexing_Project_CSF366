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

	// Node(int _order, bool leaf)
	// {
	// 	isLeaf = leaf;
	// 	order = _order;
	// 	vals.resize(order);
	// 	vals.clear();
	// 	pointers.resize(_order+1);
	// 	pointers.clear();
	// 	for (int i = 0; i < _order+1; ++i)
	// 	{
	// 		pointers.push_back(NULL);
	// 	}
	// }

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
	kas search(int _key);
	void BPinsert(int _key, int _addr);
	void insertInternal(kas val, Node* cursor, Node* child);
	Node* getParent(Node* cursor, Node* child);
	void remove(int _key, int _addr);
	void printBPT();
};

kas BPTree::search(int _key)
{
	// cout<<"Inside search\n\n";
	if(root == NULL)
	{
		kas res(-1, -1);
		cout<<"Empty Tree";
		return res;
	}
	Node *cursor = root;
	//int height = 0;
	//cout<<"Key: "<<_key<<endl;
	while(!(cursor->isLeaf))
	{
		for (int i = 0; i < cursor->size; ++i)
		{
			//cout<<"vals size: "<<cursor->vals.size()<<endl; 
			//cout<<"ptrs size: "<<cursor->pointers.size()<<endl; 
			cout<<"Key: "<<_key<<endl;
			cout<<"Curr val: "<<cursor->vals[i].key<<endl;
			// cout<<"Before if\n\n";
			if(_key < (cursor->vals[i].key))
			{
				// cout<<"Inside if\n\n";
				cursor = cursor->pointers[i];
				//height++;
				break;
			}
			if(i == (cursor->size-1))
			{
				// cout<<"Inside else\n\n";
				cursor = cursor->pointers[i+1];
				//height++;
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
			return cursor->vals[i];
		}
		else if(i == cursor->size-1)
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
			//int flag = 0;
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
					//if(cursor->pointers[i+1] != NULL)
						cursor = cursor->pointers[i+1];
					//else 
					//	flag = 1;
					break;
				}
				// cout<<"Outside for ifs\n\n";
			}
			// cout<<"Outside for\n\n";

			//if(flag)
			 	// break;

			//cout<<"Cursor is LEaf:\n\n "<<cursor->isLeaf<<"\n\n";

			//cout<<"Random string\n\n\n\n";
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
			//cursor->vals.insert(cursor->vals.begin() + pos, x);
			cursor->size += 1;
			cursor->pointers[cursor->size] = cursor->pointers[cursor->size - 1];
			cursor->pointers[cursor->size - 1] = NULL;
		}
		else
		{
			// cout<<"Inside else\n\n";
			//cout<<"Random\n\n";
			//printf("\n");
			Node *newLeaf = new Node();
			// cout<<"After new\n\n";
			kas tempNode[MAXorder+1];
			for (int i = 0; i < MAXorder; i++)
			{
				tempNode[i] = cursor->vals[i];
			}
			
			//vector<kas> modvec(cursor->vals);
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
				//if cursor is a root node, we create a new root
				Node* newRoot = new Node();
				newRoot->vals[0] = newLeaf->vals[0];
				// cout<<"After vals[0]\n\n";
				newRoot->pointers[0] = cursor;
				newRoot->pointers[1] = newLeaf;
				// cout<<"Safe after?\n\n";
				newRoot->isLeaf = false;
				newRoot->size = 1;
				root = newRoot;
				// cout<<"Created new root\n\n";
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
		// cursor->vals.insert(cursor->vals.begin() + pos, x);
		// cursor->pointers[pos+1] = child;
	}
	else
	{
		// cout<<"Inside else\n\n";
		//printf("\n");
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
		// vector<kas> modkeys(cursor->vals);
		// vector<Node*> modNodes(cursor->pointers);
		//cout<<"Sizes: "<<modkeys.size()<<" "<<modNodes.size()<<"\n\n";
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
			//if cursor is a root node, we create a new root
			Node* newRoot = new Node;
			newRoot->vals[0] = cursor->vals[cursor->size];
			newRoot->pointers[0] = cursor;
			newRoot->pointers[1] = newInternal;
			newRoot->isLeaf = false;
			newRoot->size = 1;
			root = newRoot;
			//cout<<"Created new root\n";
		}
		else
		{
			// cout<<"Inside lel else\n\n";
			insertInternal(cursor->vals[cursor->size], getParent(root, cursor), newInternal);
		}

		// bool flag1 = false;
		// if(pos == modkeys.size())
		// 	flag1 = true;
		// //cout<<val.key<<"\n\n";
		// //cout<<"modNodes first time:\n\n";
		// //int count = 0;
		// // for(Node* i : modNodes){
		// // 	cout<<count<<"\n\n";
		// // 	count++;
		// // 	for(kas j : i->vals)
		// // 		cout<<"balnk:\n\n "<<j.key<<"\n\n";
		// // }
		// if(!flag1)
		// {
		// 	modkeys.insert(modkeys.begin() + pos, x);
		// 	modNodes.insert(modNodes.begin() + pos + 1, child);
		// }
		// else
		// {
		// 	modkeys.push_back(x);
		// 	modNodes.push_back(child);
		// }
		// //count = 0;
		// // cout<<"modNodes second time:\n\n";
		// // for(Node* i : modNodes){
		// // 	cout<<count<<"\n\n";
		// // 	count++;
		// // 	for(kas j : i->vals)
		// // 		cout<<"balnk:\n\n "<<j.key<<"\n\n";
		// // }
		// int mid = (MAXorder + 1)/2, nodemid = (modNodes.size() + 1) / 2;
		// cursor->vals.clear();
		// cursor->pointers.clear();
		// //cout<<"Before vecskasfgdj\n\n";
		// vector<kas> temp1(modkeys.begin(), modkeys.begin() + mid);
		// cursor->vals = temp1;
		// //cout<<"First quart of vecs\n\n";
		// vector<Node*> temp2(modNodes.begin(), modNodes.begin() + nodemid);
		// //cout<<"Before pointers\n\n";
		// cursor->pointers = temp2;
		// //cout<<"Half of vecs\n\n";
		// vector<kas> temp3(modkeys.begin() + mid, modkeys.end());
		// newInternal->vals = temp3;
		// //cout<<"Mid: "<<modNodes.end() - modNodes.begin() - mid<<" Size: "<<modNodes.size()<<"\n\n";
		// //cout<<"Last quart of vecs\n\n";
		// //cout<<"Random\n\n";
		// vector<Node*> temp4(modNodes.begin() + nodemid, modNodes.end());
		// //cout<<"After vec line\n\n";
		// newInternal->pointers = temp4;
		// //cout<<"Before if\n\n";
		// if(cursor==root)
		// {
		// 	//cout<<"Insidesdgf if\n\n";
		// 	//printf("\n");
		// 	Node* newRoot = new Node(MAXorder, false);
		// 	newRoot->vals.push_back(newInternal->vals[0]);
		// 	newRoot->pointers[0] = cursor;
		// 	newRoot->pointers[1] = newInternal;
		// 	root = newRoot;
		// }
		// else
		// {
		// 	//cout<<"Inside dkfjelse\n\n";
		// 	auto par = getParent(root, cursor);
		// 	//cout<<"After getpar\n\n";
		// 	insertInternal(newInternal->vals[0], par, newInternal);
		// 	//cout<<"After call\n\n";
		// }
	}
}

Node* BPTree::getParent(Node* cursor, Node* child)
{
	// cout<<"Inside getparent\n\n";
	Node* parent = NULL;
	//cout<<"Before if par\n\n";
	//cout<<"Trial1: "<<cursor->isLeaf <<"\n\n";
	//cout<<"Trial2: "<<(cursor->pointers[0])->isLeaf <<"\n\n";
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

void BPTree::printBPT()
{
	// cout<<"Before if\n\n";
	// if(root == NULL)
	// {
	// 	cout<<"Empty Tree";
	// 	return;
	// }
	// queue<Node*> q;
	// deque<int> numch;
	// cout<<"After if\n\n";
	// q.push(root);
	// numch.push_back(1);
	// while(!q.empty())
	// {
	// 	//cout<<"Inside while\n\n";
	// 	Node *temp = q.front();
	// 	temp->display();
	// 	//cout<<"Temp vals size: "<<temp->vals.size()<<"  Temp ptrs size: "<<temp->pointers.size()<<endl;
	// 	for (int i = 0; i < temp->pointers.size(); i++)
	// 	 {
	// 		if(temp->pointers[i] == NULL)
	// 			continue;
	// 		else
	// 	 		q.push(temp->pointers[i]);
	// 	}
	// 	numch.push_back(temp->pointers.size());
	// 	q.pop();
	// 	int tp = numch.front()-1;
	// 	numch.pop_front();
	// 	numch.push_front(tp);
	// 	if(numch.front() == 0)
	// 	{
	// 		cout<<"\n\n";
	// 		numch.pop_front();
	// 	}
	// }
}
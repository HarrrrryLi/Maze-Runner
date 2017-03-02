#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
	bHeap = NULL;
	size = 0;
}

BinaryHeap::BinaryHeap(Node x)
{
	bHeap = new Node[1];
	bHeap[0] = x;
	size = 1;
}

bool BinaryHeap::is_empty()
{
	if (bHeap == NULL)
		return true;
	else
		return false;
}

bool BinaryHeap::insert(Node x,bool gs)
{
	if (is_empty())
	{
		bHeap = new Node[1];
		size++;
		bHeap[0] = x;
	}
	else
	{
		Node *temp = bHeap;
		bHeap = new Node[size + 1];
		for (int cnt = 0; cnt < size; cnt++)
			bHeap[cnt] = temp[cnt];
		bHeap[size] = x;
		size++;
		delete[] temp;
	}
	if (gs == 1)
		sort_gs();
	else
		sort_gl();
	return true;
}

bool BinaryHeap::remove(Node x,bool gs)
{
	if (is_empty())
		return false;
	else
	{	
		int p = FindbyPosition(x.get_position());
		if (p==-1)
			return false;
		Node temp = bHeap[p];
		bHeap[p] = bHeap[size - 1];
		bHeap[size - 1] = temp;
		size--;
		if (size == 0)
			bHeap = NULL;
		else 
		{
			Node *temp1 = bHeap;
			bHeap = new Node[size];
			for (int cnt = 0; cnt < size; cnt++)
				bHeap[cnt] = temp1[cnt];
			if (gs == 1)
				sort_gs();
			else
				sort_gl();
			delete[] temp1;
		}
		return true;
	}
}

bool BinaryHeap::remove(int index,bool gs)
{
	if (is_empty())
		return false;
	else
	{
		Node temp = bHeap[index];
		bHeap[index] = bHeap[size - 1];
		bHeap[size - 1] = temp;
		size--;
		if (size == 0)
			bHeap = NULL;
		else
		{
			Node *temp1 = bHeap;
			bHeap = new Node[size];
			for (int cnt = 0; cnt < size; cnt++)
				bHeap[cnt] = temp1[cnt];
			if (gs == 1)
				sort_gs();
			else
				sort_gl();
			delete[] temp1;
		}
		return true;
	}
}

bool BinaryHeap::sort_gs()
{
	if (is_empty())
		return false;
	else
	{
		for (int cnt = size-1; cnt >= 0; cnt--)
		{
			if ((cnt - 1)/2 >= 0 && bHeap[cnt].get_f() < bHeap[(cnt - 1) / 2].get_f() ||(bHeap[cnt].get_f() == bHeap[(cnt - 1) / 2].get_f() && bHeap[cnt].get_g()<= bHeap[(cnt - 1) / 2].get_g()))
			{
				Node temp = bHeap[cnt];
				bHeap[cnt] = bHeap[(cnt - 1) / 2];
				bHeap[(cnt - 1) / 2] = temp;
			}
		}
		return true;
	}

}

bool BinaryHeap::sort_gl()
{
	if (is_empty())
		return false;
	else
	{
		for (int cnt = size - 1; cnt >= 0; cnt--)
		{
			if ((cnt - 1) / 2 >= 0 && bHeap[cnt].get_f() < bHeap[(cnt - 1) / 2].get_f() || (bHeap[cnt].get_f() == bHeap[(cnt - 1) / 2].get_f() && bHeap[cnt].get_g()>= bHeap[(cnt - 1) / 2].get_g()))
			{
				Node temp = bHeap[cnt];
				bHeap[cnt] = bHeap[(cnt - 1) / 2];
				bHeap[(cnt - 1) / 2] = temp;
			}
		}
		return true;
	}

}


Node BinaryHeap::peekTop()
{
	return *bHeap;
}

void BinaryHeap::clear()
{
	delete[] bHeap;
	size = 0;
	bHeap = NULL;
}

int BinaryHeap::getHeight()
{
	return ceil(log2(size));
}

int BinaryHeap::getNodeNumber()
{
	return size;
}

int BinaryHeap::FindbyPosition(pair<int, int> p)
{
	int cnt;
	for(cnt=0;cnt<size;cnt++)
		if (bHeap[cnt].get_position() == p)
			break;
	if (cnt == size)
		return -1;
	else
		return cnt;
}

Node BinaryHeap::extractMin()
{
	if (is_empty()) 
	{
		Node x;
		x.set_f(-1);
		return x;
	}
	else
		return peekTop();
}

Node::Node()
{
	f = g = h = h_new = 0;
	search = 0;
	obsevered = false;
}

int Node::get_f()
{
	return f;
}

int Node::get_g()
{
	return g;
}

int Node::get_h()
{
	return h;
}

int Node::get_h_new()
{
	return h_new;
}

void Node::set_f(int s)
{
	f = s;
}

void Node::set_g(int s)
{
	g = s;
}

void Node::set_h(int s)
{
	h = s;
}

void Node::set_h_new(int s)
{
	h_new = s;
}

void Node::update_f()
{
	f = g + h;
}

pair<int, int> Node::get_position()
{
	return position;
}

void Node::set_position(pair<int, int> p)
{
	position = p;
}

int Node::get_search()
{
	return search;
}

void Node::set_search(int s)
{
	search = s;
}

void Node::set_from(pair<int, int> p)
{
	from = p;
}

void Node::set_observe()
{
	obsevered = true;
}

void Node::clear_observe()
{
	obsevered = false;
}

bool Node::get_observe()
{
	return obsevered;
}

pair<int, int> Node::get_from()
{
	return from;
}

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

//循环队列  memcpy  realloc
class Queue
{
public:
	Queue(int size = 5)
	{
		_pQue = new int[size];
		_front = _rear = 0;
		_size = size;
	}
	//Queue(const Queue&) = delete;
	//Queue& operator=(const Queue&) = delete;
	Queue(const Queue &src)
	{
		_size = src._size;
		_front = src._front;
		_rear = src._rear;
		_pQue = new int[_size];
		for (int i = _front; 
			i != _rear; 
			i = (i + 1) % _size)
		{
			_pQue[i] = src._pQue[i];
		}
	}
	Queue& operator=(const Queue &src)
	{
		if (this == &src)
			return *this;

		delete[]_pQue;

		_size = src._size;
		_front = src._front;
		_rear = src._rear;
		_pQue = new int[_size];
		for (int i = _front;
			i != _rear;
			i = (i + 1) % _size)
		{
			_pQue[i] = src._pQue[i];
		}
		return *this;
	}
	~Queue()
	{
		delete[]_pQue;
		_pQue = nullptr;
	}
	void push(int val) // 入队操作
	{
		if (full())
			resize(); // 扩容
		_pQue[_rear] = val;
		_rear = (_rear + 1) % _size;
	}
	void pop() // 出队操作
	{
		if (empty())
			return;
		_front = (_front + 1) % _size;
	}
	int front() // 获取队头元素
	{
		return _pQue[_front];
	}
	bool full() { return (_rear + 1) % _size == _front; }
	bool empty() { return _front == _rear; }
private: 
	int *_pQue; // 申请队列的数组空间
	int _front; // 指示队头的位置
	int _rear;  // 指示队尾的位置
	int _size;  // 队列扩容的总大小

	void resize()
	{
		int *ptmp = new int[2 * _size];
		int index = 0;
		for (int i = _front;
			i != _rear;
			i = (i + 1) % _size) // 扩容后,把front遍历到rear一个一个重新按照第0位置存放
		{
			ptmp[index++] = _pQue[i];
		}
		delete[]_pQue;
		_pQue = ptmp;
		_front = 0;
		_rear = index;
		_size *= 2; // 队列总大小指示值也要变大
	}
};
int main()
{
	Queue queue;
	for (int i = 0; i < 20; ++i)
	{
		queue.push(rand() % 100);
	}

	while (!queue.empty())
	{
		cout << queue.front() << " ";
		queue.pop();
	}
	cout << endl;

	Queue queue1 = queue; // 拷贝构造
	queue1 = queue; // 赋值构造

	return 0;
}
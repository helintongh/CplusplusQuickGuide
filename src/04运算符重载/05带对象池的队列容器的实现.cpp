/*** 
 * @Author: helintongh
 * @Date: 2020-08-29 16:57:50
 * @LastEditTime: 2020-08-29 22:17:09
 * @LastEditors: helintongh
 * @Description: 
 * @FilePath: /hlt/运算符重载/带对象池的队列容器的实现.cpp
 */
#include <iostream>
using namespace std;
/*
运算符的重载：成员方法、全局方法
内存池  进程池  线程池  连接池  对象池
*/
template<typename T>
class Queue
{
public:
	Queue()
	{
		_front = _rear = new QueueItem();
	}
	~Queue()
	{
		QueueItem *cur = _front; // 指向当前队首
		while (cur != nullptr) // 从当前开始删除
		{
			_front = _front->_next; // 记录后一个节点
			delete cur; // 删除当前节点
			cur = _front; // 当前指向下一个待删节点
		}
	}
	void push(const T &val) // 入队操作
	{
		QueueItem *item = new QueueItem(val); // malloc
		_rear->_next = item; // 队尾指针指向新的节点
		_rear = item;       // 队尾指向item
	}
	void pop()
	{
		if (empty())
			return;
		QueueItem *first = _front->_next;
		_front->_next = first->_next;
		if (_front->_next == nullptr)
		{
			_rear = _front;
		}
		delete first; // free
	}
	T front()const
	{
		return _front->_next->_data; // 返回数据
	}
	bool empty()const { return _front == _rear; } // 队首==队尾时队列为空
private:
	// 产生一个QueueItem的对象池（10000个QueueItem节点）
	struct QueueItem 
	{
		QueueItem(T data = T()) :_data(data), _next(nullptr) {} // T类型可以适配多种类型,默认构造
		//给QueueItem提供自定义内存管理
		void* operator new(size_t size) // 不加static也是静态方法，因为下面的new和delete函数使用的时候对象都不存在
		{
			if (_itemPool == nullptr)
			{
				_itemPool = (QueueItem*)new char[POOL_ITEM_SIZE*sizeof(QueueItem)]; // 按字节开辟大小
				// 开辟过后需要把申请出来的对象连在一起
                QueueItem *p = _itemPool; // 数组首地址
				for (; p < _itemPool + POOL_ITEM_SIZE - 1; ++p)
				{
					p->_next = p + 1; // 当前节点的next域指向下一个节点地址
				}
				p->_next = nullptr; // 最后一个节点的next域指向null
			}

			QueueItem *p = _itemPool; // p等于对象池首节点,p暴露给外部
			_itemPool = _itemPool->_next; // 因为首节点p暴露给外部了,首节点指向下一个
			return p; // 返回指针p
		}
		void operator delete(void *ptr) // 归还到对象池,把要delete的节点加到池子里即可
		{
			QueueItem *p = (QueueItem*)ptr;
			p->_next = _itemPool;
			_itemPool = p;
		}
		T _data; // 数据域
		QueueItem *_next; // 指向下一个节点的指针域
		static QueueItem *_itemPool;
		static const int POOL_ITEM_SIZE = 100000; // 对象池节点个数
	};

	QueueItem *_front; // 指向头节点  
	QueueItem *_rear;  // 指向队尾
};

template<typename T>
typename Queue<T>::QueueItem *Queue<T>::QueueItem::_itemPool = nullptr; // typename告诉编译器是QueueItem类型
// 这句话有点难理解,其实可理解通过int *i = nullptr;去理解  
// Queue<T>::QueueItem相当于例子中的int
// *Queue<T>::QueueItem::_itemPool相当于 *i

int main()
{
	Queue<int> que;
	for (int i = 0; i < 1000000; ++i)
	{
        // 短时间内大量调用malloc和free
		que.push(i); // QueueItem(i)
		que.pop(); // QueueItem
	}
	cout << que.empty() << endl;

	return 0;
}
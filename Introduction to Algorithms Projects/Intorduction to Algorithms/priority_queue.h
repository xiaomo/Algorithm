//////////////////////////////////////////////////////////////////////////
/// @file		priority_queue.h
/// @brief		���ȶ���
/// @details	COPYRIGHT NOTICE
///			    Copyright (c) 2011
///			    All rights reserved.\n
///			    ʵ����һ�����ȶ���
///
/// @author		̷����	chuanqi.tan(at)gmail.com
/// @date		2011-5-25
/// @version	1.0
//////////////////////////////////////////////////////////////////////////
/// �޸ļ�¼��
/// 2010/6/17	1.0	̷����	����

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
using namespace std;

namespace ita
{
	/// @brief ���ȶ���
	///
	/// �ѵ���ҪӦ��֮һ�����ȶ��С�\n
	/// ���ȼ���ߵ�Ԫ���ڶ��ף�������Ԫ�������ڡ��Ƚ��ӡ������ͷ�ѵ����ʡ�
	/// @param	ItemType		������Ԫ�ص�����
	/// @param	Comparator		���ڱȽ϶�����Ԫ�����ȼ��ıȽ���
	/// @param	ContainerType	���ȶ����ڲ���ʹ�õ���������
	/// @see	void MakeHeap(vector<int> &, size_t , size_t)
	/// @see	void BuildHeap(vector<int> &)
	/// @note	�����ж��е�Ԫ��һ�������뵽������ȥ�˾Ͳ�Ӧ�����޸ģ����ڶ����е�Ԫ��Ӧ��ֻ֧��Top, Pop, Push����
	template <
		typename ItemType,
		typename Comparator = less<ItemType>,
		typename ContainerType = vector<ItemType >>
	class PriorityQueue
	{
	public:
		typedef PriorityQueue<ItemType, Comparator, ContainerType>	_MyType;
		typedef	ItemType &			Reference;
		typedef ItemType const &	ConstReference;

		/// ����һ���յ����ȶ���
		PriorityQueue()
		{}

		/// ��һ�������ʼ��һ�����ȶ���
		template<typename IterType>
		PriorityQueue( IterType begin, IterType end ) : _queue( begin, end )
		{
			make_heap( _queue.begin(), _queue.end(), _comparator );
		}

		/// ����������һ��Ԫ��
		void Push( ItemType const &item )
		{
			_queue.push_back( item );
			push_heap( _queue.begin(), _queue.end(), _comparator );
		}

		/// @brief ����const�Ķ���Ԫ��
		/// @return		���ȼ���ߵĶ���Ԫ�ص�const����
		ConstReference Top() const
		{
			return *_queue.begin();
		}

		/// @brief ���ʷ�const�Ķ���Ԫ��
		///
		/// �ڱ�׼STL�����ȶ���ʵ�����������const��������������Ϊ��Ӧ���������������Ϊ�����Ļ�����ͨ�������const�������޸�Top Item�����ȼ������������жӾͿ��ܲ��پ���һ�����ˣ�\n
		/// �����Ҫ�ı����ȼ���Ӧ��ʹ��RefreshQueue����ܵķ���
		/// @return		���ȼ���ߵĶ���Ԫ�ص�<b>��const</b>����
		/// @see	void RefreshQueue()
		/// @deprecated		<b>����޸��˶���Ԫ�ص����ȼ��������������ȶ����ڲ��Ĳ�һ����</b>
		Reference Top()
		{
			return *_queue.begin();
		}

		/// ���׵�Ԫ�س���
		void Pop()
		{
			pop_heap( _queue.begin(), _queue.end(), _comparator );
			_queue.pop_back();
		}

		/// ��ѯ�����Ƿ�Ϊ��
		bool IsEmpty()
		{
			return _queue.empty();
		}

		/// @brief �������������ж��е�Ԫ��
		///
		/// ��������ǳ���Ҫ�������������֮�������жӾͿ���֧���޸����ȼ��Ĳ����ˡ�
		/// @code
		/// auto comparator = [](ItemType *item1, ItemType *item2){return item1->Priority() < item2->Priority();};
		/// PriorityQueue<ItemType *, comparator> q;
		/// items[6]->SetPriority(66);		//�ӱ𴦸ı���ĳ��Ԫ�ص����ȼ�
		/// q.RefreshQueue();				//һ��Ҫ�ǵõ���RefreshQueue������������Ԫ�ص����ȼ����ⲿ�޸�֮�����ȶ��е��ڲ�״̬����һ�£�		///
		/// @endcode
		void RefreshQueue()
		{
			make_heap( _queue.begin(), _queue.end(), _comparator );
		}

		/// �����������е�Ԫ����ʾ���������
		void Display()
		{
			copy( _queue.begin(), _queue.end(), ostream_iterator<ItemType>( cout, "  " ) );
			cout << endl;
		}

	private:
		ContainerType			_queue;			///< ����
		Comparator				_comparator;	///< �Ƚ���
	};

}
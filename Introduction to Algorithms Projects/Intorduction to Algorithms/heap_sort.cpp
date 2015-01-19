//////////////////////////////////////////////////////////////////////////
/// @file		heap_sort.cpp
/// @brief		�ѵ�ʹ���������
/// @details	COPYRIGHT NOTICE
///			    Copyright (c) 2011
///			    All rights reserved.\n
///
///
/// @author		̷����	chuanqi.tan(at)gmail.com
/// @date		2011/06/17
/// @version	1.0
//////////////////////////////////////////////////////////////////////////
/// �޸ļ�¼��
/// 2011/06/17   10:18	1.0	̷����	����


#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "priority_queue.h"
using namespace std;

namespace ita
{


	/// @brief ���ֶѵ�����
	///
	/// ��to_make��[0,length)Ԫ����Ϊһ����ȫ���������Ե�i��Ԫ��Ϊ�����������˵�i��Ԫ��֮�ⶼ�����ѵ�����
	/// ���ô˷���֮�������ȫ�������Ե�i��Ԫ��Ϊ���������������ѵ�����
	/// @param	to_make		�������ݵ�����
	/// @param	length		���to_make��[0,length)Ԫ����Ϊһ����ȫ������<br/>
	///						��length��Ԫ��֮��[length, n)��Ԫ�ز������������ȫ��������
	/// @param	i			��Ҫ����ĵ�i��Ԫ��
	/// @note				to_make��ǰlength��Ԫ�ز���һ����һ���ѣ���Ϊ���������ѵ����ʣ���������ӳ��Ϊ��ȫ������
	void MakeHeap( vector<int> &to_make, size_t length, size_t i )
	{
		size_t left = 2 * i + 1;
		size_t right = 2 * i + 2;
		size_t the_max = i;

		if ( left < length && to_make[left] > to_make[i] )
		{
			the_max = left;
		}
		if ( right < length && to_make[right] > to_make[the_max] )
		{
			the_max = right;
		}

		if ( the_max != i )
		{
			std::swap( to_make[i], to_make[the_max] );
			MakeHeap( to_make, length, the_max );
		}
	}

	/// @brief ����
	///
	/// ��to_built����Ľ���һ����ͷ��
	void BuildHeap( vector<int> &to_built )
	{
		//����ֻ��Ҫ��to_built.size() / 2 - 1��ʼ��ԭ�����ڣ�
		//��Ҷ�ӽ����˵�����������ӽ�㣨Ϊ�գ���������ѵĶ���ģ�����ֻ��Ҫ�����Ҷ�ӽ��
		for ( int i = to_built.size() / 2 - 1; i >= 0; --i )
		{
			MakeHeap( to_built, to_built.size(), i );
		}
	}

	/// ������
	void HeapSort( vector<int> &to_sort )
	{
		BuildHeap( to_sort );
		for ( int i = to_sort.size() - 1; i > 0; --i )
		{
			std::swap( to_sort[0], to_sort[i] );
			MakeHeap( to_sort, i, 0 );
		}
	}

	/// ���� �����������ȶ��� ��ʵ��
	int testHeapSort()
	{
		int to_init[] = {8, 5, 78, 45, 64, 987, 45, 34, 23, 4, 23};
		vector<int> to_sort( to_init, to_init + sizeof( to_init ) / sizeof( int ) );
		cout << "ԭʼ���飬׼�����ж�����";
		copy( to_sort.begin(), to_sort.end(), ostream_iterator<int>( cout, "  " ) );
		HeapSort( to_sort );
		cout << endl << "�����������";
		copy( to_sort.begin(), to_sort.end(), ostream_iterator<int>( cout, "  " ) );
		cout << endl << endl;

		cout << "��ʼ��һ�����ȶ��У�";
		PriorityQueue<int, greater<int>> queue;
		for ( int i = 0; i < 10; ++i )
		{
			queue.Push( rand() % 1000 );
		}
		queue.Display();

		cout << "��ʼ���ϵ�ȡ������ȼ���������У�" << endl;
		while( !queue.IsEmpty() )
		{
			cout << queue.Top() << ":\t";
			queue.Pop();
			queue.Display();
		}

		cout << "��ʼ����������У�" << endl;
		for ( size_t i = 0; i < to_sort.size(); ++i )
		{
			queue.Push( to_sort[i] );
			queue.Display();
		}

		queue.Display();

		return 0;
	}

}
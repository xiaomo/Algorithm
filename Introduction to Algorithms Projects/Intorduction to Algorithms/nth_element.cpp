//////////////////////////////////////////////////////////////////////////
/// @file		nth_element.cpp
/// @brief		��λ����˳��ͳ��ѧ
/// @details	COPYRIGHT NOTICE
///			    Copyright (c) 2011
///			    All rights reserved.\n
///			    ��O(n)��ʱ����Ѱ��һ�������еĵ�i��˳��ͳ����\n
///				��i��˳��ͳ�����Ķ���Ϊ���ü����е�iС��Ԫ��\n
///				����������ʱ��ѡ��˳��ͳ�����ķ������Կ�������Ϊģ�͡���ͬ�ڿ���������һ�������㷨��˼��Ҳ��
///				������������еݹ黮�֡����Ϳ�������ͬ���ǣ����������ݹ鴦���ֵ����ߣ���randomized-select
///				ֻ�����ֵ�һ�ߡ����ɴ˽�����������ʱ����O(nlgn)�½�����O(n)��
///
/// @author		̷����	chuanqi.tan(at)gmail.com
/// @date		2011/06/17
/// @version	1.0
//////////////////////////////////////////////////////////////////////////
/// �޸ļ�¼��
/// 2011/06/17   12:31	1.0	̷����	����


#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

namespace ita
{
	namespace
	{

		/// Ѱ��v������Ӽ�[begin_index, end_index]�еĵ�i��Ԫ��˳��ͳ������0 <= i < end_index-begin_index
		int _NthElement( vector<int> &v, int const begin_index, int const end_index, int const n )
		{
			//����жϴ���ֻ��һ������return�ļ��ɣ�û������ж��㷨Ҳ����ȷ�ģ�
			if ( begin_index == end_index )
			{
				return v[begin_index];
			}

			//���ȡ��
			int swap_index = rand() % ( end_index - begin_index + 1 ) + begin_index;
			swap( v[swap_index], v[end_index] );

			//�������һ����Ԫ���зָ��������
			int i = begin_index;
			for ( int j = begin_index; j < end_index; ++j )
			{
				if ( v[j] < v[end_index] )
				{
					swap( v[i++], v[j] );
				}
			}
			swap( v[i], v[end_index] );

			//��Ԫ�Ǳ�����ĵ�k��Ԫ��˳��ͳ������0<=k<size
			int k = i - begin_index;

			if ( n == k )
			{
				//�ҵ���
				return v[i];
			}
			if ( n < k )
			{
				//�������������
				return _NthElement( v, begin_index, i - 1, n );
			}
			else
			{
				//������������ң�������Ԫ�ǵ�k��Ԫ��˳��ͳ����(0<=k<size)������С�ڵ�����Ԫ��Ԫ����k+1����������Ԫ�������Ѱ��������ĵ�n-(k+1)��˳��ͳ����
				return _NthElement( v, i + 1, end_index, n - k - 1 );
			}
		}

	}

	/// @brief Ѱ��v�����еĵ�i��˳��ͳ������0<=i<size
	///
	/// �Կ�������Ϊģ�͡���ͬ�ڿ���������һ�������㷨��˼��Ҳ��
	///	������������еݹ黮�֡����Ϳ�������ͬ���ǣ����������ݹ鴦���ֵ����ߣ���randomized-select
	///	ֻ�����ֵ�һ�ߡ����ɴ˽�����������ʱ����O(nlgn)�½�����O(n)��
	/// @param	v	Ҫ���в��Ҳ����ļ���
	/// @param	i	���Ҽ����еĵ�i��˳��ͳ����
	/// @return		�����еĵ�i��˳��ͳ����
	/// @see	int _NthElement(vector<int> &v, int const begin_index, int const end_index, int const n)
	int NthElement( vector<int> &v, int const i )
	{
		return _NthElement( v, 0, v.size() - 1, i );
	}

	/// ��λ����˳��ͳ��ѧ
	int testNthElement()
	{
		vector<int> v;
		for ( int i = 0; i < 10; ++i )
		{
			v.push_back( ( rand() % 1000 ) );
		}
		copy( v.begin(), v.end(), ostream_iterator<int>( cout, "  " ) );
		cout << endl;

		for ( int i = 0; i < 10; ++i )
		{
			cout << i << "th element is:" << NthElement( v, i ) << endl;
		}

		return 0;
	}
}
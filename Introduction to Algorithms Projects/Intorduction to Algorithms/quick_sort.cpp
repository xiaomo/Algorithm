//////////////////////////////////////////////////////////////////////////
/// @file		quick_sort.cpp
/// @brief		��������
/// @details	COPYRIGHT NOTICE
///			    Copyright (c) 2011
///			    All rights reserved.\n
///			    ʵ���˿��������㷨�Լ����㷨���ۡ�7-6��ġ���ģ������Ŀ�������
///
/// @author		̷����	chuanqi.tan(at)gmail.com
/// @date		2011/06/17
/// @version	1.0
//////////////////////////////////////////////////////////////////////////
/// �޸ļ�¼��
/// 2011/06/17   10:30	1.0	̷����	����


#include <vector>
#include <iostream>
#include <iterator>
#include <ctime>
#include <algorithm>
using namespace std;

namespace ita
{

	/// @brief ���������ȡ�������Ŀ�������
	///
	/// ���������ƽ��Ч��ΪO(nlgn)������ΪO(n^2)
	void QuickSort( vector<int> &ToSort, int BeginIndex, int EndIndex )
	{
		if( BeginIndex < EndIndex )
		{
			//�������ȡ�������������
			//һ��Ҫʹ�ã���ƽ�����ܵ���������̫����
			int random_swap = ( rand() % ( EndIndex - BeginIndex + 1 ) ) + BeginIndex;
			std::swap( ToSort[random_swap], ToSort[EndIndex] );

			//i������Ǳ�ToSort[EndIndex]С��Ԫ�ص��Ͻ磬��ToSort[BeginIndex,i)��Ԫ��ֵ����ToSort[EndIndex]ҪС
			//Ҳ��ζ����һ����ToSort[EndIndex]С��Ԫ��Ҫ���õ�λ�ã������ڵ�ǰ����ToSort[i] >= ToSort[EndIndex]
			int i = BeginIndex;

			//j�����Ѿ�������Ԫ�ص��Ͻ�
			for ( int j = BeginIndex; j != EndIndex; ++j )
			{
				//�ҵ������ToSort[EndIndex]С��Ԫ��
				if ( ToSort[j] < ToSort[EndIndex] )
				{
					swap( ToSort[i], ToSort[j] );	//�������ToSort[EndIndex]С��Ԫ���Ƶ���i��ȥ,������i���������
					++i;							//�������ҵ���һ����ToSort[EndIndex]С��Ԫ��,�����Ͻ�Ӧ��+1
				}
			}
			swap( ToSort[i], ToSort[EndIndex] );

			QuickSort( ToSort, BeginIndex, i - 1 );
			QuickSort( ToSort, i + 1, EndIndex );
		}
	}


	/// @brief ��ģ������Ŀ�������
	///
	/// ���������� ���㷨����7-6�⣩\n
	/// ����������һ���������⣬���޷�׼ȷ��֪��������ĸ������ֵ����Ƕ��١��������е�ÿ�����֣�
	/// ����ֻ֪��������ʵ���ϵ�ĳ�������ڡ��༴����������n������[a(i), b(i)]�ı����䣨����С��
	/// �����±�����ã���ͬ��������a(i) <= b(i)���㷨��Ŀ���Ƕ���Щ�������ģ������
	/// ��fuzzy-sort�����༴�������������һ������<i(1), i(2), ..., i(n)>��ʹ�ô���һ��c(j)����
	/// ����[a(i(j)), b(i(j))]������c(1) <= c(2) <= c(3) <= ... <= c(n)�� :\n
	/// -   Ϊn�������ģ���������һ���㷨������㷨Ӧ�þ����㷨��һ��ṹ�������Կ���������
	///		�˵㣨����a(i)����ҲҪ�ܳ�������ص���������������ʱ�䡣�����Ÿ������ص���Խ��Խ�࣬
	///		�Ը��������ģ��������������Խ��Խ���ס�����㷨Ӧ�ܳ�����������ص����� \n
	/// -   ֤������һ������£�����㷨����������ʱ��Ϊ��(nlgn)���������е����䶼�ص�ʱ��������
	///		����ʱ��Ϊ��(n)���༴��������һ��ֵx��ʹ�ö����е�i������x��[a(i), b(i)]��������㷨
	///		��Ӧ��ʽ�ؼ���������������Ӧ�����ص��������ӣ�������Ȼ���������ơ�
	void SmoothQuickSort( vector< pair<int, int> > &to_sort, int begin_index, int end_index )
	{
		if ( begin_index < end_index )
		{
			//ȡ���һ������Ϊ��Ԫ
			auto principal = to_sort[end_index];
			//��ȡҪ�Ƚϵ����䣨��ȥ��Ԫ��Ϊ[begin_index, end_index) => [i,j]
			//����[i,j]��˼�ǣ��������е�Ԫ��Ҫ����δ����Ҫ���໥�ص�������һ���ص�ֵ�����Ҹ�ֵ����to_sort[end_index]�ص�
			//������Ŀ�й涨����������to_sort[end_index]�������
			int i = begin_index;
			int j = end_index - 1;

			for ( int k = begin_index; k <= j; )	//kΪ��ǰ���ڴ����Ԫ��
			{
				if ( to_sort[k].second <= principal.first )
				{
					//�ϸ�С����Ԫ
					swap( to_sort[i], to_sort[k] );
					++i;
					++k;
				}
				else if ( to_sort[k].first >= principal.second )
				{
					//�ϸ������Ԫ
					swap( to_sort[j], to_sort[k] );
					--j;
				}
				else
				{
					// ����Ԫ�������ص����������ԪΪ�ص����䣨������
					// �˷����ο��� http://blogold.chinaunix.net/u/18517/showart_487873.html
					//
					// �����뷨��ĺã���Ϊ��С����Ԫ�����䣨�����������ԾͿ�����Ϊ�Ժ��κ�����С֮����Ԫ���ص�
					// �����䶼һ���뵱ǰ����to_sort[k]�ص�����Ϊ����ȫ������С�����Ԫ��\n
					// ��������Ϳ���ȷ�������[i,j]�е�����Ԫ���ڱ����Լ��������Ԫ������ȣ������е�Ԫ���໥
					// �ص��������Բ���Ҫ�ٴ�����ͷ�������Ŀ�еġ���������ص���������������ʱ�䡱\n
					// ���û���ⲽ��С���䣬��ֻ����Ϊ[i,j]�е�Ԫ�ظ�������Ԫ���ص����޷��ж�Ϊ������ȡ�
					// @note	���������Ū���һ���ǣ������ص���û�д����ԣ��ص������Ԫ�ز�������Ϊ�������
					principal.first = max( to_sort[k].first, principal.first );
					principal.second = min( to_sort[k].second, principal.second );
					++k;
				}
			}
			swap( to_sort[j + 1], to_sort[end_index] );

			SmoothQuickSort( to_sort, begin_index, i - 1 );
			SmoothQuickSort( to_sort, j + 2, end_index );
		}
	}

	/// ���Կ�������Ͷ�ģ������Ŀ�������
	int testQuickSort()
	{
		cout << "==========================��������=============================" << endl;
		vector<int> ToSort;
		for ( int i = 0; i < 100; ++i )
		{
			ToSort.push_back( rand() );
		}
		cout << "������100������" << endl;
		copy( ToSort.begin(), ToSort.end(), ostream_iterator<int>( cout, "  " ) );
		QuickSort( ToSort, 0, ToSort.size() - 1 );
		cout << endl << "��������Ľ�����£�" << endl;
		copy( ToSort.begin(), ToSort.end(), ostream_iterator<int>( cout, "  " ) );

		cout << endl << "======================ģ������Ŀ�������=========================" << endl;
		vector< pair<int, int> > to_sort_smooth;
		for ( int i = 0; i < 10; ++i )
		{
			int b = rand() % 100;
			to_sort_smooth.push_back( make_pair( b, b + rand() % 100 ) );
		}
		SmoothQuickSort( to_sort_smooth, 0, to_sort_smooth.size() - 1 );
		for_each( to_sort_smooth.begin(), to_sort_smooth.end(), []( pair<int, int> &p )
		{
			cout << p.first << "\t --> \t" << p.second << endl;
		} );

		return 0;
	}

}
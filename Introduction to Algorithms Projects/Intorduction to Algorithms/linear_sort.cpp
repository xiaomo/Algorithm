//////////////////////////////////////////////////////////////////////////
/// @file		linear_sort.cpp
/// @brief		����ʱ�������㷨
/// @details	COPYRIGHT NOTICE
///			    Copyright (c) 2011
///			    All rights reserved.\n
///			    ʵ����3���ܹ�������ʱ���ڽ��н���������㷨���������򡢻�������Ͱ����\n
///				���Ƕ���<b>�ǱȽ�</b>�������㷨��\n
///				���е�����ʱ���ڵ������㷨����������һ���ļ��裬�ǽ�����һ���ļ�������ϵġ�
///
/// @author		̷����	chuanqi.tan(at)gmail.com
/// @date		2011/06/17
/// @version	1.0
//////////////////////////////////////////////////////////////////////////
/// �޸ļ�¼��
/// 2011/06/17   11:15	1.0	̷����	����


#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

namespace ita
{
	/// @brief ��������
	///
	/// ���������˼���ǣ��ٶ����е�Ԫ�ض�����[0, k_max_size)���䣬Ȼ����n��ʱ����ͳ�����е�Ԫ�صĸ�����\n
	/// ������ЩԪ�صĸ�����Ϣ֮�󣬾Ϳ����ع������ǵ��������ˡ�\n
	/// ���������������
	/// - ���������һ����Ҫ�Ծ��������ȶ��������㷨������ȶ����ǻ�������Ļ�ʯ��
	/// - ����������뷨��ĺܼ򵥡���Ч���ɿ�
	/// - ȱ�����ڣ�
	///		-# ��Ҫ�ܶ����Ŀռ䣨��ǰ���͵�ֵ�ķ�Χ��
	///		-# ֻ�ܶ���ɢ��������Ч����int��double�Ͳ����ˣ�
	///		-# ���ڼ��裺������С��Χ�ڵ��������ɵġ�
	void CountingSort()
	{
		int const k_max_size = 100;		//�����������Ԫ�ض�����λ������[0, k_max_size)
		//��ʼ������Ϊ[0, k_max_size)֮����������Ϊ����
		std::vector<int> v;
		for ( int i = 0; i < 100; ++i )
		{
			v.push_back( rand() % k_max_size );
		}

		//���м��� c[i] = j������i�����������г�����j��
		std::vector<int> c( k_max_size, 0 );
		std::for_each( v.begin(), v.end(), [&]( int i )
		{
			++c[i];
		} );

		//�����еļ����������ܽ���������򣬲�û��ʹ��ԭ���ϵķ���
		//�����ϵ��㷨��ֱ�ӣ��������ϳ���һ����Ч������ͬ���Ľ���ʱ�临�Ӷȵģ��ƺ����õ㡣
		v.clear();
		for ( int i = 0; i < k_max_size; ++i )
		{
			for ( int k = 0; k < c[i]; ++k )
			{
				v.push_back( i );
			}
		}

		copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, "  " ) );
	}

	namespace{

		/// ��������ʱֵ����ά����k_max_dim = 3��ζ��Ԫ�ص�����Ϊ[0, 999]
		int const k_max_dim = 3;

	}

	/// @brief ��������
	///
	/// ����������ǰ��մӵ�λ����λ��˳������ѡȡ�������Ԫ�أ�Ȼ�����ȶ���ǰ���·�����һ������֮�У��ͷ��˿��ƺ����ơ�
	/// - ��������ʱ��ÿһά���е����������㷨ʱҪ������������㷨�������ȶ��ġ�
	/// - ����������ֱ���෴�����ǰ��մӵ�λ����λ��˳������ġ�\n
	///   �Ҿ���ԭ�����ڣ�����Чλ�Ե���Чλ���ž����Ե����á�
	/// @note	���������ڲ���ʹ�õ��������㷨�������ȶ���
	/// @see		k_max_dim
	void RadixSort( std::vector<int> &v, int dim )
	{
		//���ݵ�dimά�Ĵ�С���С��ȶ������������stable����Ҫ���ǻ�������Ļ�ʯ
		stable_sort( v.begin(), v.end(), [&]( int left, int right ) -> bool
		{
			//�õ�һ������ĳһά��ֵ
			//eg:	GetDim(987, 1) = 9
			//		GetDim(987, 2) = 8
			//		GetDim(987, 3) = 7
			auto GetDim = []( int number, int d ) -> int
			{
				for ( int i = 1; i <= k_max_dim - d; ++i )
				{
					number /= 10;
				}
				return number % 10;
			};
			return GetDim( left, dim ) < GetDim( right, dim );
		} );

		if ( dim > 1 )
		{
			RadixSort( v, dim - 1 );
		}
	}

	/// ���������㷨�ĳ�ʼ���͵���
	void RadixSortCaller()
	{
		//��ʼ��[0,999]֮����������Ϊ����
		std::vector<int> v;
		for ( int i = 0; i < 10; ++i )
		{
			v.push_back( rand() % static_cast<int>( pow( 10.0, static_cast<double>( k_max_dim ) ) ) );
		}
		std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, "  " ) );
		std::cout << std::endl;

		RadixSort( v, k_max_dim );
		std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, "  " ) );
	}

	/// @brief Ͱ����
	///
	/// Ͱ������㷨���裺
	/// - ����Ͱ���������е�Ԫ�ط��뵽��Ӧ��Ͱ��ȥ��\n
	///	  ���磨0.21  0.45  0.24  0.72  0.7  0.29  0.77  0.73  0.97  0.12���������ǵ�С������1λ�����뵽��Ӧ��10��Ͱ��ȥ
	/// - ��ÿһ��Ͱ���Ԫ�ؽ�������\n
	///   �������Ͱ2��������2��Ԫ��0.21, 0,24�� �����ǽ��к��ڲ�����
	/// - ���ΰ�ÿ��Ͱ�е�Ԫ����ȡ�����������һ��\n
	///   �õ����Ľ����0.12  0.21  0.24  0.29  0.45  0.7  0.72  0.73  0.77  0.97��
	///
	/// Ͱ����Ҳֻ����������ʱ���ܴﵽ���ԣ���������������������ʱ��ȡ�������ڲ�ʹ�õ��������㷨������ʱ�䣬һ��ΪO(nlgn)��
	/// - Ͱ������ڼ��裺����ĵ�Ԫ�ؾ��ȵķֲ�������[0, 1]�ϡ�
	/// - �о�Ͱ��û��ʲô���ʵ�ּ�ֵ����Ϊ���޶�����������䣬��Ҫ������Ǿ��ȷֲ����������������á�
	void BucketSort()
	{
		//��ʼ��[0,1)֮��������
		vector<double> v;
		for ( int i = 0; i < 10; ++i )
		{
			v.push_back( ( rand() % 100 ) * 1.0 / 100.0 );
		}
		copy( v.begin(), v.end(), ostream_iterator<double>( cout, "  " ) );
		cout << endl;

		//����Ͱ���������е�Ԫ�ط��뵽��Ӧ��Ͱ��ȥ
		vector< vector<double> > bucket( 10 );	//10��Ͱ
		for_each( v.begin(), v.end(), [&]( double d )
		{
			bucket[d * 10].push_back( d );
		} );

		//��ÿһ��Ͱ���Ԫ�ؽ�������
		for_each( bucket.begin(), bucket.end(), []( vector<double> &sub_v )
		{
			sort( sub_v.begin(), sub_v.end() );
		} );

		//���ΰ�ÿ��Ͱ�е�Ԫ����ȡ�����������һ��
		v.clear();
		for_each( bucket.begin(), bucket.end(), [&]( vector<double> &sub_v )
		{
			v.insert( v.end(), sub_v.begin(), sub_v.end() );
		} );

		copy( v.begin(), v.end(), ostream_iterator<double>( cout, "  " ) );
	}

	/// ���Լ������� �������� Ͱ����
	int testLinearSort()
	{
		cout << endl << "===========��ʼ��������===========" << endl;
		CountingSort();
		cout << endl << "===========��ʼ��������===========" << endl;
		RadixSortCaller();
		cout << endl << "===========��ʼͰ����===========" << endl;
		BucketSort();

		getchar();
		return 0;
	}
}
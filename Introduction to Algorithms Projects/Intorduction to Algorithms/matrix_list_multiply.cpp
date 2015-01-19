//////////////////////////////////////////////////////////////////////////
/// @file		matrix_list_multiply.cpp
/// @brief		�������˷�����
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
/// 2011/06/17   15:01	1.0	̷����	����



#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
#include <fstream>
using namespace std;

namespace ita
{
    namespace
    {
        void Print( vector< vector<int> > const &pos, int i, int j )
        {
            if ( i  == j )
            {
                cout << "A" << i;
            }
            else
            {
                cout << "(";
                Print( pos, i, pos[i][j] );
                Print( pos, pos[i][j] + 1, j );
                cout << ")";
            }
        }
    }

    /// @brief �������˷�����
    ///
    /// ����n������{A1,A2,...,An},����Ai��Ai+1�ǿɳ˵ģ�i=1,2,...n-1������Ҫ������n����������˻���
    /// ���ھ���ĳ˷��������ɣ�����ͨ�������ſ���ʹ�ü����������˻�����಻ͬ�ļ������Ȼ�����ò�ͬ�ļ����ŷ�ʽ������Ҫ���ܼ������ǲ�һ���ġ�
    /// �ڼ���������˻�ʱ����ͬ�ļ����ŷ�ʽ�����µĲ�ͬ�ļ���Լ������кܴ��Ӱ�졣���ȷ������������˻�A1A2��...,An��һ���������ʹ�����˴������������˻���Ҫ�����˴������ٱ��Ϊһ�����⡣
    void MatrixListMultiply()
    {
        int maxtix_length[] = {30, 35, 15, 5, 10, 20, 25};

        //��ʼ��һ��6*6�Ķ�άvector
        //times[i][j]��ʾ�ӵ�i�����󵽵�j������֮����˵����ټ����������i>jʱû������
        vector< vector<int> > times;
        times.resize( 6 );
        for_each( times.begin(), times.end(), []( vector<int> &v )
        {
            v.resize( 6 );
        } );
        //����һ��6*6�Ķ�ά����������ÿ�ζ����н������Ż��ֵ�λ��
        //k_pos[i][j]��ʾ�ڼ���ӵ�i�����󵽵�j������֮����˵����ټ������ʱ��Ӧ�ô�k_pos[i][j]���л���
        auto k_pos = times;

        for ( int l = 2; l <= 6; ++l )
        {
            //���㳤��Ϊl����������Ҫ�����ټ�������������ȵ�������Ϊ�̵����б����ڳ�������֮ǰ���м���
            for ( int i = 0; i < 6 - l + 1; ++i )
            {
                int j = i + l - 1;
                times[i][j] = numeric_limits<int>::max();

                for ( int k = i; k < j; ++k )
                {
                    int value = times[i][k] + times[k + 1][j] + maxtix_length[i] * maxtix_length[k + 1] * maxtix_length[j + 1];
                    if ( value < times[i][j] )
                    {
                        times[i][j] = value;
                        k_pos[i][j] = k;
                    }
                }
            }
        }

        //for (int i = 0; i < 6; ++i)
        //{
        //	for (int j = 0; j < 6; ++j)
        //	{
        //		cout << times[i][j] << "\t";
        //	}
        //	cout << endl;
        //}
        cout << times[0][5] << endl;
        Print( k_pos, 0, 5 );

        getchar();
    }
}
//////////////////////////////////////////////////////////////////////////
/// @file		assemble_dispatch.cpp
/// @brief		װ���ߵ�������
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
/// 2011/06/17   14:09	1.0	̷����	����


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
    /// @brief װ���ߵ�������
    ///
    /// ĳ����������2��װ���ߣ�ÿ��װ������n ��װ��վ����˳����1��n ��������װ���߶�Ӧ��װ��վִ����ͬ�Ĺ��ܣ������õ�ʱ����ܲ�ͬ��������i����ˮ�ߣ�i=1��2��
    /// �ĵ�j ��װ��վ������ʱ��Ϊs[i][j]���ӵ�i����ˮ�ߵĵ�j ��װ��վ�Ƶ���j+1��װ��վ��ʱ����Ժ��ԣ����Ƶ�����һ����ˮ�ߵ���һ��װ��վ����Ҫһ����ʱ��t[i][j]��
    /// - ����������ˮ����Ҫ��ʱ��e[i]������ˮ��ʱ��Ҫ��ʱ��x[i]��
    /// - ������װ����Ҫ��˳�򾭹�����װ��վ��
    /// - ������֪װ��ʱ��s[i][j]��ת��ʱ��t[i][j]�Լ�����ʱ��e[i]������ˮ��ʱ��x[i]��Ҫ�����װ��һ����������Ҫ�����ʱ�䡣
    void AssembleDispatch()
    {
        int e[] = {2, 4};
        int x[] = {3, 2};
        int S0[] = {7, 9, 3, 4, 8, 4};
        int S1[] = {8, 5, 6, 4, 5, 7};
        int *s[] = {S0, S1};
        int T0[] = {2, 3, 1, 3, 4};
        int T1[] = {2, 1, 2, 2, 1};
        int *t[] = {T0, T1};

        //f[i][j]��ʾ��ɵ�i��װ���ߵĵ�j��װ��վ��װ�乤�����֮����Ҫ������ʱ��
        vector< vector<int> > f( 2 );
        f[0].resize( 6 );
        f[1].resize( 6 );

        //l[i][j]��ʾ��i��װ�����ϵĵ�j��װ��վ��ɹ���������ʱ����ѡ�õ�����һ��װ�����ϵ�j-1װ��վ
        //j = 0, l[i][j]ʱû�����壬��Ϊ��0��װ��վû��ѡ��
        vector< vector<int> > l( 2 );
        l[0].resize( 6 );
        l[1].resize( 6 );

        f[0][0] = e[0] + s[0][0];
        f[1][0] = e[1] + s[1][0];
        for ( int i = 1; i < 6; ++i )
        {
            //����f[0][i]
            if ( f[0][i - 1] + s[0][i] < f[1][i - 1] + s[0][i] + t[1][i - 1] )
            {
                f[0][i] = f[0][i - 1] + s[0][i];
                l[0][i] = 0;
            }
            else
            {
                f[0][i] = f[1][i - 1] + s[0][i] + t[1][i - 1];
                l[0][i] = 1;
            }

            //����f[1][i]
            if ( f[1][i - 1] + s[1][i] < f[0][i - 1] + s[1][i] + t[0][i - 1] )
            {
                f[1][i] = f[1][i - 1] + s[1][i];
                l[1][i] = 1;
            }
            else
            {
                f[1][i] = f[0][i - 1] + s[1][i] + t[0][i - 1];
                l[1][i] = 0;
            }

            //�������Ҫ��¼l[i][j]�������ͺܷ����ʵ���ˣ��ɼ���̬�滮��ʵ�ȵݹ黹����ʵ��
            //f[0][i] = min( f[0][i - 1] + s[0][i], f[1][i - 1] + s[0][i] + t[1][i - 1] );
            //f[1][i] = min( f[1][i - 1] + s[1][i], f[0][i - 1] + s[1][i] + t[0][i - 1] );
        }

        int l_star = ( f[0][5] + x[0] < f[1][5] + x[1] ? 0 : 1 );
        int final_min_time = min( f[0][5] + x[0], f[1][5] + x[1] );
        cout << "��̵�װ��·����Ҫʱ�䣺" << final_min_time << endl;

        vector<int> route;
        for ( int i = 5; i >= 0; --i )
        {
            route.push_back( l_star );
            l_star = l[l_star][i];
        }
        reverse( route.begin(), route.end() );		//��ת
        copy( route.begin(), route.end(), ostream_iterator<int>( cout, " --> " ) );
        getchar();
    }
}
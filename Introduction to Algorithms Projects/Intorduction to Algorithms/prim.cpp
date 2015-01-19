//////////////////////////////////////////////////////////////////////////
/// @file		prim.cpp
/// @brief		Prim��С�������㷨
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
/// 2011/06/17   17:00	1.0	̷����	����



#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <iterator>
#include <bitset>
#include <queue>
#include "graphics.h"

using namespace std;

namespace ita
{
    /// @brief Prim��С�������㷨
    ///
    /// <b>��С��Ȩֵ������������n-1���ߣ����������е�n�����㣬�������б��ϵ�Ȩֵ����С��</b>\n\n
    /// Prim�㷨�У�����A���γɵ����������뼯��A�еİ�ȫ��������������һ���������еĶ������СȨ�ߡ�\n
    /// Prim�㷨������ȡ�������ȶ���Q�����ʵ�ֵģ�������ʹ��쳲���������ʵ����С���ȶ��У��Ϳ��Խ�Prim�㷨������ʱ��Ľ�ΪO(E+VlgV)��
    void Prim()
    {
        cout << "Prim��С������" << endl;
        vector<char> v;
        for ( int i = 0; i < 9; ++i )
        {
            v.push_back( 'a' + i );
        }
        GrpahicsViaAdjacencyMatrix<char, int> g( v, Undigraph );
        g.Link2Vertex( 0, 1, 4 );
        g.Link2Vertex( 0, 7, 8 );
        g.Link2Vertex( 1, 2, 8 );
        g.Link2Vertex( 1, 7, 11 );
        g.Link2Vertex( 2, 3, 7 );
        g.Link2Vertex( 2, 5, 4 );
        g.Link2Vertex( 2, 8, 2 );
        g.Link2Vertex( 3, 4, 9 );
        g.Link2Vertex( 3, 5, 14 );
        g.Link2Vertex( 4, 5, 10 );
        g.Link2Vertex( 5, 6, 2 );
        g.Link2Vertex( 6, 7, 1 );
        g.Link2Vertex( 6, 8, 6 );
        g.Link2Vertex( 7, 8, 7 );
        int start_index = 0;

        //parent[i] = j������ѡȡ��С������ʱ��i��������һ�������j
        vector<int> parent( v.size(), -1 );
        //������С�������еĶ���ļ���
        //pair<����ı�ţ��ö����������Ѿ�����С�������еĶ������̾���>
        map<int, int> key;
        for ( int i = 0; i < g.GetVertex().size(); ++i )
        {
            key.insert( make_pair( i, numeric_limits<int>::max() ) );
        }
        key[start_index] = 0;

        while ( !key.empty() )
        {
            //�õ�����С�����������ⶥ�������С��Ԫ��
            auto min_ele = min_element( key.begin(), key.end(), []( pair<int const, int> &p1, pair<int const, int> &p2 )
            {
                return p1.second < p2.second;
            } );
            int min_index = min_ele->first;
            cout << ( parent[min_index] == -1 ? *"&" : g.GetVertex()[parent[min_index]] ) << " -- " << g.GetVertex()[min_index] << endl;
            key.erase( min_ele );

            for ( int i = 0; i < g.GetVertex().size(); ++i )
            {
                if ( key.find( i ) != key.end() && g.IsLinked( i, min_index ) && key[i] > g.GetEdge()[i][min_index] )
                {
                    key[i] = g.GetEdge()[i][min_index];
                    parent[i] = min_index;
                }
            }
        }

    }
}
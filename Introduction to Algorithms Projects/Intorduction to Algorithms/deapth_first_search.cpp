//////////////////////////////////////////////////////////////////////////
/// @file		deapth_first_search.cpp
/// @brief		�����������
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
/// 2011/06/17   16:56	1.0	̷����	����


#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <bitset>
#include "graphics.h"
#include "deapth_first_search.h"

using namespace std;

namespace ita
{
    /// @brief ������ȱ���������
    ///
    /// ��������������˴���һ���������ɭ���⣬�����������ͬʱΪÿ������Ӹ�ʱ�����ÿ������v������ʱ�����\n
    /// ������v��һ�α�����ʱ����¼�µ�һ��ʱ���d[v]�����������v���ڽӱ�ʱ����¼�µڶ���ʱ���f[v]��\n
    /// �������������������ͼ�㷨���õ���ʱ��������Ƕ������������������ʱ������кܴ�İ�����\n
    /// ������¸�ϰ��������㷨���õ���������ʾ����ʹ������2��ʱ���������Ǻ����úܺõĴ��°�������¼����2��ʱ���֮�󣬺ܶණ�������������ʱ������Ƶ������ˣ���������������ȱ����Ĵ���ȣ���\n
    template<typename T>
    void DeapthFirstSearch( GraphicsViaAdjacencyList<T> &g )
    {
        vector<int>		d( g.GetVertex().size() );				//ʱ���d
        vector<int>		f( g.GetVertex().size() );				//ʱ���f
        vector<bool>	traversed( g.GetVertex().size(), false );	//��ʶ�����Ƿ��Ѿ�������
        int				time = 0;

        cout << endl << "������ȱ�����";
        for ( size_t i = 0; i < g.GetVertex().size(); ++i )
        {
            if ( !traversed[i] )
            {
                vector<int> ids = DFS_Visit( g, i, d, f, traversed, time );
                for ( size_t k = 0; k < ids.size(); ++k )
                {
                    cout << g.GetVertex()[ids[k]] << "[" << d[ids[k]] << "," << f[ids[k]] << "] ";
                }
            }
        }

        cout << endl << "������ȱ�����";
        vector<pair<int, pair<int, int>>> r;
        for ( size_t i = 0; i < g.GetVertex().size(); ++i )
        {
            r.push_back( make_pair( i, make_pair( d[i], f[i] ) ) );
        }

        // ����ʱ���d������ú���֮�����������ȱ����Ľ��
        // �������Լ��Ƶ������ģ�֤��˼·�ǣ�����������ȵġ����Ŷ�����ʱ���d����ǰ��Ľ������λ��ǰ��������ڣ�
        // Ҳ����λ������������������ǰ������˵����ͬʱ����ʱ����������������ð�������d����Ϳ��Եó�������ȵĴ���
        // ������f�����ֿ��Եó����������˳��
        sort( r.begin(), r.end(), []( pair<int, pair<int, int>> const & p1, pair<int, pair<int, int>> const & p2 )
        {
            return p1.second.first < p2.second.first;
        } );
        for ( size_t i = 0; i < r.size(); ++i )
        {
            cout << g.GetVertex()[r[i].first] << "[" << r[i].second.first << "," << r[i].second.second << "] ";
        }
    }

    /// ���������������
    void testDeapthFirstSearch()
    {
        vector<char> v;
        for ( int i = 0; i < 8; ++i )
        {
            v.push_back( 'r' + i );
        }
        GraphicsViaAdjacencyList<char> g( v, Undigraph );
        g.Link2Vertex( 0, 1 );
        g.Link2Vertex( 0, 4 );
        g.Link2Vertex( 1, 5 );
        g.Link2Vertex( 2, 5 );
        g.Link2Vertex( 2, 3 );
        g.Link2Vertex( 2, 6 );
        g.Link2Vertex( 3, 6 );
        g.Link2Vertex( 3, 7 );
        g.Link2Vertex( 5, 6 );
        g.Link2Vertex( 6, 7 );

        DeapthFirstSearch( g );
    }
}
//////////////////////////////////////////////////////////////////////////
/// @file		strongly_connected_component.cpp
/// @brief		ǿ��ͨ��֧
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
/// 2011/06/17   16:03	1.0	̷����	����


#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <iterator>
#include <bitset>
#include "graphics.h"
#include "deapth_first_search.h"

using namespace std;


namespace ita
{
    /// @brief Ѱ��ǿ��ͨ��֧����
    ///
    /// ǿ��ͨ��֧������ͼG=(V, E)��һ��ǿ��ͨ��֧����һ�����Ķ��㼯��C������C�е�ÿһ�Զ���u,v������u -> v��v -> u���༴����u��v�ǻ���ɴ�ġ�\n
    /// Ѱ��ǿ��ͨ��֧�ļ����㷨��Ѱ��ǿ��ͨ��֧���㷨��ʱ�临�Ӷ�ΪO(V+E)��
    /// - ��G����������ȱ����õ�ÿ�������ʱ���f[x]��
    /// - ���G������ͼG^T��
    /// - ����f[x]������˳��Ϊ����˳���G^T����������ȱ�����������G�����������˳���G^T�ٽ���������ȱ�����
    /// - ����c�õ��ĸ�����������ԭͼG�ĸ�ǿ��ͨ��֧��
    void StronglyConnectedComponent()
    {
        cout << "ǿ���ӷ�֧" << endl;
        vector<char> v;
        for ( int i = 0; i < 8; ++i )
        {
            v.push_back( 'a' + i );
        }
        GraphicsViaAdjacencyList<char> g( v, Digraph );
        g.Link2Vertex( 0, 1 );
        g.Link2Vertex( 1, 2 );
        g.Link2Vertex( 1, 4 );
        g.Link2Vertex( 1, 5 );
        g.Link2Vertex( 2, 3 );
        g.Link2Vertex( 2, 6 );
        g.Link2Vertex( 3, 2 );
        g.Link2Vertex( 3, 7 );
        g.Link2Vertex( 4, 0 );
        g.Link2Vertex( 4, 5 );
        g.Link2Vertex( 5, 6 );
        g.Link2Vertex( 6, 5 );
        g.Link2Vertex( 6, 7 );
        g.Link2Vertex( 7, 7 );

        //step1:��g����������ȱ���
        vector<int>		d( g.GetVertex().size() );				//ʱ���d
        vector<int>		f( g.GetVertex().size() );				//ʱ���f
        vector<bool>	traversed( g.GetVertex().size(), false );	//��ʶ�����Ƿ��Ѿ�������
        int				time = 0;

        for ( size_t i = 0; i < g.GetVertex().size(); ++i )
        {
            if ( !traversed[i] )
            {
                DFS_Visit( g, i, d, f, traversed, time );
            }
        }

        //step2:�õ�gT���õ���ʱ���f��������
        GraphicsViaAdjacencyList<char> gT( g );
        for ( size_t i = 0; i < gT.GetEdges().size(); ++i )
        {
            gT.GetEdges()[i] = nullptr;
        }
        for ( size_t i = 0; i < g.GetVertex().size(); ++i )
        {
            for ( size_t j = 0; j < g.GetVertex().size(); ++j )
            {
                if ( g.IsLinked( i, j ).first )
                {
                    gT.Link2Vertex( j, i );
                }
            }
        }
        vector<pair<int, pair<int, int>>> r;
        for ( size_t i = 0; i < g.GetVertex().size(); ++i )
        {
            r.push_back( make_pair( i, make_pair( d[i], f[i] ) ) );
        }
        //����ʱ���f�������ź���Ľ��
        sort( r.rbegin(), r.rend(), []( pair<int, pair<int, int>> const & p1, pair<int, pair<int, int>> const & p2 )
        {
            return p1.second.second < p2.second.second;
        } );
        for ( size_t i = 0; i < r.size(); ++i )
        {
            cout << g.GetVertex()[r[i].first] << "[" << r[i].second.first << "," << r[i].second.second << "] ";
        }
        cout << endl;

        //step3����gT����ʱ��������������½���������ȱ��������õ��ĸ���������g��ǿ��ͨ��֧
        traversed.assign( gT.GetVertex().size(), false );
        time = 0;

        for ( size_t i = 0; i < r.size(); ++i )
        {
            if ( !traversed[r[i].first] )
            {
                vector<int> ids = DFS_Visit( gT, r[i].first, d, f, traversed, time );
                for ( size_t k = 0; k < ids.size(); ++k )
                {
                    cout << gT.GetVertex()[ids[k]];
                }
                cout << endl;
            }
        }

    }

}
//////////////////////////////////////////////////////////////////////////
/// @file		breadth_first_search.cpp
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
/// 2011/06/17   16:02	1.0	̷����	����


#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <bitset>
#include "graphics.h"

using namespace std;

namespace ita
{
    /// @brief ������ȱ���
    ///
    /// @param	g				ʹ���ڽӱ��ʾ��ͼ
    /// @param	start_index		��������㿪ʼ���й�����ȱ���
    template<typename T>
    void BreadthFirstSearch( GraphicsViaAdjacencyList<T> &g, size_t start_index )
    {
        queue<size_t>	q;
        vector<bool>	trivaled( g.GetVertex().size(), false );
        q.push( start_index );
        trivaled[start_index] = true;

        cout << "������ȱ�����";
        while ( !q.empty() )
        {
            //���û�б��������еĽ��
            char current = q.front();
            q.pop();
            cout << g.GetVertex()[current] << "  ";

            for ( size_t i = 0; i < g.GetVertex().size(); ++i )
            {
                if ( !trivaled[i] && g.IsLinked( current, i ).first )
                {
                    //û�б������� �� �뵱ǰ������Ԫ���ڽ�
                    q.push( i );
                    trivaled[i] = true;
                }
            }
        }
    }

    /// ������ȱ���
    void testBreadthFirstSearch()
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

        BreadthFirstSearch( g, 1 );
        cout << endl;
    }
}
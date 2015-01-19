#pragma once
//////////////////////////////////////////////////////////////////////////
/// @file		dijkstra.h
/// @brief		Dijstra���·��
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
/// 2011/06/17   17:39	1.0	̷����	����


#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <iterator>
#include <bitset>
#include <queue>
#include <limits>
#include "graphics.h"
#include "bellman_ford.h"

using namespace std;


namespace ita
{
    /// @brief Dijstra���·��
    ///
    /// <b>���·����һ�����㵽��һ����������Ȩֵ·����������������㷨����һ������Ȩ����λȨֵ��ͼ��ִ�е����·���㷨��</b>\n
    /// Dijkstra�㷨��һ��̰�Ĳ��Ե��㷨����������ʱ��һ���Bellman-Ford�㷨Ҫ�á�\n
    ///	<span style="color:#FF0000 ">Dijkstra�㷨��ÿ��ѭ���У�ÿ�ν�����ȡdֵ��С�Ķ���u�Ǳ�֤���̰�Ĳ�����ȷ�ԵĹؼ��������ڡ�</span>\n
    ///	��Ϊͨ������S�����е�Ԫ�ض��Ѿ�ȥ�����ɳڹ�u�ˣ�����S�еĵ����ڱ�������dֵ����uҪ�����Լ�ʹ�������е��κ�һ��ȥ�ɳ�u��Ҳ�����ܴﵽ�����ڸ�С��dֵ�ˡ�\n
    ///	��ˣ���ÿ��ѭ����ѡȡ��ǰdֵ��С�Ķ�����뵽S������ȥһ���ܱ�֤���õ�ȫ�����Ž⡣\n\n
    ///	DIJKSTRA(G, w, s)\n
    /// 	1  INITIALIZE-SINGLE-SOURCE(G, s)\n
    /// 	2  S �� �ռ�\n
    /// 	3  Q �� V[G]\n
    ///		4  while Q != �ռ�\n
    /// 	5      do u �� EXTRACT-MIN(Q)\n
    /// 	6         S �� S ���� {u}\n
    ///		7         for each vertex v ���� Adj[u]\n
    ///		8             do RELAX(u, v, w)\n
    /// @remarks	Dijkstra�㷨�ٶ�����ͼ�е����бߵ�Ȩֵ���ǷǸ���
    /// @param	g				���ڽӱ���ʾ��ͼ
    /// @param	start_index		���㶥��start_index���������е�����·��
    /// @param	d				�㷨������d[i]�洢��start_index������i�����·��
    /// @parem	parent_index	��¼�㷨�����еĽ����е�ѡ���㷨������parent_index[i]��ʾ��start_index������i�����·���ĵ����ڶ������ı��
    template<typename T>
    void Dijkstra( GraphicsViaAdjacencyList<T> &g, int start_index, vector<int> &d, vector<int> &parent_index )
    {
        auto edges = g.GetAllEdges();

        InitializeSingleSource( g, d, parent_index, start_index );

        auto greater_pred = [&]( int index1, int index2 )
        {
            return d[index1] > d[index2];
        };

        //ʹ����ͨ���������������ȶ��С������Կ���ʹ�ö���Ѻ�쳲������������м���
        vector<int> Q;
        for ( size_t i = 0; i < g.GetVertex().size(); ++i )
        {
            Q.push_back( i );
        }
        make_heap( Q.begin(), Q.end(), greater_pred );


        while( !Q.empty() )
        {
            for_each( edges.begin(), edges.end(), [&]( pair<size_t, size_t> const & p )
            {
                if ( p.first == Q[0] )
                {
                    //�����д�min_ele�����ı߽����ɳڲ���
                    Relax( g, d, parent_index, p.first, p.second );
                }
            } );

            //����d��Relax�����˸ı䣬�൱�ڸı������ȶ����������������ֵ�����Ҫ�ؽ���
            swap( Q[0], Q[Q.size() - 1] );
            Q.pop_back();
            make_heap( Q.begin(), Q.end(), greater_pred );
        }
    }
}
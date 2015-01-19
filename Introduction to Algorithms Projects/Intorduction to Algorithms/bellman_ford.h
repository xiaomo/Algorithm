#pragma once
//////////////////////////////////////////////////////////////////////////
/// @file		bellman_ford.h
/// @brief		Bellman-Ford���·���㷨
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
/// 2011/06/17   17:40	1.0	̷����	����

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

using namespace std;


namespace ita
{
    namespace
    {
        /// ��ʼ��
        template<typename T>
        void InitializeSingleSource( GraphicsViaAdjacencyList<T> &g, vector<int> &d, vector<int> &parent_index, int start_index )
        {
            for ( size_t i = 0; i < g.GetVertex().size(); ++i )
            {
                d[i] = numeric_limits<int>::max();
                parent_index[i] = -1;
            }
            d[start_index] = 0;
        }

        /// @brief �ɳ�
        ///
        /// ǰ�������ǣ�index1->index2������һ����
        /// �����index1�����������ɳ�index2��dֵ����������parent[index2] = index1
        template<typename T>
        void Relax( GraphicsViaAdjacencyList<T> &g, vector<int> &d, vector<int> &parent_index, int index1, int index2 )
        {
            if ( d[index2] > d[index1] + g.IsLinked( index1, index2 ).second->Weight )
            {
                d[index2] = d[index1] + g.IsLinked( index1, index2 ).second->Weight;
                parent_index[index2] = index1;
            }
        }
    }

    /// @brief Bellman-Ford���·���㷨
    ///
    /// <b>���·����һ�����㵽��һ����������Ȩֵ·����������������㷨����һ������Ȩ����λȨֵ��ͼ��ִ�е����·���㷨��</b>\n
    /// Bellman-Ford�㷨�ǳ��򵥣������еı߽���|v|-1��ѭ������ÿ��ѭ���ж�ÿһ���߽����ɳڵĲ�����\n
    /// @remarks		floyd�㷨��������ߴ��ڸ�Ȩ�ߣ�ֻҪ�����ڴ�Դ��ɴ�ĸ�Ȩ��·��������������Ÿ�Ȩ��·�������ܼ�������
    /// @param	g				���ڽӱ���ʾ��ͼ
    /// @param	start_index		���㶥��start_index���������е�����·��
    /// @param	d				�㷨������d[i]�洢��start_index������i�����·��
    /// @parem	parent_index	��¼�㷨�����еĽ����е�ѡ���㷨������parent_index[i]��ʾ��start_index������i�����·���ĵ����ڶ������ı��
    /// @return			�㷨�Ƿ�ִ�гɹ���ȡ����ͼ���Ƿ���ڡ���Ȩ��·����
    /// @retval	true	�㷨ִ�гɹ���ͼ�в����ڡ���Ȩ��·
    /// @retval	false	�㷨ִ��ʧ�ܣ�ͼ�д��ڡ���Ȩ��·
    template<typename T>
    bool BellmanFord( GraphicsViaAdjacencyList<T> &g, int start_index, vector<int> &d, vector<int> &parent_index )
    {
        auto edges = g.GetAllEdges();

        InitializeSingleSource( g, d, parent_index, start_index );

        for ( size_t i = 0; i < g.GetVertex().size() - 1; ++i )
        {
            for_each( edges.begin(), edges.end(), [&]( pair<size_t, size_t> const & p )
            {
                Relax( g, d, parent_index, p.first, p.second );
            } );
        }

        for ( size_t i = 0; i < edges.size(); ++i )
        {
            if ( d[edges[i].second] > d[edges[i].first] + g.IsLinked( edges[i].first, edges[i].second ).second->Weight )
            {
                return false;
            }
        }

        return true;
    }
}
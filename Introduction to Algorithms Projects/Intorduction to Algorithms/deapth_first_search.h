#pragma once
//////////////////////////////////////////////////////////////////////////
/// @file		deapth_first_search.h
/// @brief		��������������ĵݹ����
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
/// 2011/06/17   16:05	1.0	̷����	����



#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <bitset>
#include "graphics.h"

using namespace std;

namespace ita
{
    /// @brief ������ȱ����ĵݹ麯��
    ///
    /// �Ӷ���index��ʼ������������ȵĹ������α�����ֻ�������index������Է��ʵĽ��������index���ɵ���Ľ�㲻����ʡ�
    /// @param	g				Ҫ������ͼ��ʹ���ڽӱ�ı�ʾ����
    /// @param	index			��index���㿪ʼ���б���
    /// @param	d				ʱ���d
    /// @param	f				ʱ���f
    /// @param	traversed		��ʶ�����Ƿ��Ѿ�������
    /// @param	time			ȫ��ʱ�䣬��������ʱ���d��f
    /// @return			���ر���������ȱ����õ��������������������Ľ��ı��
    template<typename T>
    vector<int> DFS_Visit( GraphicsViaAdjacencyList<T> &g, size_t index, vector<int> &d, vector<int> &f, vector<bool> &traversed, int &time )
    {
        vector<int> this_time_traversed;
        this_time_traversed.push_back( index );
        traversed[index] = true;
        ++time;
        d[index] = time;

        for ( size_t i = 0; i < g.GetVertex().size(); ++i )
        {
            if ( !traversed[i] && g.IsLinked( index, i ).first )
            {
                vector<int> v = DFS_Visit( g, i, d, f, traversed, time );
                this_time_traversed.insert( this_time_traversed.end(), v.begin(), v.end() );
            }
        }

        ++time;
        f[index] = time;
        return this_time_traversed;
    }

}
//////////////////////////////////////////////////////////////////////////
/// @file		disjoint_set_forest.cpp
/// @brief		���ڲ��ཻ���ϵ����ݽṹ�����鼯��
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
/// 2011/06/17   16:01	1.0	̷����	����


#include <iostream>
#include <vector>
using namespace std;

#include "disjoint_set_forest.h"

namespace ita
{
    /// ���ڲ��ཻ���ϵ����ݽṹ�����鼯��
    void testDisjointSetForest()
    {
        vector<DisjointSetForest::DisjointSet<int> *> nodes;
        for ( int i = 0; i < 10; ++i )
        {
            nodes.push_back( DisjointSetForest::MakeSet( i ) );
        }


        for ( int i = 0; i < 5; ++i )
        {
            int index1 = rand() % 10;
            int index2 = rand() % 10;
            DisjointSetForest::Union( nodes[index1], nodes[index2] );
            cout << "Union : " << index1 << "---" << index2 << endl;
        }

        for ( int i = 0; i < 10; ++i )
        {
            cout << i << "-------------->" << DisjointSetForest::FindSet( nodes[i] )->Item << endl;
        }

        //for (int i = 0; i < nodes.size(); ++i)
        //{
        //	FindSet(nodes[i]);
        //	cout << FindSet(nodes[i])->Item << endl;
        //}
    }
}
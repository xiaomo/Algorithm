//////////////////////////////////////////////////////////////////////////
/// @file		huffman_code.cpp
/// @brief		̰���㷨��Huffman��������
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
/// 2011/06/17   15:52	1.0	̷����	����

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>
#include <numeric>
#include <set>
#include <map>
using namespace std;

namespace ita
{
    namespace
    {
        struct Node
        {
            Node *Left, *Right;
            char	Char;
            double	Value;
        };

        void ShowLeaf( Node * root, string const &code )
        {
            if ( root )
            {
                if ( !root->Left && !root->Right )
                {
                    //Ҷ�ӽ����
                    cout << root->Char << " ===> " << code << endl;
                }
                else
                {
                    ShowLeaf( root->Left, code + "0" );
                    ShowLeaf( root->Right, code + "1" );
                }
            }
        }
    }

    /// @brief ʹ��̰���㷨���Huffman��������
    ///
    /// ����ԭ������ò��ȳ��ı�������ʾ��ͬ����Ƶ�ʵ��ַ�������Ƶ�ʸߵ��ַ������ñȽ϶̵ı�������ʾ������Ƶ�ʵ͵ģ����ǽϳ��ı�������ʾ��
    void HuffmanCode()
    {
        string orgin_str = "abcadbabacadbacdabadeabadabaewbadsafdsawebadsfasdfababadasdfabababcadb";
        map<char, double> frequency;
        for_each( orgin_str.begin(), orgin_str.end(), [&]( char const & c )
        {
            ++frequency[c];
        } );

        vector<Node *> nodes;
        for_each( frequency.begin(), frequency.end(), [&]( pair<char const, double> &item )
        {
            item.second /= orgin_str.size();

            Node *node = new Node();
            node->Value = item.second;
            node->Char = item.first;
            nodes.push_back( node );
        } );

        for_each( frequency.begin(), frequency.end(), [&]( pair<char const, double> &item )
        {
            cout << item.first << ":  " << item.second << endl;
        } );

        while ( nodes.size() > 1 )
        {
            //�г���һ����㣬��ѭ��
            sort( nodes.begin(), nodes.end(), []( Node * n1, Node * n2 )
            {
                return n1->Value < n2->Value;
            } );

            Node *new_node = new Node();
            new_node->Left = nodes[0];
            new_node->Right = nodes[1];
            new_node->Value = nodes[0]->Value + nodes[1]->Value;

            nodes.erase( nodes.begin(), nodes.begin() + 2 );
            nodes.push_back( new_node );
        }

        ShowLeaf( nodes[0], "" );
        getchar();
    }




}
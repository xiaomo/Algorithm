//////////////////////////////////////////////////////////////////////////
/// @file		binomial_heaps.cpp
/// @brief		�����
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
/// 2011/06/17   15:47	1.0	̷����	����

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include "graphviz_shower.h"
using namespace std;

namespace ita
{
    /// @brief �����
    ///
    /// ���������<b>һ��</b>���������<b>������</b>��ɣ�\n
    /// - H�е�ÿ����������ѭ<span style="color:#FF0000 ">��С�����ʣ����Ĺؼ��ִ��ڻ�����丸���Ĺؼ���</span>��
    /// ����˵����������С������ġ�
    /// - �������������k�Ļ�����H����������һ������Ҳ��k�Ķ���������<span style="color:#FF0000 ">����</span>����0��1�ã�
    /// ��һ�ö������ĸ����ж���K�����������̫�����ˣ��������ܶ��������������ģ�
    ///
    /// ��һ�����ʱ�֤�˶������ĸ�����������С�Ĺؼ��֡��ڶ���������˵�������Ϊn�Ķ�������ֻ��logn + 1�ö�������\n
    /// ��������һ�ֵݹ�Ķ���:\n
    /// - ������B[0]��������һ���ڵ�
    /// - B[k]��������B[k-1]��������ɣ�����һ����������һ������������
    template<typename KeyType>
    class BinomialHeap
    {
    public:
        /// ������е�һ�����
        struct BinomialHeapNode
        {
            BinomialHeapNode	*Parent;
            BinomialHeapNode	*Child;
            BinomialHeapNode	*Sibling;

            unsigned int 		Degree;
            KeyType				Key;
        };

        /// ����һ���յĶ����
        BinomialHeap()
        {
            _head_list = nullptr;
        }

        /// ����
        ~BinomialHeap()
        {
            BinomialHeapNode *tree = _head_list;

            //�������������������
            while( tree )
            {
                auto next = tree->Sibling;
                _DeleteTree( tree );
                tree = next;
            }
        }

        /// �ڶ�����в���һ���½��
        void Insert( KeyType new_key )
        {
            BinomialHeap new_heap;
            new_heap._head_list = new BinomialHeapNode();
            new_heap._head_list->Parent = new_heap._head_list->Child = new_heap._head_list->Sibling = nullptr;
            new_heap._head_list->Degree = 0;
            new_heap._head_list->Key = new_key;

            this->Union( new_heap );
        }

        /// ��ȡ���е���СԪ��ֵ
        KeyType Mininum() const
        {
            vector<KeyType> values_in_head_list;
            BinomialHeapNode *node = _head_list;
            while( node != nullptr )
            {
                values_in_head_list.push_back( node->Key );
                node = node->Sibling;
            }
            return *min_element( values_in_head_list.begin(), values_in_head_list.end() );
        }

        /// ����������е���СԪ�أ�����ȡ����СԪ�ص�ֵ
        KeyType ExtractMinium()
        {
            vector<BinomialHeapNode *> head_nodes;
            BinomialHeapNode *l = _head_list;
            while( l )
            {
                head_nodes.push_back( l );
                l = l->Sibling;
            }
            auto min_ele = min_element( head_nodes.begin(), head_nodes.end(), []( BinomialHeapNode * left, BinomialHeapNode * right )
            {
                return left->Key < right->Key;
            } );
            int min_index = min_ele - head_nodes.begin();
            KeyType min_value = ( *min_ele )->Key;
            BinomialHeapNode	*min_node = head_nodes[min_index];

            if ( min_index == 0 )
            {
                if ( head_nodes.size() > 1 )
                {
                    _head_list = head_nodes[1];
                }
                else
                {
                    //������ֻ��һ��Ԫ��
                    _head_list = nullptr;
                }
            }
            else if ( min_index == head_nodes.size() - 1 )
            {
                head_nodes[min_index - 1]->Sibling = nullptr;
            }
            else
            {
                head_nodes[min_index - 1]->Sibling = head_nodes[min_index + 1];
            }

            BinomialHeap new_head;
            new_head._head_list = min_node->Child;
            BinomialHeapNode *x = new_head._head_list;
            while ( x )
            {
                x->Parent = nullptr;
                x = x->Sibling;
            }
            this->Union( new_head );

            delete min_node;
            return min_value;
        }

        /// @brief ��һ������ֵ������С����
        ///
        /// @note		x������ֵk�����x����ԭֵС
        void Decrease( BinomialHeapNode *x, KeyType k )
        {
            if ( k > x->Key )
            {
                throw exception( "ֻ�ܼ�С��������" );
            }

            x->Key = k;
            BinomialHeapNode *y = x;
            BinomialHeapNode *z = y->Parent;
            while ( z && y->Key < z->Key )
            {
                swap( y->Key, z->Key );
                y = z;
                z = y->Parent;
            }
        }

        /// ɾ��һ�����
        void Delete( BinomialHeapNode *node )
        {
            if ( node )
            {
                Decrease( node, numeric_limits<KeyType>::min() );
                ExtractMinium();
            }
        }

        /// @brief ��������һ�������
        ///
        /// ������һ����������ϵ��������,�����ϲ������֮��,other�Ķ�����е����ݽ���Ч
        void Union( BinomialHeap &other )
        {
            vector<BinomialHeapNode *> nodes;
            BinomialHeapNode *l = _head_list;
            BinomialHeapNode *r = other._head_list;
            while ( l )
            {
                nodes.push_back( l );
                l = l->Sibling;
            }
            while ( r )
            {
                nodes.push_back( r );
                r = r->Sibling;
            }
            if ( nodes.empty() )
            {
                return;
            }

            // sort and merge
            sort( nodes.begin(), nodes.end(), []( BinomialHeapNode * left, BinomialHeapNode * right )
            {
                return left->Degree < right->Degree;
            } );
            for ( size_t i = 0; i < nodes.size() - 1; ++i )
            {
                nodes[i]->Sibling = nodes[i + 1];
            }
            nodes[nodes.size() - 1]->Sibling = nullptr;

            // reset head list
            this->_head_list = nodes[0];
            other._head_list = nullptr;		//destory binomial heaps has been unioned
            if ( this->_head_list == nullptr )
            {
                return;
            }

            // begin to merge nodes in head list with same degree
            BinomialHeapNode *prev_x = nullptr;
            BinomialHeapNode *x = _head_list;
            BinomialHeapNode *next_x = x->Sibling;

            while( next_x )
            {
                if ( x->Degree != next_x->Degree || ( next_x->Sibling != nullptr && next_x->Sibling->Degree == x->Degree ) )
                {
                    prev_x = x;
                    x = next_x;
                }
                else if ( x->Key < next_x->Key )
                {
                    x->Sibling = next_x->Sibling;
                    _Link( next_x, x );
                }
                else
                {
                    if ( prev_x == nullptr )
                    {
                        _head_list = next_x;
                    }
                    else
                    {
                        prev_x->Sibling = next_x;
                    }

                    _Link( x, next_x );
                    x = next_x;
                }

                next_x = x->Sibling;
            }
        }

        /// @brief ����һ��ֵΪkey�Ľ��
        ///
        /// @note		���еĶѶԲ��Ҳ�����֧�ֶ��ܲʱ�临�Ӷ�ΪO(n)
        BinomialHeapNode * Search( KeyType key ) const
        {
            BinomialHeapNode *tree = _head_list;

            //��������
            while( tree )
            {
                BinomialHeapNode *node = _SearchInTree( tree, key );
                if ( node != nullptr )
                {
                    return node;
                }
                tree = tree->Sibling;
            }
            return nullptr;
        }

        /// ����ѵĵ�ǰ״̬�Ƿ�Ϊ��
        bool IsEmpty() const
        {
            return _head_list == nullptr;
        }

        /// �õ�����ѵĸ�����
        BinomialHeapNode * GetHeadList()
        {
            return _head_list;
        }

        /// ʹ��Grpahviz��ʾ��ǰ�����
        void Display() const
        {
            stringstream ss;

            ss << "digraph graphname" << "{" << endl
               << "    RootList [shape = box];" << endl;

            BinomialHeapNode *node = _head_list;
            if ( node )
            {
                ss << "    RootList -> " << node->Key << ";" << endl;
            }
            while( node )
            {
                _DisplayTree( ss, node );

                if ( node->Sibling )
                {
                    ss << "    " << node->Key << " -> " << node->Sibling->Key << ";" << endl;
                }
                node = node->Sibling;
            }

            ss << "}" << endl;
            qi::ShowGraphvizViaDot( ss.str() );

        }

    private:
        /// ����һ�á���������
        void _DeleteTree( BinomialHeapNode *tree )
        {
            if ( tree )
            {
                BinomialHeapNode *node = tree->Child;
                while( node )
                {
                    auto next = node->Sibling;
                    _DeleteTree( node );
                    node = next;
                }

                delete tree;
            }
        }

        /// ��D(k-1)�ȵ�y������ӵ�D(k-1)�ȵ�z�ӵ���ȥ��ʹ��z��Ϊһ��D(k)�ȵĽ��
        void _Link( BinomialHeapNode *y, BinomialHeapNode *z )
        {
            y->Parent = z;
            y->Sibling = z->Child;
            z->Child = y;
            ++z->Degree;
        }

        /// ��һ�ö�����������ĳ�����
        BinomialHeapNode * _SearchInTree( BinomialHeapNode *tree, KeyType key ) const
        {
            if ( tree->Key == key )
            {
                return tree;
            }

            BinomialHeapNode *node = tree->Child;
            while( node )
            {
                BinomialHeapNode *n = _SearchInTree( node, key );
                if ( n )
                {
                    return n;
                }
                node = node->Sibling;
            }

            return nullptr;
        }

        /// ��һ�ö�����
        void _DisplayTree( stringstream &ss, BinomialHeapNode *tree ) const
        {
            if ( tree )
            {
                BinomialHeapNode *child = tree->Child;
                if ( child )
                {
                    vector<BinomialHeapNode *> childs;
                    while ( child )
                    {
                        childs.push_back( child );
                        child = child->Sibling;
                    }

                    for_each( childs.begin(), childs.end(), [&]( BinomialHeapNode * c )
                    {
                        ss << "    " << c->Key << " -> " << tree->Key << ";" << endl;
                        _DisplayTree( ss, c );
                    } );
                }
            }
        }

    private:
        BinomialHeapNode *_head_list;			///< ������
    };


    /// �����
    void testBinomialHeaps()
    {
        cout << "�����" << endl;
        BinomialHeap<int> bh;
        for ( int i = 0; i < 10; ++i )
        {
            bh.Insert( rand() % 100 );
        }
        bh.Display();

        while ( !bh.IsEmpty() )
        {
            cout << bh.ExtractMinium() << "\t";
        }
        bh.Display();

        for ( int i = 0; i < 64; ++i )
        {
            int r = rand() % 100;
            if ( bh.Search( r ) == nullptr )
            {
                bh.Insert( r );
            }
        }
        bh.Display();

        for ( int i = 0; i < 100; ++i )
        {
            bh.Delete( bh.Search( i ) );
        }
        bh.Display();
    }
}
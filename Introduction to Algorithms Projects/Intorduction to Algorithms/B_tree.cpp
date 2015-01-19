//////////////////////////////////////////////////////////////////////////
/// @file		B_tree.cpp
/// @brief		B��
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
#include <string>
#include <sstream>
#include <cassert>
#include "graphviz_shower.h"
using namespace std;

namespace ita
{
    /// @brief B��
    ///
    /// B-����<b>����������</b>���ƹ�\n
    /// һ��t(t��2��tΪB������С����)�׵�B-���������������ʵ�m������\n
    /// - ÿ��������ٰ�������������\n
    ///		(j��P0��Kl��P1��K2������Ki��Pi)\n
    ///		���У�\n
    ///		- jΪ�ؼ�������
    ///		- Ki(1��i��j)�ǹؼ��֣��ؼ������е�������K1 <K2<��<Ki��
    ///		- Pi(0��i��j)�Ǻ���ָ�롣����Ҷ��㣬ÿ��PiΪ��ָ�롣
    ///		- ע�⣺
    ///			- ʵ����Ϊ��ʡ�ռ䣬Ҷ����п�ʡȥָ����Pi����������ÿ�����������һ����־��leaf����ֵΪ��ʱ��ʾҶ��㣬
    ///			����Ϊ�ڲ���㡣
    ///			- ��ÿ���ڲ�����У�������keys(Pi)����ʾ����Pi�е����йؼ��֣����У�\n
    ///				 ��������������keys(P0)<K1<keys(P1)<K2<��<Ki<keys(Pi)\n
    ///			  ���ؼ����Ƿֽ�㣬��һ�ؼ���Ki��������е����йؼ��־�С��Ki���ұ������е����йؼ��־�����Ki��
    ///
    ///	- ����Ҷ������ͬһ���ϣ�Ҷ�ӵĲ���Ϊ���ĸ߶�h��
    ///	- ÿ���Ǹ�������������Ĺؼ��ָ���j���㣺\n
    ///			t - 1 �� j �� 2*t - 1\n
    ///	  ��ÿ���Ǹ��������Ӧ�� t-1 ���ؼ��֣������� 2*t-1 ���ؼ��֡�\n
    ///	  ��Ϊÿ���ڲ����Ķ��������ǹؼ���������1����ÿ���Ǹ����ڲ����������t��������������2*t��������\n
    ///	- �����ǿգ����������1���ؼ��֣�����������Ҷ�ӣ�����������2����������������2*t-1���ؼ��֣���������2*t��������\n
    class BTree
    {
    public:
        /// B���е�һ�����
        struct BTreeNode
        {
            vector<int>			Keys;
            vector<BTreeNode *>	Childs;
            BTreeNode			*Parent;		///< ����㡣���ý�������ĸ����ʱ��Parent���Ϊnullptr
            bool				IsLeaf;			///< �Ƿ�ΪҶ�ӽ��

            BTreeNode() : Parent( nullptr ), IsLeaf( true ) {}

            size_t KeysSize()
            {
                return Keys.size();
            }
        };

        /// ����һ����С��Ϊt��B��(t>=2)
        BTree( int t ) : _root( nullptr ), _t( t )
        {
            assert( t >= 2 );
        }

        ~BTree()
        {
            _ReleaseNode( _root );
        }

        /// @brief B���Ĳ��Ҳ���
        ///
        /// ��B-���в��Ҹ����ؼ��ֵķ��������ڶ����������ϵĲ��ҡ���ͬ������ÿ�������ȷ�����²��ҵ�·����һ���Ƕ�·����
        /// keynum+1·�ġ�\n
        /// ʵ�����������൱���׵�!
        pair<BTreeNode *, size_t> Search( int key )
        {
            return _SearchInNode( _root, key );
        }

        /// @brief ����һ��ֵ�Ĳ���
        ///
        /// ����û��ʹ�á��㷨���ۡ�����ܵ�һ�˵ķ����������Լ���������Ķ��˵ķ���
        /// Ч�ʿ϶��������Ͻ��ܵ�һ�������������ܽ�����⡣\n
        /// ��Ϊ��������϶�����Ҷ�ӽ���Ͻ��е�,����˳����������ֱ��Ҫ���в��������Ҷ�ӽ�㽫��ֵ���뵽��Ҷ�ӽ����ȥ.
        /// �����Ϊ������������ʹ�øý���ֵ�ĸ���>2*t-1���Ͻ磬����Ҫ�ݹ����Ͻ��з��Ѳ�����
        /// ������ѵ��˸���㣬��Ҫ���������ߵ������\n
        /// ��ֻ���ڽ��з��Ѳ���ʱ�Ż᳤�ߣ�
        bool Insert( int new_key )
        {
            if ( _root == nullptr )	//����
            {
                _root = new BTreeNode();
                _root->IsLeaf = true;
                _root->Keys.push_back( new_key );
                return true;
            }

            if ( Search( new_key ).first == nullptr )	//�Ƿ��Ѿ����ڸý��
            {
                BTreeNode *node = _root;
                while ( !node->IsLeaf )
                {
                    int index = 0;
                    while ( index < node->Keys.size() && new_key >= node->Keys[index] )
                    {
                        ++index;
                    }
                    node = node->Childs[index];
                }

                //���뵽Keys��ȥ
                node->Keys.insert( find_if( node->Keys.begin(), node->Keys.end(), bind2nd( greater<int>(), new_key ) ), new_key );

                //�ٵݹ����ϴ�����̫������
                while ( node->KeysSize() > 2 * _t - 1 )
                {
                    //=====��ʼ����======
                    int prove_node_key = node->Keys[node->KeysSize() / 2 - 1];			// Ҫ�����Ľ���key

                    //��벿�ֳ�Ϊһ���½ڵ�
                    BTreeNode *new_node = new BTreeNode();
                    new_node->IsLeaf = node->IsLeaf;
                    new_node->Keys.insert( new_node->Keys.begin(), node->Keys.begin() + node->KeysSize() / 2, node->Keys.end() );
                    new_node->Childs.insert( new_node->Childs.begin(), node->Childs.begin() + node->Childs.size() / 2, node->Childs.end() );
                    assert( new_node->Childs.empty() || new_node->Childs.size() == new_node->Keys.size() + 1 );
                    for_each( new_node->Childs.begin(), new_node->Childs.end(), [&]( BTreeNode * c )
                    {
                        c->Parent = new_node;
                    } );

                    //�Ѻ�벿�ִ�ԭ���Ľڵ���ɾ��
                    node->Keys.erase( node->Keys.begin() + node->KeysSize() / 2 - 1, node->Keys.end() );
                    node->Childs.erase( node->Childs.begin() + node->Childs.size() / 2, node->Childs.end() );
                    assert( node->Childs.empty() || node->Childs.size() == node->Keys.size() + 1 );

                    BTreeNode *parent_node = node->Parent;
                    if ( parent_node == nullptr )	//���ѵ��˸���㣬��Ҫ�����ˣ���ҪNEWһ��������
                    {
                        parent_node = new BTreeNode();
                        parent_node->IsLeaf = false;
                        parent_node->Childs.push_back( node );
                        _root = parent_node;
                    }
                    node->Parent = new_node->Parent = parent_node;

                    auto insert_pos = find_if( parent_node->Keys.begin()
											 , parent_node->Keys.end()
											 , bind2nd( greater<int>(), prove_node_key ) ) - parent_node->Keys.begin();
                    parent_node->Keys.insert( parent_node->Keys.begin() + insert_pos, prove_node_key );
                    parent_node->Childs.insert( parent_node->Childs.begin() + insert_pos + 1, new_node );

                    node = parent_node;
                }

                return true;
            }
            return false;
        }

        /// @brief ɾ��һ�����Ĳ���
        ///
        /// ɾ�������ο�����ƪ���£�http://student.zjzk.cn/course_ware/data_structure/web/chazhao/chazhao9.3.2.5.htm \n
        /// ��һ�ؼ���K������ǰ��(���)����K��������(������)������(��)�µĽ�������(��ǰ)һ���ؼ��֡�\n
        /// ����B�������ʣ�B����ÿһ������Key�ĸ�������Ϊ[t-1, 2*t-1]֮�䣬���������Min = t - 1\n
        /// ����ɾ�ؼ���K���ڵĽ�����Ҷ������K������ǰ��(����)K'ȡ��K��Ȼ���Ҷ����ɾȥK'��\n
        /// ��Ҷ��*x��ʼɾȥĳ�ؼ���K����������Ϊ��\n
        /// - ����һ����x->keynum>Min����ֻ��ɾȥK������ָ��(*x��Ҷ�ӣ�K����ָ��Ϊ��)����ʹɾ������������\n
        /// - ���ζ�����x->keynum=Min����Ҷ���еĹؼ��ָ���������Сֵ��ɾK������ָ�����ƻ�B-��������(3)��\n
        ///			��*x����(����)���ֵܽ��*y�еĹؼ�����Ŀ����Min����*y�е����(����С)�ؼ���������˫�׽��*parent��
        ///			������*parent����Ӧ�Ĺؼ���������x�С���Ȼ�����ƶ�ʹ��˫���йؼ�����Ŀ���䣻*y���Ƴ�һ���ؼ��֣�����
        ///			keynum��1������ԭ����Min���ʼ���1���ؼ��ֺ�keynum�Դ��ڵ���Min����*x��������һ���ؼ��֣���ɾK��*x��
        ///			����Min���ؼ��֡��漰�ƶ��ؼ��ֵ�������������B-��������(3)�� ����������������B��������(1)��
        ///			�ƶ���ɺ�ɾ�������������\n
        /// - ����������*x�������ڵ������ֵ�(Ҳ����ֻ��һ���ֵ�)�еĹؼ�����Ŀ��Ϊ��СֵMin�����������ƶ������Ͳ���Ч��
        ///			��ʱ��*x�������\n
        ///			�ֵܺϲ���������*x�������ֵ�*y(�������ֵܵ������������)����*x��ɾȥK�����������󣬽�˫�׽��*parent
        ///			�н���*x��*y֮��Ĺؼ�\n
        ///			��K����Ϊ�м�ؼ��֣��벢x��*y�еĹؼ���һ��"�ϲ�"Ϊһ���µĽ��ȡ��*x��*y����Ϊ*x��*yԭ����Min����
        ///			���֣���˫�������˵�K'��\n
        ///			���˴�*x��ɾ����K�����½����ǡ��2Min(��2��m/2��-2��m-1)���ؼ��֣�û���ƻ�B-��������(3)��������K'��
        ///			˫�����Ƶ��½����൱\n
        ///			�ڴ�*parent��ɾȥ��K'����parent->keynumԭ����Min����ɾ���������˽���������ͬ��Ҫͨ���ƶ�*parent��
        ///			�����ֵ��еĹؼ��ֻ�\n
        ///			*parent���� �����ֵܺϲ��ķ�����ά��B-�����ʡ������£��ϲ����������ϴ���������������ֻ��һ���ؼ�
        ///			��ʱ���ϲ���������ʹ����\n
        ///			�㼰���������Ӻϲ���һ���µĸ����Ӷ�ʹ�������ĸ߶ȼ���һ�㡣<br/>
        ///	@note		���ڻ�ͷ���������ֶַ��˵ķ���Ҳ��ֻ�ʺ���ѧԺ�ɣ����ڴ��в����������У�������ϵͳ�о�����������
        ///				���ķ��������ٴ��̵ķ��ʴ�����һ�й��������ġ���ʵ����������һ�˷���Ҳ��������ʵ�֣�һ��Ҫ�һ���
        ///				��ʵ������
        bool Delete( int key_to_del )
        {
            auto found_node = Search( key_to_del );
            if ( found_node.first == nullptr )		//�Ҳ���ֵΪkey_to_del�Ľ��
            {
                return false;
            }

            if ( !found_node.first->IsLeaf )		//��Ҫɾ���Ľ�㲻��Ҷ�ӽ��ʱ������ǰ�����滻����ɾ������ǰ��
            {
                //ǰ��
                BTreeNode *previous_node = found_node.first->Childs[found_node.second];
                while ( !previous_node->IsLeaf )
                {
                    previous_node = previous_node->Childs[previous_node->Childs.size() - 1];
                }

                //�滻
                found_node.first->Keys[found_node.second] = previous_node->Keys[previous_node->Keys.size() - 1];
                found_node.first = previous_node;
                found_node.second = previous_node->Keys.size() - 1;
            }

            //�����found_nodeһ����Ҷ�ӽ��
            assert( found_node.first->IsLeaf );
            _DeleteLeafNode( found_node.first, found_node.second );

            return true;
        }

        /// ʹ��Graphiviz��ʾ��ǰB�����ڲ��ṹ
        void Display()
        {
            stringstream ss;

            ss << "digraph graphname" << ( rand() % 1000 ) << "{" << endl
               << "    node [shape = record,height = .1];" << endl;
            _GetDotLanguageViaNodeAndEdge( ss, _root );
            ss << "}" << endl;

            qi::ShowGraphvizViaDot( ss.str() );
        }


    private:
        void _ReleaseNode( BTreeNode *node )
        {
            for_each( node->Childs.begin(), node->Childs.end(), [&]( BTreeNode * c )
            {
                _ReleaseNode( c );
            } );
            delete node;
        }

        /// @brief ɾ��B���е�һ��Ҷ�ӽ��
        ///
        /// @param	node	Ҫɾ����Ҷ�ӽ�㣡
        /// @param	index	Ҫɾ����Ҷ�ӽ���ϵĵڼ���ֵ
        /// @note			���뱣֤�����node���ΪҶ�ӽ��
        void _DeleteLeafNode( BTreeNode *node, size_t index )
        {
            assert( node && node->IsLeaf );

            if ( node == _root )
            {
                //Ҫɾ����ֵ�ڸ�����ϣ����Ҵ�ʱ�����Ҳ��Ҷ�ӽ�㣬��Ϊ������������ʱҪ��֤node������Ҷ�ӽ��
                _root->Keys.erase( _root->Keys.begin() + index );
                if ( _root->Keys.empty() )
                {
                    //��Ϊ��һ�ÿ�B��
                    delete _root;
                    _root = nullptr;
                }
                return;
            }

            //�����ǷǸ��������

            if ( node->Keys.size() > _t - 1 )
            {
                //Ҫɾ���Ľ����Key����Ŀ>t-1�������-1Ҳ�������B��������
                node->Keys.erase( node->Keys.begin() + index );
            }
            else	//�����ƽ��
            {
                //�Ƿ�赽��һ������
                bool		borrowed = false;

                //���Ŵ����ֵܽ�һ�����
                BTreeNode	*left_brother = _GetLeftBrother( node );
                if ( left_brother && left_brother->Keys.size() > _t - 1 )
                {
                    int index_in_parent = _GetIndexInParent( left_brother );
                    BTreeNode *parent = node->Parent;

                    node->Keys.insert( node->Keys.begin(), parent->Keys[index_in_parent] );
                    parent->Keys[index_in_parent] = left_brother->Keys[left_brother->KeysSize() - 1];
                    left_brother->Keys.erase( left_brother->Keys.end() - 1 );

                    ++index;
                    borrowed = true;
                }
                else
                {
                    //�����ֵܽ費��ʱ�����Ŵ����ֵܽ�һ�����
                    BTreeNode	*right_brother = _GetRightBrother( node );
                    if ( right_brother && right_brother->Keys.size() > _t - 1 )
                    {
                        int index_in_parent = _GetIndexInParent( node );
                        BTreeNode *parent = node->Parent;

                        node->Keys.push_back( parent->Keys[index_in_parent] );
                        parent->Keys[index_in_parent] = right_brother->Keys[0];
                        right_brother->Keys.erase( right_brother->Keys.begin() );

                        borrowed = true;
                    }
                }

                if ( borrowed )
                {
                    //��Ϊ�赽�˽�㣬���Կ���ֱ��ɾ�����
                    _DeleteLeafNode( node, index );
                }
                else
                {
                    //���Ҷ��費��ʱ��ɾ���ٺϲ�
                    node->Keys.erase( node->Keys.begin() + index );
                    _UnionNodes( node );
                }
            }
        }

        /// @brief node��һ�����ڵĽ����кϲ�
        ///
        /// ����ѡȡ���ֵܽ�㣬�ٴξ�ѡ�����ֵܽ��
        void _UnionNodes( BTreeNode * node )
        {
            if ( node )
            {
                if ( node == _root )	//node��ͷ���
                {
                    if ( _root->Keys.empty() )
                    {
                        //ͷ��������ƶ�һ������ʱ���ĸ߶�-1
                        _root = _root->Childs[0];
                        _root->Parent = nullptr;

                        delete node;
                        return;
                    }
                }
                else
                {
                    if ( node->KeysSize() < _t - 1 )
                    {
                        BTreeNode *left_brother = _GetLeftBrother( node );
                        if ( left_brother == nullptr )
                        {
                            left_brother = _GetRightBrother( node );
                            swap( node, left_brother );
                        }

                        //�����ֵܽ��кϲ�
                        int index_in_parent = _GetIndexInParent( left_brother );
                        node->Keys.insert( node->Keys.begin(), node->Parent->Keys[index_in_parent] );
                        node->Parent->Keys.erase( node->Parent->Keys.begin() + index_in_parent );
                        node->Parent->Childs.erase( node->Parent->Childs.begin() + index_in_parent + 1 );
                        left_brother->Keys.insert( left_brother->Keys.end(), node->Keys.begin(), node->Keys.end() );
                        left_brother->Childs.insert( left_brother->Childs.begin(), node->Childs.begin(), node->Childs.end() );
                        for_each( left_brother->Childs.begin(), left_brother->Childs.end(), [&]( BTreeNode * c )
                        {
                            c->Parent = left_brother;
                        } );

                        delete node;
                        _UnionNodes( left_brother->Parent );
                    }
                }
            }
        }

        pair<BTreeNode *, size_t> _SearchInNode( BTreeNode *node, int key )
        {
            if ( !node )
            {
                //δ�ҵ�����Ϊ�յ����
                return make_pair( static_cast<BTreeNode *>( nullptr ), 0 );
            }
            else
            {
                int index = 0;
                while ( index < node->Keys.size() && key >= node->Keys[index] )
                {
                    if ( key == node->Keys[index] )
                    {
                        return make_pair( node, index );
                    }
                    else
                    {
                        ++index;
                    }
                }

                if ( node->IsLeaf )
                {
                    //�Ѿ��ҵ����ˣ�������������δ�ҵ�
                    return make_pair( static_cast<BTreeNode *>( nullptr ), 0 );
                }
                else
                {
                    return _SearchInNode( node->Childs[index], key );
                }
            }
        }

        void _GetDotLanguageViaNodeAndEdge( stringstream &ss, BTreeNode *node )
        {
            if ( node && !node->Keys.empty() )
            {
                int index = 0;
                ss << "    node" << node->Keys[0] << "[label = \"";
                while ( index < node->Keys.size() )
                {
                    ss << "<f" << 2 * index << ">|";
                    ss << "<f" << 2 * index + 1 << ">" << node->Keys[index] << "|";
                    ++index;
                }
                ss << "<f" << 2 * index << ">\"];" << endl;;

                if ( !node->IsLeaf )
                {
                    for( int i = 0; i < node->Childs.size(); ++i )
                    {
                        BTreeNode *c = node->Childs[i];
                        ss << "    \"node" << node->Keys[0] << "\":f" << 2 * i << " -> \"node" << c->Keys[0] << "\":f" << ( 2 * c->Keys.size() + 1 ) / 2 << ";" << endl;
                    }
                }

                for_each( node->Childs.begin(), node->Childs.end(), [&]( BTreeNode * c )
                {
                    _GetDotLanguageViaNodeAndEdge( ss, c );
                } );
            }
        }

        /// �õ�һ���������ֵܽ�㣬������������ֵܽ���򷵻�nullptr
        BTreeNode * _GetLeftBrother( BTreeNode *node )
        {
            if ( node && node->Parent )
            {
                BTreeNode *parent = node->Parent;
                for ( int i = 1; i < parent->Childs.size(); ++i )
                {
                    if ( parent->Childs[i] == node )
                    {
                        return parent->Childs[i - 1];
                    }
                }
            }
            return nullptr;
        }

        /// �õ�һ���������ֵܽ�㣬������������ֵܽ���򷵻�nullptr
        BTreeNode * _GetRightBrother( BTreeNode *node )
        {
            if ( node && node->Parent )
            {
                BTreeNode *parent = node->Parent;
                for ( int i = 0; i < static_cast<int>( parent->Childs.size() ) - 1; ++i )
                {
                    if ( parent->Childs[i] == node )
                    {
                        return parent->Childs[i + 1];
                    }
                }
            }
            return nullptr;
        }

        /// �õ�һ��������丸��������ڵڼ����ӽ��
        /// @return	����-1ʱ��ʾ����
        int _GetIndexInParent( BTreeNode *node )
        {
            assert( node && node->Parent );

            for ( int i = 0; i < node->Parent->Childs.size(); ++i )
            {
                if ( node->Parent->Childs[i] == node )
                {
                    return i;
                }
            }

            return -1;
        }


        BTreeNode	*_root;			///< B���ĸ����ָ��
        int			_t;				///< B���� ��С�����������еĽ���Keys�ĸ���Ӧ��t-1 <= n <= 2t-1�����˸�����������Ϊ1��Key
    };


    /// B��
    void testBTree()
    {
        BTree btree( 3 );

        for ( int i = 0; i < 20; ++i )
        {
            btree.Insert( rand() % 100 + 1 );
        }
        btree.Display();
        for ( int i = 1; i <= 100; i += 2 )
        {
            btree.Delete( i );
        }
        btree.Display();
        for ( int i = 0; i <= 100; i += 2 )
        {
            btree.Delete( i );
        }
        btree.Display();
        for ( int i = 0; i < 30; ++i )
        {
            btree.Insert( rand() % 1000 + 1 );
        }
        //btree.Delete(501);
        ////btree.Display();
        //btree.Delete(869);
        //btree.Delete(896);
        //btree.Display();
        //btree.Delete(828);
        btree.Display();
    }
}
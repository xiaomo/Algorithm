//////////////////////////////////////////////////////////////////////////
/// @file		binary_search_tree.cpp
/// @brief		���������
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
/// 2011/06/17   13:02	1.0	̷����	����


#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
#include <sstream>
#include "graphviz_shower.h"
using namespace std;

namespace ita
{
	/// @brief ���������
	///
	/// ����������Ķ��壺���κν��X�����������еĹؼ�����󲻳���key[X]�����������еĹؼ�����С��С��key[x]��
	/// ����֤�����������Ķ������ƽ������µ���Ϊ���ӽ����������µ���Ϊ�������ǽӽ������µ���Ϊ������һ����n���ؼ������������Ķ���������������߶�ΪO(lgn)
	class BinarySearchTree
	{
	private:
		/// ����������еĽ��
		struct _Node
		{
			int Value;
			_Node *Parent;
			_Node *Left;
			_Node *Right;
		};

	public:
		BinarySearchTree() : _root( nullptr )
		{}

		~BinarySearchTree()
		{
			//�Ӹ���㿪ʼ�ݹ������
			_RecursiveReleaseNode( _root );
		}

		/// @brief ����һ�����
		///
		/// �����������в���һ��ֵ
		/// @param	new_value	Ҫ�����ֵ
		/// @return				�Ƿ����ɹ���ʧ����ζ�������Ѿ����ڸ�ֵ
		bool Insert( int const new_value )
		{
			if ( Search( new_value ) )
			{
				//�Ѿ�����
				return false;
			}

			if ( !_root )
			{
				//������ǵ�1���ڵ�
				_root = new _Node();
				_root->Value = new_value;
				return true;
			}

			//�ǵ�1���ڵ�
			_Node *current_node = _root;

			while ( current_node )
			{
				_Node *&next_node_pointer = ( new_value > current_node->Value ? current_node->Right : current_node->Left );
				if ( next_node_pointer )
				{
					current_node = next_node_pointer;
				}
				else
				{
					next_node_pointer = new _Node();
					next_node_pointer->Value = new_value;
					next_node_pointer->Parent = current_node;
					break;
				}
			}

			return true;
		}

		/// @brief ɾ�����
		///
		/// �ڶ����������ɾ��һ��ֵ
		/// @param	delete_value	Ҫɾ����ֵ
		/// @return					�Ƿ�ɾ���ɹ���ɾ��ʧ����ζ������û�����ֵ�Ľ��
		bool Delete( int const delete_value )
		{
			_Node *delete_node = _Search( _root, delete_value );
			if ( !delete_node )
			{
				//δ�ҵ��õ�
				return false;
			}
			else
			{
				_DeleteNode( delete_node );
				return true;
			}
		}

		/// @brief ����Ԫ��
		///
		/// �ڵ�ǰ����������в���ĳһֵ
		/// @param	search_value	Ҫ���ҵ�ֵ
		/// @return					�Ƿ��ڶ��������ҵ�ֵΪsearch_value�Ľ��
		/// @retval		true		���ҵ��˸�Ԫ��
		/// @retval		false		�Ҳ�����Ԫ��
		bool Search( int const search_value ) const
		{
			return _Search( _root, search_value ) != nullptr;
		}

		/// @brief ʹ��dot������ǰ���������
		void Display() const
		{
			stringstream ss;
			ss << "digraph graphname" << ( rand() % 1000 ) << "{" << endl
				<< "    node [shape = record,height = .1];" << endl;
			_Display( ss, _root );
			ss << "}" << endl;

			qi::ShowGraphvizViaDot( ss.str() );
		}

	private:
		/// ������ɾ������
		///
		/// Ψһ�е��Ѷȵĵط�������ɾ��ͬʱ�������������Ľ��ʱ��Ҫ����һЩ����\n
		/// �����������е���ȵĸ��ӣ���ʵ���Ժܼ򵥵�˵���ף����������Ľ��x���ҵ�x����ǰ�������̣�y����x��ֵ�滻Ϊ
		/// y��ֵ��Ȼ��ݹ�ɾ��y���Ϳ����ˡ���Ϊyһ��û������������̶�Ӧû���������������Եݹ�ɾ����ʱ����Ǻܼ򵥵�
		/// ����ˡ�
		/// @note		������ķ�����ȷ�����Ͻ��ܵ�Ҫ�ö���������⣬�����﷽�����õĵĹؼ����ڣ�\n
		///				�ҵ�_DeleteNode�Ĳ�����Ҫɾ���Ľ���ָ�룬��������ɾ��ͬʱ�������������Ľ��ʱ���ҿ���ֱ��ʹ��y
		///				��ֵ����x��㣬�ٵݹ�ɾ��y��㡣����������Ĳ������ǽ���ָ����ǽ���ֵ���ٵݹ�ɾ��y����ֵ
		///				ʱ�ͻ�����⣬��Ϊ��ʱx����ֵ==y����ֵ�ˡ��ţ��ҵ������Խ��ָ��Ϊ������˼·��ȷ����
		void _DeleteNode( _Node * delete_node )
		{
			if ( delete_node->Left && delete_node->Right )
			{
				//Ҫɾ���Ľ��ͬʱ������������������
				//ǰ����㣺ǰ��һ�����ڣ���Ϊ�ý��ͬʱ������������
				_Node *previous_node = _GetPreviousNode( delete_node );

				delete_node->Value = previous_node->Value;

				//previous_ndeһ��û���������������ٵݹ����һ���������if��else��֧
				_DeleteNode( previous_node );
			}
			else
			{
				//Ҫɾ���Ľ��������һ���ӽ��Ϊ��
				//sub_nodeΪdelete_node������
				//sub_nodeҪôΪdelete_node����������ҪôΪdelete_node����������������delete_node���ӽ��ʱΪ��
				_Node *sub_node = ( delete_node->Left ? delete_node->Left : delete_node->Right );

				if ( delete_node->Parent == nullptr )
				{
					//�ǵ�1�����
					_root = sub_node;
				}
				else
				{
					( delete_node->Parent->Left == delete_node 
						? delete_node->Parent->Left 
						: delete_node->Parent->Right ) 
						= sub_node;

					if ( sub_node )
					{
						//��delete_node���ӽ��ʱ��Ҫ�����ӽ���Parentָ��
						sub_node->Parent = delete_node->Parent;
					}
				}

				delete delete_node;
			}
		}

		/// @brief �õ�һ��ͬʱ�������������Ľڵ��ǰ��
		///
		/// @note		node��ǰ��һ�����ڣ���Ϊnodeͬʱ���������������������������������Ⱦ�����������㷨�Ľ���Ǵ���ġ�\n
		///				�Ժ��Ϊ����������������������ʱ��Ӧ��һ·���ϴ��ݣ�ֱ���ҵ�����㣨û�к�̣��������ҵ�һ�η����������ݣ�����ҵ���Ϊֹ���ҵĴ���������ﷸһ�δ����ˣ�����Ϊ�ܼ򵥵ģ�
		_Node * _GetPreviousNode( _Node * node )
		{
			if ( !node->Left || !node->Right )
			{
				//�Ⱦ������������㣬�����������ƵĽ���ǰ���㷨����������
				throw std::exception( "node����ͬʱ������������������" );
			}

			//����ע���Ⱦ�������node��һ��ͬʱ�������������Ľ�㣬�����㷨����������
			//�����ǰ��������һ�£����ҵ�ͷ
			node = node->Left;
			while ( node->Right )
			{
				node = node->Right;
			}

			return node;
		}

		void _RecursiveReleaseNode( _Node *node )
		{
			if ( node )
			{
				_RecursiveReleaseNode( node->Left );
				_RecursiveReleaseNode( node->Right );
				delete node;
			}
		}

		/// �ǵݹ����һ�����
		_Node * _Search( _Node *node, int const search_value ) const
		{
			while ( node && node->Value != search_value )
			{
				if ( search_value < node->Value )
				{
					node = node->Left;
				}
				else
				{
					node = node->Right;
				}
			}

			//���������nodeΪ�վ���δ�ҵ�
			return node;
		}

		void _Display( stringstream &ss, _Node *node ) const
		{
			if ( node )
			{
				ss << "    node" << node->Value << "[label = \"<f0>|<f1>" << node->Value << "|<f2>\"];" << endl;

				if ( node->Left )
				{
					ss << "    \"node" << node->Value << "\":f0 -> \"node" << node->Left->Value << "\":f1;" << endl;
					_Display( ss, node->Left );
				}

				if ( node->Right )
				{
					ss << "    \"node" << node->Value << "\":f2 -> \"node" << node->Right->Value << "\":f1;" << endl;
					_Display( ss, node->Right );
				}
			}
		}

		_Node *_root;			///< ����������ĸ����
	};


	/// ���Զ��������
	int testBinarySearchTree()
	{
		BinarySearchTree bst;
		//�����ֵ����һ�ö��������
		for ( int i = 0; i < 10; ++i )
		{
			bst.Insert( rand() % 100 );
		}
		bst.Display();

		//ɾ�����е�����ֵ���
		for ( int i = 1; i < 100; i += 2 )
		{
			if( bst.Delete( i ) )
			{
				cout << "### Deleted [" << i << "] ###" << endl;
			}
		}
		bst.Display();

		//����100���ڵ���������ڶ���������У�����ʾ
		cout << endl;
		for ( int i = 0; i < 100; i += 1 )
		{
			if ( bst.Search( i ) )
			{
				cout << "����[" << i << "]Ԫ�أ�\t�ɹ�" << endl;
			}
		}

		return 0;
	}
}
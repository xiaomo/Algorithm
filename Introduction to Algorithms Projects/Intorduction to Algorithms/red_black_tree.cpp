//////////////////////////////////////////////////////////////////////////
/// @file		red_black_tree.cpp
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
/// 2011/06/17   13:23	1.0	̷����	����


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
	/// @brief �����
	///
	/// �������漸������(�������)�Ķ�������������Ϊ�������
	/// -# ÿ�������Ǻ�ɫ�������Ǻ�ɫ��
	/// -# ������Ǻڵġ�
	/// -# ���е�Ҷ���(NULL)�Ǻ�ɫ�ġ���NULL����Ϊһ���ڱ���㣬����Ӧ��ָ��NULL��ָ�룬������ָ����NULL��㡣��
	/// -# ���һ������Ǻ�ɫ�ģ��������������ӽڵ㶼�Ǻ�ɫ�ġ�
	/// -# ��ÿ����㣬�Ӹý�㵽�������������·���ϰ�����ͬ��Ŀ�ĺڽ�㡣
	///
	/// ����������ʣ�
	/// - �ڸ߶ȵĶ��壺 ��ĳ��������(�������ý��)����һ��Ҷ��������һ��·���ϣ���ɫ���ĸ�����Ϊ�ý��x�ĺڸ߶ȡ�
	/// ������ĺڸ߶ȶ���Ϊ������ĺڸ߶ȡ�
	/// - ���������������ʵ���еõ�����Ӧ�õĸ������ݽṹ��C++STL�еĹ�������map,set���Ǻ������Ӧ�ã����Ա�׼��������
	/// Ч��̫���ˣ����ñ�׼����������ʹ�ñ�׼����������\n Linux�ں��е��û�̬��ַ�ռ����Ҳʹ���˺������
	/// - ���������ࡰ<b>ƽ���</b>���������е�һ�֣����ȣ�<span style="color:#FF0000 ">�������һ�ֽ���ƽ��Ķ�����
	/// </span>�������ܱ�֤���������£������Ķ�̬���ϲ�����ʱ��ΪO(lgn)��
	/// - ͨ�����κ�һ���Ӹ���Ҷ�ӵ�·���ϸ��������ɫ��ʽ�����ƣ������ȷ��û��һ��·���������·����������������ǽӽ�ƽ��ġ�
	/// - һҪȫ�Ǻڽ�����������Ҳ���������Ķ��塣����������Ч�ʱ���ͷǳ��߰�������Ч����õĶ������ˣ�����˵����
	/// �������һ����������ͨ�ĺ����Ҫ��û������������ô�ϸ�
	/// - �����֮������ô��Ч������Ϊ����<span style="color:#FF0000 ">����ƽ��</span>�ģ��ֲ�Ҫ����ȫ��ƽ�⣬������ά
	/// ���Ĵ��ۡ��ڼ������ѧ���д��������������ӣ�ʹ�ý��ƵĶ��������Ч�ʡ������ѡ�쳲������ѵȵ�����ʤ����
	/// @param	TKey	����м�������
	/// @param	TValue	�����ֵ������
	template<typename TKey, typename TValue>
	class RBTree
	{
	public:
		/// ������н����ɫ��ö��
		enum RBTreeNodeColor
		{
			BLACK,			///< ��ɫ
			RED				///< ��ɫ
		};

		/// ������еĽ��
		struct RBTreeNode
		{
			TKey				Key;			///< ����е�KEY
			TValue				Value;			///< ����е�ֵ
			RBTreeNodeColor		Color;			///< ������ɫ����ɫ���Ǻ�ɫ
			RBTreeNode			*Parent;		///< �����ָ��
			RBTreeNode			*Left;			///< ����ָ��
			RBTreeNode			*Right;			///< �Һ���ָ��

			/// @brief ����Ƿ���Ч���ڱ����nil ������Ч��㣩
			/// @return			�ý���Ƿ�Ϊ��Ч��㣬����Ϊnil���
			/// @retval	true	��nil���
			/// @retval false	nil���
			inline bool IsValid() const
			{
				return ( this != s_nil );
			}
		};

		RBTree()
		{
			if ( !s_nil )
			{
				//Ҷ�ӽ����һ������ĺڽ��
				s_nil = new RBTreeNode();
				s_nil->Color = BLACK;
			}

			_root = s_nil;
		}

		~RBTree()
		{
			_RecursiveReleaseNode( _root );
		}

		/// @brief ����һ�����
		///
		/// ������Ĳ�������������Z������T�У��ͺ���T��һ����ͨ�Ķ��������һ����Ȼ��Z��Ϊ��ɫ��Ϊ��֤��������ܼ���
		/// ���֣����ǵ���һ�������������Խ��������ɫ����ת����ô�����������ǻ۵ģ����ȣ�������Z��λ�õ�ȷӦ�ú���ͨ
		/// ���������һ������Ϊ����������������һ�ö����������Ȼ��Z��Ϊ��ɫ����Ϊ�˱�֤����5����ȷ�ԣ���Ϊ����5��
		/// �����ƻ����������Իָ��ģ�������п��ܱ��ƻ������ʾ�ֻʣ������2������4�ˣ��ⶼ����ͨ�������ĸ������������
		/// ���ġ�\n
		/// ������������ƻ������ʣ�
		/// - ����2������һ�ÿ������в������ʱ������
		/// - ����4�����½�㱻���뵽��ɫ���֮��ʱ������
		bool Insert( TKey key, TValue value )
		{
			if ( Search( key )->IsValid() )
			{
				//key�ظ������ʧ��
				return false;
			}
			else
			{
				//����ӵĽ��Ϊ���㣬��Left=Right=s_nil
				RBTreeNode *new_node = new RBTreeNode();
				new_node->Key = key;
				new_node->Value = value;
				new_node->Color = RED;
				new_node->Left = new_node->Right = s_nil;

				_InsertAsNormalBSTree( new_node );
				_InsertFixup( new_node );
				return true;
			}
		}

		/// @brief ɾ��һ�����
		/// �������ɾ���������Ͳ������һ��������BST��ɾ����������Ȼ�������Ӧ�ĸ�����������Ӧ�ĵ�����\n
		/// ����ֻ�б�ɾ���Ľ��Ϊ�ڽ��ʱ����Ҫ�����޲����������£�
		/// - ���и����ĺڸ߶ȶ�û�б仯
		/// - �������������ڵĺ�ɫ���
		/// - ��Ϊ�����ɾ���ĵ��Ǻ�ɫ���Ͳ������Ǹ������Ը���Ȼ�Ǻ�ɫ��
		///
		/// ����ɾ���˺ڽ��֮�󣬺����������5���ƻ�������˵��������5���ƻ�����޸��Ѷ������ġ�����������޸�����ʹ��
		/// ��һ�����µ�˼�룬����Ϊ��ɾ���Ľ����ӽ���ж����һ�ֺ�ɫ������һ�ض���ĺ�ɫ����֮������5�͵õ��˼���
		/// ��Ȼ����ͨ��ת�Ƶķ����𲽰���һ�ض���ĺ�ɫ������ת��ֱ�������ߺ�ɫ�Ľ�㣬���������һ�ض���ĺ�ɫ��\n
		/// ɾ�������п��ܱ��ƻ������ʣ�
		/// - ����2����y�Ǹ�ʱ����y��һ�������Ǻ�ɫ������ʱ������ӳ�Ϊ����㣻
		/// - ����4����x��p[y]���Ǻ�ɫʱ��
		/// - ����5������y��·���У��ڸ߶ȶ������ˣ�
		bool Delete( TKey key )
		{
			RBTreeNode *z = Search( key );
			if ( z->IsValid() )
			{
				//ʵ��Ҫɾ���Ľ�㣬��Ϊ�������һ������������ʵ��ɾ��y֮��ʹﵽ��z��Ч��
				RBTreeNode *y = nullptr;
				if ( !z->Left->IsValid() || !z->Right->IsValid() )
				{
					//������һ������Ϊnil
					y = z;
				}
				else
				{
					//���Һ��Ӿ���Ϊnil�����Һ��
					y = _Successor( z );
				}

				RBTreeNode *x = ( y->Left->IsValid() ? y->Left : y->Right );
				x->Parent = y->Parent;

				if ( !y->Parent->IsValid() )
				{
					_root = x;
				}
				else
				{
					if ( y == y->Parent->Left )
					{
						y->Parent->Left = x;
					}
					else
					{
						y->Parent->Right = x;
					}
				}

				if ( y != z )
				{
					z->Key = y->Key;
					z->Value = y->Value;
				}

				if ( y->Color == BLACK )
				{
					_DeleteFixup( x );
				}

				delete y;	//���ʵ��ɾ����y���
				return true;
			}
			else
			{
				//Ҫɾ���Ľ�㲻����
				return false;
			}
		}

		/// �ں����������һ�����
		RBTreeNode * Search( TValue const &value )
		{
			RBTreeNode *node = _root;
			while ( node != s_nil && node->Value != value )
			{
				node = ( value < node->Value ? node->Left : node->Right );
			}
			return node;
		}

		/// �жϺ�����Ƿ�Ϊ��
		bool Empty()
		{
			return !( _root->IsValid() );
		}

		/// @brief ��ʾ��ǰ�����������״̬
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
		void _RecursiveReleaseNode( RBTreeNode *node )
		{
			if ( node->IsValid() )
			{
				_RecursiveReleaseNode( node->Left );
				_RecursiveReleaseNode( node->Right );
				delete node;
			}
		}

		void _Display( stringstream &ss, RBTreeNode *node ) const
		{
			if ( node->IsValid() )
			{
				ss << "    node" << node->Value << "[label = \"<f0>|<f1>" << node->Value << "|<f2>\", color = " << ( node->Color == RED ? "red" : "black" ) << "];" << endl;

				if ( node->Left->IsValid() )
				{
					ss << "    \"node" << node->Value << "\":f0 -> \"node" << node->Left->Value << "\":f1;" << endl;
					_Display( ss, node->Left );
				}

				if ( node->Right->IsValid() )
				{
					ss << "    \"node" << node->Value << "\":f2 -> \"node" << node->Right->Value << "\":f1;" << endl;
					_Display( ss, node->Right );
				}
			}
		}

		/// @brief ��һ�����򵥵ؼ�������
		///
		/// �Ӹú����Ϊ��ͨ�Ķ���������򵥵Ľ��в����������Ҫ�ڴ�֮���������������������
		/// @note		һ��Ҫ��֤node->Keyһ����һ���µ�ֵ�����������ѭ���������ﲻ���
		void _InsertAsNormalBSTree( RBTreeNode *node )
		{
			if ( !_root->IsValid() )
			{
				//������ǵ�1���ڵ�
				_root = node;
				_root->Left = _root->Right = _root->Parent = s_nil;
				_root->Color = BLACK;
				return;
			}

			//�ǵ�1���ڵ�
			RBTreeNode *current_node = _root;

			while ( true )
			{
				RBTreeNode *&next_node_pointer = ( node->Key > current_node->Key ? current_node->Right : current_node->Left );
				if ( next_node_pointer->IsValid() )
				{
					current_node = next_node_pointer;
				}
				else
				{
					//���������Ĳ������
					node->Parent = current_node;
					next_node_pointer = node;
					break;
				}
			}
		}

		/// @brief �Բ���������޸�
		///
		/// ���ڶԺ�����Ĳ�������ƻ��˺���������ʣ�������Ҫ������������
		/// @note		node�Ľ������Ҫ����Ľ�㣬�������ƻ��˺�����ʣ���һ���Ǻ���
		void _InsertFixup( RBTreeNode * node )
		{
			while ( node->Parent->Color == RED )
			{
				//��ʶnode�ĸ�����Ƿ�Ϊnode���游��������
				bool parent_is_left_child_flag = ( node->Parent == node->Parent->Parent->Left );
				//������
				RBTreeNode *uncle = parent_is_left_child_flag ? node->Parent->Parent->Right : node->Parent->Parent->Left;
				if ( uncle->Color == RED )
				{
					//case1
					node->Parent->Color = BLACK;
					uncle->Color = BLACK;
					node->Parent->Parent->Color = RED;
					node = node->Parent->Parent;
				}
				else
				{
					if ( node == ( parent_is_left_child_flag ? node->Parent->Right : node->Parent->Left ) )
					{
						//case2
						node = node->Parent;
						parent_is_left_child_flag ? _LeftRotate( node ) : _RightRotate( node );
					}

					//case3
					node->Parent->Color = BLACK;
					node->Parent->Parent->Color = RED;
					parent_is_left_child_flag ? _RightRotate( node->Parent->Parent ) : _LeftRotate( node->Parent->Parent );
				}
			}

			//��������2���ƻ�ֻ��Ҫ��򵥵�һ�仰
			_root->Color = BLACK;
		}

		/// ����
		///
		/// ��ת������һ���ܱ��ֶ�����������ʵĲ������ֲ�����
		void _LeftRotate( RBTreeNode * node )
		{
			if ( !( node->IsValid() && node->Right->IsValid() ) )
			{
				//��������Ҫ��Է��ڱ����в���������Ҫ���Һ���Ҳ�����ڱ�
				throw std::exception( "��������Ҫ��Է��ڱ����в���������Ҫ���Һ���Ҳ�����ڱ�" );
			}
			else
			{
				//node���Һ���
				RBTreeNode *right_son = node->Right;

				node->Right = right_son->Left;
				if ( right_son->Left->IsValid() )
				{
					right_son->Left->Parent = node;
				}
				right_son->Parent = node->Parent;
				if ( !( node->Parent->IsValid() ) )
				{
					_root = right_son;
				}
				else
				{
					if ( node == node->Parent->Left )
					{
						node->Parent->Left = right_son;
					}
					else
					{
						node->Parent->Right = right_son;
					}
				}
				right_son->Left = node;
				node->Parent = right_son;
			}
		}

		/// ����
		///
		/// ��ת������һ���ܱ��ֶ�����������ʵĲ������ֲ�����
		void _RightRotate( RBTreeNode * node )
		{
			if ( !( node->IsValid() && node->Left->IsValid() ) )
			{
				//��������Ҫ��Է��ڱ����в���������Ҫ������Ҳ�����ڱ�
				throw std::exception( "��������Ҫ��Է��ڱ����в���������Ҫ������Ҳ�����ڱ�" );
			}
			else
			{
				//node������
				RBTreeNode *left_son = node->Left;

				node->Left = left_son->Right;
				if ( left_son->Right->IsValid() )
				{
					left_son->Right->Parent = node;
				}
				left_son->Parent = node->Parent;
				if ( !( node->Parent->IsValid() ) )
				{
					_root = left_son;
				}
				else
				{
					if ( node == node->Parent->Left )
					{
						node->Parent->Left = left_son;
					}
					else
					{
						node->Parent->Right = left_son;
					}
				}
				left_son->Right = node;
				node->Parent = left_son;
			}
		}

		/// ��ɾ���������޸�
		void _DeleteFixup( RBTreeNode *x )
		{
			while( x != _root && x->Color == BLACK )
			{
				bool node_is_parent_left_child = ( x == x->Parent->Left );
				RBTreeNode *w = node_is_parent_left_child ? x->Parent->Right : x->Parent->Left;

				if( w->Color == RED )
				{
					//case1
					w->Color = BLACK;
					x->Parent->Color = RED;
					_LeftRotate( x->Parent );
					w = x->Parent->Right;
				}

				//case2
				if( w->Left->Color == BLACK && w->Right->Color == BLACK )
				{
					//�������Ӷ�Ϊ�ڽ��
					w->Color = RED;
					x = x->Parent;
				}
				else
				{
					//case3
					if( ( node_is_parent_left_child ? w->Right->Color : w->Left->Color ) == BLACK )
					{
						( node_is_parent_left_child ? w->Left->Color : w->Right->Color ) = BLACK;
						w->Color = RED;
						node_is_parent_left_child ? _RightRotate( w ) : _LeftRotate( w );
						w = ( node_is_parent_left_child ? x->Parent->Right : x->Parent->Left );
					}

					//case4
					w->Color = x->Parent->Color;
					x->Parent->Color = BLACK;
					( node_is_parent_left_child ? w->Right->Color : w->Left->Color ) = BLACK;
					node_is_parent_left_child ? _LeftRotate( x->Parent ) : _RightRotate( x->Parent );
					x = _root;
				}
			}

			//���ֻ��Ҫ����xΪ�ڽ��Ϳ��ԣ�_root�ĸı��Ѿ����������Զ�������
			x->Color = BLACK;    //��Ϊ��ɫ��
		}

		/// �õ��ڵ�ĺ��
		RBTreeNode * _Successor( RBTreeNode *node )
		{
			if ( node->Right->IsValid() )
			{
				//�����ҽ��ʱ����һ�£���ͷ
				node = node->Right;
				while ( node->Left->IsValid() )
				{
					node = node->Left;
				}
				return node;
			}
			else
			{
				//�������ҽ��ʱ��һֱ���ϣ�ֱ���ҵ�һ�η��Һ��ӻ򵽸���Ϊֹ
				RBTreeNode *y = node->Parent;
				while ( !y->IsValid() && node == y->Right )
				{
					node = y;
					y = y->Parent;
				}
				return y;
			}
		}


		RBTreeNode *_root;				///< �����
		static RBTreeNode *s_nil;		///< �������Ҷ�ӽ�㣨�ڱ���
	};


	template<typename TKey, typename TValue>
	typename RBTree<TKey, TValue>::RBTreeNode * RBTree<TKey, TValue>::s_nil = nullptr;

	/// �����
	int testRedBlackTree()
	{
		int init[] = {11, 2, 14, 1, 7, 15, 5, 8};
		RBTree<int, int> bst;
		//for ( int i = 0; i < sizeof( init ) / sizeof( init[0] ); ++i )
		//{
		//    bst.Insert( init[i], init[i] );
		//}
		//bst.Insert( 4, 4 );
		//bst.Display();

		//�����ֵ����һ�ö��������
		for ( int i = 0; i < 50; ++i )
		{
			int v = rand() % 100;
			bst.Insert( v, v );
		}
		bst.Display();

		//bst.Delete(5);
		//ɾ�����е�С����
		for ( int i = 0; i < 100; ++i )
		{
			if ( i % 2 == 1 && i < 50 )
			{
				if ( bst.Delete( i ) )
				{
					cout << "Deleted [" << i << "]" << endl;
				}
			}
		}
		bst.Display();
		//ɾ�����еĴ�ż��
		for ( int i = 0; i < 100; ++i )
		{
			if ( i % 2 == 0 && i > 50 )
			{
				if ( bst.Delete( i ) )
				{
					cout << "Deleted [" << i << "]" << endl;
				}
			}
		}
		bst.Display();
		//��������
		for ( int i = 0; i < 50; ++i )
		{
			int v = rand() % 100;
			bst.Insert( v, v );
		}
		bst.Display();
		//ɾ������
		for ( int i = 0; i < 100; ++i )
		{
			if ( bst.Delete( i ) )
			{
				cout << "Deleted [" << i << "]" << endl;
			}

		}
		//bst.Display();

		for ( int i = 0; i < 50; ++i )
		{
			int v = rand() % 100;
			bst.Insert( v, v );
		}
		bst.Display();

		return 0;
	}
}
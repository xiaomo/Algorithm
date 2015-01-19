//////////////////////////////////////////////////////////////////////////
/// @file		hash_table.cpp
/// @brief		ɢ�б�
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
/// 2011/06/17   12:43	1.0	̷����	����

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
using namespace std;


namespace ita
{
	/// @brief ȫ��ɢ�б�
	///
	/// - ȫ��ɢ�б���һ��ʹ�á����ӷ����������ײ�����ɢ�б�����\n
	/// - �������֤�˶����κ����룬�㷨�����нϺõ�ƽ�����ܡ�\n
	/// - ȫ���ɢ�к����飺��HΪһ��ɢ�к��������������Ĺؼ�����Uӳ�䵽{0,1,��,m-1}�У�������һ���������Ϊ��ȫ��ġ������H�������ѡ��һ��ɢ�к��������ؼ���K��Jʱ�����߷�����ײ�ĸ��ʲ�����1/m��
	/// - �������ɢ�к�����ѡȡ���ڡ�<b>ִ�п�ʼ</b>�������ѡȡһ���Ǻ���Ҫ�ģ�Ҫ��Ȼ�ͻ᲻���׵�ʱ����ô���в��ҡ�\n
	///   ������ν�������Ӧ��������⣺����ĳһ��ɢ�б���˵�����ڳ�ʼ��ʱ�Ѿ���a,b�̶��ˣ����Ƕ���һ����δ��ʼ����ȫ��ɢ�б���˵��a,b�����ѡȡ�ġ�
	///
	/// ȫ��ɢ�к����࣬����ѡ��һ���㹻�������p ��ʹ��ÿһ�����ܵĹؼ���k ���䵽0 ��p-1 �ķ�Χ�ڣ�������β��0 ��p-1��\n
	/// �������Ǽ���ȫ����0 �C 15��p Ϊ17���輯��Zp Ϊ{0, 1, 2, ��, p-1}������Zp* Ϊ{1, 2, 3, ��, p-1}��\n
	/// ����p �����������ǿ��Զ���ɢ�к���\n
	///                     h(a, b, k) = ((a*k + b) mod p) mod m\n
	/// ����a ����Zp��b ����Zp*��������������a ��b ���ɵ�ɢ�к���������˺����ء���ȫ��ɢ�С�\n
	/// ȫ��ɢ�еĻ���˼������ִ��<b>��ʼ</b>ʱ����һ����ϸ��Ƶĺ����У������ѡ��һ����Ϊɢ�к�����\n
	/// ʹ֮������Ҫ�洢�Ĺؼ��֡����ܶ���ѡ���������Ĺؼ��֣���ƽ����̬���ܺá�\n
	/// @param	T	ɢ�б���Ҫ�洢��Ԫ������
	template<typename T>
	class UniversalHashTable
	{
	public:
		/// ����һ��ȫ��ɢ�б�,ͬʱ��һ����ϸ��Ƶĺ����У������ѡ��һ����Ϊɢ�к�����
		UniversalHashTable()
		{
			_p = 101;		//һ���㹻�������
			_m = 10;		//�۵ĸ���
			_items.resize( _m, nullptr );
			for ( int i = 0; i < _m; ++i )
			{
				//ȫ�������ú�ͷ���
				_items[i] = new _Node();
				_items[i]->Next = nullptr;
			}

			// ȫ��ɢ�еĻ���˼������ִ��<b>��ʼ</b>ʱ����һ����ϸ��Ƶĺ����У������ѡ��һ����Ϊɢ�к�����
			_a = rand() % ( _p - 1 ) + 1;
			_b = rand() % _p;
		}

		~UniversalHashTable()
		{
			for_each( _items.begin(), _items.end(), []( _Node * item )
			{
				while ( item )
				{
					auto next = item->Next;
					delete item;
					item = next;
				}
			} );
		}

		/// ��ɢ�б��в���һ��Ԫ��
		void Insert( T const &new_value )
		{
			//ʼ�ղ����ڼ����ͷ��ͷ���֮��ĵ�1��λ��
			_Node *new_item = new _Node;
			new_item->Item = new_value;
			new_item->Next = nullptr;
			int hash_value = _HashFunction( new_value );

			new_item->Next = _items[hash_value]->Next;
			_items[hash_value]->Next = new_item;
		}

		/// @brief ��ɢ�б���ɾ��һ��Ԫ��
		///
		/// @return	�Ƿ�ɹ���ɾ��������Ԫ��
		bool Delete( T const &delete_value )
		{
			int hash_value = _HashFunction( delete_value );
			_Node *root = _items[hash_value];

			while ( root->Next )
			{
				if ( root->Next->Item == delete_value )
				{
					auto temp = root->Next;
					root->Next = root->Next->Next;
					delete temp;
					return true;
				}
				else
				{
					root = root->Next;
				}
			}

			return false;
		}

		/// ��ɢ�б�������һ��Ԫ��
		T * Search( T const &search_value )
		{
			int hash_value = _HashFunction( search_value );
			_Node *root = _items[hash_value]->Next;

			while ( root )
			{
				if ( root->Item == search_value )
				{
					return &( root->Item );
				}
				root = root->Next;
			}
			return nullptr;
		}

		/// ��ɢ�б��е����е�Ԫ����ʾ���������
		void Display()
		{
			for ( int i = 0; i < _m; ++i )
			{
				_Node *item = _items[i]->Next;	//����ͷ���

				cout << "��[" << setw( 3 ) << i << setw( 3 ) << "]";
				while ( item )
				{
					cout << " -> " << item->Item;
					item = item->Next;
				}
				cout << endl;
			}
		}


	private:
		/// @brief �ڵ㣨ʹ�õ�����
		///
		/// Ҫ����˫����ͻ᷽��ܶడ
		struct _Node
		{
			T Item;
			_Node *Next;
		};

		/// @brief ȫ��ɢ�к���
		///
		/// ��������һ��ʼʱ���ѡȡ_a,_b���ټ���ѡȡ_p,_m�ķ���������ȫ��ɢ�еĺ������ڣ�����
		/// h(a, b, k) = ((a*k + b) mod p) mod m
		int _HashFunction( T k )
		{
			return static_cast<int>( _a * k + _b ) % _p % _m;
		}


		int _p, _m, _a, _b;			///< ȫ��ɢ�б�ĸ�������
		vector<_Node *> _items;		///< �ۣ��洢�����ļ���ʹ�õ��Ǵ�ͷ���ĵ�����
	};


	/// ����ȫ��ɢ�б���
	int testHashTable()
	{
		UniversalHashTable<int> table;
		cout << "��ʼ��UniversalHashTable���������[0,100)��" << endl;
		for ( int i = 0; i < 100; ++i )
		{
			table.Insert( i );
		}
		table.Display();

		cout << "��ʼɾ������[0,5)��" << endl;
		for ( int i = 0; i < 5; ++i )
		{
			table.Delete( i );
		}
		table.Display();

		for ( int i = 0; i < 10; ++i )
		{
			auto finded = table.Search( i );
			cout << "��ʼ�������[" << i << "]��";
			if ( finded )
			{
				cout << *finded << endl;
			}
			else
			{
				cout <<  "δ�ҵ�" << endl;
			}
		}

		return 0;
	}

}
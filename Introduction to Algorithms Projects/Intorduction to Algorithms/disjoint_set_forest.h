//////////////////////////////////////////////////////////////////////////
/// @file		disjoint_set_forest.h
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
/// 2011/06/17	1.0	̷����	����

namespace ita
{

	/// @brief ��������ʾ��ʵ�ֵ� ���ڲ��ཻ���ϵ����ݽṹ�����鼯��
	///
	/// ʹ���ˡ�·��ѹ�����͡����Ⱥϲ������ּ��������ٲ��鼯������ʱ�䡣\n
	/// ���ַ���ʵ�ֵĲ��鼯������ʱ����ʵ���������Եģ�������������˵�ǳ����Եġ�\n
	/// ���ڲ��ཻ���ϵ����ݽṹ�ֳ�Ϊ�鲢�����ںܶ��Ӧ���У�����ͼ���㷨�о���ʹ�ã����й���������ȣ�����N����ͬ��Ԫ�طֳ�һ�鲻�ཻ�ļ��ϡ�\n
	/// ���ཻ��������������Ҫ�Ĳ�����<span style="color:#FF0000 ">�ҳ�����Ԫ�������ļ���</span> �� <span style="color:#FF0000 ">�ϲ���������</span>��
	class DisjointSetForest
	{
	public:
		/// �����е�һ��Ԫ��
		template<typename T>
		struct DisjointSet
		{
			T				Item;		///< Ԫ�ص�ֵ
			int				Rank;		///< Ԫ�ص���
			DisjointSet		*Parent;	///< Ԫ�صĸ�Ԫ��

			/// ����һ����㣺��ӦMAKE-SET����
			DisjointSet( T const &item ) : Item( item ), Rank( 0 )
			{
				Parent = this;
			}
		};

		#pragma region �鲢����3����������

		/// ����һ�����ϵĲ�����MAKE-SET
		template<typename T>
		static DisjointSet<T> * MakeSet( T const &item )
		{
			return new DisjointSet<T>( item );
		}

		/// �����������ϵĲ�����FIND-SET
		/// @remarks	ʹ����·��ѹ��
		template<typename T>
		static DisjointSet<T> * FindSet( DisjointSet<T> *a_set )
		{
			//·��ѹ��
			if ( a_set != a_set->Parent )		//�жϱ����Ǵ���
			{
				a_set->Parent = FindSet( a_set->Parent );
			}
			return a_set->Parent;
		}

		/// �ϲ�������UNION
		/// @remarks	ʹ���˰��Ⱥϲ�
		template<typename T>
		static void Union( DisjointSet<T> *x, DisjointSet<T> *y )
		{
			_Link( FindSet( x ), FindSet( y ) );
		}

		#pragma endregion

	private:
		template<typename T>
		static void _Link( DisjointSet<T> *x, DisjointSet<T> *y )
		{
			if ( x->Rank > y->Rank )
			{
				y->Parent = x;
			}
			else
			{
				x->Parent = y;
				//���Ⱥϲ�
				if ( x->Rank == y->Rank )
				{
					//ֻ��������ͬʱ�ŻὫ���ĸ�������+1
					++( y->Rank );
				}
			}
		}
	};
}
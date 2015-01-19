#pragma once
//////////////////////////////////////////////////////////////////////////
/// @file		graphics.h
/// @brief		ͼ�����ֱ�ʾ��������1���ڽӱ�����2���ڽӾ���
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
/// 2011/06/17   16:02	1.0	̷����	����


#include <vector>
#include <utility>
using namespace std;

namespace ita
{
    /// ͼ�����ͣ�����ͼ��������ͼ
enum GraphicsType :
    short
    {
        Digraph,			///< ����ͼ
        Undigraph			///< ����ͼ
    };

    /// ʹ���ڽӱ���ʾһ��ͼ
    template<typename T>
    class GraphicsViaAdjacencyList
    {
    public:
        /// �ڽӱ��ϵ�һ�����
        struct AdjacencyListNode
        {
            size_t			AimNodeIndex;	///< Ŀ�궥��ı��
            double			Weight;			///< �������ӱߵ�Ȩֵ
            AdjacencyListNode	*Next;			///< ָ����һ�����
        };

    public:
        /// ͨ���������ʼ��һ��ͼ
        GraphicsViaAdjacencyList( vector<T> const &v, GraphicsType type ) : _v( v ), _e( v.size(), nullptr ), _type( type )
        {

        }

        ~GraphicsViaAdjacencyList()
        {
            for_each( _e.begin(), _e.end(), []( AdjacencyListNode * e )
            {
                while ( e )
                {
                    AdjacencyListNode *temp = e;
                    e = e->Next;
                    delete temp;
                }
            } );
        }


        /// ��ʶͼ���������֮����һ����
        void Link2Vertex( size_t index1, size_t index2, double weight = 1 )
        {
            AdjacencyListNode *node = new AdjacencyListNode();
            node->AimNodeIndex = index2;
            node->Next = _e[index1];
            node->Weight = weight;
            _e[index1] = node;

            if ( _type == Undigraph )
            {
                //����ͼ
                node = new AdjacencyListNode();
                node->AimNodeIndex = index1;
                node->Next = _e[index2];
                node->Weight = weight;
                _e[index2] = node;
            }
        }

        /// @brief ��ѯ���������Ƿ�����
        ///
        /// �������������Ƿ�������ͬʱ�����ظ����ߵ�Ȩֵ��������������ͷ���<false, 0>�������Ȩֵ������
        pair<bool, AdjacencyListNode *> IsLinked( size_t index1, size_t index2 ) const
        {
            AdjacencyListNode *l = _e[index1];
            while( l )
            {
                if ( l->AimNodeIndex == index2 )
                {
                    return make_pair( true, l );
                }
                l = l->Next;
            }
            return make_pair( false, nullptr );
        }

        /// �������еĶ���
        inline vector<T> & GetVertex()
        {
            return _v;
        }

        /// �������еıߵ��ڽӱ�
        inline vector<AdjacencyListNode *> & GetEdges()
        {
            return _e;
        }

        /// �������еıߵı��ֵ��
        vector<pair<size_t, size_t>> GetAllEdges()
        {
            vector<pair<size_t, size_t>> edges;
            for ( size_t i = 0; i < _e.size(); ++i )
            {
                AdjacencyListNode *l = _e[i];
                while( l )
                {
                    edges.push_back( make_pair( i, l->AimNodeIndex ) );
                    l = l->Next;
                }
            }
            return edges;
        }


    private:
        //GraphicsViaAdjacencyList(GraphicsViaAdjacencyList<T> const &);
        //GraphicsViaAdjacencyList<T> & operator=(GraphicsViaAdjacencyList<T> &);

        vector<T>				_v;		///< ͼ�Ķ���ļ���
        vector<AdjacencyListNode *>	_e;		///< ͼ�ıߣ����ڽӱ�
        GraphicsType			_type;	///< ͼ������
    };


    /// ʹ���ڽӾ�������ʾһ��ͼ
    template<typename VertexType, typename WeightType>
    class GrpahicsViaAdjacencyMatrix
    {
    public:
        GrpahicsViaAdjacencyMatrix( vector<VertexType> const &v, GraphicsType type = Digraph ) : _v( v ), _e( v.size(), vector<WeightType>( v.size() ) ), _type( type )
        {

        }

        /// ��ʶ��������֮����һ��ȨֵΪweight�ı�
        void Link2Vertex( size_t index1, size_t index2, WeightType weight )
        {
            _e[index1][index2] = weight;
            if ( _type == Undigraph )
            {
                _e[index2][index1] = weight;
            }
        }

        /// ��ѯ���������Ƿ�����
        bool IsLinked( size_t index1, size_t index2 ) const
        {
            return _e[index1][index2] != WeightType();
        }

        /// �������еĶ���
        inline vector<VertexType> & GetVertex()
        {
            return _v;
        }
        /// �������еı�
        inline vector<vector<WeightType>> & GetEdge()
        {
            return _e;
        }



    private:
        vector<VertexType>				_v;		///< ͼ�Ķ���ļ���
        vector<vector<WeightType>>		_e;		///< ͼ�ıߣ����ڽӾ���
        GraphicsType					_type;	///< ͼ������
    };

}
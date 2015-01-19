//////////////////////////////////////////////////////////////////////////
/// @file		intorduction_to_algorithms.cpp
/// @brief		��������Main
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


#include <iostream>

namespace ita
{
    //��6�£�������
    int testHeapSort();						//������

    //��7�£���������
    int testQuickSort();					//��������

    //��8�£�����ʱ������
    int testLinearSort();					//����ʱ������

    //��9�£���λ����˳��ͳ��ѧ
    int testNthElement();					//��λ����˳��ͳ��ѧ

    //��11�£�ɢ�б�
    int testHashTable();					//ɢ�б�

    //��12�£����������
    int testBinarySearchTree();				//���������

    //��13�£������
    int testRedBlackTree();					//�����

    //��15�£���̬�滮
    void AssembleDispatch();				//װ���ߵ���
    void MatrixListMultiply();				//�������˷�
    int LongestCommonSubsequence();			//�����������
    void BestBinarySearchTree();			//���Ŷ��������
    void NeatlyPrint();						//�����ӡ
    void PlanParty();						//�ۻ�ƻ�
    void BitonicTour();						//˫���ó�

    //��16�£�̰���㷨
    void HuffmanCode();						//����������

    //��18�£�B��
    void testBTree();						//B��

    //��19�£������
    void testBinomialHeaps();				//�����

    //��20�£�쳲�������
    int testFibonacciHeap();				//쳲�������

    //��21�£����ڲ��ཻ���ϵ����ݽṹ
    void testDisjointSetForest();			//���ڲ��ཻ���ϵ����ݽṹ�����鼯��

    //��22�£�ͼ�Ļ����㷨
    void testBreadthFirstSearch();			//������ȱ���
    void testDeapthFirstSearch();			//������ȱ���
    void TopologicalSort();					//��������
    void StronglyConnectedComponent();		//ǿ��ͨ��֧

    //��23�£���С������
    void Kruskal();							//Kruskal��С�������㷨
    void Prim();							//Prim��С�������㷨

    //��24�£���Դ���·��
    bool testBellmanFord();					//BellmanFord��Դ���·���㷨
    void testDijkstra();					//Dijkstra��Դ���·���㷨

    //��25�£�ÿ�Զ��������·��
    void FloydWarshall();					//FloydWarshallÿ�Զ������·���㷨
    void Johnson();							//Johnsonÿ�Զ������·���㷨

    //��26�£������
    void testFordFulkerson();				//FordFulkerson������㷨

	//��32�£��ַ���ƥ��
	int StringMatchAlgorithms();			//�ַ���ƥ���㷨

	//��33�£����㼸��
	void testComputionalGeometry();
}

using namespace ita;
int _tmain( int argc, _TCHAR* argv[] )
{
    testHeapSort();

    //testQuickSort();

    //testLinearSort();

    //testNthElement();

    //testHashTable();

    //testBinarySearchTree();

    //testRedBlackTree();

    //AssembleDispatch();
    //MatrixListMultiply();
    //LongestCommonSubsequence();
    //BestBinarySearchTree();
    //NeatlyPrint();
    //PlanParty();
    //BitonicTour();

    //HuffmanCode();

    //testBTree();

    //testBinomialHeaps();

    //testFibonacciHeap();

    //testDisjointSetForest();

    //testBreadthFirstSearch();
    //testDeapthFirstSearch();
    //TopologicalSort();
    //StronglyConnectedComponent();

    //Kruskal();
    //Prim();

    //testBellmanFord();
    //testDijkstra();

    //FloydWarshall();
    //Johnson();

    //testFordFulkerson();

	//StringMatchAlgorithms();

	//testComputionalGeometry();

	system("pause");
    return 0;
}


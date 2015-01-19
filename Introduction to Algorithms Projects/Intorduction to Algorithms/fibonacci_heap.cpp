/**
* template Fibonacci Heap
*
* @ref http://en.wikipedia.org/wiki/Fibonacci_heap
* @ref http://www.cse.yorku.ca/~aaw/Jason/FibonacciHeapAlgorithm.html
* @author Erel Segal http://tora.us.fm/rentabrain
* @date 2010-11-11
*/

/**
* chuanqi.tan(at)gmail.com	����˵��
*
* 쳲������������ѷǳ����ƣ��Ͳ����Լ�����д�ˡ�
* ����Ĵ���ת���ԣ�http://ideone.com/9jYnv ���ִ���ķ��ǳ��ִ����ҷǳ�ϲ��������������ݴ���
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "fibonacci_heap.h"
using namespace std;


namespace ita
{

    /// 쳲�������
    int testFibonacciHeap()
    {
        try
        {
            FibonacciHeap<string, uint> h;
            h.debug = true;
            h.debugRemoveMin = false;
            h.debugDecreaseKey = false;

            h.insert( "a", 4 );
            h.insert( "b", 2 );
            h.insert( "c", 7 );
            h.insert( "d", 5 );
            h.insert( "e", 1 );
            h.insert( "f", 8 );
            h.printRoots( cout );

            while ( !h.empty() )
            {
                cout << "min=" << *h.minimum() << endl;
                h.removeMinimum();
                h.printRoots( cout );
            }

            cout << endl << endl;

            vector <FibonacciHeapNode<string, uint>*> nodes( 6 );
            nodes[0] =
                h.insert( "a", 400 );
            nodes[1] =
                h.insert( "b", 200 );
            nodes[2] =
                h.insert( "c", 70 );
            nodes[3] =
                h.insert( "d", 50 );
            nodes[4] =
                h.insert( "e", 10 );
            nodes[5] =
                h.insert( "f", 80 );
            h.printRoots( cout );
            cout << "min=" << *h.minimum() << endl;

            h.removeMinimum();
            cout << "min=" << *h.minimum() << endl;
            nodes[4] = NULL;
            h.printRoots( cout );

            for ( uint i = 0; i < nodes.size(); ++i )
            {
                if ( !nodes[i] ) // minimum - already removed
                    continue;
                h.decreaseKey( nodes[i], nodes[i]->key() / 10 );
                cout << "min=" << *h.minimum() << endl;
                h.printRoots( cout );
            }

            cout << endl << endl;

            h.insert( "AA", 4 );
            h.insert( "BB", 2 );
            h.insert( "CC", 7 );
            h.insert( "DD", 5 );
            h.insert( "EE", 1 );
            h.insert( "FF", 8 );
            h.printRoots( cout );

            while ( !h.empty() )
            {
                cout << "min=" << *h.minimum() << endl;
                h.removeMinimum();
                h.printRoots( cout );
            }

            cout << endl << endl;

        }
        catch ( string s )
        {
            cerr << endl << "ERROR: " << s << endl;
        }

        return 0;
    }

}
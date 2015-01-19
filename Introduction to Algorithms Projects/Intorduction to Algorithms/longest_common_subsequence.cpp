//////////////////////////////////////////////////////////////////////////
/// @file		longest_common_subsequence.cpp
/// @brief		������Ӵ�����
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
/// 2011/06/17   14:51	1.0	̷����	����

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

namespace ita
{

    namespace	//���������ռ�
    {
        string const LeftHandSide = "abcbdabbadbcddbacbdad";
        string const RightHandSide = "bdcaadcbdbddababba";


        /// ��ͨ�ĵݹ�,ʱ�临�Ӷ�Ϊn��ָ����
        int LongestCommonSubsequenceViaRecurise( int i, int j )
        {
            if ( i == 0 || j == 0 )
            {
                return 0;
            }
            else
            {
                if ( LeftHandSide[i - 1] == RightHandSide[j - 1] )
                {
                    return LongestCommonSubsequenceViaRecurise( i - 1, j - 1 ) + 1;
                }
                else
                {
                    return max( LongestCommonSubsequenceViaRecurise( i, j - 1 ), LongestCommonSubsequenceViaRecurise( i - 1, j ) );
                }
            }
        }



        /// �����˱���¼���ܵĵݹ�
        ///
        /// ���뱸��¼֮��������ٶȳ�������ȵ�����,�ڵݹ����кܶ��ظ���������ļ���������,����һ��СС�ĸĶ�,����������Ч��
        /// ����Ķ��Ϳ������ӱ���¼�Ĺ���
        /// 1:����ǰ���һ���ж�,�Ƿ��Ѿ��������,����Ѿ�������˾�ֱ��ȡ�������.
        /// 2:ÿ��Ҫ����֮ǰ�Ȱѽ������һ��.
        int _LongestCommonSubsequenceViaMemoize( int i, int j, vector< vector<int> > &memoize, vector< vector<int> > &chooses )
        {
            //�����鱸��¼�Ĺ��̾��ǡ�����¼����������ͨ�ݹ������
            //����˵����¼�����򵥺��ã�ֻ��Ҫʹ�õݹ��˼ά���ټ���һ�������ӵݹ�����memoize�Ϳ����ˡ�
            if ( memoize[i][j] != -1 )
            {
                //�ȼ���Ѿ������ڱ���¼��
                return memoize[i][j];
            }

            if ( i == 0 || j == 0 )
            {
                memoize[i][j] = 0;
                return 0;
            }
            else
            {
                if ( LeftHandSide[i - 1] == RightHandSide[j - 1] )
                {
                    //д����¼
                    memoize[i][j] = _LongestCommonSubsequenceViaMemoize( i - 1, j - 1, memoize, chooses ) + 1;
                    chooses[i][j] = 0;			//��¼ѡ��for step 4
                }
                else
                {
                    int i_sub = _LongestCommonSubsequenceViaMemoize( i - 1, j, memoize, chooses );
                    int j_sub = _LongestCommonSubsequenceViaMemoize( i, j - 1, memoize, chooses );

                    chooses[i][j] = ( i_sub > j_sub ? -1 : 1 );		//��¼ѡ��for step 4
                    memoize[i][j] = max( i_sub, j_sub );				//д����¼
                }

                //����¼���Ѿ����浱ǰ��������Ľ⣬ֱ�Ӵӱ���¼��ȡ��������
                return memoize[i][j];
            }
        }

        void LongestCommonSubsequenceViaMemoize()
        {
            //LongestCommonSubsequenceViaMemoize�����ı���¼��
            //memoize[i][j]��ζ��:ȡLeftHandSide��ǰi���ַ��õ������ַ�����ȡRightHandSide��ǰj���ַ��õ������ַ��� ������������еĳ���
            vector< vector<int> > memoize;
            //��ʼ��memoize����,ʹ����Ϊmemoize[0..m, 0..n]
            memoize.resize( LeftHandSide.size() + 1 );
            for_each( memoize.begin(), memoize.end(), []( vector<int> &v )
            {
                v.resize( RightHandSide.size() + 1, -1 );
            } );
            //��¼�ݹ���ÿһ����������ѡ�������������LCS�����Ƕ�̬�滮�еĲ���4
            vector< vector<int> > chooses = memoize;

            //ִ�еݹ飬���LCS�ĳ��ȣ�ͬʱ��¼����ÿ�εݹ�������ѡ��
            cout << _LongestCommonSubsequenceViaMemoize( LeftHandSide.size(), RightHandSide.size(), memoize, chooses ) << endl;

            //��̬�滮��step 4����������Ž⣨LCS��
            //������ʹ�ñ���¼�ķ������Ǵ�ͳ�Ķ�̬�滮���������������Ž⣨LCS������̫��
            //�ܽ�step4��˼·�������ģ�
            //�ڶ�̬�滮���ߵݹ�Ĺ����У�����Ҫ��¼��ÿ��������ѡ��������chooses[i][j]����
            //������ÿһ��������ѡ��������������Ž⣨LCS��
            string left = LeftHandSide;
            string right = RightHandSide;
            vector<char> result;
            while ( !left.empty() && !right.empty() )
            {
                int choose = chooses[left.size()][right.size()];
                if ( choose == 0 )
                {
                    result.push_back( left[left.size() - 1] );
                    left.erase( left.end() - 1 );
                    right.erase( right.end() - 1 );
                }
                else if ( choose == -1 )
                {
                    left.erase( left.end() - 1 );
                }
                else
                {
                    right.erase( right.end() - 1 );
                }
            }
            reverse( result.begin(), result.end() );
            copy( result.begin(), result.end(), ostream_iterator<char>( cout ) );
            cout << endl;
        }

        /// ��ͳ�Ķ�̬�滮
        ///
        /// ��ͳ�Ķ�̬�滮�������¼���ܵĵݹ�����������:һ�����Ե����ϵ�,һ���ǴӶ�����
        /// ��ͳ�Ķ�̬�滮�������¼���ܵĵݹ���Ȼ������ͬ�Ľ������Ӷ�,������ͳ�Ķ�̬�滮�������Ÿ��õĳ�������,���Ч�ʸ���
        void LongestCommonSubsequenceViaDynamicProgramming()
        {
            // lcs[i][j]��ζ��:ȡLeftHandSide��ǰi���ַ��õ������ַ�����ȡRightHandSide��ǰj���ַ��õ������ַ��� 
            // ������������еĳ��ȣ�����ʼ��Ϊ0��
            vector< vector<int> > lcs(LeftHandSide.size() + 1, vector<int>(RightHandSide.size() + 1, 0));

            for ( size_t i = 1; i <= LeftHandSide.size(); ++i )
            {
                for ( size_t j = 1; j <= RightHandSide.size(); ++j )
                {
                    if ( LeftHandSide[i - 1] == RightHandSide[j - 1] )
                    {
                        lcs[i][j] = lcs[i - 1][j - 1] + 1;
                    }
                    else
                    {
                        lcs[i][j] = max( lcs[i][j - 1], lcs[i - 1][j] );
                    }
                }
            }

            cout << lcs[LeftHandSide.size()][RightHandSide.size()] << endl;
        }

    }

    /// @brief ������Ӵ�����
    ///
    /// һ���������е����������ڸ�������ɾȥ����Ԫ�غ�õ������С�������������X��Y������һ����Z����X������������Y��������ʱ����Z������X��Y�Ĺ��������С�\n
    /// ������Ӵ�����������������е�һ������������С����磬X=��ABCBDAB����Y=��BCDB����X��һ�������С�\n
    /// 	���������\n
    /// 	������������A��B��������Z��A��B�Ĺ��������У���ָZͬ��A��B�������С�����Ҫ����֪������A��B������������С�������о�A�����������У���һһ������Ƿ�����B�������У�����ʱ��¼�����ֵ������У������������������С����ַ������ʱ̫�������ȡ��\n
    /// 	���������������������ηֽ�������⣬��A=��a0��a1������am-1����B=��b0��b1������bm-1������Z=��z0��z1������zk-1��Ϊ���ǵ�����������С�����֤�����������ʣ� \n
    /// 	- ���am-1=bn-1����zk-1=am-1=bn-1���ҡ�z0��z1������zk-2���ǡ�a0��a1������am-2���͡�b0��b1������bn-2����һ������������У�
    /// 	- ���am-1!=bn-1������zk-1!=am-1���̺���z0��z1������zk-1���ǡ�a0��a1������am-2���͡�b0��b1������bn-1����һ������������У�
    /// 	- ���am-1!=bn-1������zk-1!=bn-1���̺���z0��z1������zk-1���ǡ�a0��a1������am-1���͡�b0��b1������bn-2����һ������������С�
    /// 	����������A��B�Ĺ���������ʱ������am-1=bn-1�����һ�����һ�������⣬�ҡ�a0��a1������am-2���͡�b0��b1������bm-2����һ�� ����������У����am-1!=bn-1����Ҫ�������\n
    ///		�����⣬�ҳ���a0��a1������am-2���͡�b0��b1������bn-1����һ������������� ���ҳ���a0��a1������am-1���͡�b0��b1������bn-2����һ������������У���ȡ�����нϳ�����ΪA��B������������С�\n
    /// 	Ϊ�˽�Լ�ظ�����ͬ�������ʱ�䣬����һ�����飬���������Ƿ�����ս����ã�������������Ľ���ڸ������У�����Ƕ�̬�滮�������õĻ�������������˵�����¡� \n
    /// 	����c[i][j]Ϊ���С�a0��a1������ai-2���͡�b0��b1������bj-1��������������еĳ��ȣ�����c[i][j]�ɵݹ�ر������£� \n
    /// 	- c[i][j] = 0                         ���i=0��j=0��
    /// 	- c[i][j] = c[i-1][j-1]+1             ���i,j>0����a[i-1] == b[j-1]��
    /// 	- c[i][j] = max{c[i][j-1], c[i-1][j]} ���i,j>0����a[i-1] != b[j-1]��
    /// 	������ʽ��д�������������е�����������еĳ��Ⱥ���������c[i][j]�Ĳ�����������c[i-1][j-1]��c[i-1][j]��c[i][j-1]���ʿ��Դ�c[m][n]��ʼ������c[i][j]�Ĳ������̣������������������С�ϸ�ڼ�����
    int LongestCommonSubsequence()
    {
        LongestCommonSubsequenceViaMemoize();
        LongestCommonSubsequenceViaDynamicProgramming();

        cout << LongestCommonSubsequenceViaRecurise( LeftHandSide.size(), RightHandSide.size() ) << endl;

        return 0;
    }

}
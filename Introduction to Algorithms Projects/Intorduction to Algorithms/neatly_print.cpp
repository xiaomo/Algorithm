//////////////////////////////////////////////////////////////////////////
/// @file		neatly_print.cpp
/// @brief		�����ӡ����
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
/// 2011/06/17   14:40	1.0	̷����	����

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>
#include <set>
using namespace std;

namespace ita
{
    namespace
    {
        /// @brief �����ӡ��̰���㷨
        ///
        /// ����֤�������������ӡ���⣬̰���㷨�ܹ��õ����Ž⣡
        int NeatlyPrintViaGreedy( vector<string> const &words, int const max_length )
        {
            int cost = 0;
            set<int> split_pos;

            int current_line_length = 0;
            for ( int i = 0; i < words.size(); ++i )
            {
                int add_char_num = ( current_line_length == 0 ? words[i].size() : words[i].size() + 1 );
                if ( add_char_num + current_line_length <= max_length )
                {
                    //��ǰ�зŵ���
                    current_line_length += add_char_num;
                }
                else
                {
                    //��ǰ���Ѿ��Ų����ˣ�����
                    split_pos.insert( i );
                    cost += pow( ( max_length - current_line_length ), 1.0 );
                    current_line_length = words[i].size();
                }
            }

            current_line_length = 0;
            for ( size_t i = 0; i < words.size(); ++i )
            {
                if ( split_pos.find( i ) != split_pos.end() )
                {
                    //����
                    string space( max_length - current_line_length, ' ' );
                    cout << space << '|' << endl;
                    current_line_length = 0;
                }

                if ( current_line_length != 0 )
                {
                    cout << ' ';
                }
                cout << words[i];

                current_line_length += ( current_line_length == 0 ? words[i].size() : words[i].size() + 1 );
            }

            return cost;
        }

        /// @brief ����������ӡ�Ķ�̬�滮�㷨
        ///
        /// �������������Ĺ��ڱ���Ľⷨ������֤�Ǵ���ġ����޵���ģ�\n
        /// ��̬�滮�õ���Ӧ�������Ž⣬�����Ǵ��Ž⡣�����ﶯ̬�滮�Ľ����û��̰���㷨�ã������̬�滮����ȫ����ģ�\n
        /// ���������ν�Ķ�̬�滮��ʹ�õĽ���ƹ�ʽʵ���ǲ������������޵���\n
        int NeatlyPrintViaDyanmicProgrammingWrong( vector<string> const &words, int const max_length )
        {
            //cost[i]��ʾ[0..i]���ʵ���С����
            vector<int> cost( words.size() );

            //w[i][j]��ʾ�ѵ�[i,j]�����ʷ��뵽һ��ʱ�����л�ʣ�µĿո��������
            //���һ�зŲ�����ô���ַ�����w[i][j]Ϊ�������i>jʱ��w[i][j]ΪĬ��ֵ0��
            vector<vector<int>> w( words.size(), vector<int>( words.size() ) );
            for ( size_t i = 0; i < words.size(); ++i )
            {
                for ( size_t j = i; j < words.size(); ++j )
                {
                    int least_length = max_length;
                    for ( size_t k = i; k <= j; ++k )
                    {
                        least_length -= words[k].size();
                    }
                    least_length -= ( j - i );	//���пո���Ҫע��

                    if ( least_length >= 0 )
                    {
                        w[i][j] = pow( least_length, 1.0 );
                    }
                    else
                    {
                        w[i][j] = numeric_limits<int>::max();
                    }
                }
            }

            for ( int i = 1; i < words.size(); ++i )
            {
                vector<int> vi;
                for ( int k = 0; k < i; ++k )
                {
                    //��words[k]֮����з���
                    if ( w[k + 1][i] != numeric_limits<int>::max() )
                    {
                        vi.push_back( cost[k] + w[k + 1][i] );
                    }

                }
                auto min_iter = min_element( vi.begin(), vi.end() );
                cost[i] = *min_iter;
            }

            return cost[words.size() - 1];
        }



        /// @brief ��ȷ�������ӡ�Ķ�̬�滮�㷨
        ///
        /// ��̬�滮�õ���Ӧ�������Ž⣬�����Ǵ��Ž⡣\n
        /// ���Ǳ������ȷ�ⷨ���ö�̬�滮�Ľ����̰���㷨�Ľ����ͬ��ͬ��Ҳ��֤�˶��ڱ�����˵��̰���㷨�ܹ��������Ž⣡\n
        int NeatlyPrintViaDyanmicProgramming( vector<string> const &words, int const max_length )
        {
            size_t size = words.size();

            //һ���������Ϣ
            struct Message
            {
                int Cost;
                int FirstLineCharNumber;
                int LastLineCharNumber;
                int LineNumber;

                bool operator<( Message const &other )
                {
                    return this->Cost < other.Cost;
                }
            };
            //c[i][j]��ʾ[i,j]������֮��������ӡ��Ϣ
            vector<vector<Message>> c( size, vector<Message>( size ) );

            //Ԥ������Ϊ1���������㣩�����
            for ( size_t i = 0; i < size; ++i )
            {
                c[i][i].Cost = 0;
                c[i][i].FirstLineCharNumber = words[i].size();
                c[i][i].LastLineCharNumber = words[i].size();
                c[i][i].LineNumber = 1;
            }

            //���Ƴ���>1ʱ�����
            for ( int length = 2; length <= size; ++length )
            {
                for ( size_t i = 0; i < size - length + 1; ++i )
                {
                    size_t j = i + length - 1;

                    vector<Message> vi;
                    for ( size_t k = i; k < j; ++k )
                    {
                        //��c[i][j]��Ϊc[i][k]��c[k+1][j]��������
                        Message a_message;
                        //c[i][k]��c[k+1][j]�����ֵ���β���Ƿ��ܽ��Ϊһ��
                        bool	can_link_2_parts = c[i][k].LastLineCharNumber + c[k + 1][j].FirstLineCharNumber + 1 <= max_length;

                        //LineNumber
                        a_message.LineNumber = c[i][k].LineNumber + c[k + 1][j].LineNumber;
                        if ( can_link_2_parts )
                        {
                            //��β�����ܽ��Ϊһ��
                            --a_message.LineNumber;
                        }

                        //FirstLineCharNumber
                        if ( can_link_2_parts && c[i][k].LineNumber == 1 )
                        {
                            //��β�����ܽ��Ϊһ�� �� ǰ����ֻ��һ��
                            a_message.FirstLineCharNumber = c[i][k].FirstLineCharNumber + c[k + 1][j].FirstLineCharNumber + 1;
                        }
                        else
                        {
                            a_message.FirstLineCharNumber = c[i][k].FirstLineCharNumber;
                        }

                        //LastLineCharNumber
                        if ( can_link_2_parts && c[k + 1][j].LineNumber == 1 )
                        {
                            //��β�����ܽ��Ϊһ�� �� �󲿷�ֻ��һ��
                            a_message.LastLineCharNumber = ( c[i][k].LastLineCharNumber + c[k + 1][j].FirstLineCharNumber + 1 );
                        }
                        else
                        {
                            a_message.LastLineCharNumber = c[k + 1][j].LastLineCharNumber;
                        }

                        //Cost
                        if ( can_link_2_parts )
                        {
                            //��β�����ܽ��Ϊһ��
                            a_message.Cost = c[i][k].Cost + c[k + 1][j].Cost + ( max_length - c[i][k].LastLineCharNumber - c[k + 1][j].FirstLineCharNumber - 1 );
                        }
                        else
                        {
                            a_message.Cost = c[i][k].Cost + c[k + 1][j].Cost + ( max_length - c[i][k].LastLineCharNumber );
                        }
                        if ( a_message.LineNumber == 1 )
                        {
                            //��Ϊ���һ�еĿո���������
                            a_message.Cost = 0;
                        }

                        vi.push_back( a_message );
                    }

                    c[i][j] = *min_element( vi.begin(), vi.end() );
                }
            }

            return c[0][words.size() - 1].Cost;
        }
    }

    /// @brief �����ӡ
    ///
    /// ��Ŀ������������һ����ӡ��������ش�ӡһ�����µ����⡣�����������n�����ȷֱ�l[1], l[2], ..., l[n]�����ַ������������ĵ��ʹ��ɵ����С�
    /// ����ϣ�������������һЩ��������ش�ӡ������ÿ������M���ַ���������ȡ��ı�׼���¡����ĳһ�а�����i��j�ĵ��ʣ�i<j���ҵ���֮��ֻ��һ���գ�
    /// ������ĩ����Ŀո��ַ�����ΪM-j+i-��(k=i to j)l[k]���������ǷǸ�ֵ�����ø���������Щ���ʡ�����ϣ�������У��������һ�У�����ĩ����ո�
    /// �ַ��������������ܺ���С�������һ����̬�滮�㷨�����ڴ�ӡ��������ش�ӡ��һ����n�����ʵ����¡�
    void NeatlyPrint()
    {
        //��������������ַ���
        vector<string> words;
        for ( int i = 0; i < 100; ++i )
        {
            //�����ַ�������Ϊ1..10
            int length = rand() % 10 + 1;

            string a_word;
            for ( int j = 0; j < length; ++j )
            {
                a_word.push_back( 'a' + rand() % 26 );
            }
            words.push_back( a_word );
        }

        //һ�е�����ַ�����Ҫ��֤k_MAX_LENGTH��������һ�����ʵĳ��ȣ������޷�����
        int const k_MAX_LEGNTH = 48;

        cout << endl << "̰���㷨�ó�����С���ۣ��������һ�У�Ϊ��" << NeatlyPrintViaGreedy( words, k_MAX_LEGNTH );
        cout << endl << "��̬�滮�ó�����С���ۣ��������һ�У�Ϊ��" << NeatlyPrintViaDyanmicProgramming( words, k_MAX_LEGNTH );
        cout << endl << "���������Ĵ���Ķ�̬�滮�㷨�ó�����С���ۣ��������һ�У�Ϊ��" << NeatlyPrintViaDyanmicProgrammingWrong( words, k_MAX_LEGNTH );
        cout << endl;
    }

}
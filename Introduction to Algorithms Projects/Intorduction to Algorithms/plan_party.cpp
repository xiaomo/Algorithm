//////////////////////////////////////////////////////////////////////////
/// @file		plan_party.cpp
/// @brief		�ۻ�滮����
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
/// 2011/06/17   14:34	1.0	̷����	����

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iomanip>
#include <limits>
#include <fstream>
#include <string>
#include <numeric>
#include <set>
using namespace std;

namespace ita
{
    namespace
    {
        /// һ����
        struct Human
        {
            vector<Human *> Childs;
            int				LovePartyValue;
            string			Name;

            int				IncludeValue;			///< ��Human����ۻ�ʱ������Ϊ�����������ܵõ������ϲ�����ܺ�
            int				NotIncludeValue;		///< ��Human������ۻ�ʱ������Ϊ�����������ܵõ������ϲ�����ܺ�
            //IsValid�Ƕ�̬�滮�ı���¼��ʽ��һ������
            bool			IsValid;				///< IncludeValue,NotIncludeValueֵ�Ƿ���Ч������ЧʱΪĬ��ֵ0��

            Human( string const &name, int rank_value )
                : Name( name ), LovePartyValue( rank_value ), IncludeValue( rank_value ), IsValid( false )
            {}
        };

        void PlanPartyViaDyanmicProgramming( Human *root )
        {
            if ( root != nullptr && !root->IsValid )
            {
                //root �μӵ����
                root->IncludeValue = accumulate( root->Childs.begin(), root->Childs.end(), root->LovePartyValue, []( int acc, Human * human )->int
                {
                    PlanPartyViaDyanmicProgramming( human );
                    return acc + human->NotIncludeValue;
                } );

                //root ���μӵ����
                root->NotIncludeValue = accumulate( root->Childs.begin(), root->Childs.end(), 0, []( int acc, Human * human )->int
                {
                    PlanPartyViaDyanmicProgramming( human );
                    return acc + max( human->IncludeValue, human->NotIncludeValue );
                } );

                root->IsValid = true;
            }

        }
    }

    /// �ۻ�滮����
    void PlanParty()
    {
        Human *root = new Human( "TCQ", 4 );		//�ܲý��

        Human *c1 = new Human( "WY", 2 );
        Human *c2 = new Human( "ABC", 3 );
        root->Childs.push_back( c1 );
        root->Childs.push_back( c2 );

        PlanPartyViaDyanmicProgramming( root );
        cout << max( root->IncludeValue, root->NotIncludeValue );
    }
}
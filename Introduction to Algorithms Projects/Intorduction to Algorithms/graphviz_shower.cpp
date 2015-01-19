//////////////////////////////////////////////////////////////////////////
/// @file		graphviz_shower.cpp
/// @brief		����Graphviz��ʾdot������������ͼ
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

#include <string>
#include <fstream>
using namespace std;

namespace qi
{
    void ShowGraphvizViaDot( std::string const &dot )
    {
        ofstream dot_file( "c:\\graphiv_show.dot" );
        dot_file << dot;
        dot_file.close();
        system( "dot -Tpng c:\\graphiv_show.dot -o c:\\graphiv_show.png" );
        system( "c:\\graphiv_show.png" );
    }
}
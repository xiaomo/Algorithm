//////////////////////////////////////////////////////////////////////////
/// @file		string_match.cpp
/// @brief		�ַ���ƥ���㷨
/// @details	COPYRIGHT NOTICE
///			    Copyright (c) 2011
///			    All rights reserved.\n
///
///
/// @author		̷����	chuanqi.tan(at)gmail.com
/// @date		2012/02/20
/// @version	1.0
//////////////////////////////////////////////////////////////////////////
/// �޸ļ�¼��
/// 2012/02/20		1.0	̷����	����

#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <iterator>
#include <bitset>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <utility>

using namespace std;


namespace ita
{
	//����״̬�Զ���
	class DefineAutomationMatcher{
	public:
		DefineAutomationMatcher(string const &pattern) : _pattern(pattern){
			for (size_t i = 0; i < _pattern.size(); ++i)				//��״̬i��ʼ
			{
				for (size_t j = 0; j < sk_Character_Set.size(); ++j)	//�����ַ�sk_Character_Set[j]����״̬ת��
				{
					size_t k = i + 1;									//��ͼת�Ƶ�״̬k
					while (k > 0 && !_IsPostfix(_pattern, i, sk_Character_Set[j], k)){
						--k;
					}

					if (k > 0){
						_state_transfer_f.insert(make_pair(make_pair(i, sk_Character_Set[j]), k));
					}
				}
			}

		}

		int Match(string const &text){
			int current_state = 0;
			for (size_t i = 0; i < text.size(); ++i){
				auto iter = _state_transfer_f.find(make_pair(current_state, text[i]));
				if (iter == _state_transfer_f.end()){
					current_state = 0;		//�ָ�����ʼ״̬
				}
				else{
					current_state = (*iter).second;

					if (current_state == _pattern.size()){					
						return i - _pattern.size() + 1;		//ƥ��ɹ�
					}
				}
			}

			return -1;		//ƥ��ʧ��
		}

	private:
		bool _IsPostfix(string const &p, size_t i, char c, size_t k){
			string str1 = p.substr(0, k);
			string str2 = p.substr(0, i) + c;
			return str1 == str2.substr(str2.size() - k);
		}

		static string const			sk_Character_Set;			//�ַ���
		string const				_pattern;					//Ҫƥ���ģʽ
		map<pair<int, char>, int>	_state_transfer_f;			//״̬ת�ƺ���
	};

	string const DefineAutomationMatcher::sk_Character_Set = "abcdefghijklmnopqrstuvwxyz";


	//KMP�㷨
	int KMPMatch(string const &text, string const &p){
		//step 1: get pi array
		vector<int> pi(p.size(), 0);

		for (int i = 1; i < p.size(); ++i){
			for (int j = i - 1; j >= 0; --j){
				if (p.substr(0, j + 1) == p.substr(i - j, j + 1)){
					pi[i] = j + 1;
					break;
				}
			}
		}

		//step 2: match
		for (int i = 0; i <= text.size() - p.size(); ){
			int j = 0;
			while (j < p.size() && text[i + j] == p[j]){
				++j;
			}

			if (j >= p.size()){			//matched��ƥ��ɹ�
				return i;
			}
			else if (j == 0){			//swap to next����һ��ƥ��Ͳ�ͬ���ƶ�����һ��
				++i;
			}
			else{
				i += (j - pi[j - 1]);	//skip���������ƣ���ʽΪj-1+1 - pi[j-1] = j-pi[j-1]
			}
		}

		return -1;
	}

	int StringMatchAlgorithms()
	{
		string pattern = "abc";
		DefineAutomationMatcher matcher(pattern);

		for (int i = 0; i < 50000; ++i){
			string text = "aaaaaaaaaa";
			for (int j = 0; j < text.size(); ++j){
				text[j] += (rand() % 26);
			}

			bool b1 = (KMPMatch(text, pattern) != -1);
			bool b2 = (matcher.Match(text) != -1);

			if (b1 != b2){
				cout << "���ַ��������ͬ������ : " << text << endl;
			}

			if (text.find(pattern) != -1){
				cout << "���ְ��� 'abc' �Ĵ� : " << text << "\t";

				if (b1 && b2){
					cout << "���ַ�����ƥ��ɹ� : " << text << endl;
				}
				else{
					cout << "����һ�ַ���δƥ��ɹ� : " << text << endl;
				}
			}
			else{
				if (b1 || b2){
					cout << "������ 'abc' �Ĵ���ĳ�ַ�����ƥ�䣺" << text << endl;
				}
			}
		}		

		return 0;
	}


}
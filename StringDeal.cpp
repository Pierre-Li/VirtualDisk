#include "StringDeal.h"

StringDeal::StringDeal()
{
}

//输出int转换为字符串，每三位用逗号隔开
string StringDeal::IntToString(int num)
{
	string str;
	while (num)
	{
		str += ('0' + num % 10);
		num /= 10;
	} 
	reverse(str.begin(), str.end());
	for (int i = (int)str.size()-3; i > 0; i -=3)
	{
		str.insert(i, ",");
	}
	return str;
}

//判断是否含有通配符字符串
bool StringDeal::IsHaveWildCard(const string& name)
{
	for (auto it:name)
	{
		if (it == '*' || it == '?')
		{
			return true;
		}
	}
	return false;
}

//通配符匹配
bool StringDeal::MatchsWildCard(const string wild_card, const string str_name)
{
	
	int wild_size = wild_card.size();
	int str_size = str_name.size();
	vector<vector<int> > b_dp(str_size + 1, vector<int>(wild_size + 1, 0));
	b_dp[0][0] = 1;
	for (int i = 1;i <= str_size;i++)
	{
		char ch = str_name[i-1];
		b_dp[i][0] = b_dp[i - 1][0] && (ch == '*');
		for (int j = 1; j<= wild_size;j++)
		{
			char ch2 = wild_card[j - 1];
			if (ch == '*')
			{
				b_dp[i][j] = b_dp[i - 1][j] || b_dp[i][j - 1];
			}
			else
			{
				b_dp[i][j] = b_dp[i - 1][j - 1] && (ch == '?' || ch2 == ch);
			}
		}
	}
	if (b_dp[str_size][wild_size] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

StringDeal::~StringDeal()
{
}
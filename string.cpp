#include <bits/stdc++.h>

using namespace std;

bool isnotspace(int c)
{
	return (!isspace(c));
}

string ltrim(const string &str) {
	string s(str);

	s.erase(
		s.begin(),
		find_if(s.begin(), s.end(), isnotspace)
	);

	return s;
}

string rtrim(const string &str) {
	string s(str);

	s.erase(
		find_if(s.rbegin(), s.rend(), isnotspace).base(),
		s.end()
	);

	return s;
}

vector<string> split(const string &str, string del = " ") {
	vector<string> tokens;

	string::size_type start = 0;
	string::size_type end = 0;

	while ((end = str.find(del, start)) != string::npos) {

		string res = str.substr(start, end - start);
		// if (res != "")
		tokens.push_back(res);

		start = end + del.size();
	}
	// if (str.substr(start) != "")
	tokens.push_back(str.substr(start));

	return tokens;
}

void	parse_time(string t, int & h, int & m, int & s)
{
	vector<string>	v = split(t, ":");
	h = stoi(v[0]);
	m = stoi(v[1]);
	s = stoi(v[2]);
}

string stoupper(string const & s)
{
	string u = s;

	for (char & c : u)
		c = toupper(c);
	return (u);
}

string stolower(string const & s)
{
	string u = s;

	for (char & c : u)
		c = tolower(c);
	return (u);
}

#pragma once
#include <string>
#include <vector>

namespace IHHook {
	static std::vector<std::string> split(const std::string& str, const std::string& delim) {
		std::vector<std::string> tokens;
		size_t prev = 0, pos = 0;
		do {
			pos = str.find(delim, prev);
			if (pos == std::string::npos) pos = str.length();
			std::string token = str.substr(prev, pos - prev);
			if (!token.empty()) tokens.push_back(token);
			prev = pos + delim.length();
		} while (pos < str.length() && prev < str.length());
		return tokens;
	}//split

	// trim from left
	inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v") {
		s.erase(0, s.find_first_not_of(t));
		return s;
	}

	// trim from right
	inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v") {
		s.erase(s.find_last_not_of(t) + 1);
		return s;
	}

	// trim from left & right
	inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v") {
		return ltrim(rtrim(s, t), t);
	}
}//namespace IHHook

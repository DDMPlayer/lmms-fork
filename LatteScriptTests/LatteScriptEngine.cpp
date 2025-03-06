#include <string>
#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string& str, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	
	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}
	
	return tokens;
}

std::vector<std::string> splitOutsideParentheses(const std::string& str) {
	std::vector<std::string> result;
	std::string current;
	int parenDepth = 0;
	
	for (size_t i = 0; i < str.size(); ++i) {
		char c = str[i];
		
		if (c == '(') {
			parenDepth++;
		} else if (c == ')') {
			parenDepth--;
		}
		
		if (c == ' ' && parenDepth == 0) { // Split only if outside parentheses
			if (!current.empty()) {
				result.push_back(current);
				current.clear();
			}
		} else {
			current += c;
		}
	}
	
	if (!current.empty()) {
		result.push_back(current);
	}
	
	return result;
}

class LatteScriptEngine {
public:
	void executeCode(std::string input) {
		std::vector<std::string> splits = split(input, '\n');
		
		for(int i = 0; i < splits.size(); i++) {
			std::vector<std::string> current_command = splitOutsideParentheses(splits[i]);
			std::string base_command = current_command[0];
			
			if(base_command) {
				
			}
		}
	}
};


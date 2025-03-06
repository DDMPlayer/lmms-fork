#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

enum class TokenType { VAR, IDENTIFIER, NUMBER, STRING, OPERATOR, FOR, LPAREN, RPAREN, LBRACE, RBRACE, SEMICOLON, EQUALS, FUNCTION, COMMA, END };

struct Token {
	TokenType type;
	std::string value;
};

class Lexer {
	std::string input;
	size_t pos = 0;
	
public:
	Lexer(const std::string& src) : input(src) {}
	
	std::vector<Token> tokenize() {
		std::vector<Token> tokens;
		while (pos < input.size()) {
			if (std::isspace(input[pos])) {
				++pos;
				continue;
			}
			if (std::isalpha(input[pos]) || input[pos] == '_') {
				std::string word;
				while (pos < input.size() && (std::isalnum(input[pos]) || input[pos] == '_'))
					word += input[pos++];
				if (word == "var") tokens.push_back({TokenType::VAR, word});
				else if (word == "for") tokens.push_back({TokenType::FOR, word});
				else if (word == "export_song") tokens.push_back({TokenType::FUNCTION, word});
				else tokens.push_back({TokenType::IDENTIFIER, word});
			} else if (std::isdigit(input[pos])) {
				std::string num;
				while (pos < input.size() && std::isdigit(input[pos]))
					num += input[pos++];
				tokens.push_back({TokenType::NUMBER, num});
			} else if (input[pos] == '"') {
				std::string str;
				++pos;
				while (pos < input.size() && input[pos] != '"')
					str += input[pos++];
				++pos;
				tokens.push_back({TokenType::STRING, str});
			} else {
				switch (input[pos]) {
				case '=': tokens.push_back({TokenType::EQUALS, "="}); break;
				case '(': tokens.push_back({TokenType::LPAREN, "("}); break;
				case ')': tokens.push_back({TokenType::RPAREN, ")"}); break;
				case '{': tokens.push_back({TokenType::LBRACE, "{"}); break;
				case '}': tokens.push_back({TokenType::RBRACE, "}"}); break;
				case ';': tokens.push_back({TokenType::SEMICOLON, ";"}); break;
				case ',': tokens.push_back({TokenType::COMMA, ","}); break;
				default: tokens.push_back({TokenType::OPERATOR, std::string(1, input[pos])}); break;
				}
				++pos;
			}
		}
		tokens.push_back({TokenType::END, ""});
		return tokens;
	}
};

class Parser {
	std::vector<Token> tokens;
	size_t pos = 0;
	std::unordered_map<std::string, std::string> variables;
	
public:
	Parser(const std::vector<Token>& t) : tokens(t) {}
	
	void parse() {
		while (pos < tokens.size()) {
			if (tokens[pos].type == TokenType::VAR) {
				parseVariable();
			} else if (tokens[pos].type == TokenType::FOR) {
				parseForLoop();
			} else if (tokens[pos].type == TokenType::FUNCTION) {
				parseFunction();
			} else {
				++pos;
			}
		}
	}
	
private:
	void parseVariable() {
		++pos; // Skip 'var'
		if (tokens[pos].type == TokenType::IDENTIFIER) {
			std::string varName = tokens[pos++].value;
			if (tokens[pos].type == TokenType::EQUALS) {
				++pos; // Skip '='
				std::string value = tokens[pos++].value;
				variables[varName] = value;
			}
			if (tokens[pos].type == TokenType::SEMICOLON) ++pos;
		}
	}
	
	void parseForLoop() {
		++pos; // Skip 'for'
		if (tokens[pos].type == TokenType::LPAREN) {
			++pos;
			parseVariable(); // Initialization
			std::string varName = tokens[pos - 2].value;
			
			if (tokens[pos].type == TokenType::IDENTIFIER) ++pos; // Condition
			if (tokens[pos].type == TokenType::OPERATOR) ++pos;
			std::string limit = tokens[pos++].value;
			
			if (tokens[pos].type == TokenType::SEMICOLON) ++pos;
			
			if (tokens[pos].type == TokenType::IDENTIFIER) ++pos; // Increment
			if (tokens[pos].type == TokenType::OPERATOR) ++pos;
			if (tokens[pos].type == TokenType::NUMBER) ++pos;
			
			if (tokens[pos].type == TokenType::RPAREN) ++pos;
			if (tokens[pos].type == TokenType::LBRACE) ++pos;
			
			int limitVal = std::stoi(limit);
			for (int i = 0; i <= limitVal; i++) {
				variables[varName] = std::to_string(i);
				while (tokens[pos].type != TokenType::RBRACE)
					parseFunction();
			}
			++pos;
		}
	}
	
	void parseFunction() {
		std::string funcName = tokens[pos++].value;
		if (tokens[pos].type == TokenType::LPAREN) {
			++pos;
			std::vector<std::string> args;
			while (tokens[pos].type != TokenType::RPAREN) {
				if (tokens[pos].type == TokenType::IDENTIFIER || tokens[pos].type == TokenType::STRING || tokens[pos].type == TokenType::NUMBER) {
					std::string val = tokens[pos].value;
					if (variables.find(val) != variables.end()) val = variables[val];
					args.push_back(val);
				}
				++pos;
			}
			++pos;
			if (tokens[pos].type == TokenType::SEMICOLON) ++pos;
			
			std::cout << "Calling function: " << funcName << " with args: ";
			for (const auto& arg : args) std::cout << arg << " ";
			std::cout << std::endl;
		}
	}
};

class LatteScriptEngine {
public:
	LatteScriptEngine() {
		std::string code = R"(
			var base_pitch = Engine.master_pitch;
			for(var i = 0; i <= 12; i++) {
				Engine.master_pitch = i;
				export_song("cathook_path_here" + str(i) + ".wav", true, true);
			}
		)";
		
		Lexer lexer(code);
		std::vector<Token> tokens = lexer.tokenize();
		Parser parser(tokens);
		parser.parse();
	}
};

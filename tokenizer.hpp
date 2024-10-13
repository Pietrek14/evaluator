#pragma once

#include <exception>
#include <string>
#include <vector>

namespace Evaluator {
	struct Token {
		enum class Type {
			NUMBER,
			PLUS,
			MINUS,
			MULT_SIGN,
			DIV_SIGN,
			L_PAREN,
			R_PAREN
		};

		Type type;
		std::string value;

		Token(Type type, std::string value);
	};

	class Tokenizer {
		using Tokens = std::vector<Token>;

		Tokens m_Tokens;

	public:
		Tokenizer();

		void tokenize(std::string source);
		const Tokens& get_tokens() const;

		class InvalidTokenException : public std::exception {
			char m_InvalidToken;
		public:
			InvalidTokenException(char invalid_token);

			char* what();
			char get_invalid_token() const;
		};
	};
}
#include "tokenizer.hpp"

#include <cstdio>
#include <optional>

Evaluator::Token::Token(Type type, std::string value)
	: type(type), value(value) {}

bool is_numeric(char character) {
	return (character >= 48 && character <= 57) || character == '.';
}

bool is_whitespace(char character) {
	return character == ' ' || character == '\t';
}

Evaluator::Tokenizer::Tokenizer() : m_Tokens(Tokens()) {}

void Evaluator::Tokenizer::tokenize(std::string source) {
	m_Tokens.clear();

	std::string current_value = "";
	std::optional<Token::Type> current_type = std::nullopt;

	auto finish_token = [this, &current_value, &current_type](std::optional<Token::Type> new_type) {
		if(!current_value.empty() && current_type.has_value()) {
			m_Tokens.emplace_back(current_type.value(), current_value);
		}

		current_value = "";
		current_type = new_type;
	};

	for(char character : source) {
		if(is_numeric(character)) {
			if(current_type != Token::Type::NUMBER)
				finish_token(Token::Type::NUMBER);
		}
		else if(character == '+')
			finish_token(Token::Type::PLUS);
		else if(character == '-')
			finish_token(Token::Type::MINUS);
		else if(character == '*')
			finish_token(Token::Type::MULT_SIGN);
		else if(character == '/')
			finish_token(Token::Type::DIV_SIGN);
		else if(character == '(')
			finish_token(Token::Type::L_PAREN);
		else if(character == ')')
			finish_token(Token::Type::R_PAREN);
		else if(is_whitespace(character))
			finish_token(std::nullopt);
		else
			throw InvalidTokenException(character);

		current_value += character;
	}

	finish_token(std::nullopt);
}

const Evaluator::Tokenizer::Tokens& Evaluator::Tokenizer::get_tokens() const {
	return m_Tokens;
}

Evaluator::Tokenizer::InvalidTokenException::InvalidTokenException(char invalid_token)
	: m_InvalidToken(invalid_token) {}

char* Evaluator::Tokenizer::InvalidTokenException::what() {
	char* message;
	sprintf(message, "An unknown character was passed to the tokenizer: %c", m_InvalidToken);

	return message;
}

char Evaluator::Tokenizer::InvalidTokenException::get_invalid_token() const {
	return m_InvalidToken;
}
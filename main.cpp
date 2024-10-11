#include <iostream>

#include "tokenizer.hpp"

int main() {
	std::string expression;

	std::getline(std::cin, expression);

	Evaluator::Tokenizer tokenizer;

	tokenizer.tokenize(expression);

	for(Evaluator::Token token : tokenizer.get_tokens()) {
		std::cout << token.value << " ";
	}

	return 0;
}
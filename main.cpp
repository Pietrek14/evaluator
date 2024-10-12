#include <iostream>
#include <stdlib.h>

#include "tokenizer.hpp"

int main() {
	std::string expression;

	std::getline(std::cin, expression);

	Evaluator::Tokenizer tokenizer;

	try {
		tokenizer.tokenize(expression);
	} catch(Evaluator::Tokenizer::InvalidTokenException exception) {
		std::cout << "Nieznany znak: " << exception.get_invalid_token() << std::endl;
		return EXIT_FAILURE;
	}

	for(Evaluator::Token token : tokenizer.get_tokens()) {
		std::cout << token.value << " ";
	}

	return 0;
}
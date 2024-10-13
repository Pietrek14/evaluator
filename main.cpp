#include <iostream>
#include <stdlib.h>

#include "tokenizer.hpp"
#include "operation_tree.hpp"

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

	Evaluator::OperationTree operation_tree;

	operation_tree.encode(tokenizer);

	return 0;
}
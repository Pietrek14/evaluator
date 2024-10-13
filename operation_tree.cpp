#include "operation_tree.hpp"

#include <stack>
#include <queue>
// TEMPORARY!
#include <iostream>

static int precedence(Evaluator::Token::Type token_type) {
	switch(token_type) {
		case Evaluator::Token::Type::PLUS:
		case Evaluator::Token::Type::MINUS:
			return 1;

		case Evaluator::Token::Type::MULT_SIGN:
		case Evaluator::Token::Type::DIV_SIGN:
			return 2;
	}

	return 0;
}

void Evaluator::OperationTree::encode(const Tokenizer& tokenizer) {
	// TODO: input validation

	// Reorganize the tokens into Polish notation (shunting yard algorithm)
	std::queue<Token> output_queue;
	std::stack<Token> operator_stack;

	for(auto token : tokenizer.get_tokens()) {
		switch(token.type) {
			case Token::Type::NUMBER:
				output_queue.push(token);
				break;

			case Token::Type::PLUS:
			case Token::Type::MINUS:
			case Token::Type::MULT_SIGN:
			case Token::Type::DIV_SIGN:
				while(
					!operator_stack.empty()
					&& operator_stack.top().type != Token::Type::L_PAREN
					&& precedence(operator_stack.top().type) >= precedence(token.type)
				) {
					output_queue.push(operator_stack.top());
					operator_stack.pop();
				}

				operator_stack.push(token);

				break;

			case Token::Type::L_PAREN:
				operator_stack.push(token);
				break;

			case Token::Type::R_PAREN:
				while(operator_stack.top().type != Token::Type::L_PAREN) {
					if(operator_stack.empty()) {
						// TODO: do actual error handling here
						std::cerr << "Mismatched parens!!!!! DD:\n";
						return;
					}

					output_queue.push(operator_stack.top());
					operator_stack.pop();
				}

				if(operator_stack.empty() || operator_stack.top().type != Token::Type::L_PAREN) {
					// TODO: handle your errors young man!!
					std::cerr << "Mismatched parens!!!!! DD:\n";
					return;
				}

				operator_stack.pop();
		}
	}

	while(!operator_stack.empty()) {
		if(operator_stack.top().type == Token::Type::L_PAREN) {
			// TODO: omg errors again :///
			std::cerr << "Mismatched parens!!!!! DD:\n";
			return;
		}

		output_queue.push(operator_stack.top());
		operator_stack.pop();
	}

	m_RPNTokenQueue = output_queue;

	while(!m_RPNTokenQueue.empty()) {
		std::cout << m_RPNTokenQueue.front().value << " ";
		m_RPNTokenQueue.pop();
	}
}
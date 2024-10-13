#pragma once

#include <queue>

#include "tokenizer.hpp"

namespace Evaluator {
	// TODO: Name it something sensible
	class OperationTree {
		/// @brief Tokens reordered into reversed Polish notation for easier evaluation
		std::queue<Token> m_RPNTokenQueue;

	public:
		void encode(const Tokenizer& tokenizer);
	};
};
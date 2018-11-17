#pragma once


/* https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns#Interpreter

Interpreter

Given a language, define a representation for its grammar along with an interpreter
that uses the representation to interpret sentences in the language. */

#include <iostream>
#include <string>
#include <map>
#include <list>

struct Expression;
using my_map = std::map<std::string, Expression*>;
using my_stack = std::list<Expression*>;

struct Expression {
	virtual int interpret(my_map &variables) = 0; // Pure virtual
	virtual ~Expression() = default;
};

class Number : public Expression {
	int number;
public:
	Number(int num) : number(num) {};

	int interpret(my_map &variables) override {
		return number;
	}
};

class Plus : public Expression {
	Expression* leftOperand;
	Expression* rightOperand;

public:
	Plus(Expression* left, Expression* right) :
		leftOperand(left), rightOperand(right) {};
	
	~Plus() {
		delete leftOperand;
		delete rightOperand;
	}

	int interpret(my_map &variables) override {
		return leftOperand->interpret(variables) + rightOperand->interpret(variables);
	}
};

class Minus : public Expression {
	Expression* leftOperand;
	Expression* rightOperand;

public:
	Minus(Expression* left, Expression* right) :
		leftOperand(left), rightOperand(right) {};

	~Minus() {
		delete leftOperand;
		delete rightOperand;
	}

	int interpret(my_map &variables) override {
		return leftOperand->interpret(variables) - rightOperand->interpret(variables);
	}
};

class Variable : public Expression {
	std::string name;

public:
	Variable(std::string n) : name(n) {};

	int interpret(my_map &variables) override {
		auto it = variables.find(name);
		return it == variables.end() ? 0 : it->second->interpret(variables);
	}
};

//	While the interpreter pattern does not address parsing, a parser is provided for completeness.

class Evaluator : public Expression {
	Expression* syntaxTree;

public:
	Evaluator(std::string expression) {
		my_stack expressionStack;

		size_t last = 0;
		for (size_t next = 0; last != std::string::npos; last = (next == std::string::npos) ? next : (next + 1)) {
			next = expression.find(' ', last);
			std::string token(expression.substr(last, (next == std::string::npos) ? (expression.length() - last) : (next - last)));

			if (token == "+") {
				Expression* right = expressionStack.back();
				expressionStack.pop_back();
				Expression* left = expressionStack.back();
				expressionStack.pop_back();
				Expression* subExpression = new Plus(right, left);
				expressionStack.push_back(subExpression);
			}
			else if (token == "-") {
				// Remove right operand from stack
				Expression* right = expressionStack.back();
				expressionStack.pop_back();
				// ..and then left operand
				Expression* left = expressionStack.back();
				expressionStack.pop_back();
				Expression* subExpression = new Minus(left, right);
				expressionStack.push_back(subExpression);
			}
			else {
				expressionStack.push_back(new Variable(token));
			}
		}

		syntaxTree = expressionStack.back();
		expressionStack.pop_back();
	}

	~Evaluator() {
		delete syntaxTree;
	}

	int interpret(my_map &context) override {
		return syntaxTree->interpret(context);
	}
};

void interpreter() {

	Evaluator sentence("w x z - +"); // w + (x - z)

	static const int sequences[][3] = {
		{5, 10, 42}, {1, 3, 2}, {7, 9, -5},
	};

	for (size_t i = 0; i < sizeof(sequences) / sizeof(sequences[0]); ++i) {
		my_map variables;
		variables["w"] = new Number(sequences[i][0]);
		variables["x"] = new Number(sequences[i][1]);
		variables["z"] = new Number(sequences[i][2]);

		int result = sentence.interpret(variables);
		std::cout << "Interpreter result: " << result << std::endl;

		for (my_map::iterator it = variables.begin(); it != variables.end(); ++it) {
			delete it->second;
		}
	}
}
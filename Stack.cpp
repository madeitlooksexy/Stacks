//@file		Stack.cpp
//@author	Noah Yu
//@version	1.0
/* Implementations for a stack class that handles expressions 
from infix to postfix then finally evaluating the postfix expression.*/

#include <iostream>
#include <string>


using namespace std;

//defining class
class Stack {

private:
	char *string;
	int num;

public:
	//constructor
	Stack(int maxNum) {
		string = new char[maxNum];
		num = -1;
	}

	//function to check for empty slot
	int empty() {

		return (num == -1);
	}

	//push operation
	void push(char val) {
		num = num + 1;
		string[num] = val;
	}

	//pop operation
	char pop() {
		char val;
		val = string[num];
		num = num - 1;
		return val;
	}

	char top() {

		return string[num];
	}
}; 

int preced(char ch) { // check for operator precedence

	if (ch == '+' || ch == '-') {
		return 1;
	}
	else if (ch == '*' || ch == '/') {
		return 2;
	}
	else {
		return 0;
	}
}

//function to remove whitespace from input
string processInput(string infix) { 
	string output = "";
	for (int i = 0; i < infix.length(); i++) //iterating input to construct
		if ((infix[i] != ' '))				 //a new string without spaces
			output += infix[i];
	return output; //returning new string

}

//function to convert infix to postfix
string infixToPostfix(string expr, int len) {

	int i, j;

	string postfix = "";

	//stack object
	Stack postfixStack(len);

	//setting j value to 0
	j = 0;

	//for loop to iterate over string
	for (i = 0; i < len; i++) {

		//if closing braces are encountered
		if (expr[i] == ')') {
			
			//popping element
			postfix += postfixStack.pop();
		}

		//if operator
		else if ((expr[i] == '+') || (expr[i] == '*') || (expr[i] == '-') || (expr[i] == '/')) {

			if ((preced(expr[i]) > preced(postfixStack.top()))) {
				postfixStack.push(expr[i]);
			}

			else {
				while ((!postfixStack.empty()) && (preced(expr[i]) <= preced(postfixStack.top()))) {

					//placing operand on postfix expression string
					postfix += postfixStack.pop();
				}
				postfixStack.push(expr[i]);
			}
		}

		//if operand
		else if ((expr[i] >= '0') && (expr[i] <= '9')) {

			//placing operand on postfix expression string
			postfix += expr[i];
		}
	}

	//popping all elements from stack
	while (!postfixStack.empty()) {

		//writing to the postfix expression
		postfix += postfixStack.pop();
	}

	return postfix;
}

//function to evaluate the postfix expression
double evaluatePostFix(string postfix) {

	//finding length
	int len = postfix.length();
	int a, b;

	//utilizing stack to evaluate postfix expression
	Stack postfixStack(len);

	//for loop to iterate over expression
	for (int i = 0; i < len; i++) {

		//if operator
		if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {

			//popping two operands
			a = (postfixStack.pop()) - '0';
			b = (postfixStack.pop()) - '0';

			//calculate with corresponding operation
			switch (postfix[i]) {

			case '+': postfixStack.push((a + b) + '0'); break;
			case '-': postfixStack.push((a - b) + '0'); break;
			case '*': postfixStack.push((a*b) + '0'); break;
			case '/': postfixStack.push((a / b) + '0'); break;
			}
		}

		//if operand
		else if ((postfix[i] >= '0') && (postfix[i] <= '9')) {

			//storing operand into the stack
			postfixStack.push(postfix[i]);
		}
	}

	//returning the result
	return (postfixStack.pop()) - '0';
}


//main function for user input and calculation
int main() {

	double result;
	int len;
	string expr;
	string postfix = "";

	cout << "Author: Noah Yu" << endl << endl;

	//reading expression for infix input
	cout << endl << "Processing: ";
	getline(cin, expr);

	cout << endl << "Infix expression: " << processInput(expr);

	//finding length
	len = expr.length();

	//allocating memory
	postfix = new char[len];

	//converting infix to a postfix expression
	postfix = infixToPostfix(expr, len);

	//printing postfix expression
	cout << endl << "Postfix Expression: " << postfix << endl;

	//evaluating postfix expression
	result = evaluatePostFix(postfix);

	cout << endl << "Result: " << result << endl;

	return 0;
}
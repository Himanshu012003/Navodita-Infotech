#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>

using namespace std;

// Token types
enum TokenType { NUMBER, PLUS, MINUS, MULTIPLY, DIVIDE, LPAREN, RPAREN, END };

// Token structure
struct Token {
    TokenType type;
    double value;
};

// Tokenize the input expression
vector<Token> tokenize(const string& input) {
    vector<Token> tokens;
    istringstream iss(input);
    string token;
    while (iss >> token) {
        Token t;
        if (token == "+") t.type = PLUS;
        else if (token == "-") t.type = MINUS;
        else if (token == "*") t.type = MULTIPLY;
        else if (token == "/") t.type = DIVIDE;
        else if (token == "(") t.type = LPAREN;
        else if (token == ")") t.type = RPAREN;
        else {
            t.type = NUMBER;
            t.value = stod(token);
        }
        tokens.push_back(t);
    }
    tokens.push_back({ END, 0.0 });
    return tokens;
}

// Recursive descent parser
class Parser {
public:
    Parser(const vector<Token>& tokens) : tokens(tokens), currentToken(tokens.begin()) {}

    double parse() {
        double result = parseExpression();
        if (currentToken->type != END) {
            cerr << "Syntax error." << endl;
            exit(1);
        }
        return result;
    }

private:
    vector<Token>::const_iterator currentToken;
    const vector<Token>& tokens;

    double parseExpression() {
        double left = parseTerm();
        while (currentToken->type == PLUS || currentToken->type == MINUS) {
            TokenType op = currentToken->type;
            ++currentToken;
            double right = parseTerm();
            if (op == PLUS) left += right;
            else left -= right;
        }
        return left;
    }

    double parseTerm() {
        double left = parseFactor();
        while (currentToken->type == MULTIPLY || currentToken->type == DIVIDE) {
            TokenType op = currentToken->type;
            ++currentToken;
            double right = parseFactor();
            if (op == MULTIPLY) left *= right;
            else left /= right;
        }
        return left;
    }

    double parseFactor() {
        if (currentToken->type == NUMBER) {
            double value = currentToken->value;
            ++currentToken;
            return value;
        }
        else if (currentToken->type == LPAREN) {
            ++currentToken;
            double result = parseExpression();
            if (currentToken->type != RPAREN) {
                cerr << "Syntax error." << endl;
                exit(1);
            }
            ++currentToken;
            return result;
        }
        else {
            cerr << "Syntax error." << endl;
            exit(1);
        }
    }
};

int main() {
    string input;
    cout << "Enter an arithmetic expression: ";
    getline(cin, input);

    vector<Token> tokens = tokenize(input);
    Parser parser(tokens);
    double result = parser.parse();

    cout << "Result: " << result << endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <stack>
#include <cmath>
#include <vector>

using namespace std;

struct Node {
    string token;
    Node* left;
    Node* right;
};

bool isOperator(string token) {
    if(token == "+") return true;
    if(token == "-") return true;
    if(token == "*") return true;
    if(token == "/") return true;
    return false;
}


double performOperation(string token, double leftOperand, double rightOperand) {
    if (token == "+")
        return leftOperand + rightOperand;
    else if (token == "-")
        return leftOperand - rightOperand;
    else if (token == "*")
        return leftOperand * rightOperand;
    else if (token == "/")
        return leftOperand / rightOperand;
    else
        return 0.0; // Invalid operator
}

Node* buildExpressionTree( vector<string>& tokens) {
    stack<Node*> nodeStack;

    for (int i = tokens.size() - 1; i >= 0; i--) {
        string token = tokens[i];

        Node* newNode = new Node;
        newNode->token = token;
        newNode->left = newNode->right = nullptr;

        if (!isOperator(token)) {
            nodeStack.push(newNode);
        } else {
            newNode->left = nodeStack.top();
            nodeStack.pop();
            newNode->right = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(newNode);
        }
    }

    return nodeStack.top();
}

double evaluateExpressionTree(Node* root) {

    if (!isOperator(root->token))
        return stod(root->token);

    double leftResult = evaluateExpressionTree(root->left);
    double rightResult = evaluateExpressionTree(root->right);

    return performOperation(root->token, leftResult, rightResult);
}

int main() {
    string filename = "expresie.txt";
    ifstream inputFile(filename);

    vector<string> tokens;
    string token;

    while (inputFile >> token) {
        tokens.push_back(token);
    }

    Node* root = buildExpressionTree(tokens);

    cout << "Expression result: " << evaluateExpressionTree(root);

}

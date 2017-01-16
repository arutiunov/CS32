#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

// converting infix notation to postfix notation (helper)
string infix_to_postfix(string infix, string& postfix);

// evaluate bool value of postfix expression (helper)
bool postfix_eval(string postfix);

// correctly check for precedence when converting infix notation to postfix notation (helper)
int precedence(char character);

bool valid(string s);
bool contains (int index, string s);

int evaluate(string infix, string& postfix, bool& result)
{
if (!valid(infix)) // if infix is not valid
    return 1;
    
postfix = infix_to_postfix(infix, postfix); // assign result to postfix
result = postfix_eval(postfix); // assign bool value to result
    return 0;
}

bool valid(string s)
{
    // checking for two consecutive operands
    int k(0);
    int num_oper(0);
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '&' || s[i] == '!' || s[i] == '|')
            k++;
        if (s[i] == 'F' || s[i] == 'T')
            num_oper++;

    }
    if (k == 0 && num_oper != 1)
        return false;
    
    // checking for normal syntax
    int balance(0);
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != '&' && s[i] != '|' && s[i] != '!' && s[i] != '(' && s[i] != ')' && s[i] != 'T' && s[i] != 'F' && s[i] != ' ')
            return false; // contains any other characters
        
        if (s[i] == '|')
        {
            int counter(0);// check for previous operand (can't be first one)
            for (int k = 0; k < i; k++)
            {
                if (s[k] == 'T' || s[k] == 'F')
                    counter++;
            }
            if (counter == 0)
                return false;
            
            if (i == 0) // can't be first character
                return false;
            if (contains(i, s) == false)
                return false;
            if (i + 1 == s.size())
                return false; // can't be last character
            if (s[i - 1] != 'T' && s[i] != 'F' && s[i + 1] != 'F' && s[i + 1] != 'T' && s[i - 1] != '!' && s[i + 1] != '!' && s[i + 1] != ' ' && s[i - 1] != ' ')
                return false; // has to have T/F/!/' ' before it and T/F/!/' ' after it
        }
        if (s[i] == '(')
        {
            if (i + 1 == s.size())
                return false;
            balance++;
        }
        if (s[i] == ')')
            balance--;
        if (s[i] == '&')
        {
            int counter(0);// check for previous operand (can't be first one)
            for (int k = 0; k < i; k++)
            {
                if (s[k] == 'T' || s[k] == 'F')
                    counter++;
            }
            if (counter == 0)
                return false;
            if (i == 0) // can't be first character
                return false;
            if (contains(i, s) == false)
                return false;
            if (i + 1 == s.size()) // can't be last character
                return false;
            if (s[i + 1] != 'T' && s[i + 1] != 'F' && s[i + 1] != '(' && s[i + 1] != ' ' && s[i + 1] != '!')
                return false; // can't be followed by a closing bracket
        }
        if (s[i] == 'T' || s[i] == 'F')
        {
            if (s[i + 1] == 'T' || s[i + 1] == 'F' || s[i + 1] == '(' || s[i + 1] == '!')
                return false; // can't be followed by T/F/(
        }
        if (s[i] == '!')
        {
            if (contains(i, s) == false)
                return false;
            if (i + 1 == s.size()) // can't be last character
                return false;
            if (s[i + 1] != 'T' && s[i + 1] != 'F' && s[i + 1] != '(' && s[i + 1] != '!' && s[i + 1] != ' ')
                return false; // has to be followed by T/F/(/!
        }
    }
    if (balance != 0) // if uneven number of parentheses
        return false;
    return true;
}

string infix_to_postfix(string infix, string& postfix)
{
    postfix = "";
    stack<char> expression;
    
    for (int i = 0; i < infix.size(); i++)
    {
        switch (infix[i])
        {
        case ' ':
            break;
        case 'T':
            postfix += infix[i];
            break;
                
        case 'F':
            postfix += infix[i];
            break;
                
        case '!':
            expression.push('!');
            break;
                
        case '(':
            expression.push('(');
            break;
                
        case ')':
            while (expression.top() != '(')
                {
                    postfix += expression.top();
                    expression.pop();
                }
                expression.pop(); // remove the '('
            break;
        
        case '|':
        case '&':
            while ((!expression.empty()) && (expression.top() != '(') && (precedence(infix[i]) <= precedence(expression.top())))
               {
                   postfix += expression.top();
                   expression.pop();
               }
            expression.push(infix[i]);
            break;
        }
    }
    
    while (expression.size() != 0)
    {
        postfix += expression.top();
        expression.pop();
    }
    return postfix;
}

bool postfix_eval(string postfix)
{
    stack<bool> expression;
    int counter(0);
    
    for (int i = 0; i < postfix.size(); i++)
    {
        if (postfix[i] == 'T' || postfix[i] == 'F')
        {
            if (postfix[i] == 'T')
                expression.push(true);
            else
                expression.push(false);
        }
        else if (postfix[i] == '!')
        {
            counter++;
            bool placeholder;
            if (!expression.empty())
            {
                while (counter != 0)
                {
                    placeholder = !expression.top();
                    expression.pop();
                    expression.push(placeholder);
                    counter--;
                }
            }
        }
        else
        {
           bool operand2 = expression.top();
            expression.pop();
           bool operand1 = expression.top();
            expression.pop();
            if (postfix[i] == '&')
                expression.push(operand1 && operand2);
            if (postfix[i] == '|')
                expression.push(operand1 || operand2);
        }

        }
    return (expression.top());
}

bool contains (int index, string s)
{
    int counter = 0;
    for (; index < s.size(); index++)
    {
        if (s[index] == 'T' || s[index] == 'F')
            counter++;
    }
    
    if (counter != 0)
        return true;
    return false;
}


int precedence (char character)
{
    int count(0);
    
    if (character == '!')
    {
        count = 3;
        return count;
    }
    if (character == '&')
    {
        count = 2;
        return count;
    }
    if (character == '|')
        count = 1;
        return count;
}

Here is Carrano's pseudocode for the infix to postfix conversion step:

	Initialize postfix to empty
	Initialize the operator stack to empty
	For each character ch in the infix string
	    Switch (ch)
	      case operand:
	        append ch to end of postfix
	        break
	      case '(':
	        push ch onto the operator stack
	        break
              case ')':
	          // pop stack until matching '('
	        While stack top is not '('
	          append the stack top to postfix
	          pop the stack
	        pop the stack  // remove the '('
	        break
	      case operator:
	        While the stack is not empty and the stack top is not '('
	                and precedence of ch <= precedence of stack top
	            append the stack top to postfix
                    pop the stack
                push ch onto the stack
                break
	While the stack is not empty
	    append the stack top to postfix
            pop the stack

And here is his pseudocode for the evaluation of the postfix expression:

	Initialize the operand stack to empty
	For each character ch in the postfix string
	    if ch is an operand
	        push the value that ch represents onto the operand stack
	    else // ch is a binary operator
	        set operand2 to the top of the operand stack
		pop the stack
	        set operand1 to the top of the operand stack
		pop the stack
		apply the operation that ch represents to operand1 and
	            operand2, and push the result onto the stack
	When the loop is finished, the operand stack will contain one item,
	  the result of evaluating the expression
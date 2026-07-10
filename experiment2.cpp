#include <iostream>
using namespace std;

bool isLetter(char ch)
{
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z');
}

bool isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool isKeyword(string token)
{
    return token == "int" ||
           token == "float" ||
           token == "double" ||
           token == "char" ||
           token == "if" ||
           token == "else" ||
           token == "cout" ||
           token == "cin" ||
           token == "return";
}

bool isOperator(string token)
{
    return token == "+" ||
           token == "-" ||
           token == "*" ||
           token == "/" ||
           token == "=" ||
           token == "<<" ||
           token == ">>";
}

bool isPunctuation(string token)
{
    return token == ";" ||
           token == "," ||
           token == "(" ||
           token == ")" ||
           token == "{" ||
           token == "}";
}

bool isConstant(string token)
{
    int dot = 0;

    if (token == "")
        return false;

    for (int i = 0; i < token.length(); i++)
    {
        if (token[i] == '.')
            dot++;

        else if (!isDigit(token[i]))
            return false;
    }

    return dot <= 1;
}

bool isIdentifier(string token)
{
    if (!(isLetter(token[0]) || token[0] == '_'))
        return false;

    for (int i = 1; i < token.length(); i++)
    {
        if (!(isLetter(token[i]) ||
              isDigit(token[i]) ||
              token[i] == '_'))
        {
            return false;
        }
    }

    return true;
}

void checkToken(string token)
{
    if (token == "")
        return;

    if (isKeyword(token))
        cout << token << " : Keyword" << endl;

    else if (isOperator(token))
        cout << token << " : Operator" << endl;

    else if (isPunctuation(token))
        cout << token << " : Punctuation" << endl;

    else if (isConstant(token))
        cout << token << " : Constant" << endl;

    else if (isIdentifier(token))
        cout << token << " : Identifier" << endl;

    else
        cout << token << " : Lexical Error" << endl;
}

void tokenize(string input)
{
    string token = "";

    for (int i = 0; i < input.length(); i++)
    {
        char ch = input[i];

        if (isLetter(ch) || isDigit(ch) ||
            ch == '.' || ch == '_')
        {
            token += ch;
        }

        else
        {
            checkToken(token);
            token = "";

            if (ch == ' ')
                continue;

            string symbol = "";
            symbol += ch;

            if (i + 1 < input.length())
            {
                string twoSymbols = symbol;
                twoSymbols += input[i + 1];

                if (isOperator(twoSymbols))
                {
                    symbol = twoSymbols;
                    i++;
                }
            }

            checkToken(symbol);
        }
    }

    checkToken(token);
}

int main()
{
    string input = "cout << 20 + a * 60.5;";

    tokenize(input);

    return 0;
}

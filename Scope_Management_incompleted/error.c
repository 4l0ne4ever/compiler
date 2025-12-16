/*
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

#define NUM_OF_ERRORS 30

static int firstErrorReported = 0;
static int firstErrorLine = 0;
static int firstErrorCol = 0;
static char firstErrorMsg[256] = {0};

struct ErrorMessage
{
  ErrorCode errorCode;
  char *errorName;
  char *message;
};

struct ErrorMessage errors[30] = {
    {ERR_END_OF_COMMENT, "ERR_END_OF_COMMENT", "End of comment expected."},
    {ERR_IDENT_TOO_LONG, "ERR_IDENT_TOO_LONG", "Identifier too long."},
    {ERR_NUMBER_TOO_LONG, "ERR_NUMBER_TOO_LONG", "Value of integer number exceeds the range!"},
    {ERR_INVALID_CONSTANT_CHAR, "ERR_INVALID_CONSTANT_CHAR", "Invalid char constant."},
    {ERR_INVALID_SYMBOL, "ERR_INVALID_SYMBOL", "Invalid symbol."},
    {ERR_INVALID_IDENT, "ERR_INVALID_IDENT", "An identifier expected."},
    {ERR_INVALID_CONSTANT, "ERR_INVALID_CONSTANT", "A constant expected."},
    {ERR_INVALID_TYPE, "ERR_INVALID_TYPE", "A type expected."},
    {ERR_INVALID_BASICTYPE, "ERR_INVALID_BASICTYPE", "A basic type expected."},
    {ERR_INVALID_VARIABLE, "ERR_INVALID_VARIABLE", "A variable expected."},
    {ERR_INVALID_FUNCTION, "ERR_INVALID_FUNCTION", "A function identifier expected."},
    {ERR_INVALID_PROCEDURE, "ERR_INVALID_PROCEDURE", "A procedure identifier expected."},
    {ERR_INVALID_PARAMETER, "ERR_INVALID_PARAMETER", "A parameter expected."},
    {ERR_INVALID_STATEMENT, "ERR_INVALID_STATEMENT", "Invalid statement."},
    {ERR_INVALID_COMPARATOR, "ERR_INVALID_COMPARATOR", "A comparator expected."},
    {ERR_INVALID_EXPRESSION, "ERR_INVALID_EXPRESSION", "Invalid expression."},
    {ERR_INVALID_TERM, "ERR_INVALID_TERM", "Invalid term."},
    {ERR_INVALID_FACTOR, "ERR_INVALID_FACTOR", "Invalid factor."},
    {ERR_INVALID_LVALUE, "ERR_INVALID_LVALUE", "Invalid lvalue in assignment."},
    {ERR_INVALID_ARGUMENTS, "ERR_INVALID_ARGUMENTS", "Wrong arguments."},
    {ERR_UNDECLARED_IDENT, "ERR_UNDECLARED_IDENT", "Undeclared identifier."},
    {ERR_UNDECLARED_CONSTANT, "ERR_UNDECLARED_CONSTANT", "Undeclared constant."},
    {ERR_UNDECLARED_INT_CONSTANT, "ERR_UNDECLARED_INT_CONSTANT", "Undeclared integer constant."},
    {ERR_UNDECLARED_TYPE, "ERR_UNDECLARED_TYPE", "Undeclared type."},
    {ERR_UNDECLARED_VARIABLE, "ERR_UNDECLARED_VARIABLE", "Undeclared variable."},
    {ERR_INVALID_RETURN, "ERR_INVALID_RETURN", "Expect the owner of the current scope."},
    {ERR_UNDECLARED_PROCEDURE, "ERR_UNDECLARED_PROCEDURE", "Undeclared procedure."},
    {ERR_DUPLICATE_IDENT, "ERR_DUPLICATE_IDENT", "Duplicate identifier."},
    {ERR_TYPE_INCONSISTENCY, "ERR_TYPE_INCONSISTENCY", "Type inconsistency"},
    {ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY, "ERR_PARAMETERS_ARGUMENTS_INCONSISTENCY", "The number of arguments and the number of parameters are inconsistent."}};

void error(ErrorCode err, int lineNo, int colNo)
{
  int i;
  for (i = 0; i < NUM_OF_ERRORS; i++)
    if (errors[i].errorCode == err)
    {
      if (!firstErrorReported)
      {
        firstErrorReported = 1;
        firstErrorLine = lineNo;
        firstErrorCol = colNo;
        snprintf(firstErrorMsg, sizeof(firstErrorMsg), "%s", errors[i].errorName);
        // Don't exit immediately - allow parser to continue
        return;
      }
      // If already have an error, exit with first error
      printf("%d-%d:%s\n", firstErrorLine, firstErrorCol, firstErrorMsg);
      exit(0);
    }
}

int hasError()
{
  return firstErrorReported;
}

void exitIfError()
{
  if (firstErrorReported)
  {
    printf("%d-%d:%s\n", firstErrorLine, firstErrorCol, firstErrorMsg);
    exit(0);
  }
}

void missingToken(TokenType tokenType, int lineNo, int colNo)
{
  if (firstErrorReported)
  {
    printf("%d-%d:%s\n", firstErrorLine, firstErrorCol, firstErrorMsg);
  }
  else
  {
    printf("%d-%d:Missing %s\n", lineNo, colNo, tokenToString(tokenType));
  }
  exit(0);
}

void assert(char *msg)
{
  printf("%s\n", msg);
}

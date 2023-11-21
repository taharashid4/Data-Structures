#include "Stack.h"
#include <iostream>
#include <string>

std::string largestString(std::string str, int k) {
  std::string newStr = "";
  int trackIdx = 0;
  int idx = 0;
  Stack<char> stack;
  while (str[idx] != '\0') {
    char temp = str[idx];
    while (!stack.isEmpty() && k > 0 && stack.peek() < temp) {
      stack.pop();
      newStr.erase(newStr.size() - 1);
      --k;
    }

    stack.push(temp);
    newStr += temp;
    ++idx;
  }

  // Fulfilling the k deletions criteria.
  while (!stack.isEmpty() && k > 0) {
    stack.pop();
    --k;
    newStr.erase(newStr.size() - 1);
  }

  return newStr;
}

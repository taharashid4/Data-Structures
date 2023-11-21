#include "Stack.h"
#include <iostream>
using namespace std;

string solve(string number, int k) {

  string ans = "";
  int idx = 0;
  Stack<char> stack;

  while (idx < number.length()) {
    char currNum = number[idx];

    while (!stack.isEmpty() && k > 0) {

      if (currNum == '0' && stack.size() == 1)
        break;

      else if (stack.peek() == '0' && currNum != '0') {
        int gapAmount = 0;
        int traverse = ans.size() - 1;
        while (ans[traverse] == '0' && traverse > 0) {
          ++gapAmount;
          --traverse;
        }

        char prevNum = ans[traverse];

        if (currNum < prevNum && gapAmount < k) {
          while (gapAmount >= 0 && !stack.isEmpty() && ans.size() > 0) {
            stack.pop();
            ans.erase(ans.size() - 1);
            --k;
          }
        } else {
          break;
        }
      }

      else if (stack.peek() > currNum) {
        stack.pop();
        ans.erase(ans.size() - 1);
        --k;
      }

      else {
        break;
      }
    }

    stack.push(currNum);
    ans += currNum;
    ++idx;
  }

  while (!stack.isEmpty() && k > 0) {
    stack.pop();
    --k;
    ans.erase(ans.size() - 1);
  }

  cout << ans << '\n';
  return ans;
}

#include <iostream>
using namespace std;
#include "Queue.h"
int *maxSubsequence(int nums[], int size, int k) {
  Queue<int> queue;
  int *result = new int[k];
  int sum = 0, currSum = 0;
  int startIdx = 0;
  for (int i = 0; i < k; ++i) {
    queue.enqueue(nums[i]);
    sum += queue.peek();
  }
  currSum = sum;

  for (int i = k; i < size; ++i) {
    currSum -= queue.dequeue();
    currSum += nums[i];
    queue.enqueue(nums[i]);

    if (currSum > sum) {
      sum = currSum;
      startIdx = i - k + 1;
    }
  }

  for (int i = 0; i < k; ++i)
    result[i] = nums[startIdx + i];
  return result;
}

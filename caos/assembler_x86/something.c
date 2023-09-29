#include <stdio.h>
#include <immintrin.h>

int main() {
  int n = 0;
  scanf("%i", &n);
  double matrix[n][n + 1];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n + 1; j++) {
      scanf("%lf", &matrix[i][j]);
    }
  }
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      double multi = matrix[j][i] / matrix[i][i];
      for (int k = 0; k < n + 1; k++) {
        matrix[j][k] = matrix[j][k] - multi * matrix[i][k];
      }
    }
  }
  double answer[n];
  for (int i = 0; i < n; i++) {
    answer[i] = 0;
  }
  for (int i = n - 1; i >= 0; i--) {
    double var = matrix[i][n];
    for (int j = n - 1; j > i; j--) {
      var = var - matrix[i][j] * answer[j];
    }
    answer[i] = var / matrix[i][i];
  }
  for (int i = 0; i < n; i++) {
    printf("%lf ", answer[i]);
  }
  return 0;
}


public class GetSubArraySum {

  // 全遍历 O(N^3)
  public static int getMaxSubArray1(int[] array) {
    int max = 0;
    for(int i = 0; i < array.length; i++) {
      for (int j = i; j < array.length; j++) {
        int sum = 0;
        for (int k = i; k <= j; k++) {
          sum += array[k];
        }
        if (sum > max) {
          max = sum;
        }
      }
    }
    return max;
  }

  // 保留上次遍历时的sum O(N^2)
  public static int getMaxSubArray2(int[] array) {
    int max = 0;
    for(int i = 0; i < array.length; i++) {
      int sum = 0;
      for (int j = i; j < array.length; j++) {
        sum += array[j];
        if (sum > max) {
          max = sum;
        }
      }
    }
    return max;
  }

  // 在线处理  O(N)
  public static int getMaxSubArray3(int[] array) {
    int max = 0;
    int sum = 0;
    for (int i = 0; i < array.length; i++) {
      sum += array[i];
      if (sum > max) {
        max = sum;
      }
      if (sum < 0) {
        sum = 0;
      }
    }
    return max;
  }

  public static void main(String[] args) throws Exception {
    int[] array = { -2, 11, -4, 13, -5, -2 };
    int result1 = getMaxSubArray1(array);
    int result2 = getMaxSubArray2(array);
    int result3 = getMaxSubArray3(array);
    System.out.println(result1);
    System.out.println(result2);
    System.out.println(result3);
  }
}

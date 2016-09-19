# include <stdio.h>
# include <stdlib.h>

typedef int ElementType;
# define MaxData 1000;

typedef struct HeapStruct {
  ElementType *elements;
  int size;
  int capacity; //最大容量
} HeapStruct;

typedef HeapStruct *MaxHeap;

// 新建一个数组作为堆的物理结构
MaxHeap create(int maxSize) {
  MaxHeap h = malloc(sizeof(HeapStruct));
  h->elements = malloc((maxSize + 1) * sizeof(ElementType));
  h->size = 0;
  h->capacity = maxSize;
  h->elements[0] = MaxData;
  return h;
}

void insert(MaxHeap h, ElementType element) {
  int i = h->size + 1;
  ElementType tmp;
  while(h->elements[i/2] < element && i > 1) {
    tmp = h->elements[i/2];
    h->elements[i/2] = h->elements[i];
    h->elements[i] = tmp;
    i = i / 2;
  }
  h->elements[i] = element;
  ++h->size;
}

ElementType deleteMax(MaxHeap h) {
  ElementType maxElement, tmp, changeTmp;
  int index = 1, maxChildIndex;
  maxElement = h->elements[1];

  //保持堆的数组特性
  tmp = h->elements[h->size];
  h->size = h->size - 1;

  // 拿最后一个元素替补当前根节点， 然后与下面的左右儿子比较， 找到该元素合适的位置。
  while(1) {
    h->elements[index] = tmp;
    // 找到左右两儿子的较大者
    if(h->elements[index * 2] > h->elements[index * 2 + 1]) {
      maxChildIndex = index * 2;
    } else {
      maxChildIndex = index * 2 + 1;
    }

    if(maxChildIndex > h->size) break;

    if(h->elements[index] < h->elements[maxChildIndex]) {
      changeTmp = h->elements[index];
      h->elements[index] = h->elements[maxChildIndex];
      h->elements[maxChildIndex] = changeTmp;
      index = maxChildIndex;
    } else {
      break;
    }
  }
  return maxElement;
}

int main() {
  int i;
  MaxHeap h = create(20);
  insert(h, 20);
  insert(h, 21);
  insert(h, 27);
  insert(h, 17);
  insert(h, 37);
  insert(h, 35);
  for(i = 1; i < h->size + 1; i++) {
    printf("%d ", h->elements[i]);
  }
  printf("\n-------------------------\n");
  printf("%d\n", deleteMax(h));
  for(i = 1; i < h->size + 1; i++) {
    printf("%d ", h->elements[i]);
  }
  printf("\n-------------------------\n");
  printf("%d\n", deleteMax(h));
  for(i = 1; i < h->size + 1; i++) {
    printf("%d ", h->elements[i]);
  }
  return 0;
}

# include <stdio.h>
# include <stdlib.h>

# define FALSE 0
# define TRUE 1

typedef int ElementType;
typedef int Status;
// avl

typedef struct TreeNode {
  ElementType element;
  int bf; // 平衡因子
  struct TreeNode * left;
  struct TreeNode * right;
}TreeNode;
typedef TreeNode *TreePtr;

TreePtr createTree(ElementType element){
	TreePtr tree = (TreePtr)malloc(sizeof(struct TreeNode));
  tree->element = element;
  tree->left = NULL;
  tree->right = NULL;
  tree->bf = 0;
	return tree;
}

TreePtr find(TreePtr tree, ElementType element) {
  if(!tree) return NULL;
  if(tree->element == element) return tree;
  if(tree->element < element) return find(tree->right, element);
  if(tree->element > element) return find(tree->left, element);
}

void inOrderTraversal(TreePtr tree) {
  if(tree) {
    inOrderTraversal(tree->left);
    printf("%d ", tree->element);
    inOrderTraversal(tree->right);
  }
}

void appendNode(TreePtr tree, ElementType element) {
  if(tree->element == element) {
    printf("existed\n");
    return;
  }
  if(element < tree->element && tree->left != NULL) {
    return appendNode(tree->left, element);
  }
  if(element > tree->element && tree->right != NULL) {
    return appendNode(tree->right, element);
  }

  TreePtr node = (TreePtr)malloc(sizeof(struct TreeNode));
  node->element = element;
  node->left = NULL;
  node->right = NULL;
  node->bf = 0;
  if(element < tree->element) {
    tree->left = node;
  }
  if(element > tree->element) {
    tree->right = node;
  }
}

// 顺时针, 左子树向右转
void rightRotate(TreePtr *tree) {
  TreePtr leftChild = (*tree)->left;
  (*tree)->left = leftChild->right;
  leftChild->right = (*tree);
  (*tree) = leftChild;
}

// 逆时针，右子树向左转
void leftRotate(TreePtr *tree) {
  TreePtr rightChild = (*tree)->right;
  (*tree)->right = rightChild->left;
  rightChild->left = (*tree);
  (*tree) = rightChild;
}

// 传入的tree应该是bf为2的树，
// 则左子树深度比右子树深度高2。
//1. 左子树是否需要左转。 2. 1之后的再右转。
void leftBalance (TreePtr *tree) {
  TreePtr subRightChild;
  TreePtr leftChild = (*tree)->left;
  // 看看左子树是否需要调整
  switch (leftChild->bf) {
    case 1: // 不平衡节点位于tree的左节点的左节点。
      (*tree)->bf = leftChild->bf = 0;
      rightRotate(tree);
      break;
    case -1: // 不平衡节点位于tree的左节点的右节点。
      subRightChild = (*tree)->left->right;
      // 调整三个节点的bf
      if(subRightChild->bf == 1) {
        (*tree)->bf = 1;
        leftChild->bf = 0;
      } else if(subRightChild->bf == 0) {
        (*tree)->bf = leftChild->bf = 0;
      } else if(subRightChild->bf == -1) {
        (*tree)->bf = 0;
        leftChild->bf = 1;
      }
      subRightChild->bf = 0;
      leftRotate(&(*tree)->left);
      rightRotate(tree);
  }
}

void rightBalance(TreePtr *tree) {
	TreePtr subLeftChild;
  TreePtr rightChild = (*tree)->right;
	switch(rightChild->bf) { /*  检查T的右子树的平衡度，并作相应平衡处理 */
  	case -1: /*  新结点插入在T的右孩子的右子树上，要作单左旋处理 */
  	  (*tree)->bf = rightChild->bf = 0;
  	  leftRotate(tree);
  	  break;
	  case 1: /*  新结点插入在T的右孩子的左子树上，要作双旋处理 */
      subLeftChild = rightChild->left;
		  switch(subLeftChild->bf) { /*  修改T及其右孩子的平衡因子 */
			case -1:
        (*tree)->bf= 1;
  	  	rightChild->bf= 0;
			  break;
			case 0:
        (*tree)->bf = rightChild->bf = 0;
 			  break;
			case 1:
        (*tree)->bf = 0;
				rightChild->bf = -1;
				break;
		}
		  subLeftChild->bf = 0;
		  rightRotate(&(*tree)->right);
		  leftRotate(tree); /*  对T作左旋平衡处理 */
	}
}

// 返回值为是否插入了新节点。
Status insertAVL(TreePtr *tree, ElementType element, Status *taller) { // taller的做法是多次传递同一个int变量时， 用指针。
  // 插入新节点
  if (! *tree) {
    *tree = (TreePtr)malloc(sizeof(struct TreeNode));
    (*tree)->element = element;
    (*tree)->left = (*tree)->right = NULL;
    (*tree)->bf = 0;
    *taller = TRUE;  //新加一个节点， 一定taller?
    printf("------插入了节点%d-------\n", element);
    return TRUE;
  }
  // 遍历tree
  if (element == (*tree)->element) {
    *taller = FALSE;
    return FALSE;
  }

  if (element < (*tree)->element) {
    // 递归插入
    if(!insertAVL(&(*tree)->left, element, taller)) return FALSE;
    // 插在了 tree的左节点上。
    // 现检查tree的bf，并根据bf调整旋转tree，改taller。

    if(*taller) {
      printf("\n---------taller----------\n");
      printf("节点：%d， 调整前bf：%d\n", (*tree)->element, (*tree)->bf);
      switch ((*tree)->bf) {
        // 原来是左子树较深， 插在了左， 所以要转。
        case 1:
          leftBalance(tree);
          // 转完后高度已经调整了。
          *taller = FALSE;
          break;
        // 原来平衡， 插在了左， 不用转， 但要调整自己的bf。
        case 0:
          (*tree)->bf = 1;
          *taller = TRUE;
          break;
        case -1:
          (*tree)->bf = 0;
          *taller = FALSE;
          break;
      }
      printf("节点：%d， 调整后bf：%d\n", (*tree)->element, (*tree)->bf);
    }
  } else {
      // 递归插入
      if(!insertAVL(&(*tree)->right, element, taller)) return FALSE;
      // 插在了右节点上。
      if(*taller) {
        switch ((*tree)->bf) {
          case 1:
            (*tree)->bf = 0;
            *taller = FALSE;
            break;
          case 0:
            (*tree)->bf = -1;
            *taller = TRUE;
            break;
          case -1:
            rightBalance(tree);
            *taller = FALSE;
            break;
        }
      }
    }
  return TRUE;
}

int main(){
  TreePtr tree = createTree(5);
  Status taller = FALSE;
  // insertAVL(&tree, 4, &taller);
  // insertAVL(&tree, 3, &taller);
  insertAVL(&tree, 9, &taller);
  insertAVL(&tree, 10, &taller);
  insertAVL(&tree, 11, &taller);
  insertAVL(&tree, 12, &taller);
  insertAVL(&tree, 13, &taller);
  // insertAVL(&tree, 2, &taller);
  // insertAVL(&tree, 1, &taller);
  // insertAVL(&tree, 0, &taller);
  inOrderTraversal(tree);
  printf("\n-------------------\n");
  printf("根节点=%d\n", tree->element);
  // TreePtr node;
  // appendNode(tree, 4);
  // appendNode(tree, 7);
  // appendNode(tree, 6);
  // appendNode(tree, 1);
  // appendNode(tree, 2);
  // appendNode(tree, 3);
  //
  // inOrderTraversal(tree);
  // printf("\n-------------------\n");
  // node = find(tree, 6);
  // printf("%d ", node->element);
  // printf("\n-------------------\n");
  // printf("\n-------rightrotate------------\n");
  // rightRotate(&tree);
  // rightRotate(&tree);
  // inOrderTraversal(tree);
  // printf("\n-------leftRotate---------------\n");
  // leftRotate(&tree);
  // leftRotate(&tree);
  // inOrderTraversal(tree);

}

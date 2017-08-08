#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode
{
	int data;
	struct TreeNode *left, *right;
}TreeNode;

void inorder(TreeNode *root);  //중위순회
void preorder(TreeNode *root); //전위순회
void postorder(TreeNode *root);//후위 순회
void level_order(TreeNode *ptr); //레벨 순회
void insert_node(TreeNode **root, int key);
void delete_node(TreeNode **root, int key);

int get_node_count(TreeNode *node); //노드 개수 구하기
int get_leaf_count(TreeNode *node); //단말노드 개수 구하기
int get_height(TreeNode *node);     //단말 높이
int max_num(int a, int b);  //최대값 반환

TreeNode * search(TreeNode *node, int key); //순환적인 탐색
TreeNode * search2(TreeNode *node, int key); //반복적인 탐색

TreeNode n7 = {30, NULL, NULL};
TreeNode n1 = {1, NULL, NULL};
TreeNode n2 = {4, &n1, NULL};
TreeNode n3 = {16, NULL, NULL};
TreeNode n4 = {25, NULL, &n7};
TreeNode n5 = {20, &n3, &n4};
TreeNode n6 = {15, &n2, &n5};
TreeNode * root = &n6;



void main()
{
	insert_node(&root, 2);
	delete_node(&root, 30);
	inorder(root);
	printf("\n");
	preorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	printf("%d\n",get_height(root));

}

void inorder(TreeNode *root)
{
	if(root)
	{
		inorder(root ->left);
		printf("%d ", root -> data);
		inorder(root -> right);
	}
}

void preorder(TreeNode *root)
{
	if(root)
	{
		printf("%d ", root -> data);
		preorder(root ->left);
		preorder(root -> right);
	}
}

void postorder(TreeNode *root)
{
	if(root)
	{
		postorder(root ->left);
		postorder(root -> right);
		printf("%d ", root -> data);
	}
}

//void level_order(TreeNode *ptr)
//{
//	큐 소스가 있다고 가정
//	QueueType q;
//	
//	init(&q);
//	if( ptr == NULL) return;
//	enqueue(&q, ptr);
//	while(!is_empty(&q))
//	{
//		ptr = dequeue(&q);
//		printf("%d", ptr->data);
//		if(ptr -> left)
//			enqueue(&q, ptr->left);
//		if(ptr -> right)
//			enqueue(&q, ptr->right);
//	}	
//}

int get_node_count(TreeNode *node)
{
	int count = 0;

	if(node)
	{
		count = 1 + get_node_count(node -> left) + get_node_count(node -> right);
	}

	return count;
}

int get_leaf_count(TreeNode *node)
{
	int count = 0;

	if(node)
	{
		if(node ->left == NULL && node -> right == NULL)
			return 1;
		else
			count = get_leaf_count(node -> left) + get_leaf_count(node->right);
	}
	return count;
}

int max_num(int a, int b)
{
	if(a > b)
		return a;
	else
		return b;
}

int get_height(TreeNode *node)
{
	int height = 0;
	
	if(node)
	{
		height = 1 + max_num(get_height(node -> left), get_height(node->right));
	}

	return height;
}

TreeNode * search(TreeNode *node, int key)
{
	if(node == NULL)
		return;
	if(key == node->data)
		return node;
	else if(key < node->data)
		search(node->left, key);
	else
		search(node->right, key);
}

TreeNode * search2(TreeNode *node, int key)
{
	while(node != NULL)
	{
		if(key == node->data)
			return node;
		else if( key < node->data)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

void insert_node(TreeNode **root, int key)
{
	TreeNode *p, *t;
	TreeNode *n;

	t = *root;
	p = NULL;

	//탐색
	while(t)
	{
		if(key == t -> data)
			return;
		p = t;
		if (key < p->data)
			t = p -> left;
		else
			t = p -> right;
	}

	n = (TreeNode*)malloc(sizeof(TreeNode));
	if(n == NULL)
		return;

	n -> data = key;
	n -> left = n -> right = NULL;

	if(p)
	{
		if(key < p -> data)
			p -> left = n;
		else
			p -> right = n;
	}
	else *root = n;
}

void delete_node(TreeNode **root, int key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;

	p = NULL;
	t = *root;

	while(t != NULL && t->data != key)
	{
		p = t;
		t = (key < p->data ? p ->left : p->right);
	}
	//탐색이 종료된 시점에 t가 NULL이면트리 안에 key가 없음
	if(t == NULL)
	{
		printf("해당키가 없습니다.");
		return;
	}

	if( t->left == NULL && t->right == NULL)
	{
		if(p != NULL)
		{
			if(p->left == t)
				p->left = NULL;
			else
				p->right = NULL;
		}
		else
			*root = NULL;
	}
	//삭제할 노드가 하나의 자식을 갖고있을 경우
	else if(t->left == NULL || t->right == NULL)
	{
		child = (t->left != NULL) ? t->left : t->right;
		if(p != NULL)
		{
			if(p->left == t)
				p->left = child;
			else
				p->right = child;
		}
		*root = child;
	}
	//삭제할 노드가 2개의 자식을 갖는 경우
	else
	{
		// successor탐색
		succ_p = t;
		succ = t->right;
		//후계자 찾아서 계속 왼쪽 이동
		if(succ -> left != NULL)
		{
			succ_p = succ;
			succ = succ -> left;
		}
		//후계자와 부모 자식 연결
		if(succ_p -> left == succ)
			succ_p->left = succ->right;
		else
			succ_p->right = succ->right;
		t->data = succ->data;
		t = succ;
		
	}
	//free(t);
}
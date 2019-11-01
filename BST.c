#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_QUEUE_SIZE 100


typedef struct anod * TreePointer;
struct anod { // �� ����� ����
	int key; // �й�
	char name[50];  // �̸�
	TreePointer leftChild, rightChild; // ����� �ڽĿ� ���� ������
} Ty_Node;

void menui();
void menup(TreePointer tree);
void menud();
void menus();
void menuh();
void menub();
void menuu();

TreePointer ROOT = NULL;

void insert(TreePointer *node, int k, char n[50]);
void BST_Delete(char k[50]);
void search_thing(char n[50]);
void preorder(TreePointer ptr, char n[50]);
void search_height(TreePointer ptr);
TreePointer search_BST(TreePointer curr, char person[50], TreePointer *par);
TreePointer modifiedSearch(TreePointer tree, char name[50]);
TreePointer head;

int i = 0;
int level = 0;

int main(){
	TreePointer np;
	FILE *fp;
	int res;
	int num;
	char menu;
	char person[50];
	fp = fopen("sdata.txt", "r");
	head = NULL;
	np = NULL;
	while (1){
		res = fscanf(fp, "%d  %s", &num, person);
		if (res < 2)
			break;
		insert(&np, num, person);
	}
	while (1){
		head = ROOT;
		printf("������ �۾��� (in, Sp, se, de, ch, ht, le, ex) ?");
		do {
			scanf("%s", &menu);
		} while (menu == '\n');
		if (menu == 'i')
			menui();
		else if (menu == 'S'){
			printf("ȭ���� ������ ������ �����ϴ�:\n");
			menup(head);
		}
		else if (menu == 'd')
			menud();
		else if (menu == 's')
			menus();
		else if (menu == 'h')
			menuh();
		else if (menu == 'c')
			menub();
		else if (menu == 'u')
			menuu();
		else if (menu == 'e'){
			printf("�����մϴ�\n");
			break;
		}
		else
			printf("�������� �ʴ� ��ɾ� �Դϴ�.\n");
	}
	return 0;

}

void insert(TreePointer *node, int k, char n[50]){
	TreePointer ptr, temp;
	ptr = (TreePointer)malloc(sizeof(*ptr));
	ptr->key = k;
	strcpy(ptr->name, n);
	ptr->leftChild = ptr->rightChild = NULL;
	if (!(*node)){
		*node = ptr;
		ROOT = *node;
	}
	else{
		temp = modifiedSearch(*node, n);
		if (!temp)
			printf("������ �ι��� �����մϴ�.\n");
		else{
			if (strcmp(n, temp->name) == -1)
				temp->leftChild = ptr;
			else if (strcmp(n, temp->name) == 1)
				temp->rightChild = ptr;

		}
	}
}

TreePointer modifiedSearch(TreePointer tree, char name[50]){
	TreePointer Parent = NULL;
	while (tree){
		if (strcmp(name, tree->name) == 0)
			return NULL;
		Parent = tree;
		if (strcmp(name, tree->name) == -1)
			tree = tree->leftChild;
		else if (strcmp(name, tree->name) == 1)
			tree = tree->rightChild;
	}
	return Parent;
}

void menui(){
	int num;
	char person[50];
	scanf("%d  %s", &num, person);
	insert(&head, num, person);
	printf("�Է� ����!\n");
	level = i;
	printf("���� : %d \n", level);
}

void menup(TreePointer tree){
	if (tree){
		menup(tree->leftChild);
		printf("%3d  %s\n", tree->key, tree->name);
		menup(tree->rightChild);
	}
}

void menud()
{
	char person[50];
	scanf("%s", person);
	BST_Delete(person);
	printf("�̵��� �Ͼ ����� �̸� : %s %s\n", person, person);
}

void menus(){
	int num;
	char person[50];
	scanf("%s", person);
	search_thing(person);

	if (level == 0)
		printf("�׷� ����� �������� �ʽ��ϴ�\n");
	i = 0, level = 0;
}

void menuh(){
	search_height(head);
	printf("�� BST�� ���� = %d\n", level);
	i = 0, level = 0;
}

void menub(){
	char person[50];
	scanf("%s", person);
	TreePointer parent, me;
	me = search_BST(ROOT, person, &parent);
	if (!me)
		printf("�׷� ����� �����ϴ�\n");
	else{
		if (parent->leftChild == me && parent->rightChild != NULL)
			printf("%s right child is %s\n", person, parent->rightChild->name);
		else if (parent->rightChild == me && parent->leftChild != NULL)
			printf("%s left child is %s\n", person, parent->leftChild->name);
		else
			printf("%s has no child\n", person);
	}
}

void menuu(){
	char person[50];
	scanf("%s", person);
	TreePointer parent, me;
	me = search_BST(ROOT, person, &parent);
	if (!me)
		printf("�׷� ����� �����ϴ�\n");
	else{
		if (parent->leftChild == me || parent->rightChild == me)
			printf("%s�� �θ�� %s\n", person, parent->name);
	}
}

void BST_Delete(char k[50]){
	TreePointer parent, npr, succ, curr;
	npr = search_BST(ROOT, k, &parent);
	if (!npr)
		printf("�׷� ����� �����ϴ�\n");
	else{
		if (npr->leftChild && npr->rightChild){
			succ = npr->rightChild;
			parent = npr;
			while (succ->leftChild){
				parent = succ;
				succ = succ->leftChild;
			}
			npr->key = succ->key;
			strcpy(npr->name, succ->name);
			npr = succ;
		}
		curr = npr->leftChild;
		if (!curr)
			curr = npr->rightChild;
		if (!parent)
			ROOT = curr;
		else if (parent->leftChild == npr)
			parent->leftChild = curr;
		else
			parent->rightChild = curr;
		free(npr);
		printf("�����Ǿ����ϴ�\n");
	}

}
TreePointer search_BST(TreePointer curr, char person[50], TreePointer *par){
	*par = NULL;
	while (curr){
		if (strcmp(person, curr->name) == 0)
			return curr;
		else if (strcmp(person, curr->name) == -1){
			*par = curr;
			curr = curr->leftChild;
		}
		else{
			*par = curr;
			curr = curr->rightChild;
		}
	}
	return NULL;
}

void search_thing(char n[50]){
	preorder(head, n);
}

void preorder(TreePointer ptr, char n[50]){
	i++;
	if (ptr){
		if (strcmp(n, ptr->name) == 0){
			level = i;
			printf("�̸� : %s  �й� : %d  ���� : %d \n", ptr->name, ptr->key, level);
		}
		preorder(ptr->leftChild, n);
		i--;
		preorder(ptr->rightChild, n);
		i--;
	}
}

void search_height(TreePointer ptr){
	i++;
	if (ptr){
		if (i >= level)
			level = i;
		search_height(ptr->leftChild);
		i--;
		search_height(ptr->rightChild);
		i--;
	}
}
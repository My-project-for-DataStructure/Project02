#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_QUEUE_SIZE 100


typedef struct anod * TreePointer;
struct anod { // 한 노드의 구조
	int key; // 학번
	char name[50];  // 이름
	TreePointer leftChild, rightChild; // 노드의 자식에 대한 포인터
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
		printf("수행할 작업은 (in, Sp, se, de, ch, ht, le, ex) ?");
		do {
			scanf("%s", &menu);
		} while (menu == '\n');
		if (menu == 'i')
			menui();
		else if (menu == 'S'){
			printf("화일의 내용은 다음과 같습니다:\n");
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
			printf("종료합니다\n");
			break;
		}
		else
			printf("존재하지 않는 명령어 입니다.\n");
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
			printf("동일한 인물이 존재합니다.\n");
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
	printf("입력 성공!\n");
	level = i;
	printf("레벨 : %d \n", level);
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
	printf("이동이 일어난 사람의 이름 : %s %s\n", person, person);
}

void menus(){
	int num;
	char person[50];
	scanf("%s", person);
	search_thing(person);

	if (level == 0)
		printf("그런 사람이 존재하지 않습니다\n");
	i = 0, level = 0;
}

void menuh(){
	search_height(head);
	printf("이 BST의 높이 = %d\n", level);
	i = 0, level = 0;
}

void menub(){
	char person[50];
	scanf("%s", person);
	TreePointer parent, me;
	me = search_BST(ROOT, person, &parent);
	if (!me)
		printf("그런 사람이 없습니다\n");
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
		printf("그런 사람이 없습니다\n");
	else{
		if (parent->leftChild == me || parent->rightChild == me)
			printf("%s의 부모는 %s\n", person, parent->name);
	}
}

void BST_Delete(char k[50]){
	TreePointer parent, npr, succ, curr;
	npr = search_BST(ROOT, k, &parent);
	if (!npr)
		printf("그런 사람이 없습니다\n");
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
		printf("삭제되었습니다\n");
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
			printf("이름 : %s  학번 : %d  레벨 : %d \n", ptr->name, ptr->key, level);
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
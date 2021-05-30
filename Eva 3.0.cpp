#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "stdio.h"
#include "conio.h"
#include "math.h"
#include "locale.h"
#include "string.h"
#include "windows.h"
#include "time.h"
#define SIZE 10
#define COUNT 10

 struct Complex
{
	float x;
	float y;
};

struct BTnode 
{
	struct BTnode* left;							/* адреса лівого нащадка */
	struct Complex numbers ;						/* дані, що зберігаються на вершині */
	char* key;
	struct BTnode* right;							/* адреса правого нащадка */
};


typedef struct tBST 
{													/* дескриптор дерева */
	int size;										/* число вершин */
	BTnode* root;									/* корінь дерева */
};


tBST* createTree(void);

BTnode* insertTree(tBST* dsTree, BTnode* subTree, char* key, Complex numbers);

int height(BTnode* tree);

void PrintHorizontal(BTnode* root, int space);

void preOrder(BTnode* tree);															

void inOrder(BTnode* tree);														

void postOrder(BTnode* tree);														

BTnode* searchElement(BTnode* tree, char* key);

BTnode* findSmallestElement(BTnode* tree);

BTnode* deleteElement(tBST* dsTree, BTnode* subTree, char* key);

void  input_data(Complex& buf);

void input_key(char* key);

void file(FILE* fp, BTnode* tree);

tBST* readFile(FILE* fp, tBST* tree);

int deleteTree(BTnode* tree);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	tBST* a = NULL;																		// дескриптора дерева
	BTnode* sq = NULL;																	//вершина дерева 
	Complex numbers;																	// структура комплексного числа 
	FILE* fp;																			// дескриптор файлу
	int c = 0, opp = 0, count = 0, modd = 0, arbitrium = 0, arb=0;						//змінні для вибору режиму роботи програми
	char s1[SIZE];																		// ключ
	char filename[SIZE];																// назва файлу для зчитування або запису
	do
	{


		printf("\n1-Cтворити дерево\n2-Додати елемент до дерева\n3-Розмір та висота\n4-Видалити елемент\n5-Пошук елемента\n6-Проходження дерева\n");
		printf("7-Видалити дерево\n8-Записати у файл\n9-Вивести дерево\n0-Для завершення програми\n");
		scanf("%d", &opp);
		switch (opp)
		{

		case 1:
		{
			if (a)
			{
				printf("Дерево уже створено\n");
				break;
			}

		 else if (!(a = createTree()))
			{
				printf("Дерево не створено\n");
				return -1;
			}
		}break;



		case 2:
		{
			if (!a)
			{
				printf("Дерево не створено\n");
				break;
			}
			
			printf("Як заповнювати дерево\n1-Власноруч\n2-З файлу\n");
			scanf("%d", &modd);

			if (modd == 1)
			{
				printf("Кількість елементів?:\n");
				scanf("%d", &count);
				for (int j = 0;j < count;j++)
				{
					input_key(s1);
					input_data(numbers);

					if (!a->root)
					{
						a->root = insertTree(a, a->root, s1, numbers);
					}
					
					else 
					{
						insertTree(a, a->root, s1, numbers);
					}
				}
			}
			else if (modd == 2)
			{
				printf("Введіть назву файлу\n");
				scanf("%s", filename);
				filename[strlen(filename)] = '\0';
				
				if ((fp = fopen(filename, "r")) == NULL)
				{
					printf("Не вдалось відкрити файл % s\n", filename);
				}
				a = readFile(fp,a);

			}
		}break;


		case 3:
		{
			
			if (!a)
			{
				printf("Дерево не створено");
				break;
			}
			printf("Висота дерева: %d\n", height(a->root));
			printf("Кількість вершин: %d\n", a->size);
			
		}break;


		case 4:
		{
			if (!a)
			{
				printf("Дерево не створено");
				break;
			}
			input_key(s1);
			sq = searchElement(a->root, s1);
			
			if (sq == NULL)
			{
				printf("Шуканий ключ відсутній\n");
				break;
			}
			
			else
			{
				  deleteElement(a, a->root, s1);
				break;
			}
		}break;



		case 5:
		{
			if (!a)
			{
				printf("Дерево не стоворено");
				break;
			}
			input_key(s1);
			sq=searchElement(a->root, s1);
			if (sq == NULL)
			{
				printf("Заданий ключ відсутній\n");
				break;
			}
			else
			{
				
				printf("%g+I*%g %s", sq->numbers.x, sq->numbers.y, sq->key);
				break;
			}

				
			
		}break;


		case 6:
		{
			if (!a)
			{
				printf("Ну створіть вже це дерево!\n");
				break;
			}
			printf("1-Симетричний обхід\n2-Зворотній обхід\n3-Прямий обхід\n");
			scanf("%d", &arbitrium);
			
			switch (arbitrium)
			{
				case 1:
				{
					inOrder(a->root);
				}break;

				case 2:
				{
					postOrder(a->root);
				}break;
				
				case 3:
				{
					preOrder(a->root);
				}break;

			}break;
		}


		case 7:
		{
			if (!a)
			{
				printf("Дерево не створено\n");
					break;
			}

			
			printf("Видалити дерево\n1-З дескриптором\n2-Без дескриптора\n");
			scanf("%d", &arb);
			switch (arb)
			{
			case 1:
			{
				deleteTree(a->root);
				free(a);
				a = NULL;
			}break;


			case 2:
			{
				 if (a->root == NULL)
				 {
					printf("Дерево пусте\n");
					break;
				 }

				deleteTree(a->root);
				a->size = 0;
				a->root = NULL;
			}break;


			}
		}break;


		case 8:
		{
			printf("Введіть назву файлу\n");
			scanf("%s", filename);
			filename[strlen(filename)] = '\0';

			if ((fp = fopen(filename, "w")) == NULL)
			{
				printf("Не вдалось відкрити файл %s\n", filename);
				return -2;
			}

			file(fp, a->root);
			fclose(fp);
		}break;


		case 9:
		{
			if (!a)
			{
				printf("Дерево не створено\n");
				break;
			}
			if (a->root == NULL)
			{
				printf("Дерево пусте\n");
			}
			else
			{	
				PrintHorizontal(a->root, 0);
			}
		}break;

		}
		
	} while ( opp!= 0);

	return 0;
}

/* функція createTree
	створює  дерево
	Вхід: нічого
	Вихід: дескриптор дерева 
*/

tBST* createTree(void) {
	tBST* dsBST;
	dsBST = (tBST*)malloc(sizeof(tBST));
	if (!dsBST)
	{
		return NULL;								/* немає доступної пам'яті ,дескриптор не створений */
	}
	dsBST->root = NULL;
	dsBST->size = 0;
	return dsBST;
}


/* функція insertTree
   додає елементи до дерева
   Вхід:  key - ключ, numbers - коплексне число
   Вихід: subTree - вершина дерева
*/

BTnode* insertTree(tBST* dsTree, BTnode* subTree, char* key, Complex numbers)
{
	BTnode* tempNode = NULL;										       	//тимчасова вершина
	char* tempKey = NULL;


	if (!subTree)															  //вершина вже термінальна
	{
		subTree = (BTnode*)malloc(sizeof(BTnode));
		if (!subTree)
		{
			exit(1);
		}
		tempKey = (char*)malloc(sizeof(key + 1));
		strcpy(tempKey, key);
		subTree->key = tempKey;
		subTree->numbers = numbers;
		subTree->left = subTree->right = NULL;
		dsTree->size++;
		return(subTree);
	}
	else if ((strcmp(subTree->key, key)) == 0)
	{

		subTree->numbers = numbers;
		return(subTree);

	}

	else if ((strcmp(subTree->key, key)) > 0)									//пошук по лівій гілці
	{
		subTree->left = insertTree(dsTree, subTree->left, key, numbers);
	}

	else if ((strcmp(subTree->key, key)) < 0)									//пошук по правій гілці
	{
		subTree->right = insertTree(dsTree, subTree->right, key, numbers);
	}

	return subTree;
}

/* Функція height
   визначає висоту дерева
   Вхід: tree - вершина дерева
   Вихід: height - висота дерева
*/
int height(BTnode* tree)
{
	int r, l, heightt = 0;

	if (tree)
	{
		r = tree->right ? height(tree->right) + 1 : 0;
		l = tree->left ? height(tree->left) + 1 : 0;
		heightt += (r > l ? r : l);
	}
	return heightt;
}


void PrintHorizontal(BTnode* root, int space)
{
	//Якщо дерево пусте, зупиняємо
	if (root == NULL)
		return;

	//Збільшення довжини між рівнями 
	space += COUNT;

	//Виводимо правого нащадка


	PrintHorizontal(root->right, space);


	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%s\n", root->key);

	//Виводимо лівого нащадка


	PrintHorizontal(root->left, space);

}

/*Функція preOrder
 прямий обхід дерева
Вхід:tree-вершина дерева
Вихід: нічого
*/
void preOrder(BTnode* tree)																/*Прямий*/
{
	if (tree) {																			/* якщо вершина існує */
		printf("%g+I*%g  %s\n", tree->numbers.x, tree->numbers.y, tree->key);			/* обробка  даних на вершині дерева */
		preOrder(tree->left);															/* переходимо в ліве піддерево вузла */
		preOrder(tree->right);															/* переходимо в праве піддерево вузла */
	}
	return;
}

/*Функція inOrder
 симетричний обхід дерева
Вхід:tree-вершина дерева
Вихід: нічого
*/
void inOrder(BTnode* tree)																//Симетричний обхід
{
	if (tree) {																			/* якщо вершина існує */
		inOrder(tree->left);															/* переходимо в ліве піддерево вузла */
		printf("%g+I*%g  %s\n", tree->numbers.x, tree->numbers.y, tree->key);			/* обробка даних в вершині дерева */
		inOrder(tree->right);															/* переходимо в праве піддерево вузла */
	}
	return;
}

/*Функція postOrder
зворотній обхід дерева
Вхід:tree-вершина древа
Вихід: нічого
*/
void postOrder(BTnode* tree)															//Зворотній обхід
{
	if (tree)
	{																					/* якщо вершина існує */
		postOrder(tree->left);															/* переходимо в ліве піддерево вузла */
		postOrder(tree->right);															/* переходимо в праве піддерево вузла */
		printf("%g+I*%g  %s\n", tree->numbers.x, tree->numbers.y, tree->key);			/* обробка даних в вершині дерева */
	}
	return;
}


/*Функція searchElement
шукає елемент в дереві
Вхід:key-ключ вершини яку потрібно знайти
Вихід:tree-вершина дерева
*/

BTnode* searchElement(BTnode* tree, char* key)
{
	if (!tree)
	{
		return NULL;
	}
	else if (strcmp(tree->key, key) == 0)
	{
		return tree;
	}
	else if (strcmp(tree->key, key) > 0)
	{
		searchElement(tree->left, key);
	}
	else if (strcmp(tree->key, key) < 0)
	{
		searchElement(tree->right, key);
	}

}

/*Функція findSmallestElement
шукає найменший елемент
Вихід:tree-вершина дерева
*/
BTnode* findSmallestElement(BTnode* tree)
{
	if (!tree || !tree->left)
	{
		return tree;
	}
	else
	{
		return findSmallestElement(tree->left);
	}
}


/* функція deleteElement
   видаляє вузол дерева
   Вхід: key - ключ вузла, який потрібно видалити
   Вихід: tree - вершина дерева

*/
BTnode* deleteElement(tBST* dsTree, BTnode* subTree, char* key)
{
	
	if (subTree == NULL)
		return subTree;

	if (strcmp(key, subTree->key) == -1)
	{
		subTree->left = deleteElement(dsTree, subTree->left, key);
	}

	else if (strcmp(key, subTree->key) == 1)
	{
		subTree->right = deleteElement(dsTree, subTree->right, key);
	}


	else
	{
																						// один нащадок
		if (subTree->left == NULL)														// якщо тільки правий нащадок
		{
			struct BTnode* temp = subTree->right;
			free(subTree);
			dsTree->size--;
			return temp;
		}
		else if (subTree->right == NULL)												// якщо тільки лівий нащадок
		{
			struct BTnode* temp = subTree->left;
			free(subTree);
			dsTree->size--;
			return temp;
		}
																						  // два нащадка
		struct BTnode* temp = findSmallestElement(subTree->right);

		subTree->key = temp->key;
		subTree->numbers = temp->numbers;
		subTree->right = deleteElement(dsTree, subTree->right, temp->key);
	}
	return subTree;
}


void  input_data(Complex& buf)
{

	printf("Реальна та уявна частина\n");
	scanf("%f %f", &buf.x, &buf.y);

}

void input_key(char* key)
{
	printf("Введіть ключ:");

	scanf("%s", key);
	key[strlen(key)] = '\0';
}


void file(FILE* fp, BTnode* tree)
{
	if (tree)
	{
		fprintf(fp, "%g+I*%g %s\n", tree->numbers.x, tree->numbers.y, tree->key);
		file(fp, tree->left);
		file(fp, tree->right);
	}
	return;
}

/*Функція readFile
зчитування дерева з  текстового файлу
Вхід: fp - файловий дескриптор, tree - дескриптор дерева
Вихід: tree - дерево, яке зчитане з файлу 
*/
tBST* readFile(FILE* fp, tBST* tree)
{
	Complex number;
	char key[SIZE];
	while (feof(fp) == 0)
	{
		fscanf(fp, "%g+I*%g %s\n", &number.x, &number.y, key);

		if (tree->root == NULL)
		{
			tree->root = insertTree(tree, tree->root, key, number);
		}
		else
		{
			insertTree(tree, tree->root, key, number);
		}
	}
	return tree;
}


/* функція deleteTree
   видаляє дерево
   Вихід: 0-дерево видалено,1-вершина відстутня
*/

int deleteTree(BTnode* tree) {
	if (tree) {
		deleteTree(tree->left);
		deleteTree(tree->right);
		free(tree);
		return 0;
	}
	else
		return 1;
}

#include "node.h"

/*
struct TreeNode{
	int value;
	struct TreeNode *parent;
	struct TreeNode *left;
	struct TreeNode *right;
};

typedef struct TreeNode TreeNode;

TreeNode *findNode(int number, TreeNode *Tree);
TreeNode *createNode(int number, TreeNode *node, TreeNode *parent);
TreeNode *addNode(int number, TreeNode *tree);
TreeNode *removeNode(int number, TreeNode *tree);
void *freeNode(TreeNode *node);
int readFile(char *filename);
*/

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("\nError: Wrong number of arguments");
		return 1;
	}
	if (!readFile(argv[1]))
		return 1;
	return 0;
}

/*
int readFile(char *filename)
{
	FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("\nError: File '%s' cannot be opened", filename);
        return 1;
    }
	TreeNode *tree = NULL;
	while (!feof(file))
	{
		int res = 0;
		char sym = '*';
		res = fscanf(file, "%c", &sym);
		if ((res == 1) && ((sym == '+') || (sym == '-') || (sym == '?')))
		{
			int num = -1;
			res = fscanf(file, "%d", &num);
			if ((res != 1) || (num < 0))
			{
				printf("\nError: Value error while reading number");
				return 1;
			}
			if (sym == '+')
			{
				tree = addNode(num, tree);
			}
			else if (sym == '-')
			{
				tree = removeNode(num, tree);
			}
			else if (sym == '?')
			{
				TreeNode *find_res = findNode(num, tree);
				(find_res) ? printf("\n%d Yes", num) : printf("\n%d No", num);
			}
		}
		else if ((sym != ' ') && (sym != '\t') && (sym != '\n'))
		{
			printf("\nError: Unacceptable symbol '%c' was found", sym);
			return 1;
		}
	}
	freeNode(tree);
    tree = NULL;
    fclose(file);
	return 0;
}

void *freeNode(TreeNode *node)
{
	if (node)
	{
		freeNode(node->left);
		freeNode(node->right);
		free(node);
	}
}

TreeNode *removeNode(int number, TreeNode *tree)
{
	TreeNode *cur_node = findNode(number, tree);
	if (!cur_node || !tree) //исключаем вариант, когда подается пустое дерево или удаляемого узла (УУ) нет
		return tree;

	TreeNode *new_root = NULL; //переменная, необходимая для замены корня дерева на новый в случае его удаления
	if ((cur_node->left) && (!cur_node->right)) //случай, когда УУ имеет продолжение слева, но не имеет веток справа
	{
		if ((cur_node->parent) && (cur_node->parent->left) && (cur_node->value == cur_node->parent->left->value))
		{
			cur_node->parent->left = cur_node->left;
		}
		else if ((cur_node->parent) && (cur_node->parent->right) && (cur_node->value == cur_node->parent->right->value))
		{
			cur_node->parent->right = cur_node->left;
		}
		else
		{
			new_root = cur_node->left;
		}
		cur_node->left->parent = cur_node->parent;
	}
	else if (cur_node->right) //случай, когда УУ имеет ТОЛЬКО продолжение по правой ветке
	{
		TreeNode *left_node = cur_node->right->left; //смотрим, есть ли у правой ветви УУ продолжение по левой ветви
		while (left_node) //'спускаемся вниз' по левой ветке
			if (left_node->left != NULL)
				left_node = left_node->left;
		if (left_node) // == у правой ветви УУ есть продолжение слева (left_node - 'нижний' элемент по этому продолжению)
		{
			if ((cur_node->parent) && (cur_node->parent->left) && (cur_node->value == cur_node->parent->left->value))
			{
				cur_node->parent->left = left_node;
			}
			else if ((cur_node->parent) && (cur_node->parent->right) && (cur_node->value == cur_node->parent->right->value))
			{
				cur_node->parent->right = left_node;
			}
			else
			{
				new_root = left_node;
			}
			left_node->parent = cur_node->parent;
		}
		else // == у правой ветви УУ нет продолжения слева
		{
			if ((cur_node->parent) && (cur_node->parent->left) && (cur_node->value == cur_node->parent->left->value))
			{
				cur_node->parent->left = cur_node->right;
			}
			else if ((cur_node->parent) && (cur_node->parent->right) && (cur_node->value == cur_node->parent->right->value))
			{
				cur_node->parent->right = cur_node->right;
			}
			else
			{
				new_root = cur_node->right;
			}
			cur_node->right->parent = cur_node->parent;
		}
	}
	else //случай, когда УУ не имеет ответвлений
	{
		if ((cur_node->parent) && (cur_node->parent->left) && (cur_node->value == cur_node->parent->left->value))
		{
			cur_node->parent->left = NULL;
		}
		else if ((cur_node->parent) && (cur_node->parent->right) && (cur_node->value == cur_node->parent->right->value))
		{
			cur_node->parent->right = NULL;
		}
		else
		{
			tree = NULL;
		}
	}
	if (new_root)
		tree = new_root;
	free(cur_node);
	return tree;
}

TreeNode *addNode(int number, TreeNode *tree)
{
	TreeNode *cur_node = tree;
	if (!cur_node)
	{
		tree = createNode(number, tree, NULL);
		return tree;
	}
	TreeNode *parent = tree;
	while (cur_node)
	{
		if (cur_node->value == number)
		{
			return tree;
		}
		else if (number < cur_node->value)
		{
			if (cur_node->left != NULL)
			{
				cur_node = cur_node->left;
				parent = cur_node;
			}
			else
			{
				cur_node->left = createNode(number, cur_node, parent);
				return tree;
			}
		}
		else if (number > cur_node->value)
		{
			if (cur_node->right != NULL)
			{
				cur_node = cur_node->right;
				parent = cur_node;
			}
			else
			{
				cur_node->right = createNode(number, cur_node, parent);
				return tree;
			}
		}
	}
}

TreeNode *createNode(int number, TreeNode *node, TreeNode *parent)
{
	node = (TreeNode*) malloc(sizeof(TreeNode));
	assert(node != NULL);
	node->value = number;
	node->parent = parent; 
	node->left = NULL;
	node->right = NULL;
	return node;
}

TreeNode *findNode(int number, TreeNode *tree)
{
	TreeNode *cur_node = tree;
	if (!cur_node)
		return NULL;
	while (cur_node)
	{
		if (cur_node->value == number)
		{
			return cur_node;
		}
		else if ((number < cur_node->value) && (cur_node->left != NULL))
		{
			cur_node = cur_node->left;
		}
		else if ((number > cur_node->value) && (cur_node->right != NULL))
		{
			cur_node = cur_node->right;
		}
		else
		{
			return NULL;
		}
	}
} */
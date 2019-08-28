#include "drawtree.h"

/*
treenode
{
	int data;
	treenode *lchild;
	treenode *rchild;

	int height;
};
*/

void bst_insert2(treenode **proot, treenode *new)
{
	if(*proot == NULL)
	{
		*proot = new;
		return;
	}


	if(new->data < (*proot)->data)
		bst_insert2(&(*proot)->lchild, new);
	else
		bst_insert2(&(*proot)->rchild, new);
}

void bst_remove2(treenode **proot, int data)
{
	if(data < (*proot)->data)
	{
		bst_remove2(&(*proot)->lchild, data);
	}
	else if(data > (*proot)->data)
	{
		bst_remove2(&(*proot)->rchild, data);
	}
	else
	{
		if((*proot)->lchild != NULL)
		{
			// 1
			treenode *max;
			for(max=(*proot)->lchild; max->rchild!=NULL; max=max->rchild);

			// 2
			(*proot)->data = max->data;

			// 3
			bst_remove2(&(*proot)->lchild, max->data);
		}

		else if((*proot)->rchild != NULL)
		{
			// 1
			treenode *min;
			for(min=(*proot)->rchild; min->lchild!=NULL; min=min->lchild);

			// 2
			(*proot)->data = min->data;

			// 3
			bst_remove2(&(*proot)->rchild, min->data);
		}

		else
		{
			free(*proot);
			*proot = NULL;
		}
	}


	// ...
	// ...
	// ...
}

int main(void)
{
	treenode *root = NULL;

	int n;

	while(1)
	{
		scanf("%d", &n);

		if(n > 0)
		{
			treenode *new = new_node(n);
			bst_insert2(&root, new);
		}

		else if(n < 0)
		{
			bst_remove2(&root, -n);
		}

		else
			break;

		draw(root);
	}

	system("firefox *.html");
}

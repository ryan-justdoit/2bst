#include "drawtree.h"

/*treenode
 * {
 * 	int data;
 * 	treenode *lchild;
 * 	treenoed *rchild;
 *
 * 	int height;
 * }
 */

treenode *avl_revolve_left(treenode *root)
{
	treenode *tmp = root->rchild;
	root->rchild = tmp->lchild;
	tmp->lchild = root;

	root->height = MAX(height(root->rchild),height(root->lchild)) + 1;
	tmp->height  = MAX(height(tmp->rchild),height(tmp->lchild)) + 1;

	return tmp;	
}

treenode *avl_revolve_right(treenode *root)
{
	treenode *tmp = root->lchild;
	root->lchild = tmp->rchild;
	tmp->rchild  = root;

	root-> height = MAX(height(root->lchild),height(root->rchild)) + 1;
	tmp->height = MAX(height(tmp->lchild),height(tmp->rchild)) + 1;

	return tmp;
}

treenode *avl_revolve_left_right(treenode *root)
{
	root->lchild = avl_revolve_left(root->lchild);
	return avl_revolve_right(root);
}

treenode *avl_revolve_right_left(treenode *root)
{
	root->rchild = avl_revolve_right(root->rchild);
	return avl_revolve_left(root);
}

void avl_insert2(treenode **proot,treenode *new)
{
	if(*proot == NULL)
	{
		*proot = new;
		return;
	}

	if(new->data < (*proot)->data)
		avl_insert2(&(*proot)->lchild,new);
	else
		avl_insert2(&(*proot)->rchild,new);
	//最大是2
	if(height((*proot)->lchild) - height((*proot)->rchild) >1)
	{
		if(new->data < (*proot)->lchild->data)
		{
			printf("revolving right ... \n");
			*proot = avl_revolve_right(*proot);
		}
		else
		{
			printf("revolving ...\n");
			*proot = avl_revolve_left_right(*proot);
		}
	}
	else if((height((*proot)->rchild) - height((*proot)->lchild)) > 1)
	{
		if(new->data > (*proot)->rchild->data)
		{
			printf("revolving left ... \n");
			*proot = avl_revolve_left(*proot);
		}
		else
		{
			printf("revolving ... \n");
			*proot = avl_revolve_right_left(*proot);
		}
	}
	(*proot)->height = MAX(height((*proot)->lchild),height((*proot)->rchild))+1;
}

void avl_remove2(treenode **proot,int data)
{
	if(data < (*proot)->data)
	{
		avl_remove2(&(*proot)->lchild,data);
	}
	else if(data > (*proot)->data)
	{
		avl_remove2(&(*proot)->rchild,data);
	}
	else
	{
		if((*proot)->lchild != NULL)
		{
			// 1
			treenode *max;
			for(max=(*proot)->lchild;max->rchild!=NULL;max=max->rchild);

			// 2
			(*proot)->data = max->data;

			// 3
			avl_remove2(&(*proot)->lchild,max->data);
 			
		}
		else if((*proot)->rchild != NULL)
		{
			// 1
			treenode *min;
			for(min=(*proot)->rchild; min->lchild != NULL;min=min->lchild);

			// 2
			(*proot)->data = min->data;

			// 3
			avl_remove2(&(*proot)->rchild,min->data);
		}
		else
		{
			free(*proot);
			*proot = NULL;
		}
	}
}

int main(void)
{
	treenode *root = NULL;
	int n;

	while(1)
	{
		scanf("%d",&n);
		if(n > 0)
		{
			treenode *new = new_node(n);
			avl_insert2(&root,new);
		}

		else if(n < 0)
		{
			avl_remove2(&root, -n);
		}

		else
			break;

		draw(root);
	}
	system("firefox *.html");
}

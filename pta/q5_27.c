#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

int n, m;

typedef struct mb_s{// member
	char name[11];
	struct mb_s *sibl, *chld;
	int marg;	// margin
}mb_t;

mb_t*	mb;

mb_t*	getFamily();
bool	checkcp(char x[], char y[]);	// check child parent relatinship
bool	checkda(char x[], char y[]);	// check descendant ancestor relationship
bool	checks(char x[], char y[]);		// check sibling relationship

int main()
{
	scanf("%d%d", &n, &m);
	mb	= getFamily();
	assert(mb->name != NULL);

	char x[11], y[11], r[11];	// relationship
	int i;
	for(i=0; i<m; i++){
		scanf("%s is %*s %s of %s\n", x, r, y);
		bool flag;
		if(strcmp(r, "child")==0){
			flag = checkcp(x, y);
		}
		else if(strcmp(r, "parent")==0){
			flag = checkcp(y, x);
		}
		else if(strcmp(r, "descendant")==0){
			flag = checkda(x, y);
		}
		else if(strcmp(r, "ancestor")==0){
			flag = checkda(y, x);
		}
		else if(strcmp(r, "sibling")==0){
			flag = checks(x, y);
		}

		if(flag) printf("True\n");
		else printf("False\n");
	}
	return 0;
}

mb_t* getFamily()
{
	mb_t*	stack[n];
	int		top	= -1;

	int i;
	for(i=0; i<n; i++){
		char	str[72];
		mb_t	*pmb	= (mb_t*)malloc(sizeof(mb_t));
		pmb->sibl	= pmb->chld	= NULL;

		fgets(str, 71, stdin);
		if(str[0] == '\n')
			fgets(str, 71, stdin);
		assert(str!=NULL && str[0]!='\n');
		sscanf(str, "%s", pmb->name);
		pmb->marg	= strlen(str)-1 - strlen(pmb->name);
		assert(pmb->marg >= 0 && pmb->marg % 2 == 0);

		if(top > -1){
			int	gap	= pmb->marg - stack[top]->marg;
			int j;
			switch(gap){
			case 2:
				stack[top]->chld	= pmb;
				stack[++top]	= pmb;
				break;
			case 0:
				stack[top]->sibl	= pmb;
				stack[top]	= pmb;
				break;
			default:
				for(j=gap; j < 0; j+=2)
					--top;
				// at least remains two members && ...
				assert(top > 0 && stack[top]->marg == pmb->marg);
				stack[top]->sibl	= pmb;
				stack[top]	= pmb;
			}
		}
		else{
			assert(pmb->marg == 0);
			stack[++top]	= pmb;
			mb = pmb;
		}
		assert(top > -1);
	}

	return mb;
}

// find member in pmb_a by name. save leftmost sibling in pmb_a
mb_t*	findmb(char y[], mb_t* pmb_a, mb_t** ppmb_ls);

bool	checkcp(char x[], char y[]){	// check child parent relatinship
	assert(x!=NULL && y!=NULL && x[0]!=0 && y[0]!=0 && strcmp(x, y)!=0);
	mb_t*	pmb_ls	= findmb(y, mb, NULL);
	assert(pmb_ls != NULL && strcmp(y, pmb_ls->name) == 0);
	mb_t*	pmb_c	= pmb_ls->chld;

	while(pmb_c!=NULL && strcmp(x, pmb_c->name)!=0)
		pmb_c = pmb_c->sibl;

	if(pmb_c != NULL)
		return true;
	else
		return false;
}

bool	checkda(char x[], char y[]){	// check descendant ancestor relationship
	assert(x!=NULL && y!=NULL && x[0]!=0 && y[0]!=0 && strcmp(x, y)!=0);
	mb_t*	pmb_a	= findmb(y, mb, NULL);
	assert(pmb_a != NULL && strcmp(y, pmb_a->name) == 0);
	mb_t*	pmb_d	= findmb(x, pmb_a, NULL);

	if(pmb_d != NULL){
		assert(strcmp(x, pmb_d->name) == 0);
		return true;
	}
	else
		return false;
}

bool	checks(char x[], char y[]){		// check sibling relationship
	assert(x!=NULL && y!=NULL && x[0]!=0 && y[0]!=0 && strcmp(x, y)!=0);
	mb_t*	pmb_ls;
	mb_t*	pmb_s1	= findmb(x, mb, &pmb_ls);
	assert(pmb_s1 != NULL && strcmp(x, pmb_s1->name) == 0);

	if(pmb_ls == NULL) return false;

	//else
	mb_t*	pmb_s2	= pmb_ls->sibl;
	while(pmb_s2 != NULL && strcmp(y, pmb_s2->name)!=0)
		pmb_s2	= pmb_s2->sibl;

	if(pmb_s2 != NULL)
		return true;
	else
		return false;
}

mb_t*	findmb(char y[], mb_t* pmb_a, mb_t** ppmb_ls)
{
	assert(y!=NULL && y[0]!=0 && pmb_a!=NULL);
	mb_t*	pmb_ls_tmp = NULL;

	mb_t*	queue[n+1];
	int		front=0, rear=0;

	queue[rear] = pmb_a;
	rear = (rear+1)%(n+1);

	pmb_ls_tmp = pmb_a;
	if(strcmp(y, pmb_a->name)==0){
		if(ppmb_ls != NULL)
			*ppmb_ls = pmb_ls_tmp;
		return pmb_a;
	}
	do{
		pmb_ls_tmp = queue[front]->chld;
		front = (front+1) % (n+1);
		mb_t*	pmb	= pmb_ls_tmp;
		while(pmb != NULL){
			queue[rear] = pmb;
			rear = (rear+1)%(n+1);

			if(strcmp(y, pmb->name) == 0){
				if(ppmb_ls != NULL)
					*ppmb_ls = pmb_ls_tmp;
				return pmb;
			}
			pmb = pmb->sibl;
		}
	}while(front != rear);

	return NULL;
}

#include <stdio.h>
#include <stdlib.h>

void alloc_matrix(int ***matrix, int n, int m)
{
	int i;
	*matrix=(int **) malloc(n*sizeof(int*));
	for (i=0; i<n; i++)
		(*matrix)[i]=(int*) malloc(m*sizeof(int));
}

void free_matrix(int **matrix, int n, int m)
{
	int i;
	for (i=0; i<n; i++)
		free(matrix[i]);
	free(matrix);
}

void read_matrix(int **matrix, int n, int m)
{
	int i, j;
	for (i=0; i<n; i++)
		for (j=0; j<m; j++)
			scanf("%d", matrix[i]+j);
}

void print_matrix(int **matrix, int n, int m)
{
	int i, j;
	for (i=0; i<n; i++) {
		for (j=0; j<m; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
}

struct list {
	int i, j;
	struct list* next;
};

struct queue {
	struct list* head;
	struct list* tail;
};

void print_queue(struct queue* s)
{
	struct list *tmp=s->head;
	while (tmp) {
		printf ("(%d,%d)->", tmp->i, tmp->j);
		tmp = tmp->next;
	}
	printf("\n");
}

void init_queue (struct queue **s, struct list* tmp)
{
	*s = (struct queue *) malloc(sizeof(struct queue));
	(*s)->head = tmp;
	(*s)->tail = tmp;
}

void push_queue (struct queue **s, int i, int j)
{
	struct list* tmp = malloc(sizeof(struct list));
	tmp->i = i;
	tmp->j = j;
	tmp->next = NULL;

	if (!*s)
		init_queue (s, tmp);
	else {
#ifdef DEBUG
		printf(">(%d,%d)\n", i, j);
#endif
		(*s)->tail->next = tmp;
		(*s)->tail = tmp;
	}
}

void pop_queue (struct queue* s)
{
	if (!s)
		return;

	struct list* tmp = s->head->next;
	free(s->head);
	s->head = tmp;
}

void get_element(struct queue* s, int* i, int* j)
{
	*i = s->head->i;
	*j = s->head->j;
}

void check_next_element(int **grid, int n, int m, int i, int j, struct queue** s,
		int *lvl)
{
	int tmp=grid[i][j];
	if (i<n-1 && !grid[i+1][j]) {
		grid[i+1][j]=tmp-1;
		push_queue(s, i+1, j);
	}

	if (j<m-1 && !grid[i][j+1]) {
		grid[i][j+1]=tmp-1;
		push_queue(s, i, j+1);
	}

	if (i>0 && !grid[i-1][j]) {
		grid[i-1][j]=tmp-1;
		push_queue(s, i-1, j);
	}

	if (j>0 && !grid[i][j-1]) {
		grid[i][j-1]=tmp-1;
		push_queue(s, i, j-1);
	}
	if (-tmp > *lvl)
		*lvl = -tmp-1;
}


int spawn_over_queue(int **grid, int n, int m, struct queue** s)
{
	int i, j, lvl=0;
	while ((*s)->head) {
#ifdef DEBUG
		print_queue(*s);
#endif
		get_element(*s, &i, &j);
		check_next_element(grid, n, m, i, j, s, &lvl);
		pop_queue(*s);
	}
	return lvl;
}

int answer(int **grid, int n, int m)
{
	int i, j;
	struct queue *s=NULL;
	for (i=0; i<n; i++)
		for (j=0; j<m; j++)
			if (grid[i][j]) {
				grid[i][j]=-1;
				push_queue(&s, i, j);
			}
	return spawn_over_queue(grid, n, m, &s);
}

int main ()
{
	int n, m;
	scanf("%d", &n);
	scanf("%d", &m);

	int **grid;
	alloc_matrix(&grid, n, m);
	read_matrix(grid, n, m);
#ifdef debug
	printf("\n");
	print_matrix(grid, n, m);
#endif
	printf("%d", answer(grid, n, m));
#ifdef DEBUG
	printf("\n");
	print_matrix(grid, n, m);
#endif
	free_matrix(grid, n, m);
	return 0;
}

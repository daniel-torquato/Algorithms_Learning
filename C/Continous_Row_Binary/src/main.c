#include <stdio.h>
#include <stdlib.h>


int goto_next_cell(int **grid, int n, int m, int i, int j, int *flag, int *lvl)
{
	if (grid[i][j]<1)
		return 0;

	grid[i][j]=-1-*lvl;

	if (i<n-1 && grid[i+1][j]>0) {
		if (!*flag) {
			*flag=1;
		}
		goto_next_cell(grid, n, m, i+1, j, flag, lvl);
	}

	if (j<m-1 && grid[i][j+1]>0) {
		if (!(*flag)) {
			*flag=1;
		}
		goto_next_cell(grid, n, m, i, j+1, flag, lvl);
	}

	if ((i>0 && grid[i-1][j])>0) {
		if (!(*flag)) {
			*flag=1;
		}
		goto_next_cell(grid, n, m, i-1, j, flag, lvl);
	}

	if (j>0 && grid[i][j-1]>0) {
		if (!(*flag)) {
			*flag=1;
		}
		goto_next_cell(grid, n, m, i, j-1, flag, lvl);
	}
}

int get_cont(int **grid, int n, int m)
{
	int ret=0, flag=0;
	int i, j;
	for(i=0; i<n; i++)
		for(j=0; j<m; j++) {
			if (grid[i][j]>0) {
				ret++;
				goto_next_cell(grid, n, m, i, j, &flag, &ret);
			}
			flag=0;
#ifdef DEBUG
			printf("%d ", ret);
#endif
		}
			//check_adjacence_cell(grid, &ret, i, j, n, m);

	return ret;
}

void alloc_matrix (int ***matrix, int n, int m)
{
	*matrix=(int **) malloc(n*sizeof(int*));
#ifdef MEM_DEBUG
	printf("%d\n", *matrix);
#endif
	int i;
	for (i=0; i<n; i++) {
		(*matrix)[i]=(int *) malloc(m*sizeof(int));
#ifdef MEM_DEBUG
		printf("%d ", (*matrix)[i]);
#endif
	}
#ifdef MEM_DEBUG
	printf("\n");
#endif

}

void free_matrix(int **matrix, int n, int m)
{
	int i;
#ifdef MEM_DEBUG
	printf("\n");
#endif
	for (i=0; i<n; i++) {
		free(matrix[i]);
#ifdef MEM_DEBUG
		printf("%d ", matrix[i]);
#endif
	}
#ifdef MEM_DEBUG
	printf("\n%d\n", matrix);
#endif
	free(matrix);
}

void print_matrix(int **matrix, int n, int m)
{
	int i, j;
	printf("\n");
	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int n, m;
	int i, j;
	scanf("%d", &n);
	scanf("%d", &m);
	int **grid;
	alloc_matrix(&grid, n, m);

#ifdef DEBUG
	printf("%d %d\n", n, m);
#endif

	for (i=0; i<n; i++) {
		for (j=0; j<m; j++) {
			scanf("%d", grid[i]+j);
#ifdef DEBUG
			printf("%d ", grid[i][j]);
#endif
		}
#ifdef DEBUG
		printf("\n");
#endif
	}

	printf("%d", get_cont(grid, n, m));
#ifdef DEBUG
	print_matrix(grid, n, m);
#endif
	free_matrix(grid, n, m);

	return 0;
}

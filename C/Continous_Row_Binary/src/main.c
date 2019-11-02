#include <stdio.h>
#include <stdlib.h>

int get_count_in_col(int **grid, int j, int n)
{
	int i;
	int len=0, val=0;
	for (i=0; i<n; i++) {
#ifdef MEM_DEBUG
		printf("%d ", grid[i]+j);
#endif
		if (grid[i][j]) {
			val++;
		} else {
			if (val>1)
				len++;
			val=0;
		}
#ifdef DEBUG
		printf(">%d ", grid[i][j], len);
#endif
	}
#ifdef DEBUG
	printf("\n");
#endif
	if (val>1)
		len++;

	return len;
}

int get_count_in_row(int **grid, int i, int m)
{
	int j;
	int len=0, val=0;
	for (j=0; j<m; j++) {
#ifdef MEM_DEBUG
		printf("%d ", grid[i]+j);
#endif
		if (grid[i][j]) {
			val++;
		} else {
			if (val>1)
				len++;
			val=0;
		}
#ifdef DEBUG
		printf(">%d ", grid[i][j], len);
#endif
	}
#ifdef DEBUG
	printf("\n");
#endif
	if (val>1)
		len++;

	return len;
}
int get_cont(int **grid, int n, int m)
{
	int ret=0;
	int i, j;
	for(i=0; i<n; i++)
		ret+=get_count_in_row(grid, i, m);
	for(j=0; j<m; j++)
		ret+=get_count_in_col(grid, j, n);

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
	free_matrix(grid, n, m);

	return 0;
}

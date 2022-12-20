//Copyright 2022-2023 Raducanu George-Cristian 321CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 10007

int isvalid(char c)
{
	if (strchr("LDPCMTRFOS", c) != 0)
		return 1;
	return 0;
}

int sum_mat(int **mat, int n, int m)
{
	int s = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			s = (s + mat[i][j] + MOD) % MOD;
	return s;
}

void mult_sq(int **a, int **b, int **result, int size)
{
	int **copy_a = malloc(size * sizeof(int *));
	for (int i = 0; i < size; ++i)
		copy_a[i] = malloc(size * sizeof(int));

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			copy_a[i][j] = a[i][j];

	int **copy_b = malloc(size * sizeof(int *));
	for (int i = 0; i < size; ++i)
		copy_b[i] = malloc(size * sizeof(int));

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			copy_b[i][j] = b[i][j];

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			result[i][j] = 0;

	for (int k = 0; k < size; ++k)
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j) {
				result[i][j] = result[i][j] + copy_a[i][k] * copy_b[k][j];
				result[i][j] = ((MOD + result[i][j]) % MOD + MOD) % MOD;
			}

	for (int i = 0; i < size; ++i) {
		free(copy_a[i]);
		free(copy_b[i]);
	}
	free(copy_a);
	free(copy_b);
}

void log_power(int **a, int size, int pow, int **sol)
{
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			sol[i][j] = 0;
	for (int i = 0; i < size; ++i)
		sol[i][i] = 1;

	while (pow > 0) {
		if (pow % 2 == 1)
			mult_sq(sol, a, sol, size);
		mult_sq(a, a, a, size);
		pow  /= 2;
	}
}

void summ(int **a, int **b, int **c, int size)
{
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			c[i][j] = (a[i][j] + b[i][j] + MOD) % MOD;
}

void diff(int **a, int **b, int **c, int size)
{
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			c[i][j] = (a[i][j] - b[i][j] + 2 * MOD) % MOD;
}

int **allocate(int **a, int size)
{
	a = malloc(size * sizeof(int *));
	for (int i = 0; i < size; ++i)
		a[i] = malloc(size * sizeof(int));
	return a;
}

void P_command(int ***a, int *n, int *m, int index)
{
	int idx;
	scanf(" %d", &idx);
	if (idx >= index || idx < 0) {
		printf("No matrix with the given index\n");
	} else {
		for (int i = 0; i < n[idx]; ++i) {
			for (int j = 0; j < m[idx]; ++j)
				printf("%d ", a[idx][i][j]);
			printf("\n");
			}
		}
}

void D_command(int *n, int *m, int index)
{
	int idx2;
	scanf(" %d", &idx2);
	if (idx2 >= index || idx2 < 0)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", n[idx2], m[idx2]);
}

void T_command(int ***a, int *n, int *m, int index)
{
	int idxtransp;
	scanf(" %d", &idxtransp);
	if (idxtransp >= index || idxtransp < 0) {
		printf("No matrix with the given index\n");
	} else {
		int **aux = malloc(m[idxtransp] * sizeof(int *));
		for (int i = 0; i < m[idxtransp]; ++i)
			aux[i] = malloc(n[idxtransp] * sizeof(int));

		for (int i = 0; i < n[idxtransp]; ++i)
			for (int j = 0; j < m[idxtransp]; ++j)
				aux[j][i] = a[idxtransp][i][j];

		for (int i = 0; i < n[idxtransp]; ++i)
			free(a[idxtransp][i]);
		free(a[idxtransp]);
		int auxi = n[idxtransp];
		n[idxtransp] = m[idxtransp];
		m[idxtransp] = auxi;
		a[idxtransp] = aux;
	}
}

void O_command(int ***a, int *n, int *m, int index)
{
	for (int i = 0; i < index; ++i)
		for (int j = i + 1; j < index; ++j) {
			if (sum_mat(a[i], n[i], m[i]) > sum_mat(a[j], n[j], m[j])) {
				int aux = n[i];
				n[i] = n[j];
				n[j] = aux;
				aux = m[i];
				m[i] = m[j];
				m[j] = aux;
				int **swapy = a[i];
				a[i] = a[j];
				a[j] = swapy;
			}
		}
}

void C_command(int ***a, int *n, int *m, int index)
{
	int l, c;
	int indx_c;
	scanf(" %d", &indx_c);
	scanf(" %d", &l);
	int *lin = malloc(sizeof(int) * l);
	for (int i = 0; i < l; ++i)
		scanf(" %d", &lin[i]);
	scanf(" %d", &c);
	int *col = malloc(sizeof(int) * c);
	for (int i = 0; i < c; ++i)
		scanf(" %d", &col[i]);
	if (indx_c >= index || indx_c < 0) {
		printf("No matrix with the given index\n");
	} else {
		int **aux = malloc(l * sizeof(int *));
		for (int i = 0; i < l; ++i)
			aux[i] = malloc(c * sizeof(int));
		for (int i = 0; i < l; ++i)
			for (int j = 0; j < c; ++j)
				aux[i][j] = a[indx_c][lin[i]][col[j]];
		int **dell = a[indx_c];
		a[indx_c] = aux;
		for (int i = 0; i < n[indx_c]; ++i)
			free(dell[i]);
		free(dell);
		n[indx_c] = l;
		m[indx_c] = c;
	}
	free(lin);
	free(col);
}

void R_command(int ***a, int *n, int *m, int index)
{
	int indx_r, pow;
	scanf(" %d %d", &indx_r, &pow);
	if (indx_r >= index || indx_r < 0) {
		printf("No matrix with the given index\n");
	} else {
		if (pow < 0) {
			printf("Power should be positive\n");
		} else {
			if (n[indx_r] != m[indx_r]) {
				printf("Cannot perform matrix multiplication\n");
			} else {
				int **aux3 = malloc(n[indx_r] * sizeof(int *));
				for (int i = 0; i < n[indx_r]; ++i)
					aux3[i] = malloc(n[indx_r] * sizeof(int));
				log_power(a[indx_r], n[indx_r], pow, aux3);
				int **del3 = a[indx_r];
				a[indx_r] = aux3;
				for (int i = 0; i < n[indx_r]; ++i)
					free(del3[i]);
				free(del3);
			}
		}
	}
}

void F_command(int ****a, int **n, int **m, int *index)
{
	int idxfree;
	scanf(" %d", &idxfree);
	if (idxfree >= (*index) || idxfree < 0) {
		printf("No matrix with the given index\n");
	} else {
		//dealocam matricea cu indicele idxfree
		int **del = (*a)[idxfree];
		for (int i = idxfree; i < (*index) - 1; i++)
			(*a)[i] = (*a)[i + 1];
		for (int i = 0; i < (*n)[idxfree]; ++i)
			free(del[i]);
		free(del);
		(*a) = realloc((*a), ((*index) - 1) * sizeof(int **));
		for (int i = idxfree; i < (*index) - 1; ++i) {
			(*n)[i] = (*n)[i + 1];
			(*m)[i] = (*m)[i + 1];
	}
	(*n) = realloc((*n), ((*index) - 1) * sizeof(int));
	(*m) = realloc((*m), ((*index) - 1) * sizeof(int));
	(*index)--;
	}
}

void M_command(int ****a, int **n, int **m, int  *index)
{
	int p1, p2;
	scanf(" %d %d", &p1, &p2);
	if (p1 > (*index) || p1 < 0 || p2 > (*index) || p2 < 0) {
		printf("No matrix with the given index\n");
	} else {
		if ((*m)[p1] != (*n)[p2]) {
			printf("Cannot perform matrix multiplication\n");
		} else {
			(*a) = realloc((*a), sizeof(int **) * ((*index) + 1));
			(*n) = realloc((*n), ((*index) + 1) * sizeof(int));
			(*m) = realloc((*m), ((*index) + 1) * sizeof(int));
			(*n)[(*index)] = (*n)[p1];
			(*m)[(*index)] = (*m)[p2];
			(*a)[(*index)] = malloc(sizeof(int *) * (*n)[(*index)]);
			for (int i = 0; i < (*n)[(*index)]; ++i)
				(*a)[(*index)][i] = calloc((*m)[(*index)], sizeof(int));
			// acuma fac ceva inmultire
			for (int i = 0; i < (*n)[(*index)]; ++i)
				for (int j = 0; j < (*m)[(*index)]; ++j)
					for (int k = 0; k < (*m)[p1]; ++k) {
						(*a)[(*index)][i][j] += (*a)[p1][i][k] * (*a)[p2][k][j];
						(*a)[(*index)][i][j] = MOD + (*a)[(*index)][i][j] % MOD;
						(*a)[(*index)][i][j] = (*a)[(*index)][i][j] % MOD;
					}
			(*index)++;
		}
	}
}

int main(void)
{
	int ***a;
	int *n;
	int *m;
	char c;
	int index = 0;
	while (scanf(" %c", &c)) {
		if (c == 'Q')
			break;
		if (isvalid(c) == 0)
			printf("Unrecognized command\n");
		if (c == 'L') {
			int N, M;
			scanf(" %d %d ", &N, &M);
			if (index == 0) {
				n = (int *)malloc(1 * sizeof(int));
				n[0] = N;
				m = (int *)malloc(1 * sizeof(int));
				m[0] = M;
				a = (int ***)malloc(sizeof(int **));
				a[0] = (int **)malloc(N * sizeof(int *));
				for (int i = 0; i < N; ++i)
					a[0][i] = malloc(M * sizeof(int));
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j)
						scanf(" %d", &a[0][i][j]);
				index++;
			} else {
				n = (int *)realloc(n, sizeof(int) * (index + 1));
				m = (int *)realloc(m, sizeof(int) * (index + 1));
				n[index] = N;
				m[index] = M;
				a = (int ***)realloc(a, (index + 1) * sizeof(int **));
				a[index] = (int **)malloc(N * sizeof(int *));
				for (int i = 0; i < N; ++i)
					a[index][i] = malloc(M * sizeof(int));
				for (int i = 0; i < N; ++i)
					for (int j = 0; j < M; ++j)
						scanf(" %d", &a[index][i][j]);
				index++;
			}
		}
		if (c == 'P')
			P_command(a, n, m, index);
		if (c == 'F')
			F_command(&a, &n, &m, &index);
		if (c == 'D')
			D_command(n, m, index);
		if (c == 'T')
			T_command(a, n, m, index);
		if (c == 'M')
			M_command(&a, &n, &m, &index);
		if (c == 'O')
			O_command(a, n, m, index);
		if (c == 'C')
			C_command(a, n, m, index);
		if (c == 'R')
			R_command(a, n, m, index);
		//if (c == 'S')
			//M_command(&a, &n, &m, &index);
	}

	for (int z = 0; z < index; ++z)
		for (int i = 0; i < n[z]; ++i)
			free(a[z][i]);
	for (int z = 0; z < index; ++z)
		free(a[z]);
	free(a), free(n), free(m);
	return 0;
}

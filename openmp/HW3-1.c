void rot(int N, double* a) {
omp_set_num_threads(5);
#pragma omp parallel
	{
#pragma omp for schedule(static, 5)
		for (int i = 0; i < N - 1; i++) {
			double tmp = a[i];
			a[i] = a[i + 1];
			a[i + 1] = tmp;
		}
	}
}

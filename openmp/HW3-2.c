int foo(int N, int* a, int* b, int* c, int* d) {
	double tmp, total = 0;
#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp for    // for loop # 1
			for (int i = 0; i < N; i++) {
				a[b[i]] += b[i];
				total += b[i];
			}
		}
#pragma omp section
		{
#pragma omp for   // for loop # 2
			for (int i = 0; i < N; i++) {
				tmp = c[i];
				c[i] = d[i];
				d[i] = tmp;
				total += c[i];
			}
#pragma omp for   // for loop # 3
			for (int i = 0; i < N; i++) {
				total += d[i];
			}
		}
	}
	return total;
}

/* issue 1 ) in for loop # 1, if the loop is paralized, threads can approach the same index of vector a because there can be same values with different index in vector b. 
 so the wrong value can be saved in vector a. So, the loops should be done sequentially. And the loop is inside the "sections", and only the section can be inside in it.

   issue 2 ) in for loop # 2, if the loop is paralized, threads share the tmp, so the wrong values would be saved in vecor c and d. 
   Also, as the loop share the total value, the wrong value can be saved in total. So the loops should not be paralized.

   issue 3 ) in for loop # 3 , like the issue 1, if the loop is paralized threads can approach the same total value, and if the same value is simultaneously, the wrong total
   value can be saved. So, it should not be paralized.

   issue 4 ) Overall, in loop # 2 and loop # 3, it doesn't make sense because a section is executed within a single thread but the paralized for loop is done with multiple threads.
   So, the for loop should not be inside the section.
   
   Moreover, it's not an issue for the code above but, the loop # 3 should be done after loop # 2 because the vector d in loop # 3 is dependent to loop # 2. */
 

// fixed code

int foo(int N, int* a, int* b, int* c, int* d) {
	double tmp, total = 0;
#pragma omp parallel
	{
#pragma omp sections
	{
#pragma omp section 
		{    
			for (int i = 0; i < N; i++) {
				a[b[i]] += b[i];
				total += b[i];
			}
			}
#pragma omp section
		{
			for (int i = 0; i < N; i++) {
				tmp = c[i];
				c[i] = d[i];
				d[i] = tmp;
				total += c[i];
			}
		}
	}
	
#pragma omp single 
	{  
		for (int i = 0; i < N; i++) {
			total += d[i];
				}
			}
		
	}
	return total;
}


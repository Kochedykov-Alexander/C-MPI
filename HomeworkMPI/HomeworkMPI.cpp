/*1.Написать программу, печатающую номер процесса и общее количество процессов в
коммуникаторе MPI_COMM_WORLD.*/


//#include <mpi.h>
//#include <stdio.h>
//
//int main(int argc, char* argv[])
//{
//	int rank, size;
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	printf("process %d of %d\n", rank, size);
//	MPI_Finalize();
//	
//}





/* 2.Написать программу, запустить ее на 2х процессах. На нулевом процессе задать массив
а из 10 элементов, значения сгенерировать случайным образом. Переслать этот массив
целиком первому процессу с помощью функции MPI_Send. Распечатать на первом процессе
принятый массив.
*/

//#include "mpi.h"
//#include "iostream"
//
//
//int main(int argc, char** argv)
//{
//    int size, rank;
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    if (rank == 0)
//    {
//        printf("process  %d \n", rank);
//        int a[10];
//        for (int i = 0; i < 10; i++)
//            a[i] = rand() % 100;
//        printf("send array, process %d \n", rank);
//            MPI_Send(&a, 10, MPI_INT, 1, 9, MPI_COMM_WORLD);
//    }
//    else
//    {
//        printf("process  %d \n", rank);
//        int b[10];
//        printf("%d process got array \n", rank);
//        MPI_Recv(&b, 10, MPI_INT, 0, 9, MPI_COMM_WORLD, &status);
//        for (int i = 0; i < 10; i++)
//            printf("b[%d]=%d ", i, b[i]);
//    }
//    MPI_Finalize();
//}





/*
3.Используя блокирующую операцию передачи сообщений (MPI_Send и MPI_Recv) выполнить пересылку данных одномерного массива,
из процесса с номером 1 на остальные процессы группы. На процессах получателях до выставления функции приема (MPI_Recv)
определить количество принятых данных (MPI_Probe). Выделить память под размер приемного буфера, после чего вызвать функцию MPI_Recv.
Полученное сообщение выдать на экран.
*/


//#include<mpi.h>
//#include<stdio.h>
//#include<iostream>
//
//
//int main(int argc, char** argv)
//{
//    int rank, size;
//    MPI_Status status;
//
//    
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//    if (rank == 1) {
//        int a[10] = { 19, 45, 14, 36, 14, 7, 12, 7, 103, 74};
//
//        for (int i = 0; i < size; i++) {
//            if (i != 1) {
//                MPI_Send(a, 10, MPI_INT, i, 1, MPI_COMM_WORLD);
//            }
//        }
//
//    }
//    
//    
//    else {
//        
//        int count;
//
//        /* MPI_Probe вернет управление, когда сообщение будет уже на приемной стороне в служебном буфере */
//        MPI_Probe(MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
//
//        MPI_Get_count(&status, MPI_INT, &count);
//
//        /* Принятое будет размещено в динамической памяти:
//         * заказываем в ней буфер соответствующей длины
//         */
//
//        int* buffer = new int[count];
//
//        
//        MPI_Recv(buffer, count, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
//        printf("in process: %d \n", rank);
//        for (int i = 0; i < count; i++) {
//            printf("a[%d] = %d ", i, buffer[i]);
//        }
//    }
//    
//    MPI_Finalize();
//    
//}


/*
4.Написать программу и запустить ее на p (= 2, 3, 4, 6, 8) процессах. На нулевом процессе
объявить и задать массив из 12 элементов. С помощью функции MPI_Send разослать блоки
массива на остальные процессы. Размер блока массива 12/p+1. В результате на нулевом
процессе должны быть элементы массива с 0 до 12/p+1, на первом процессе с 12/p+1 до
2×(12/p+1), на 3м процессе с 2×(12/p+1) до 3×(12/p+2) и т.д. Вывести элементы массива на
экран на каждом процессе.

*/




//#include<mpi.h>
//#include<stdio.h>
//#include<iostream>
//
//using namespace std;
//int main(int argc, char** argv)
//{
//    int rank, size;
//    MPI_Status status;
//    MPI_Init(&argc, &argv);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    
//    if (rank == 0) {
//        int a[12] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
//
//        
//        int p = 12 / size + 1;
//
//        // вывод блока из 0-го процесса
//        printf("from process %d: ", rank);
//        for (int i = 0; i < p; i++) {
//            printf("%d ", a[i]);
//        }
//        printf("\n");
//
//        //проход по всем процессам кроме 0-го
//        for (int i = 1; i < size; i++) {
//
//            // начало блока
//            int begin = i * (12 / p) + i;
//
//            //проверка последнего блока
//            if (12 - begin <= p) {
//               p = 12 - begin;
//            }
//
//            MPI_Send(a + begin, p < 0 ? 0 : p, MPI_INT, i, 1, MPI_COMM_WORLD);
//        }
//    }
//
//    else {
//
//
//        int count;
//        MPI_Probe(MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
//        MPI_Get_count(&status, MPI_INT, &count);
//        int* buffer = new int[count];
//
//        MPI_Recv(buffer, count, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
//
//        printf("process %d: ", rank);
//        for (int i = 0; i < count; i++) {
//            printf("%d ", buffer[i]);
//        }
//        printf("\n");
//    }
//    MPI_Finalize();
//}


/*5. Пусть векторы х, у заданы на нулевом процессе. Написать программу, в которой векторы
равными блоками с нулевого процесса пересылаются остальным процессам. Пересылка
данных осуществляется функцией MPI_Send. Все процессы по формуле вычисляют свои
элементы искомых массивов. Каждый процесс отправляет на нулевой процесс
подсчитанные элементы массивов. В программе реализовать следующие операции
вычисления векторов:
a) zi=αxi+βyi, где α,β, - заданные числа;
b) yi=αxi+βyi, где α,β, - заданные числа;
c) zi=xi*yi;
d) Обмен элементов двух векторов yi ↔xi.
*/



//#include<mpi.h>
//#include<stdio.h>
//#include<iostream>
//
//
//using namespace std;
//
//
//int main(int argc, char** argv)
//{
//	int rank, size;
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	
//	int a = 1;
//	int b = 2;
//
//	int n = 11;
//
//	if (rank == 0) {
//
//		int x[11] = { 0,1,2,3,4,5,6,7,8,9,10 };
//		int y[11] = { 4,5,6,7,8,9,0,1,2,3,5 };
//
//
//		int p = ceil((double)n / (size - 1));
//
//
//		for (int i = 1; i < size; i++) {
//
//
//			int begin = (i - 1) * p;
//
//
//			if (n - begin <= p) {
//				p = n - begin;
//			}
//
//
//			MPI_Send(x + begin, p < 0 ? 0 : p, MPI_INT, i, 11, MPI_COMM_WORLD);
//			MPI_Send(y + begin, p < 0 ? 0 : p, MPI_INT, i, 22, MPI_COMM_WORLD);
//		}
//
//
//		for (int i = 1; i < size; i++) {
//			MPI_Status status_z, status_y2, status_z2, status_xt, status_yt;
//			int elements_z, elements_y2, elements_z2, elements_xt, elements_yt = 0;
//			int* buffer_z, * buffer_z2, *buffer_y2, * buffer_xt, * buffer_yt;
//
//
//			MPI_Probe(i, 33, MPI_COMM_WORLD, &status_z);
//			MPI_Get_count(&status_z, MPI_INT, &elements_z);
//			buffer_z = new int[elements_z];
//			MPI_Recv(buffer_z, elements_z, MPI_INT, i, 33, MPI_COMM_WORLD, &status_z);
//			printf("process %d, part of vector z = ax + by from process %d: \n", rank, i);
//
//			
//			for (int i = 0; i < elements_z; i++) {
//				printf("%d ", buffer_z[i]);
//			}
//			printf("\n\n");
//
//
//			MPI_Probe(i, 37, MPI_COMM_WORLD, &status_y2);
//			MPI_Get_count(&status_y2, MPI_INT, &elements_y2);
//			buffer_y2 = new int[elements_y2];
//			MPI_Recv(buffer_y2, elements_y2, MPI_INT, i, 37, MPI_COMM_WORLD, &status_y2);
//
//			printf("process %d, part of vector y = ax * by  from process %d: \n", rank, i);
//
//			for (int i = 0; i < elements_y2; i++) {
//				printf("%d ", buffer_y2[i]);
//			}
//			printf("\n\n");
//
//
//			MPI_Probe(i, 34, MPI_COMM_WORLD, &status_z2);
//			MPI_Get_count(&status_z, MPI_INT, &elements_z2);
//			buffer_z2 = new int[elements_z2];
//			MPI_Recv(buffer_z2, elements_z2, MPI_INT, i, 34, MPI_COMM_WORLD, &status_z2);
//
//			printf("process %d, part of vector z = ax * by from process %d: \n", rank, i);
//
//			for (int i = 0; i < elements_z2; i++) {
//				printf("%d ", buffer_z2[i]);
//			}
//			printf("\n\n");
//
//			MPI_Probe(i, 35, MPI_COMM_WORLD, &status_xt);
//			MPI_Get_count(&status_xt, MPI_INT, &elements_xt);
//			buffer_xt = new int[elements_xt];
//			MPI_Recv(buffer_xt, elements_xt, MPI_INT, i, 35, MPI_COMM_WORLD, &status_xt);
//
//			printf("process %d, part of transition from y to x from process %d: \n", rank, i);
//
//			for (int i = 0; i < elements_z2; i++) {
//				printf("%d ", buffer_xt[i]);
//			}
//			printf("\n\n");
//
//
//			MPI_Probe(i, 36, MPI_COMM_WORLD, &status_yt);
//			MPI_Get_count(&status_yt, MPI_INT, &elements_yt);
//			buffer_yt = new int[elements_yt];
//			MPI_Recv(buffer_yt, elements_yt, MPI_INT, i, 36, MPI_COMM_WORLD, &status_yt);
//
//			printf("process %d, part of transition from x to y from process %d: \n", rank, i);
//
//			for (int i = 0; i < elements_z2; i++) {
//				printf("%d ", buffer_yt[i]);
//			}
//			printf("\n\n");
//		}
//	
//	}
//
//	else {
//		int elements_x = 0;
//		int elements_y = 0;
//		int* buffer_x;
//		int* buffer_y;
//
//		MPI_Status status_x;
//		MPI_Status status_y;
//
//		
//		MPI_Probe(MPI_ANY_SOURCE, 11, MPI_COMM_WORLD, &status_x);
//		MPI_Get_count(&status_x, MPI_INT, &elements_x);
//		buffer_x = new int[elements_x];
//		MPI_Recv(buffer_x, elements_x, MPI_INT, MPI_ANY_SOURCE, 11, MPI_COMM_WORLD, &status_x);
//
//		
//		MPI_Probe(MPI_ANY_SOURCE, 22, MPI_COMM_WORLD, &status_y);
//		MPI_Get_count(&status_y, MPI_INT, &elements_y);
//		buffer_y = new int[elements_y];
//		MPI_Recv(buffer_y, elements_y, MPI_INT, MPI_ANY_SOURCE, 22, MPI_COMM_WORLD, &status_y);
//
//		printf("\n\n");
//
//		printf("process %d: \n", rank);
//
//		
//
//		for (int i = 0; i < elements_x; i++) {
//			printf(" x : %d ", buffer_x[i]);
//		}
//		printf("\n");
//
//		
//		for (int i = 0; i < elements_x; i++) {
//			printf(" y : %d ", buffer_y[i]);
//		}
//		printf("\n");
//
//		int* z = new int[elements_x];
//		for (int i = 0; i < elements_x; i++) {
//			z[i] = a * buffer_x[i] + b * buffer_y[i];
//			//printf(" z = a* xi * + b* yi : %d ", z[i]);
//		}
//		printf("\n\n");
//
//
//		int* z2 = new int[elements_x];
//		for (int i = 0; i < elements_x; i++) {
//			z2[i] = buffer_x[i] * buffer_y[i];
//			printf(" z = xi * yi : %d ", z[i]);
//		}
//		printf("\n\n");
//
//		for (int i = 0; i < elements_y; i++) {
//			buffer_y[i] = a * buffer_x[i] + b * buffer_y[i];
//		}
//
//		printf("\n\n");
//
//		MPI_Send(z, elements_x, MPI_INT, 0, 33, MPI_COMM_WORLD);
//		MPI_Send(buffer_y, elements_y, MPI_INT, 0, 37, MPI_COMM_WORLD);
//		MPI_Send(z2, elements_x, MPI_INT, 0, 34, MPI_COMM_WORLD);
//		
//
//
//		int* t = new int[elements_x];
//		for (int i = 0; i < elements_x; i++) {
//			t[i] = buffer_x[i];
//			buffer_x[i] = buffer_y[i];
//			buffer_y[i] = t[i];
//
//		}
//
//		MPI_Send(buffer_x, elements_x, MPI_INT, 0, 35, MPI_COMM_WORLD);
//		MPI_Send(buffer_y, elements_y, MPI_INT, 0, 36, MPI_COMM_WORLD);
//	
//}
//	MPI_Finalize();
//}




/* 6. Пусть матрицы вещественных чисел A, B заданы на нулевом процессе. Написать
программу, в которой матрицы равными кусками с нулевого процесса пересылаются
остальным процессам. Пересылка данных осуществляется функцией MPI_Send. Все
процессы по формуле вычисляют свои элементы искомых матриц. Каждый процесс
отправляет на нулевой процесс подсчитанные элементы матриц. В программе реализовать
следующие операции вычисления матриц:
*/


//#include<mpi.h>
//#include<stdio.h>
//#include<iostream>
//
//using namespace std;
//
//
//int main(int argc, char** argv)
//{
//	int rank, size;
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	const int N = 5;
//
//	int sw = sqrt(size - 1);
//	int block = N / sw;
//
//	if (rank == 0) {
//
//		double blocks_a;
//		double a[N][N];
//		double b[N][N];
//
//
//		int p = ceil((double) (N + N) / (size - 1));
//		
//		
//		for (int i = 1; i < size; i++) {
//
//
//			int begin = (i - 1) * p;
//
//
//			if (N - begin <= p) {
//				p = N - begin;
//			}
//
//			
//
//
//			MPI_Send(a + begin, p < 0 ? 0 : p, MPI_INT, i, 11, MPI_COMM_WORLD);
//			MPI_Send(b + begin, p < 0 ? 0 : p, MPI_INT, i, 22, MPI_COMM_WORLD);
//		}
//
//
//
//			for (int i = 1; i < size; i++) {
//
//
//				MPI_Status status_a;
//				int elements_a = 0;
//				int* buffer_a;
//				int elements_a;
//
//
//				MPI_Probe(i, 33, MPI_COMM_WORLD, &status_a);
//				MPI_Get_count(&status_a, MPI_INT, &elements_a);
//				buffer_a = new int[elements_a];
//				MPI_Recv(buffer_a, elements_a, MPI_INT, i, 33, MPI_COMM_WORLD, &status_a);
//				
//
//
//				for (int i = 0; i < elements_a; i++) {
//					printf("%d ", buffer_a[i]);
//			
//				}
//				printf("\n\n");
//
//				
//
//				for (int i = 0; i < N; i++) {
//					for (int j = 0; j < N; j++)
//					{
//						a1[i]
//					}
//				}
//			}
//		}
//
//			else {
//
//				int elements_a = 0;
//				int elements_b = 0;
//				int* buffer_a;
//				int* buffer_b;
//				MPI_Status status_a;
//				MPI_Status status_b;
//
//				MPI_Probe(MPI_ANY_SOURCE, 11, MPI_COMM_WORLD, &status_a);
//				MPI_Get_count(&status_a, MPI_INT, &elements_a);
//				buffer_a = new int[elements_a];
//				MPI_Recv(buffer_a, elements_a, MPI_INT, MPI_ANY_SOURCE, 11, MPI_COMM_WORLD, &status_a);
//
//				MPI_Probe(MPI_ANY_SOURCE, 22, MPI_COMM_WORLD, &status_b);
//				MPI_Get_count(&status_b, MPI_INT, &elements_b);
//				buffer_b = new int[elements_b];
//				MPI_Recv(buffer_b, elements_b, MPI_INT, MPI_ANY_SOURCE, 22, MPI_COMM_WORLD, &status_b);
//
//				printf("\n\n");
//
//				printf("process %d: \n", rank);
//
//
//				int* z = new int[elements_a][elements_b];
//					for (int i = 0; i < ele; i++) {
//						z[i] = a * buffer_x[i] + b * buffer_y[i];
//						printf(" z = a* xi * + b* yi : %d ", z[i]);
//				}
//				printf("\n\n");
//				MPI_Send(z, elements_x, MPI_INT, 0, 33, MPI_COMM_WORLD);
//
//			}
//			MPI_Finalize();
//		}
//
//
//
//	

/*
*/






/*8. В массиве вещественных чисел вычислить минимальное значение и глобальный индекс
минимального элемента.Использовать функции MPI_Scatter и MPI_Reduce с операцией
MPI_MINLOC.*/


//#include <iostream>
//#include <cmath>
//#include "mpi.h"
//#include <stdio.h>
//#include <cstdlib>
//
//using namespace std;
//
//
//
//int main(int argc, char** argv) {
//    MPI_Init(&argc, &argv);
//
//    int rank, size;
//    MPI_Status status;
//
//    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//    MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//    const int p = size;
//    const int N = 150;
//    const int count = (int) (N/p);
//    int globalData[N];
//    int* localData = new int[count];
//
//    struct {
//        float value;
//        int index;
//    }
//
//    local_in, local_out;
//
//    if (rank == 0) {
//        for (int i = 0; i < N; i++) {
//            globalData[i] = (int)(rand() % 100);
//            cout << globalData[i] << " ";
//        }
//        printf("\n process - %d defined global data \n", rank);
//        printf("count of processes: %d, local_data count of massive = %d\n", size, count);
//    }
//
//    MPI_Scatter(globalData, N / size, MPI_INT, &localData, N / size, MPI_INT, 0, MPI_COMM_WORLD);
//
//    local_in.value = localData[0];
//    local_in.index = 0;
//    for (int i = 1; i < count; i++) {
//        if (local_in.value > localData[i]) {
//            local_in.value = localData[i];
//            local_in.index = i;
//        }
//    }
//    local_in.index = rank * count + local_in.index;
//    MPI_Reduce(&local_in, &local_out, 1, MPI_FLOAT_INT, MPI_MINLOC, 0, MPI_COMM_WORLD);
//
//
//    if (rank == 0) {
//        float min_value = local_out.value;
//        int min_index = local_out.index % N;
//        cout << "\n\n minimal value = " << min_value << " with index = " << min_index;
//    }
//
//    MPI_Finalize();
//    return 0;
//}


/*9. Написать программу вычисления нормы матрицы А по формуле 
𝑠 = max j=0..m (∑ 𝑎𝑏𝑠(𝑎𝑖,𝑗))𝑛 𝑖=0, 
где m- число столбцов, n - число строк. Для распределения
элементов матрицы А по процессам использовать функцию MPI_Scatter. Для получения
итогового значения использовать функцию MPI_Reduce с операцией MPI_MAX.
*/

	/*#include "mpi.h"
	using namespace std;

	int main(int argc, char** argv)
	{

		int rank, word_size;
		MPI_Init(&argc, &argv);
		MPI_Comm_size(MPI_COMM_WORLD, &word_size);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		int block = 3;
		int N = word_size * block;
		int M = N;
		int** a = new int[N][M];
		int** local = new int[block][M];



		if (rank == 0) {




			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < N; ++j) {
					a[i][j] = rand() % 100;
				}
			}
			
		}
		MPI_Scatter(&(a[0][0]), block * M, MPI_INT, &(local[0][0]), block * M, MPI_INT, 0, MPI_COMM_WORLD);
		if (rank == 0) {
			stringstream ss;
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < M; ++j) {
					cout << a[i][j] << " ";
				}
				cout << endl;
			}
			cout << ss.str();
		}
		int local_ans = accumulate(local[0], local[0] + M, (int)0);
		for (int i = 1; i < block; ++i) local_ans = max(local_ans, accumulate(local[i], local[i] + M, (int)0));
		int ans;

		MPI_Reduce(&local_ans, &ans, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
		if (rank == 0) cout << "ans = " << ans << endl;
	MPI_Finalize();
}
		*/


/* 10. Написать программу вычисления поэлементного умножения матриц Сi, j = Ai, jBi.j.
Использовать функции MPI_Scatter для распределения элементов матриц A и B, и
MPI_Gather для сбора вычисленных данных в матрицу C.
*/
//
//using namespace std;
//
//#include<mpi.h>
//#include<stdio.h>
//#include<iostream>
//#include <mpi.h>
//#include <vector>
//#include <ctime>
//
//
//
//
//int main(int argc, char** argv)
//{
//	int rank, size, source = 0;
//
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	#define N 10
//	#define BUF_SIZE 100
//
//	std::vector<std::vector<int>> A(N);
//	std::vector<std::vector<int>> B(N);
//	std::vector<int> sbuf, rbuf, s2buf, r2buf, g_rcvbuf;
//	
//
//
//	if (rank == 0) {
//
//
//		for (int i = 0; i < N; i++) {
//			for (int j = 0; j < N; j++) {
//				A.at(i).push_back(rand() % N);
//				B.at(i).push_back(rand() % N);
//			}
//		}
//
//		std::cout << "matrix A: " << std::endl;
//		for (int i = 0; i < N; i++) {
//			for (int j = 0; j < N; j++) {
//				std::cout << A.at(i).at(j) << " ";
//			}
//			std::cout << std::endl;
//		}
//
//		std::cout << "matrix B: " << std::endl;
//		for (int i = 0; i < N; i++) {
//			for (int j = 0; j < N; j++) {
//				std::cout << B.at(i).at(j) << " ";
//			}
//			std::cout << std::endl;
//		}
//
//		for (int i = 0; i < N; i++) {
//			for (int j = 0; j < N; j++) {
//				sbuf.push_back(A.at(i).at(j));
//			}
//		}
//
//		for (int i = 0; i < N; i++) {
//			for (int j = 0; j < N; j++) {
//				s2buf.push_back(B.at(i).at(j));
//			}
//		}
//		
//		int count = ceil((double) BUF_SIZE / (size - 1));
//	
//
//		MPI_Scatter(sbuf.data(), count , MPI_INT, rbuf.data(), count, MPI_FLOAT, source, MPI_COMM_WORLD);
//		MPI_Scatter(s2buf.data(), count, MPI_INT, r2buf.data(), count, MPI_FLOAT, source, MPI_COMM_WORLD);
//	}
//
//	else {
//
//
//		int r = 0;
//
//		for (int i = 0; i < BUF_SIZE; i++) {
//			r += rbuf.at(i) * r2buf.at(i);
//
//		}
//
//
//		MPI_Gather(&r, 1, MPI_FLOAT, g_rcvbuf.data(), 1, MPI_FLOAT, source, MPI_COMM_WORLD);
//	}
//
//		if (rank == 0) {
//			std::cout << "result for 0 process = " << " ";
//			for (auto i : g_rcvbuf)
//				std::cout << i << " ";
//			std::cout << std::endl;
//		}
//
//		MPI_Finalize();
//		return 0;
//	}
//
//
//






/*
11. Написать программу умножения матрицы на вектор z = Ax.
Распределить матрицу А равномерно вдоль строк, вектор х передать всем процессам.
После выполнения операции умножения матрицы на вектор на каждом процессе необходимо выполнить
сбор полученных локальных частей результирующего вектора на один из процессов.
Использовать функцию MPI_Bcast для рассылки вектора x, для распределения элементов матрицы использовать
функцию MPI_Scatter, для сбора локальных частей результирующего вектора в глобальный вектор
использовать функцию MPI_Gather.
*/

//
//#include <mpi.h>
//#include <vector>
//#include <ctime>
//#include <iostream>
//
//#define matrix_size 3
//#define vector_size 3
//#define n 10
//
//std::vector<std::vector<float>> a(matrix_size);
//std::vector<float> x, a_rcvbuf, g_rcvbuf, a_sendbuf;
//
//float result;
//
//void get_fill() {
//	srand(time(0));
//	for (int i = 0; i < matrix_size; i++) {
//		for (int j = 0; j < matrix_size; j++) {
//			a.at(i).push_back(rand() % n);
//		}
//	}
//
//	for (int i = 0; i < vector_size; i++)
//		x.at(i) = (rand() % n);
//}
//
//void print_vector() {
//	std::cout << "matrix a: " << std::endl;
//
//	for (int i = 0; i < matrix_size; i++) {
//		for (int j = 0; j < matrix_size; j++) {
//			std::cout << a.at(i).at(j) << " ";
//		}
//		std::cout << std::endl;
//	}
//
//	std::cout << std::endl << "vector x: " << std::endl;
//	for (auto x : x)
//		std::cout << x << " ";
//	std::cout << std::endl;
//}
//
//void multiplication(int process_id) {
//	for (int i = 0; i < vector_size; i++) {
//		result += a_rcvbuf.at(i) * x.at(i);
//		std::cout << a_rcvbuf.at(i) << " ";
//	}
//	std::cout << "multiplication result = " << result << " process_id = " << process_id << std::endl;
//}
//
//int main(int argc, char** argv) {
//
//	int process_id, size, root = 0;
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
//
//	x.resize(vector_size);
//	a_rcvbuf.resize(vector_size);
//	g_rcvbuf.resize(vector_size);
//
//	if (process_id == 0) {
//
//		get_fill();
//		print_vector();
//
//		for (int i = 0; i < matrix_size; i++) {
//			for (int j = 0; j < matrix_size; j++) {
//				a_sendbuf.push_back(a.at(i).at(j));
//			}
//		}
//		for (int i = 0; i < vector_size; i++) {
//			std::cout << a_sendbuf.at(i) << "\n ";
//		}
//		std::cout << std::endl << "\n " << std::endl;
//	}
//
//	MPI_Scatter(a_sendbuf.data(), vector_size, MPI_FLOAT, a_rcvbuf.data(), vector_size, MPI_FLOAT, root, MPI_COMM_WORLD);
//	MPI_Bcast(&x.front(), vector_size, MPI_FLOAT, root, MPI_COMM_WORLD);
//
//	multiplication(process_id);
//
//	MPI_Gather(&result, 1, MPI_FLOAT, g_rcvbuf.data(), 1, MPI_FLOAT, root, MPI_COMM_WORLD);
//
//	if (process_id == 0) {
//		std::cout << "result for 0 process = " << " ";
//		for (auto i : g_rcvbuf)
//			std::cout << i << " ";
//		std::cout << std::endl;
//	}
//
//	MPI_Finalize();
//	return 0;
//}



/*
12. Реализовать при помощи операций MPI_Send и MPI_Recv коллективный сбор
данных - операцию MPI_Gather. Обратите внимание, функция MPI_Gather
производит сборку блоков данных, посылаемых всеми процессами группы, в
один массив процесса с номером root. Длина блоков предполагается
одинаковой. Объединение происходит в порядке увеличения номеров
процессов-отправителей. То есть данные, посланные процессом i из своего
буфера sendbuf, помещаются в i-ю порцию буфера recvbuf процесса root. Длина
массива, в который собираются данные, должна быть достаточной для их
размещения.
*/

//#include <mpi.h>
//#include <iostream>
//
//#define N 10
//
//int main(int argc, char** argv) {
//
//	MPI_Init(&argc, &argv);
//
//	int x[10];
//	int rank, size;
//
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//
//	int count = 2;
//	int* subarr1 = new int[count];
//
//	if (rank == 0) {
//		printf("Send from 0 process: ");
//		for (int i = 0; i < N; i++) {
//			x[i] = rand() % 100;
//			printf(" %d ", x[i]);
//		}
//		printf("\n");
//	}
//
//	if (rank == 0) {
//		
//		/*MPI_Sendrecv(x, count, MPI_INT, 0, 12, subarr1, count, MPI_INT, 0, 12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);*/
//
//		for (int i = count; i <= N; i += count) {
//			MPI_Send(x + i - count, count, MPI_INT, i / count , 12, MPI_COMM_WORLD);
//		}
//
//	}
//	else {
//		MPI_Recv(subarr1, count, MPI_INT, 0, 12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//	}
//	int* newArr = new int[count];
//	
//	if (rank != 0) {
//
//		for (int i = 0; i < count; i++) {
//			printf(" %d ", subarr1[i]);
//		}
//
//		printf(" from process %d\n", rank);
//
//		MPI_Send(subarr1, count, MPI_INT, 0, 11, MPI_COMM_WORLD);
//	}
//
//	else {
//		printf("Recv: ");
//		for (int i = 1; i < size; ++i) {
//			MPI_Recv(newArr, count, MPI_INT, i, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//			for (int j = 0; j < count; ++j) {
//				printf(" %d ", newArr[j]);
//			}
//		}
//	}
//
//	MPI_Finalize();
//	return 0;
//}



/*
14. Предположим, что на каждом процессе есть свое число х. Необходимо найти
сумму всех элементов х и сумму разослать всем процессам. Можно
использовать связку двух функций: MPI_Reduce и MPI_Bcast, т.е. сначала
результат операции редукции разместить на одном процессе, а потом с
помощью функции MPI_Bcast разослать его всем остальным процессам. Можно
использовать функцию MPI_Allreduce, которая аналогична функции
MPI_Reduce, но сохраняет результат редукции в адресном пространстве всех
процессов. Написать программу для измерения времени, необходимого для
выполнения функции MPI_Allreduce на MPI_COMM_WORLD. Как изменяется
время работы функции MPI_Allreduce при изменении размера коммуникатора?
Насколько быстрее работает MPI_Allreduce чем связка двух функций
MPI_Reduce и MPI_Bcast?
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv)
{
	int x, sum = 0;
	double beginTimeStamp, endTimeStamp, funcExecutionDuration, global;
	int size, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	x = rand();

	beginTimeStamp = MPI_Wtime();

	MPI_Reduce(&x, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Bcast(&sum, 1, MPI_INT, 0, MPI_COMM_WORLD);

	endTimeStamp = MPI_Wtime();
	funcExecutionDuration = endTimeStamp - beginTimeStamp;
	MPI_Reduce(&funcExecutionDuration, &global, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("MPI_Reduce + MPI_Bcast time: %f\n", global);
	}

	sum = 0;

	beginTimeStamp = MPI_Wtime();

	MPI_Allreduce(&x, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

	endTimeStamp = MPI_Wtime();
	funcExecutionDuration = endTimeStamp - beginTimeStamp;
	MPI_Reduce(&funcExecutionDuration, &global, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0)
	{
		printf("MPI_Allreduce time: %f\n", global);
	}

	MPI_Finalize();
}

/*
15. На процессе с номером 0 объявить и заполнить значениями матрицу a[8][8]. 
Создать новый тип данных для рассылки нечетных строк  матрицы а в матрицу b[4][8],
и для рассылки   четных   строк   матрицы  в  матрицу   c[4][8],   
используя   функцию MPI_Type_vector.
*/


using namespace std;


int main(int argc, char** argv)
{
	int rank, size;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Datatype ntype;
	MPI_Datatype ctype;

	MPI_Type_contiguous(1, MPI_INT, &ntype);
	MPI_Type_commit(&ntype);

	int b[4][8];
	int c[4][8];

	if (rank == 0) {

		int a[8][8];

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				a[i][j] = rand() % 100;
			}
		}


		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (i % 2 == 0) {
					MPI_Send(&a[i][j], 1, ntype, 3, 11, MPI_COMM_WORLD);
				}
			}
		}
	}

	else if (rank == 3) {



	}
	

	}


}

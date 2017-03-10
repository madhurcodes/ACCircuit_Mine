#include<stdio.h>
#include<math.h>
#include "myheader.h"
extern graph *circuit;

int invert(float matrix[][2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size + 1])
{
    int hh = 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size;
    float a[hh][hh], k, d, cons[hh];
    int i, j;
//	printf("Enter the order of the Matrix : ");
    //scanf("%f", &k);
    k = hh;
//	printf("Enter the elements of %.0fX%.0f Matrix : \n", k, k);
    for (i = 0;i < k; i++)
    {
        for (j = 0;j < k; j++)
        {
            a[i][j] = matrix[i][j];
            //scanf("%f", &a[i][j]);
        }
    }
    d = determinant(a, k);

    if (d == 0)
        printf("\nInverse of Entered Matrix is not possible\n");
    else
        cofactor(a, k);
}
/*For calculating Determinant of the Matrix */
float determinant(float a[][2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size], float k)
{
    int hh = 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size;
    float s = 1, det = 0, b[hh][hh];
    int i, j, m, n, c;
    if (k == 1)
    {
        return (a[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0;i < k; i++)
            {
                for (j = 0 ;j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }

    return (det);
}

void cofactor(float num[][2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size], float f)
{
    int hh = 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size ;
    float b[hh][hh], fac[hh][hh];
    int p, q, m, n, i, j;
    printf("try1\n\n\nThe inverse of matrix is : \n");

    for (i = 0;i < f; i++)
    {
        for (j = 0;j < f; j++)
        {
            printf("\t%f", num[i][j]);
        }
        printf("\n");
    }
    for (q = 0;q < f; q++)
    {
        for (p = 0;p < f; p++)
        {
            m = 0;
            n = 0;
            for (i = 0;i < f; i++)
            {
                for (j = 0;j < f; j++)
                {
                    if (i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = powf(-1, q + p) * determinant(b, f - 1);
        }
    }
    transpose(num, fac, f);
}
/*Finding transpose of matrix*/
void transpose(float num[][2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size], float fac[][2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size], float r)
{
    int i, j;
    int hh = 2 * circuit->myAdjList->size + 2 * circuit->myEdgeList->size;
    float b[hh][hh], inverse[hh][hh], d;

    for (i = 0;i < r; i++)
    {
        for (j = 0;j < r; j++)
        {
            b[i][j] = fac[j][i];
        }
    }


    printf("try2\n\n\nThe inverse of matrix is : \n");

    for (i = 0;i < r; i++)
    {
        for (j = 0;j < r; j++)
        {
            printf("\t%f", inverse[i][j]);
        }
        printf("\n");
    }


    d = determinant(num, r);
    for (i = 0;i < r; i++)
    {
        for (j = 0;j < r; j++)
        {
            inverse[i][j] = b[i][j] / d;
        }
    }
    printf("\n\n\nThe inverse of matrix is : \n");

    for (i = 0;i < r; i++)
    {
        for (j = 0;j < r; j++)
        {
            printf("\t%f", inverse[i][j]);
        }
        printf("\n");
    }
}



//
//int invert()
//{   int hh = 50;
//    int i,j,k,n;
//    float A[hh][hh],c,x[100];
//    printf("\nEnter the size of matrix: ");
//    scanf("%d",&n);
//    printf("\nEnter the elements of augmented matrix row-wise:\n");
//    for(i=1; i<=n; i++)
//    {
//        for(j=1; j<=(n+1); j++)
//        {
//            printf(" A[%d][%d]:", i,j);
//            scanf("%f",&A[i][j]);
//        }
//    }
//    /* Now finding the elements of diagonal matrix */
//    for(j=1; j<=n; j++)
//    {
//        for(i=1; i<=n; i++)
//        {
//            if(i!=j)
//            {
//                c=A[i][j]/A[j][j];
//                for(k=1; k<=n+1; k++)
//                {
//                    A[i][k]=A[i][k]-c*A[j][k];
//                }
//            }
//        }
//    }
//    printf("\nThe solution is:\n");
//    for(i=1; i<=n; i++)
//    {
//        x[i]=A[i][n+1]/A[i][i];
//        printf("\n x%d=%f\n",i,x[i]);
//    }
//
//    return(0);
//}

//#include<stdio.h>
//#include<math.h>
//float determinant(float [][25], float);
//void cofactor(float [][25], float);
//void transpose(float [][25], float [][25], float);
//int invert()
//{
//    float a[25][25], k, d;
//    int i, j;
//    printf("Enter the order of the Matrix : ");
//    scanf("%f", &k);
//    printf("Enter the elements of %.0fX%.0f Matrix : \n", k, k);
//    for (i = 0;i < k; i++)
//    {
//        for (j = 0;j < k; j++)
//        {
//            scanf("%f", &a[i][j]);
//        }
//    }
//    d = determinant(a, k);
//    if (d == 0)
//        printf("\nInverse of Entered Matrix is not possible\n");
//    else
//        cofactor(a, k);
//}
//
//For calculating Determinant of the Matrix
//float determinant(float a[25][25], float k)
//{
//    float s = 1, det = 0, b[25][25];
//    int i, j, m, n, c;
//    if (k == 1)
//    {
//        return (a[0][0]);
//    }
//    else
//    {
//        det = 0;
//        for (c = 0; c < k; c++)
//        {
//            m = 0;
//            n = 0;
//            for (i = 0;i < k; i++)
//            {
//                for (j = 0 ;j < k; j++)
//                {
//                    b[i][j] = 0;
//                    if (i != 0 && j != c)
//                    {
//                        b[m][n] = a[i][j];
//                        if (n < (k - 2))
//                            n++;
//                        else
//                        {
//                            n = 0;
//                            m++;
//                        }
//                    }
//                }
//            }
//            det = det + s * (a[0][c] * determinant(b, k - 1));
//            s = -1 * s;
//        }
//    }
//
//    return (det);
//}
//
//void cofactor(float num[25][25], float f)
//{
//    float b[25][25], fac[25][25];
//    int p, q, m, n, i, j;
//    for (q = 0;q < f; q++)
//    {
//        for (p = 0;p < f; p++)
//        {
//            m = 0;
//            n = 0;
//            for (i = 0;i < f; i++)
//            {
//                for (j = 0;j < f; j++)
//                {
//                    if (i != q && j != p)
//                    {
//                        b[m][n] = num[i][j];
//                        if (n < (f - 2))
//                            n++;
//                        else
//                        {
//                            n = 0;
//                            m++;
//                        }
//                    }
//                }
//            }
//            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
//        }
//    }
//    transpose(num, fac, f);
//}
//Finding transpose of matrix
//void transpose(float num[25][25], float fac[25][25], float r)
//{
//    int i, j;
//    float b[25][25], inverse[25][25], d;
//
//    for (i = 0;i < r; i++)
//    {
//        for (j = 0;j < r; j++)
//        {
//            b[i][j] = fac[j][i];
//        }
//    }
//    d = determinant(num, r);
//    for (i = 0;i < r; i++)
//    {
//        for (j = 0;j < r; j++)
//        {
//            inverse[i][j] = b[i][j] / d;
//        }
//    }
//    printf("\n\n\nThe inverse of matrix is : \n");
//
//    for (i = 0;i < r; i++)
//    {
//        for (j = 0;j < r; j++)
//        {
//            printf("\t%f", inverse[i][j]);
//        }
//        printf("\n");
//    }
//}
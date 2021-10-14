#include "../include/structures.h"

double random_value(double max){   
  srand((unsigned int)clock());
  return (rand() > RAND_MAX / 2 ? 1 : 1) * (max / RAND_MAX) * rand(); 
}

void init_tab(double *tab,double max,int row, int column){
  int i; time_t t;
  srand((unsigned) time(&t));
  for(i = 0; i< (row*column) ; i++){
    tab[i]=roundf(random_value(max)*100)/100;
  }
}

mat_t initMatrix(int _row, int _column){
  mat_t mat; int i;
  mat.row = _row ; mat.column = _column;
  mat.m = malloc(_row * sizeof(double));
  for (i = 0; i < _row; i++)
    mat.m[i] = malloc(_column * sizeof(double));
  return mat;
}

mat_t create_Matrix(double *tab, int row, int column){
  mat_t mat;
  int i, j, index;
  mat = initMatrix(row, column);
  if( mat.m == NULL ){
     fprintf(stderr,"Allocation impossible");
     exit(EXIT_FAILURE);
  }
  for (i = 0; i < mat.row; i++){
    for (j = 0; j < mat.column; j++){
      index = (i*mat.column)+j;
      mat.m[i][j] = tab[index] ;
    }
  }
  return mat;
}

mat_t create_MatrixV0(int row,int column){
  mat_t mat;
  int i, j, k, l, z, zi;
  mat = initMatrix(row,column);
  if( mat.m == NULL ){
     fprintf(stderr,"Allocation impossible");
     exit(EXIT_FAILURE);
  }
  for (i = 0, k = mat.row; i < mat.row; i++, k--)
  {
    l = k;
    mat.m[i][i] = (double)l;
    l >>= 1;
    for (j = i + 1, z = 1, zi = 0; j < mat.column; j++)
    {
      if (z == zi)
      {
        mat.m[i][j] = (double)l;
        mat.m[j][i] = (double)l;
        l >>= 1;
        z <<= 1;
        zi = 0;
      }
      else
      {
        mat.m[i][j] = 0.0;
        mat.m[j][i] = 0.0;
        zi++;
      }
    }
  }
  return mat;
}

mat_t multiplication_two_Matrix(FILE *f, mat_t matA,mat_t matB){
  mat_t mul = initMatrix(matA.row,matB.column);
  int i ,j ,k;
  if ((matA.column == matB.row) && (matA.row == matB.column)){
    for(i = 0; i <matA.row ; i++){
      for(j = 0; j < matB.column; j++){        
          for(k = 0; k <matB.row; k++){
            mul.m[i][j] += (matA.m[i][k]*matB.m[k][j]);
          }
      }
    }
  fprintf(f,"\nLa multiplication de deux matrices : \n");
  }else{
    fprintf(f,"\nVous ne respectez pas les dimension des matrices pour faire la multiplication\n");
  }
  return mul;
}

void displayMatrix(mat_t mat){
  int i, j;
  printf("\nMatrix :\n \nmat_=>{\n");
  for (i = 0; i < mat.row; i++){
    for (j = 0; j < mat.column; j++)
      printf("%.2lf \t", mat.m[i][j]);
    printf("\n");
  }
  printf("}\n");
}

void displayMatrix_V2(mat_t mat){
  int i, j;
  printf("\nMatrix :\n\n");
  for (i = 0; i < mat.row; ++i){
    for (j = 0; j < mat.column; ++j)
      printf("mat[%d][%d] = %0.2lf \n", i, j, mat.m[i][j]);
  } 
}

double memoryMatrix(mat_t mat){
    return 2*sizeof(int) + sizeof(mat.m) * mat.row * mat.column;
}

void freeMat(mat_t mat){
  int i;
  for (i = 0; i < mat.row; i++)
    free(mat.m[i]);
  free(mat.m);
}

vec_t initVector(int size){
  vec_t vect;
  vect.size = size;
  vect.vec = malloc(size * sizeof(*vect.vec));
  return vect;
}

vec_t matrix_to_vector(mat_t mat, int size){
  int i, j, index;
  vec_t vect = initVector(size);
  for (i = 0; i < mat.row; i++){
    for (j = 0; j < mat.column; j++){
      index = (i * mat.column) + j;
      vect.vec[index].j = j;
      vect.vec[index].i = i;
      vect.vec[index].val = mat.m[i][j];
    }
  }
  return vect;
}
mat_t vector_to_matrix(vec_t vect, int size){
  int i, j, row, column, index;
  mat_t mat ;
  for (i = 0; i < size; i++){
      row = vect.vec[i].i+1;
      column = vect.vec[i].j+1;
  }
  mat = initMatrix(row, column);
  for (i = 0; i < mat.row; i++){
    for (j = 0; j < mat.column; j++){
      index = (i * mat.column) + j;
      mat.m[i][j] = vect.vec[index].val;
    }
  }
  return mat;
}

double multiplication_two_vectors(FILE *f,vec_t vectA, vec_t vectB){
  double vectMul;int i;
  if(vectA.size == vectB.size){
    for(i = 0; i < vectA.size; i++){
      vectMul += vectA.vec[i].val * vectB.vec[i].val; 
    }
  fprintf(f,"\nLe produit de deux vecteurs : \n");
  }
  return vectMul;
}

void displayVectors(vec_t vect){
  int i;
  printf("\nMatrix to Vector :\n\n");
  for (i = 0; i < vect.size; ++i)
    printf("(%d, %d) => vect[%d] = %g\n", vect.vec[i].i,  vect.vec[i].j, i, vect.vec[i].val);
}

double memoryVector(vec_t vect){
    return (sizeof(vect.vec[0].i) + sizeof(vect.vec[0].j) + sizeof(vect.vec[0].val)) * vect.size + sizeof(vect.size);
}

void freeVect(vec_t vect){
    free(vect.vec);
}

mco_t initCompact_matrix(int row,int column){
  int i;
  mco_t mco;
  mco.size = row;
  mco.vect = malloc(mco.size * sizeof (*mco.vect));
  mco.vect->size = column;
  for(i=0 ;i<mco.size; i++)
    mco.vect[i].vec = malloc(mco.vect->size * sizeof(*mco.vect->vec));
  return mco;
}

mco_t matrix_to_compact_matrix(mat_t mat){
  int i, j;
  mco_t mco = initCompact_matrix(mat.row, mat.column);
  for (i = 0; i < mat.row; i++){
    for (j = 0; j < mat.column; j++){
      mco.vect[i].vec[j].j= j;
      mco.vect[i].vec[j].val= mat.m[i][j];
    }
  }
  return mco;
}

mco_t multiplication_two_matrix_mco(FILE *f, mco_t mcoA,mco_t mcoB){
  mco_t mul = initCompact_matrix(mcoA.size,mcoB.vect->size);
  int i ,j ,k;
  if ((mcoA.vect->size == mcoB.size) && (mcoA.size == mcoB.vect->size)){
    for(i = 0; i <mcoA.size ; i++){
      for(j = 0; j < mcoB.vect->size; j++){        
          for(k = 0; k <mcoB.size; k++){
            mul.vect[i].vec[j].val += (mcoA.vect[i].vec[k].val*mcoB.vect[k].vec[j].val);
          }
      }
    }
  fprintf(f,"\nLa multiplication de deux matrices compacte : \n");
  }else{
    fprintf(f,"\nVous ne respectez pas les dimension des matrices pour faire la multiplication\n");
  }
  return mul;
}

mco_t multiplication_matrix_compact_matrix(FILE *f,mco_t mco,mat_t mat){
  mco_t mul = initCompact_matrix(mco.size,mco.vect->size);
  int i ,j ,k;
  if ((mco.vect->size == mat.row) && (mco.size == mat.column)){
    for(i = 0; i <mco.size; i++){
      for(j = 0; j < mat.column; j++){        
          for(k = 0; k <mco.size; k++){
            mul.vect[i].vec[j].val += (mco.vect[i].vec[k].val* mat.m[k][j]);
          }
      }
    }
  fprintf(f,"\nLa multiplication de matrices compacte * matrices normale : \n");
  }else{
    fprintf(f,"\nVous ne respectez pas les dimension des matrices pour faire la multiplication\n");
  }
  return mul;
}

void displayCompact_matrix(mco_t mco){
  int i, j;
  printf("\nMatrix :\n\n");
  for (i = 0; i < mco.size; ++i){
    for (j = 0; j < mco.vect->size; ++j)
      printf("Mco[%d][%d] = %0.2f\n",i,mco.vect[i].vec[j].j, mco.vect[i].vec[j].val);
  } 
}

double memoryCompactMatrix( mco_t mco){
    return ((sizeof(mco.vect->vec[0].j) + sizeof(mco.vect->vec[0].val)) * mco.vect->size + sizeof(mco.vect->size)) * mco.size + sizeof(mco.size);
}

void freeMco(mco_t mco){
  int i;
  for(i=0 ;i<mco.size; i++)
    free(mco.vect[i].vec);
  free(mco.vect);
}

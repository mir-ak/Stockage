#include "../include/structures.h"

void outputMat(FILE *f,mat_t mat){
    int i, j;
    if(f==NULL){
        printf("Erreur lors de l'ouverture d'un fichier");
        exit(1);
    }
  
    fprintf(f,"mat_=>{\n");
    for (i = 0; i < mat.row; i++){
        for (j = 0; j < mat.column; j++)
            fprintf(f,"%.2lf \t", mat.m[i][j]);
        fprintf(f,"\n");
    }
    fprintf(f,"}\n");
}

void outputVect(FILE *f,vec_t vect,double val){
    int i;
    if (val !=1){
        fprintf(f,"VectA X VectB = %.2lf\n", val);
    }else{
        fprintf(f,"Vecteur : \n");
        for (i = 0; i < vect.size; ++i)
            fprintf(f,"(%d, %d) => vect[%d] = %.2lf\n", vect.vec[i].i,  vect.vec[i].j, i, vect.vec[i].val);
    }
  
}

void outputMco(FILE *f,mco_t mco){
    int i, j;
    fprintf(f,"\nMatrix :\n\n");
    for (i = 0; i < mco.size; ++i){
        for (j = 0; j < mco.vect->size; ++j)
            fprintf(f,"mco_column[%d][%d] = %.2lf\n",i,mco.vect[i].vec[j].j,mco.vect[i].vec[j].val);
    }
}

void outputTime(FILE *f, mat_t MatA, vec_t VectA, mco_t McoA,double *tab, int row, int column){
    int i,size;
    clock_t start,end, delta1, delta2 , delta3;
    for(i = 1; i< 1000; i = i + 100){
    
    start = clock();
    /*MatA = create_MatrixV0(tab,column,row);*/
    MatA = create_Matrix(tab,row,column);
    end = clock();
    delta1 = end - start;
    
    size = MatA.row * MatA.column;

    start = clock();
    VectA = matrix_to_vector(MatA,size);
    end = clock();
    delta2 = end - start;
   
    start = clock();
    McoA = matrix_to_compact_matrix(MatA);
    end = clock();
    delta3 = end - start;
    fprintf(f,"%d %f %f %f \n", i, to_milliS(delta1), to_milliS(delta2),to_milliS(delta3));
  }
}

void fileclose(FILE *a, FILE *b, FILE *c, FILE *d){
  fclose(a);
  fclose(b);
  fclose(c);
  fclose(d);
}

void plot_in_png(){
    FILE *pipe_gp = popen("gnuplot -p", "w");
    fputs("set terminal png\n", pipe_gp);
    fprintf(pipe_gp,"set xlabel \n");
    fprintf(pipe_gp,"set output 'output/curves_times.png'\n"
                    "set ylabel 'time(M/S)'\n"
                    "set grid\n"
                    "set style data lines\n"
                    "plot './output/Courbe.data' u 1:2 w l title 'Matrix'"
                    ",'./output/Courbe.data' u 1:3 w l title 'Vector'"
                    ",'./output/Courbe.data' u 1:4 w l title 'Compact Matrix' \n");
    pclose(pipe_gp);
}


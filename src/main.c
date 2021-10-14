
#include "../include/structures.h"

int main(int argc, char **argv){
  int size,row,column;
  double VectMul=1;
  double memoryMat,memoryVect,memoryMco;
  double *tab;
  mat_t MatA, MatB, MatMul;
  vec_t VectA, VectB;
  mco_t McoA, McoB, McoMul,Mat_x_Mco;
  FILE *Fmat = fopen("./output/Matrice.txt", "w");
  FILE *Fvec = fopen("./output/Vecteur.txt", "w");
  FILE *Fmco = fopen("./output/Matrice_Compacte.txt", "w");
  FILE *data = fopen("./output/Courbe.data", "w");
 
  printf("veuillez saisir le nombre de ligne de la matrice : ");
  scanf("%d", &row);
  printf("veuillez saisir le nombre de colonnes de la matrice : ");
  scanf("%d", &column);
  tab = malloc(row*column*sizeof(*tab));
 /************************************* Matrice *************************************/
  // genere les nombre aleatoire
  init_tab(tab,10, row, column);
  // cree la première matrice
  MatA = create_Matrix(tab,row,column);
  // cree matrice version prof
  //MatA = create_MatrixV0(row,column);
  // ecrire la matrice (deja creer) dans un fichier
  outputMat(Fmat,MatA);
  // regenere les nombre aleatoire
  init_tab(tab,10,row,column);
  // cree la deuxiéme matrice
  MatB = create_Matrix(tab,column,row);
  //cree matrice version prof
  //MatB = create_MatrixV0(row,column);
  // ecrire la deuxiéme matrice (deja creer) dans un fichier
  outputMat(Fmat,MatB);
  // cree la matrice produit de MatA et MatB
  MatMul = multiplication_two_Matrix(Fmat,MatA,MatB);
  // ecrire la matrice (deja creer) dans un fichier
  outputMat(Fmat,MatMul);
  // calculer la memoire de la matrice compactede la matrice
  memoryMat = memoryMatrix(MatA);
  // calculer la taille pour cree le vecteur 
  size = MatA.row * MatA.column;

/************************************* vecteur *************************************/  
  // cree le premier vecteur
  VectA = matrix_to_vector(MatA,size);
  // ecrire le vecteur (deja creer) dans un fichier
  outputVect(Fvec,VectA,VectMul);
  // cree le deuxiéme vecteur
  VectB = matrix_to_vector(MatB,size);
  // ecrire le vecteur (deja creer) dans un fichier
  outputVect(Fvec,VectB,VectMul);
  // calculer le produit de VectA et VectB
  VectMul = multiplication_two_vectors(Fvec,VectA, VectB);
  // ecrire le resultat de produit de deux vecteur dans un fichier
  outputVect(Fvec,VectA,VectMul);
  // calculer la memoire de la matrice compactede vecteur
  memoryVect = memoryVector(VectA);
  /********************************* Matrice_compacte ********************************/
  // cree la première matrice compacte
  McoA = matrix_to_compact_matrix(MatA);
  // ecrire la matrice compacte (deja creer) dans un fichier (Matrice_Compacte.txt)
  outputMco(Fmco,McoA);
  // vree la deuxiéme matrice compacte
  McoB = matrix_to_compact_matrix(MatB);
  // ecrire la deuxiéme matrice compacte (deja creer) dans un fichier (Matrice_Compacte.txt) 
  outputMco(Fmco,McoB);
  // cree la matrice compacte produit de McoA et McoB
  McoMul  = multiplication_two_matrix_mco(Fmco,McoA,McoB);
  // ecrire la matrice produit dans un fichier (Matrice_Compacte.txt)
  outputMco(Fmco,McoMul); 
  // cree la matrice compacte produit de matrice compacte et matrice (Mco * Mat)
  Mat_x_Mco = multiplication_matrix_compact_matrix(Fmco,McoA,MatA);
  // ecrire la matrice produit dans un fichier (Matrice_Compacte.txt)
  outputMco(Fmco,Mat_x_Mco);
  // calculer la memoire de la matrice compacte
  memoryMco = memoryCompactMatrix(McoA);
  
   // calculer l'evolution de temps des trois modèles et enregistrer les donnees dans un fichier .data
  outputTime(data,MatA,VectA,McoA,tab,row,column);
  // ferme les fichier 
  fileclose(Fmat, Fvec, Fmco, data);
  // dessiner un graphique a courbe de l'evolution de temps des trois modèles dans une image .png
  plot_in_png();  

  printf("\nvous y trouverez les informations des trois modèles dans leur fichiers dans le dossier output ツ\n\n");
  // afficher la memoire des trois modèles
  printf("la mémoire utilisée dans la Matrice = %g octets\n",memoryMat);
  printf("la mémoire utilisée dans le Vecteur = %g octets\n",memoryVect);
  printf("la mémoire utilisée dans la Matrice Compacte = %g octets\n",memoryMco);
  
  // supprime l'allocation de memoire
  freeMat(MatA);freeMat(MatB);freeMat(MatMul);
  freeVect(VectA);freeVect(VectB);
  freeMco(McoA);freeMco(McoB);freeMco(McoMul);
  free(tab);
  return 0;
}

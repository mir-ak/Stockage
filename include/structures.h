#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <sys/dir.h>

#define to_milliS(time)(time/(CLOCKS_PER_SEC/1000.0))

typedef double matrice;
struct mat{
	int row;
  	int column;
	matrice **m; 
};
typedef struct mat mat_t;

// la structure de vecteur de structure 
struct index_values{
	int i;
	int j;
	double val;
};
typedef struct index_values index_values_t;

struct vec{
	int size;
	index_values_t *vec;
};
typedef struct vec vec_t;

// la structure de vecteur de vecteur structure 
struct index_j_values{
	int j;
	double val;
};
typedef struct index_j_values index_j_values_t;

struct vect{
	int size;//col
	index_j_values_t *vec; 
};
typedef struct vect vect_t;

struct mco{
	int size;//row
	vect_t *vect;	
};
typedef struct mco mco_t;

/**
 * Fonction qui génére un nombre aléatoire entre [0.1,max]
 * @param max le nombre maximum
 * @param return nombre générer (double)
 */
double random_value(double max);

/**
 * Fonction qui remplit un tableau de nombre aléatoire entre [0.1,max]
 * @param tab  tableau a remplir
 * @param max le nombre maximum
 * @param row taille de tableau (pas ligne)
 * @param column taille de tableau (pas column)
 */
void init_tab(double *tab, double max, int row, int column);

/************************************* Matrice *************************************/

/**
 * Fonction qui allouer la mémoire pour la structur matrice
 * @param max le nombre maximum
 * @param row taille de lignes a alouer pour la matrice
 * @param column taille de colonnes a alouer pour la matrice
 * @param return matrice allouer
 */
mat_t initMatrix(int _row, int _column);

/**
 * Fonction qui cree la matrice avec des nombre aléatoire a l'aide d'un tableau (affection)
 * @param tab  tableau de nombre aléatoire
 * @param row taille de lignes de la matrice
 * @param column taille de colonnes de la matrice
 * @param return matrice creer
 */
mat_t create_Matrix(double *tab, int row, int column);

/**
 * Fonction qui cree la matrice avec la version de prof
 * @param row taille de lignes de la matrice
 * @param column taille de colonnes de la matrice
 * @param return la matrice creer
 */
mat_t create_MatrixV0(int row,int column);

/**
 * Fonction qui multiplier deux matrice
 * @param f fichier pour ecrire la description  
 * @param matA la première matrice
 * @param matB la deuxième matrice
 * @param return une matrice (le produit de deux matrice)
 */
mat_t multiplication_two_Matrix(FILE *F, mat_t matA,mat_t matB);

/**
 * Fonction qui affiche la matrice 
 * @param mat la matrice a afficher
 */
void displayMatrix(mat_t mat);

/**
 * Fonction qui affiche la matrice avec une autre version d'affichage
 * @param mat la matrice a afficher
 */
void displayMatrix_V2(mat_t mat);

/**
 * Fonction qui calcul l’utilisation de la mémoire de la matrice
 * @param mat la matrice a calculer
 */
double memoryMatrix(mat_t mat);
/**
 * Fonction qui supprime la memoir allouée pour la structure de la matrice 
 * @param mat la matrice 
 */
void freeMat(mat_t mat);

/**
 * Fonction qui ecrit la matrice (creer) dans un fichier 
 * @param f  le nome de fichier ou on vas ecrir la matrice 
 * @param mat la matrice a creer 
 */
void outputMat(FILE *f,mat_t mat);

/************************************* vecteur *************************************/

/**
 * Fonction qui allouer la mémoire pour la structure vecteur
 * @param size  taille a allouer pour le vecteur 
 * @param return vecteur allouer
 */
vec_t initVector(int size);

/**
 * Fonction qui transforme la matrice en vecteur
 * @param mat la matrice a transformer 
 * @param size la taille de vecteur
 * @param return vecteur creer 
 */
vec_t matrix_to_vector(mat_t mat, int size);

/**
 * Fonction qui transforme le vecteur en matrice 
 * @param vect le vecteur a transformer 
 * @param size la taille de la matrice en (ligne et colonne)
 * @param return matrice creer
 */
mat_t vector_to_matrix(vec_t vect,int size);

/**
 * Fonction qui multiplier deux vecteurs 
 * @param f fichier pour ecrire la description  
 * @param vectA le premier vecteur
 * @param vectB le deuxième vecteur
 * @param return le produit de vecteur c'est un double
 */
double multiplication_two_vectors(FILE *f,vec_t vectA, vec_t vectB);

/**
 * Fonction qui affiche le vecteur
 * @param vect le vecteur a afficher
 */
void displayVectors(vec_t vect);

/**
 * Fonction qui calcul l’utilisation de la mémoire de vecteur
 * @param mat le vecteur a calculer
 */
double memoryVector( vec_t vect);

/**
 * Fonction qui supprime la memoir allouée pour la structure de vecteur
 * @param vect le vecteur 
 */
void freeVect(vec_t vect);

/**
 * Fonction qui ecrit le vecteur (creer) dans un fichier et la multiplication de deux vecteur 
 * @param f  le nome de fichier ou on vas ecrir le vecteur
 * @param vect le vecteur a creer 
 * @param val le resultat de produit de deux vecteur 
 */
void outputVect(FILE *f,vec_t vect,double val);

/********************************* Matrice_compacte ********************************/

/**
 * Fonction qui allouer la mémoire pour la structure matrice compacte
 * @param row  taille de lignes a allouer pour la matrice compacte 
 * @param column taille de colonnes a alouer pour la matrice compacte
 * @param return matrice compacte allouer
 */
mco_t initCompact_matrix(int row,int column);

/**
 * Fonction qui transforme la matrice en matrice compacte
 * @param vect la matrice a transformer 
 * @param return matrice compacte creer
 */
mco_t matrix_to_compact_matrix(mat_t mat);

/**
 * Fonction qui multiplier deux matrice compacte
 * @param f fichier pour ecrire la description  
 * @param mcoA la premier matrice compacte
 * @param mcoB la deuxième matrice compacte
 * @param return une matrice compacte (le produit de deux matrice)
 */
mco_t multiplication_two_matrix_mco(FILE *f, mco_t mcoA,mco_t mcoB);

/**
 * Fonction qui multiplier matrice et matrice compacte
 * @param f fichier pour ecrire la description  
 * @param mcoA la matrice compacte
 * @param mcoB la matrice 
 * @param return une matrice compacte (le produit de deux matrice (mat*mco))
 */
mco_t multiplication_matrix_compact_matrix(FILE *f,mco_t mco,mat_t mat);

/**
 * Fonction qui affiche la matrices compacte
 * @param vect la matrice compacte a afficher
 */
void displayCompact_matrix(mco_t mco);

/**
 * Fonction qui calcul l’utilisation de la mémoire de la matrice compacte
 * @param mat la matrice compacte a calculer
 */
double memoryCompactMatrix( mco_t mco);

/**
 * Fonction qui supprime la memoir allouée pour la structure de la matrice compacte
 * @param mco la matrice compacte
 */
void freeMco(mco_t mco);

/**
 * Fonction qui ecrit la matrice compacte (creer) dans un fichier 
 * @param f  le nome de fichier ou on vas ecrir la matrice 
 * @param mco la matrice compacte a creer 
 */
void outputMco(FILE *f,mco_t mco);

/**
 * Fonction qui calcule l'evolution de temps des trois modèles (matrice vecteur matrice compacte) 
 * et enregistrer les donnees dans un fichier .data
 * @param f  le nome de fichier ou on vas enregistrer les donnees
 * @param MatA la matrice a creer
 * @param Vect le vecteur a creer
 * @param Mco la matrice compacte a creer
 * @param tab le tableau des no aléatoire pour creer la matrice
 * @param row taille de lignes
 * @param column taille de colonnes
 */
void outputTime(FILE *f,mat_t matA,vec_t vectA, mco_t mcoA,double *tab, int row,int column);

/**
 * Fonction qui ferme les fichiers aprés l'utilisation 
 * @param a fichiers a ferme
 * @param b fichiers a ferme
 * @param c fichiers a ferme
 * @param d fichiers a ferme
 */
void fileclose(FILE *a, FILE *b, FILE *c, FILE *d);

/**
 * Fonction qui cree un graphique a Courbe de l'evolution de temps des trois modèles (matrice vecteur matrice compacte) 
 * on recupere les donnees dans le fichier .data (creer garce a la fonction outputTime())
 */
void plot_in_png();

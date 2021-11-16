// main.cpp - Implementation d'un algorithme de tri par LSA, LPT et RMA
// Date: 2020-19-11
// Created by: BODO Maxence & EL FARISI Belal

#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

int LSA(int M[],int D[],int n, int m){

    //Initialise les machines à un temps 0
    for(int i=0;i<m;i++){M[i]=0;}

    //Pour toute les taches
    for(int i =0;i<n;i++){
        int min=0;
        //Mettre la tache dans la machine ayant finis sa tache en premiere, si plusieurs machines au même temps mettre dans la premiere machine
        for(int j = min+1;j<m;j++){ 
            if(M[j]<M[min]){
                min=j;
            }
        }
        M[min]+=D[i];
    }
    
    //Cherche la valeur la plus grande des machines qui corresponds aux temps le plus long donc le résultat LSA
    int res=0;
    for(int i=0;i<m;i++){
        if (M[i]>res){
            res = M[i];
        }
    }
    return res;
}

void triDecroissant(int D[],int n){
	bool en_desordre = true;
	for (int i = 0; i < n && en_desordre; ++i)
	{
		en_desordre = false;
		for (int j = 1; j < n - i; ++j)
			if (D[j-1] < D[j])
			{
				std::swap(D[j], D[j-1]);
				en_desordre = true;
 			}
	}
}

int LPT(int M[],int D[],int n, int m){
    //tri d'abords les taches par longueur décroissante 
    triDecroissant(D,n);

    //Puis applique LSA dessus
    int result = LSA(M,D,n,m);
    return result;
}

int RMA(int M[],int D[],int n, int m){
    int rand =0;
    //Initialise les valeurs des temps des machines à 0
    for(int i=0;i<m;i++){M[i]=0;}

    //Choisis une valeur aléatoire entre 0 et le nombre de machine et place une tache dans une machine aléatoirement
    for(int i =0;i<n;i++){
        rand =std::rand()%m;
        M[rand]+=D[i];
    }

    //Cherche la valeur la plus grande des machines qui corresponds aux temps le plus long donc le résultat RMA
    int res=0;
    for(int i=0;i<m;i++){
        if (M[i]>res){
            res = M[i];
        }
    }
    return res;
}

void modeI2p(){
    //Declaration variable
    float borneSup=0;
    float borneMoy=0;
    int resultLSA=0;
    float ratioLSA=0;
    int resultLPT=0;
    float ratioLPT=0;
    int resultRMA=0;
    float ratioRMA=0;
    int p; // paramètre entier
    int m; //nb de machine
    int n; //nb tâches

    std::cout<<"Bienvenue dans le mode I2p"<<std::endl<<"Veuillez rentrer les différentes valeurs nécessaires ! "<<std::endl;
    std::cout<<"Rentrez p = ";
    std::cin>>p;
    std::cout<<std::endl;
    m=2*p; //Nombre de machine
    n=2*std::pow(p,2)+2*p+1; //Nombre de tache

    //Création et remplissage du tableau de tache
    const int constTache = n;
    const int constMachine = m;
    int D[constTache];
    int M[constMachine];

    int c=0;
    for(int i=c; i<4*p; i++){ D[i]=1;};
    c+=4*p;

    for(int i=c; i<c+(2*p*(p-1)); i++){D[i]=2;};
    c+=(2*p*(p-1));

    for(int i= (4*p)+(2*p*(p-1)); i<c+1; i++){D[i]=2*p;}    

    std::cout<<"Nombre de machine : "<<m<<std::endl<<"Nombre de Tâche : "<<n<<std::endl<<std::endl;

    //Calcul borne inférieur "maximum"
    int compt=0;
    for(int i =0;i<n;i++){
        if(D[i+1]>D[i]){
            compt=i;
        }
    }
    borneSup=D[compt];

    //Calcul borne inférieur "moyenne"
    compt=0;
    for(int i =0;i<n;i++){
        compt+=D[i];
    }
    borneMoy = (compt/m)+1; //+1 pour arondir a l'entier supérieur

    //Affichage resultat;
    std::cout<<"Borne inférieur ''maximum'' = "<<borneSup<<std::endl;
    std::cout<<"Borne inférieur ''moyenne'' = "<<borneMoy<<std::endl<<std::endl;

    resultLSA = LSA(M,D,n,m);
    ratioLSA = resultLSA/std::max(borneSup,borneMoy);
    std::cout<<"Resultat LSA = "<<resultLSA<<std::endl;
    std::cout<<"Ratio LSA = "<<ratioLSA<<std::endl<<std::endl;

    resultLPT = LPT(M,D,n,m);
    ratioLPT=resultLPT/std::max(borneSup,borneMoy);
    std::cout<<"Resultat LPT = "<<resultLPT<<std::endl;
    std::cout<<"Ratio LPT = "<<ratioLPT<<std::endl<<std::endl;

    resultRMA = RMA(M,D,n,m);
    ratioRMA=resultRMA/std::max(borneSup,borneMoy);
    std::cout<<"Resultat RMA = "<<resultRMA<<std::endl;
    std::cout<<"Ratio RMA = "<<ratioRMA<<std::endl<<std::endl;

}

void modeRand(){
    //Declaration variable
    int m;
    int n;
    int k;
    int dmin;
    int dmax;
    int resultLSA=0, resultLPT=0, resultRMA=0;
    float ratioLSA=0.0, ratioLPT=0.0,ratioRMA=0.0;
    float borneMax=0.0,borneMoy=0.0;

    std::cout<<"Bienvenue dans le mode random"<<std::endl<<"Veuillez rentrer les différentes valeurs nécessaires ! "<<std::endl;
    std::cout<<"n = ";
    std::cin>>n;
    std::cout<<"m = ";
    std::cin>>m;
    std::cout<<"k = ";
    std::cin>>k;
    std::cout<<"dmin = ";
    std::cin>>dmin;
    std::cout<<"dmax = ";
    std::cin>>dmax;
    std::cout<<std::endl;
    int const constM =m;
    int M[constM]; //tableau de machine
    int const constN=n;
    int D[constN]; //tableau de tâche
    

    for(int i =0;i<k;i++){
        
        int random;
        //Remplissage du tableau de tache avec des taches situés entre dmin et dmax
        for(int i=0;i<constN;i++){
            random =dmin+(int)((float)rand()*(dmax-dmin+1)/(RAND_MAX-1));
            D[i]=random;
        }
        
        //Calcul borne inférieur "maximum"
        borneMax=0;
        for (int i=0;i<n;i++){
            if (D[i]>borneMax){
                borneMax=D[i];
            }
        }
        

        //Calcul borne inférieur "moyenne"
        int compt=0;
        for(int i =0;i<n;i++){
            compt+=D[i];
        }
        borneMoy = (compt/m)+1; //+1 pour arondir a l'entier supérieur

        //Calcul des résultats des différentes méthodes de tri 
        resultLSA=LSA(M,D,n,m);
        resultLPT=LPT(M,D,n,m);
        resultRMA=RMA(M,D,n,m);
        
        //Calcul du ratio des différentes méthodes de tri puis ajout dans une variable globale
        float ratioLSATemp = resultLSA/std::max(borneMax,borneMoy);
        float ratioLPTTemp = resultLPT/std::max(borneMax,borneMoy);
        float ratioRMATemp = resultRMA/std::max(borneMax,borneMoy);

        ratioLSA+=ratioLSATemp;
        ratioLPT+=ratioLPTTemp;
        ratioRMA+=ratioRMATemp;
    }

    //Affiche la moyenne des ratios LSA, LPT et RMA
    std::cout<<"ratio moyen LSA = "<<float(ratioLSA/k)<<std::endl;
    std::cout<<"ratio moyen LPT = "<<float(ratioLPT/k)<<std::endl;
    std::cout<<"ratio moyen RMA = "<<float(ratioRMA/k)<<std::endl;
    
}

int main(){
    //Variable
    int rep;

    //Algorithme
    srand((unsigned int)time(0));
    std::cout<<"_-_-_-_-_-_Algorithme réalisé par Belal El Farissi et Maxence Bodo _-_-_-_-_-_"<<std::endl<<std::endl;
    std::cout<<"Bonjour, bienvenue dans l'algorithme Min Makespan"<<std::endl;
    std::cout<<"Pour commencer quel mode voulez vous utiliser ?"<<std::endl;
    std::cout<<"Tapez 1 pour la génération d'une instance de type I2p"<<std::endl;
    std::cout<<"Tapez 2 pour la génération aléatoire de plusieurs instances"<<std::endl;
    std::cout<<"Tapez 3 pour découvrir le sens de la vie"<<std::endl;
    std::cout<<"Tapez 0 pour quitter le programme"<<std::endl;
    std::cin>>rep;
    std::cout<<std::endl;

    switch(rep){
        case 0:
            break;
        case 1:
            modeI2p();
            break;
        case 2:
            modeRand();
            break;
        case 3:
            std::cout<<"La grande question sur la vie, l univers et le reste est 42 selon Adamns Douglas !!";
            break;
        default:
            std::cout<<"Erreur saisie"<<std::endl;
            break;
    }
    std::cout<<std::endl<<"Merci pour votre utilisation ! et à bientôt ;-)"<<std::endl;
}


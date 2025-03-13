#include "TP4.hpp"

// Constructeur d'initialisation
template <typename T>
Colonne<T>::Colonne(std::string nomColonne, T* tableauAttribut) : nomColonne(nomColonne), tableauAttribut(tableauAttribut), tailleTableau(0){};

// Constructeur par défaut
template <typename T>
Colonne<T>::Colonne() : nomColonne(""), tableauAttribut(nullptr), tailleTableau(0){};

// Constructeur avec argument string nomColonne
template <typename T>
Colonne<T>::Colonne(std::string nomColonne) : nomColonne(nomColonne), tableauAttribut(nullptr), tailleTableau(0){};

// Constructeur de copie
template <typename T>
Colonne<T>::Colonne(const Colonne& autre) : nomColonne(autre.nomColonne), tailleTableau(autre.tailleTableau){
	tableauAttribut = new T[tailleTableau];
	for (size_t i = 0; i<tailleTableau; i++){
		tableauAttribut[i] = autre.tableauAttribut[i];
	}
};

template <typename T>
Colonne<T>::~Colonne(){
	delete[] tableauAttribut;
};


// Méthode add(T valeur) qui ajoute une valeur à la fin du tableau
template <typename T>
void Colonne<T>::add(T valeur){
	// On crée un nouveau tableau de taille tailleTableau + 1
	T* nouveauTableau = new T[tailleTableau+1];
	// On copie les valeurs de tableauAttribut dans nouveauTableau
	for (size_t i = 0; i < tailleTableau; i++){
		nouveauTableau[i] = tableauAttribut[i];
	}
	// On ajoute la valeur à la fin du tableau
	nouveauTableau[tailleTableau] = valeur;
	// On libère la mémoire de tableauAttribut
	delete[] tableauAttribut;
	// On met tableauAttribut à jour
	tableauAttribut = nouveauTableau;
	// On met à jour la taille du tableau
	tailleTableau++;
};


// Méthode taille() pour retourner la taille actuelle de la colonne
template <typename T>
size_t Colonne<T>::taille(void){
	return tailleTableau;
};

// Surcharge de [] pour accéder à une valeur à la position i et permet de la modifier par assignation
template <typename T>
T& Colonne<T>::operator [](size_t i){
	if ((i>= tailleTableau) || (i<0)){
		std::cerr << "Erreur : indice hors limite" << std::endl;
	}
	return tableauAttribut[i];
};

// Surcharge de [] juste pour lire la valeur
template <typename T>
const T& Colonne<T>::operator [](size_t i) const{
	if ((i>= tailleTableau) || (i<0)){
		std::cerr << "Erreur : indice hors limite" << std::endl;
	}
	return tableauAttribut[i];
};

//afficherColonne() : voir .hpp

template <typename T>
void Colonne<T>::vider(void){
	delete[] tableauAttribut;
	tableauAttribut = nullptr;
	tailleTableau = 0;
};


/////////////////////////////////////

// Méthode privée qui vérifie si un nom de colonne est déjà utilisé
bool DataFrame::colonneExiste(std::string nom){
	for (size_t i = 0; i < nomsColonnes.size(); i++){
		if (nomsColonnes[i] == nom){
			return true;
		}
	}
	return false;
};

// Méthode addColonne surdéfinie pour les différents types de colonnes
// Deux colonnes ne peuvent pas avoir le même nom.
void DataFrame::addColonne(Colonne<int> colonne, std::string nom){
	if(colonneExiste(nom)){
		std::cerr << "Erreur : nom de colonne déjà utilisé" << std::endl;
	}
	else{
		colonnesInt.push_back(colonne);
		nomsColonnes.push_back(nom);
		typeColonne.push_back(0);
		nbColonnes++;
		nbColonnesInt++;
		nbLignes += colonne.taille();
	}
};

void DataFrame::addColonne(Colonne<std::string> colonne, std::string nom){
	if(colonneExiste(nom)){
		std::cerr << "Erreur : nom de colonne déjà utilisé" << std::endl;
	}
	else{
		colonnesString.push_back(colonne);
		nomsColonnes.push_back(nom);
		typeColonne.push_back(2);
		nbColonnes++;
		nbColonnesString++;
		nbLignes += colonne.taille();
	}
};

void DataFrame::addColonne(Colonne<double> colonne, std::string nom){
	if(colonneExiste(nom)){
		std::cerr << "Erreur : nom de colonne déjà utilisé" << std::endl;
	}
	else{
		colonnesDouble.push_back(colonne);
		nomsColonnes.push_back(nom);
		typeColonne.push_back(1);
		nbColonnes++;
		nbColonnesDouble++;
		nbLignes += colonne.taille();
	}
};

size_t DataFrame::nombreLignes(){
	return nbLignes;
};

size_t DataFrame::nombreColonnes(){
	return nbColonnes;
};



void DataFrame::supprimerColonne(std::string nom){
	int iInt = 0;
	int iDouble = 0;
	int iString = 0;

	for (size_t i = 0; i < nomsColonnes.size(); i++){
		//Grâce à ce switch, on sait à quelle colonne on a affaire
		switch (typeColonne[i]){
			case 0:{
				iInt += 1;
				break;
			}
			case 1:{
				iDouble += 1;
				break;
			}
			case 2:{
				iString += 1;
				break;
			}
			
			default:
				break;
			}


		if (nomsColonnes[i] == nom){
			//on efface le nom de la colonne
			nomsColonnes.erase(nomsColonnes.begin() + i);
			//on efface la bonne colonne, en fonction de quelle colonne il s'agit + son instance dans le vecteur de type
			switch (typeColonne[i]){
				case 0:{
					colonnesInt.erase(colonnesInt.begin() + iInt);
					typeColonne.erase(typeColonne.begin() + i);
					nbColonnesInt--;
					break;
				}
				case 1:{
					colonnesDouble.erase(colonnesDouble.begin() + iDouble);
					typeColonne.erase(typeColonne.begin() + i);
					nbColonnesDouble--;
					break;
				}
				case 2:{
					colonnesString.erase(colonnesString.begin() + iString);
					typeColonne.erase(typeColonne.begin() + i);
					nbColonnesString--;
					break;
				}
				default:
					break;
			}
		}
	}
};

// Constructeur par défaut
DataFrame::DataFrame(){
	tailleDataFrame = 0;
	nbColonnes = 0;
	nbColonnesInt = 0;
	nbColonnesDouble = 0;
	nbColonnesString = 0;
	nbLignes = 0;
};

// Constructeur de copie
DataFrame::DataFrame(const DataFrame& autre){
	tailleDataFrame = autre.tailleDataFrame;
	nbColonnes = autre.nbColonnes;
	nbColonnesInt = autre.nbColonnesInt;
	nbColonnesDouble = autre.nbColonnesDouble;
	nbColonnesString = autre.nbColonnesString;
	nbLignes = autre.nbLignes;
	colonnesInt = autre.colonnesInt;
	colonnesDouble = autre.colonnesDouble;
	colonnesString = autre.colonnesString;
	nomsColonnes = autre.nomsColonnes;
	typeColonne = autre.typeColonne;
};

// Destructeur
DataFrame::~DataFrame(){
	colonnesInt.clear();
	colonnesDouble.clear();
	colonnesString.clear();
	nomsColonnes.clear();
	typeColonne.clear();
};

template <typename T>
Colonne<T>& getColonne(std::string nom){
	int iInt = 0;
	int iDouble = 0;
	int iString = 0;

	for (size_t i = 0; i < nomsColonnes.size(); i++){
		switch (typeColonne[i]){
			case 0:{
				iInt += 1;
				break;
			}
			case 1:{
				iDouble += 1;
				break;
			}
			case 2:{
				iString += 1;
				break;
			}
			default:
				break;
		}
		if (nomsColonnes[i] == nom){
			switch (typeColonne[i]){
				case 0:{
					return colonnesInt[iInt];
					break;
				}
				case 1:{
					return colonnesDouble[iDouble];
					break;
				}
				case 2:{
					return colonnesString[iString];
					break;
				}
				default:
					break;
			}
		}
	}
};

template <typename T>
T& DataFrame::operator[](std::string nom){
	return getColonne<T>(nom);
};

template <typename T>
T& DataFrame::operator()(size_t ligne, std::string nom){
	return getColonne<T>(nom)[ligne];
}



int main(int argc, char* argv[]){
	Colonne<int> col("Exemple");
	col.add(10);
	col.add(20);
	col.add(30);

	afficherColonne(col);

	return 0;

}
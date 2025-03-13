#ifndef TP4_H
#define TP4_H

#include <map>
#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include <cstddef>

template <typename T>

class Colonne{
	private:
		std::string nomColonne;
		T* tableauAttribut;
		size_t tailleTableau;
	//

	public:
		// Constructeur d'initialisation
		Colonne(std::string nomColonne, T* tableauAttribut);

		// Constructeur par défaut
		Colonne();

		// Constructeur avec argument string nomColonne
		Colonne(std::string nomColonne);

		// Constructeur de copie
		Colonne(const Colonne& autre);

		// Destructeur
		~Colonne();

		// Méthode add(T valeur) qui ajoute une valeur à la fin du tableau
		void add(T valeur);

		// Méthode taille() pour retourner la taille actuelle de la colonne
		size_t taille(void);

		// Surcharge de [] pour accéder à une valeur à la position i et permet de la modifier par assignation
		T& operator [](size_t i);
		// Surcharge de [] juste pour lire la valeur
		const T& operator [](size_t i) const;
		
		// Méthode amie qui affiche le contenu d'une colonne
		/*N.B. je n'ai pas réussi à l'implémenter dans le .cpp*/
		friend void afficherColonne(const Colonne<T>& colonne){
			std::cout << "Nom de la colonne : \n" << colonne.nomColonne << std::endl;
			std::cout << "Contenu de la colonne : " << std::endl;
			for (size_t i = 0; i < colonne.tailleTableau; i++){
				std::cout << colonne.tableauAttribut[i] << "\n";
			}
			std::cout << std::endl;
		};

		// Méthode vider() (self-explainatory)
		void vider(void);
	//
};

class DataFrame{
	// Stocke dynamiquement plusieurs Colonnes
	private:
		std::vector <Colonne<int>> colonnesInt;
		std::vector <Colonne<double>> colonnesDouble;
		std::vector <Colonne<std::string>> colonnesString;
		std::vector <std::string> nomsColonnes;
		std::vector <int> typeColonne; // 0 : int, 1 : double, 2 : string
		size_t tailleDataFrame;
		size_t nbColonnes;
		size_t nbColonnesInt;
		size_t nbColonnesDouble;
		size_t nbColonnesString;
		// Le nombre de lignes correspond à la taille de la colonne la plus longue
		size_t nbLignes;
		// size_t nbLignesInt;
		// size_t nbLignesDouble;
		// size_t nbLignesString;

		//Probalbment un autre moyen de trouver le nombre de lignes... jsp

		// Méthode privée qui vérifie si un nom de colonne est déjà utilisé
		bool colonneExiste(std::string nom);

	//

	public:
		// Méthode addColonne surdéfinie pour les différents types de colonnes
		// Deux colonnes ne peuvent pas avoir le même nom.
		void addColonne(Colonne<int> colonne, std::string nom);
		
		//m^mee chose à faire ici
		void addColonne(Colonne<double> colonne, std::string nom);
			
		//idem
		void addColonne(Colonne<std::string> colonne, std::string nom);
		
		//self-explainatory
		size_t nombreLignes();
		size_t nombreColonnes();
		void supprimerColonne(std::string nom);

		// Constructeur par défaut
		DataFrame();

		// Constructeur de copie
		DataFrame(const DataFrame& autre);

		// Destructeur
		~DataFrame();

		// Methode template qui retourne une colonne avec en entrée son nom
		template <typename T>
		Colonne<T>& getColonne(std::string nom);

		// Surcharge de [] qui permet l'accès à une colonne par son nom
		template <typename T>
		T& operator[](std::string nom);

		// Surcharche de () qui permet le remplacement d'une valeur spécifique via le nom de sa colonne et le numéro de sa ligne
		template <typename T>
		T& operator()(size_t ligne, std::string nom);

		friend void afficherContenu(DataFrame df){
			std::cout << "Contenu du DataFrame : " << std::endl;
			int iInt = 0;
			int iDouble = 0;
			int iString = 0;
			for (size_t i = 0; i < df.nbColonnes; i++){
				std::cout << "Nom de la colonne : " << df.nomsColonnes[i] << std::endl;
				switch (df.typeColonne[i]){
					case 0:{
						std::cout << "Colonne Int" << std::endl;
						iInt += 1;
						// Boucle itérant sur le vecteur actuel
						for (size_t j = 0; j < df.colonnesInt[iInt].taille(); j++){
							std::cout << df.colonnesInt[iInt][j] << std::endl;
						}
						break;
					}
					case 1:{
						std::cout << "Colonne Double" << std::endl;
						iDouble += 1;
						// Boucle itérant sur le vecteur actuel
						for (size_t j = 0; j < df.colonnesDouble[iDouble].taille(); j++){
							std::cout << df.colonnesDouble[iDouble][j] << std::endl;
						}
						break;
					}
					case 2:{
						std::cout << "Colonne String" << std::endl;
						iString += 1;
						// Boucle itérant sur le vecteur actuel
						for (size_t j = 0; j < df.colonnesString[iString].taille(); j++){
							std::cout << df.colonnesString[iString][j] << std::endl;
						}
						
						break;
					}
				}
			}
			std::cout << std::endl;
		};
	//
};

#endif
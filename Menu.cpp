//------------- Realisation de la classe <%class%> ( fichier %class%.cpp ) -----------------

//------------- Include syst�me ------------------------------------------------------------
#include <iostream>
#include <cstring>

using namespace std;

//------------- Include personnel ----------------------------------------------------------
#include "Menu.h"

//------------- Constantes -----------------------------------------------------------------

//------------- Methodes publiques ---------------------------------------------------------

void Menu::run()
{

	/*TrajetSimple* ts1 = new TrajetSimple("DONTRIEN", "REIMS", "VOITURE");
	TrajetSimple* ts2 = new TrajetSimple("PARIS", "DONTRIEN", "VOITURE");
	TrajetSimple* ts3 = new TrajetSimple("REIMS", "PARIS", "VOITURE");
	TrajetSimple* ts4 = new TrajetSimple("MARSEILLE", "DONTRIEN", "VOITURE");

	catal.Add(ts1);
	catal.Add(ts2);
	catal.Add(ts3);
	catal.Add(ts4); */ //Exemples destin�s aux tests

	char lecture[100];
	lecture[0] = '\0';


	bool modif = false;

	while (strcmp(lecture, "bye") != 0) //On entre dans le menu
	{
		modif = true;

		if (currentMenu == SelectionMenu::M_MENU) // Selection du premier sous menu
		{
			if (strcmp(lecture, "ct") == 0)
			{
				currentMenu = SelectionMenu::CT_MENU;
			}
			else if (strcmp(lecture, "af") == 0)
			{
				cout << catal << endl;
			}
			else if (strcmp(lecture, "rp") == 0)
			{
				currentMenu = SelectionMenu::RP_MENU;
			}
			else if (strcmp(lecture, "dt") == 0)
			{
				currentMenu = SelectionMenu::DELETE_TRAJET;
			}
			else
			{
				modif = false;
				cout << endl << "Menu :\n -Creer un trajet [ct]\n -Afficher le contenu du catalogue [af]\n -Rechercher un parcours [rp]\n -Supprimer un trajet (Simple ou compose) [dt]\n -Quitter [bye]" << endl;
			}
		}
		else if (currentMenu == SelectionMenu::CT_MENU)
		{
			if (strcmp(lecture, "ts") == 0) //Ajout trajet simple
			{
				TrajetSimple *trajet = creerTrajetSimple();
				catal.Add(trajet);
			}
			else if (strcmp(lecture, "tc") == 0) //Ajout trajet compose
			{
				TrajetCompose *trajet = creerTrajetCompose(catal);
				catal.Add(trajet);
			}
			else if (strcmp(lecture, "r") == 0)
			{
				currentMenu = SelectionMenu::M_MENU;
			}
			else
			{
				modif = false;
				cout << endl << "Ajouter un trajet:\n -Trajet Simple [ts]\n -Trajet Compose [tc]\n -Retour [r]" << endl;
			}
		}
		else if (currentMenu == SelectionMenu::RP_MENU)
		{
			if (strcmp(lecture, "vs") == 0) //Lancement de la recherche simple
			{
				cout << "Recherche version simple" << endl;
				char *vDep = new char[100];
				char *vArr = new char[100];
				cout << "Ville de depart : ";
				cin >> vDep;
				cout << "Ville d'arrivee : ";
				cin >> vArr;

				catal.RechercheSimple(vDep, vArr);

				delete[] vDep;
				delete[] vArr;
			}
			else if (strcmp(lecture, "va") == 0) //Lancement de la recherche avancee
			{
				cout << "Recherche version avancee" << endl;
				char *vDep = new char[100];
				char *vArr = new char[100];
				cout << "Ville de depart : ";
				cin >> vDep;
				cout << "Ville d'arrivee : ";
				cin >> vArr;

				catal.RechercheAvancee(vDep, vArr);

				delete[] vDep;
				delete[] vArr;
			}
			else if (strcmp(lecture, "r") == 0)
			{
				currentMenu = SelectionMenu::M_MENU;
			}
			else
			{
				modif = false;
				cout << endl << "Recherche de parcours :\n -Version Simple [vs]\n -Version Avancee [va]\n -Retour [r]" << endl;
			}
		}
		else if (currentMenu == SelectionMenu::DELETE_TRAJET) //Suppression d'un element
		{
			int indiceASupprimer = -1;
			while (indiceASupprimer < 1)
			{
				cout << "Indiquer l'indice du trajet � supprimer du catalogue : ";
				cin >> indiceASupprimer;
			}
			catal.DeleteElement(indiceASupprimer - 1);
			currentMenu = SelectionMenu::M_MENU;
		}
		lecture[0] = '\0';

		if (!modif)
		{
			cin >> lecture;
			cout << endl;
		}
	}
}//--------Fin de run

TrajetSimple* Menu::creerTrajetSimple()
{
	char *vDep = new char[100];
	char *vArr = new char[100];
	char *mTrans = new char[100];

	cout << "Creation d'un trajet simple" << endl << "Entrez la ville de depart : ";
	cin >> vDep;
	cout << "Entrez la ville d'arrivee : ";
	cin >> vArr;
	cout << "Entrez le moyen de transport : ";
	cin >> mTrans;
	cout << endl;

	TrajetSimple *ts = new TrajetSimple(vDep, vArr, mTrans);

	delete[] vDep;
	delete[] vArr;
	delete[] mTrans;

	return ts;
}//--------Fin de creerTrajetSimple

TrajetCompose* Menu::creerTrajetCompose(const Catalogue & catalogue)
{
	TrajetCompose *newTrajet = new TrajetCompose();

	char lecture[100];
	lecture[0] = '\0';
	bool modif = false;

	while (strcmp(lecture, "fa") != 0)
	{
		modif = true;

		if (strcmp(lecture, "ts") == 0)
		{
			TrajetSimple *trajet = creerTrajetSimple();
			newTrajet->AjouterTrajet(trajet);
		}
		else if (strcmp(lecture, "te") == 0)
		{
			cout << "Choisir un element dans le catalogue (numero) : " << endl << catalogue << endl;
			bool correct = false;
			while (!correct)
			{
				int num;
				cin >> num;
				if (num > catalogue.GetNbElement())
				{
					cout << "Nombre trop grand, veillez choisir un nombre plus petit." << endl;
				}
				else if (num < 1)
				{
					cout << "Nombre trop peit, veillez choisir un nombre plus grand." << endl;
				}
				else
				{
					correct = true;
					Trajet *addClone = catalogue[num - 1]->Clone();
					newTrajet->AjouterTrajet(addClone);
				}
			}
		}
		else
		{
			modif = false;
			cout << endl << "Creer un Trajet compose :\n -Ajouter Trajet Simple [ts]\n -Ajouter Trajet existant [te]\n -Fin d'ajout [fa]" << endl;
		}
		lecture[0] = '\0';

		if (!modif)
		{
			cin >> lecture;
			cout << endl;
		}
	}

	return newTrajet;
}//--------Fin de creerTrajetCompose

//------------- Surcharge d'op�rateurs -----------------------------------------------------

//------------- Constructeurs - Desctructeur -----------------------------------------------

Menu::Menu() : currentMenu(SelectionMenu::M_MENU), catal()
{
#ifdef MAP
	cout << "Appel du constructeur de <Menu>" << endl;
#endif
	run();
}//------Fin du constructeur

Menu::~Menu()
{
#ifdef MAP
	cout << "Appel du destructeur de <Menu>" << endl;
#endif
}//------Fin du destructeur

//------------- Methodes prot�g�es ---------------------------------------------------------






int main()
{
	Menu menu;
	return 0;
}
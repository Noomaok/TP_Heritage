//------------- Realisation de la classe <%class%> ( fichier %class%.cpp ) -----------------

//------------- Include syst�me ------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdarg.h>

using namespace std;

//------------- Include personnel ----------------------------------------------------------
#include "Menu.h"

//------------- Constantes -----------------------------------------------------------------

//------------- Methodes publiques ---------------------------------------------------------

bool Menu::checkExists(string file) const
{
	ifstream file_to_check(file.c_str());
	if(file_to_check.is_open())
		return true;
	file_to_check.close();
	return false;
}

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
			else if (strcmp(lecture, "save") == 0)
			{
				currentMenu = SelectionMenu::SAVE;
			}
			else if (strcmp(lecture, "load") == 0)
			{
				currentMenu = SelectionMenu::LOAD;
			}
			else
			{
				modif = false;
				cout << endl << "Menu :\n -Creer un trajet [ct]\n -Afficher le contenu du catalogue [af]\n -Rechercher un parcours [rp]\n -Sauvegarder [save]\n -Charger [load]\n -Quitter [bye]" << endl;
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
		else if (currentMenu == SelectionMenu::SAVE)
		{
			if(strcmp(lecture, "none") == 0)
			{
				Sauvegarde(CritereType::NONE);
			}
			else if (strcmp(lecture, "r") == 0)
			{
				currentMenu = SelectionMenu::M_MENU;
			}
			else
			{
				modif = false;
				cout << endl << "Sauvegarde :\n -Pas de critere [none]\n -En fonction du type [type]\n -En fonction des villes [dep] [arr] [both]\n -Sur un intervalle [inter]\n -Retour [r]" << endl;
			}
		}
		else if (currentMenu == SelectionMenu::LOAD)
		{
			if(strcmp(lecture, "none") == 0)
			{
				Chargement(CritereType::NONE);
			}
			else if (strcmp(lecture, "r") == 0)
			{
				currentMenu = SelectionMenu::M_MENU;
			}
			else
			{
				modif = false;
				cout << endl << "Sauvegarde :\n -Pas de critere [none]\n -En fonction du type [type]\n -En fonction des villes [dep] [arr] [both]\n -Sur un intervalle [inter]\n -Retour [r]" << endl;
			}
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

void Menu::Sauvegarde(CritereType type, ...) const
{
	va_list ap;
	va_start(ap, type);

	string saveName;
	cout << "Veuillez saisir le nom de la sauvegarde : ";
	cin >> saveName;
	saveName = string(DIR) + saveName;
	
	if(checkExists(saveName))
	{
		char rep;
		cout << "Le fichier existe deja, voulez-vous l'ecraser ? (o/n) " << endl;
		cin >> rep;
		if(rep == 'n')
			return;
	}

	ofstream fichierSave;
	fichierSave.open(saveName);

	if(type == CritereType::NONE)
	{
		for(int i = 0; i < catal.GetNbElement(); i++)
		{
			Trajet * unTrajet = catal[i];
			int typeTrajet =  unTrajet->GetType();
			fichierSave << typeTrajet << " " << unTrajet->GetVilleDepart() << " " << unTrajet->GetVilleArrivee() << " ";
			unTrajet->SaveTrajet(fichierSave);
		}
	}

	fichierSave.close();
}//--------Fin de Sauvegarde

void Menu::Chargement(CritereType type, ...)
{
	va_list ap;
	va_start(ap, type);

	string loadName;
	cout << "Veuillez saisir le nom du fichier a charger : ";
	cin >> loadName;
	loadName = string(DIR) + loadName;

	if(!checkExists(loadName))
	{
		cout << "Le fichier n'existe pas" << endl;
		return;
	}

	ifstream fichierLoad;
	fichierLoad.open(loadName);

	if(type == CritereType::NONE)
	{
		int type;
		while(!fichierLoad.eof())
		{
			fichierLoad >> type;
			if(type == 0)
			{
				string villeDep, villeArr, moyTransport;
				fichierLoad >> villeDep >> villeArr >> moyTransport;
				TrajetSimple *nouveauTrajet = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyTransport.c_str());
				catal.Add(nouveauTrajet);
			}
		}
	}

}//--------Fin dde Chargement

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
	system("mkdir -p save");
	Menu menu;
	return 0;
}

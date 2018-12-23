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
			else if (strcmp(lecture, "type") == 0)
			{
				int selection;
				cout << "Type des trajets à sauvegarder :\n -Simple [0]\n -Composé [1]" << endl;
				cin >> lecture;
				if((strcmp(lecture, "0") == 0) || strcmp(lecture, "1") == 0)
				{
					selection = (strcmp(lecture, "0") == 0) ? 0 : 1;
					Sauvegarde(CritereType::ON_TYPE, selection);
				}
				else
				{
					cout << "Selection invalide !" << endl;
				}
			}
			else if (strcmp(lecture, "dep") == 0)
			{
				char *ville = new char[100];
				cout << "Saisir la ville de départ : ";
				cin >> ville;
				Sauvegarde(CritereType::ON_DEPART, ville);
				delete [] ville;
			}
			else if (strcmp(lecture, "arr") == 0)
			{
				char *ville = new char[100];
				cout << "Saisir la ville d'arrivée : ";
				cin >> ville;
				Sauvegarde(CritereType::ON_ARRIVEE, ville);
				delete [] ville;
			}
			else if (strcmp(lecture, "both") == 0)
			{
				char *villeD = new char[100];
				cout << "Saisir la ville de départ : ";
				cin >> villeD;
				char *villeA = new char[100];
				cout << "Saisir la ville d'arrivée : ";
				cin >> villeA;
				Sauvegarde(CritereType::ON_BOTH, villeD, villeA);
				delete [] villeD;
				delete [] villeA;
			}
			else if (strcmp(lecture, "inter") == 0)
			{
				int start;
				cout << "Taille actuelle du catalogue : " << catal.GetNbElement() << endl << "Saisir l'indice de départ : ";
				cin >> start;
				int end;
				cout << "Saisir l'indice de fin : ";
				cin >> end;
				if(end - start + 1 > 0)
				{
					Sauvegarde(CritereType::ON_INTER,start,end);
				}
				else
				{
					cout << "Intervalle invalide !" << endl;
				}
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
			else if (strcmp(lecture, "type") == 0)
			{
				char selection = 'X';
				cout << "Type des trajets à charger :\n -Simple [0]\n -Composé [1]" << endl;
				cin >> selection;
				if((selection == '0') || (selection == '1'))
				{
					Chargement(CritereType::ON_TYPE, selection);
				}
				else
				{
					cout << "Selection invalide !" << endl;
				}
			}
			else if (strcmp(lecture, "dep") == 0)
			{
				char *ville = new char[100];
				cout << "Saisir la ville de départ : ";
				cin >> ville;
				Chargement(CritereType::ON_DEPART, ville);
				delete [] ville;
			}
			else if (strcmp(lecture, "arr") == 0)
			{
				char *ville = new char[100];
				cout << "Saisir la ville d'arrivée : ";
				cin >> ville;
				Chargement(CritereType::ON_ARRIVEE, ville);
				delete [] ville;
			}
			else if (strcmp(lecture, "both") == 0)
			{
				char *villeD = new char[100];
				cout << "Saisir la ville de départ : ";
				cin >> villeD;
				char *villeA = new char[100];
				cout << "Saisir la ville d'arrivée : ";
				cin >> villeA;
				Chargement(CritereType::ON_BOTH, villeD, villeA);
				delete [] villeD;
				delete [] villeA;
			}
			else if (strcmp(lecture, "r") == 0)
			{
				currentMenu = SelectionMenu::M_MENU;
			}
			else
			{
				modif = false;
				cout << endl << "Chargement :\n -Pas de critere [none]\n -En fonction du type [type]\n -En fonction des villes [dep] [arr] [both]\n -Sur un intervalle [inter]\n -Retour [r]" << endl;
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
	cout << endl << "Veuillez saisir le nom de la sauvegarde : ";
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
	else if(type == CritereType::ON_TYPE)
	{
		int selection = va_arg(ap, int);
		for(int i = 0; i < catal.GetNbElement(); i++)
		{
			Trajet * unTrajet = catal[i];
			int typeTrajet =  unTrajet->GetType();

			if(typeTrajet == selection)
			{
				fichierSave << typeTrajet << " " << unTrajet->GetVilleDepart() << " " << unTrajet->GetVilleArrivee() << " ";
				unTrajet->SaveTrajet(fichierSave);
			}
		}
	}
	else if(type == CritereType::ON_DEPART)
	{
		char* ville = va_arg(ap, char*);
		for(int i = 0; i < catal.GetNbElement(); i++)
		{
			Trajet * unTrajet = catal[i];
			int typeTrajet =  unTrajet->GetType();
			const char* villeDepart = unTrajet->GetVilleDepart();
			if(strcmp(ville,villeDepart) == 0)
			{
				fichierSave << typeTrajet << " " << villeDepart << " " << unTrajet->GetVilleArrivee() << " ";
				unTrajet->SaveTrajet(fichierSave);
			}
		}
	}
	else if(type == CritereType::ON_ARRIVEE)
	{
		char* ville = va_arg(ap, char*);
		for(int i = 0; i < catal.GetNbElement(); i++)
		{
			Trajet * unTrajet = catal[i];
			int typeTrajet =  unTrajet->GetType();
			const char* villeArrivee = unTrajet->GetVilleArrivee();
			if(strcmp(ville,villeArrivee) == 0)
			{
				fichierSave << typeTrajet << " " << unTrajet->GetVilleDepart() << " " << villeArrivee << " ";
				unTrajet->SaveTrajet(fichierSave);
			}
		}
	}
	else if(type == CritereType::ON_BOTH)
	{
		char* villeD = va_arg(ap, char*);
		char* villeA = va_arg(ap, char*);
		for(int i = 0; i < catal.GetNbElement(); i++)
		{
			Trajet * unTrajet = catal[i];
			int typeTrajet =  unTrajet->GetType();
			const char* villeDepart = unTrajet->GetVilleDepart();
			const char* villeArrivee = unTrajet->GetVilleArrivee();
			if(strcmp(villeD,villeDepart) == 0 && strcmp(villeA,villeArrivee) == 0)
			{
				fichierSave << typeTrajet << " " << villeDepart << " " << villeArrivee << " ";
				unTrajet->SaveTrajet(fichierSave);
			}
		}
	}
	else if(type == CritereType::ON_INTER)
	{
		int start = va_arg(ap, int);
		int end = va_arg(ap, int);
		for(int i = start-1; i < catal.GetNbElement() && i < end; i++)
		{
			Trajet * unTrajet = catal[i];
			int typeTrajet =  unTrajet->GetType();
			fichierSave << typeTrajet << " " << unTrajet->GetVilleDepart() << " " << unTrajet->GetVilleArrivee() << " ";
			unTrajet->SaveTrajet(fichierSave);
		}
	}
	// Mark end of file for loading
	fichierSave << '3';

	fichierSave.close();
}//--------Fin de Sauvegarde

void Menu::Chargement(CritereType type, ...)
{
	va_list ap;
	va_start(ap, type);

	string loadName;
	//ce serait pratique d'afficher les sauvegardes disponibles à cet endroit
	//system("ls -l"); <- mais dans le dossier "/save"
	cout << endl << "Veuillez saisir le nom du fichier a charger : ";
	cin >> loadName;
	loadName = string(DIR) + loadName;

	if(!checkExists(loadName))
	{
		cout << "Le fichier n'existe pas" << endl;
		return;
	}

	ifstream fichierLoad;
	fichierLoad.open(loadName);

	char categorie = 'X';
	string villeDep, villeArr, moyTransport;
	int nbTrajet;
	string useless; //Permet de se débarasser des strings que l'on veut eviter

	if(type == CritereType::NONE)
	{
		while(categorie != '3')
		{
			fichierLoad >> categorie >> villeDep >> villeArr;
			if(categorie == '0')
			{
				fichierLoad >> moyTransport;
				TrajetSimple *nouveauTrajet = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyTransport.c_str());
				catal.Add(nouveauTrajet);
			}
			else if(categorie == '1')
			{
				fichierLoad >> nbTrajet;
				TrajetCompose *nouveauTrajet = new TrajetCompose();
				fichierLoad.seekg(nouveauTrajet->loadTrajetCompose(fichierLoad, fichierLoad.tellg(), nbTrajet));
				catal.Add(nouveauTrajet);
			}
		}
	}
	else if(type == CritereType::ON_TYPE)
	{
		char selection = va_arg(ap, int);

		while(categorie != '3') //Modification de la logique car certain trajets simple contenue dans un trajet compose n'etait pas skip
		{
			fichierLoad >> categorie >> villeDep >> villeArr;
			bool checkLoad = categorie == selection;
			if(categorie == '0')
			{
				fichierLoad >> moyTransport;
				if(checkLoad)
				{
					TrajetSimple *nouveauTrajet = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyTransport.c_str());
					catal.Add(nouveauTrajet);
				}
			}
			else if(categorie == '1')
			{
				fichierLoad >> nbTrajet;
				if(checkLoad)
				{
					TrajetCompose *nouveauTrajet = new TrajetCompose();
					fichierLoad.seekg(nouveauTrajet->loadTrajetCompose(fichierLoad, fichierLoad.tellg(), nbTrajet));
					catal.Add(nouveauTrajet);
				}
				else
				{
					for(int i = 0; i < nbTrajet; i++) //On skip les n trajets appartenant au trajet composé
					{
						fichierLoad >> useless >> useless >> useless >> useless; 
						//Il faudrait verifier si le trajet compose contient un autre trajet compose
						//Pour ça il faudrait verifier la derniere valeur de useless,
						//Si c'est un entier, alors on l'ajoute a nbTrajet et on continue de skip les trajets
						//Mais comme on ne prevoit pas c'est cas la, ce n'est pas la priorite
					}
				}
			}
		}
	}
	else if(type == CritereType::ON_DEPART)
	{
		const char* ville = va_arg(ap, char*);

		while(categorie != '3') //Modification de la logique car certain trajets simple contenue dans un trajet compose n'etait pas skip
		{
			fichierLoad >> categorie >> villeDep >> villeArr;
			bool checkLoad = strcmp(ville,villeDep.c_str()) == 0;
			if(categorie == '0')
			{
				fichierLoad >> moyTransport;
				if(checkLoad)
				{
					TrajetSimple *nouveauTrajet = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyTransport.c_str());
					catal.Add(nouveauTrajet);
				}
			}
			else if(categorie == '1')
			{
				fichierLoad >> nbTrajet;
				if(checkLoad)
				{
					TrajetCompose *nouveauTrajet = new TrajetCompose();
					fichierLoad.seekg(nouveauTrajet->loadTrajetCompose(fichierLoad, fichierLoad.tellg(), nbTrajet));
					catal.Add(nouveauTrajet);
				}
				else
				{
					for(int i = 0; i < nbTrajet; i++) //On skip les n trajets appartenant au trajet composé
					{
						fichierLoad >> useless >> useless >> useless >> useless; 
					}
				}
			}
		}
	}
	else if(type == CritereType::ON_ARRIVEE)
	{
		const char* ville = va_arg(ap, char*);

		while(categorie != '3')
		{
			fichierLoad >> categorie >> villeDep >> villeArr;
			bool checkLoad = strcmp(ville,villeArr.c_str()) == 0;
			if(categorie == '0')
			{
				fichierLoad >> moyTransport;
				if(checkLoad)
				{
					TrajetSimple *nouveauTrajet = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyTransport.c_str());
					catal.Add(nouveauTrajet);
				}
			}
			else if(categorie == '1')
			{
				fichierLoad >> nbTrajet;
				if(checkLoad)
				{
					TrajetCompose *nouveauTrajet = new TrajetCompose();
					fichierLoad.seekg(nouveauTrajet->loadTrajetCompose(fichierLoad, fichierLoad.tellg(), nbTrajet));
					catal.Add(nouveauTrajet);
				}
				else
				{
					for(int i = 0; i < nbTrajet; i++) //On skip les n trajets appartenant au trajet composé
					{
						fichierLoad >> useless >> useless >> useless >> useless; 
					}
				}
			}
		}
	}
	else if(type == CritereType::ON_BOTH)
	{
		const char* villeD = va_arg(ap, char*);
		const char* villeA = va_arg(ap, char*);

		while(categorie != '3')
		{
			fichierLoad >> categorie >> villeDep >> villeArr;
			bool checkLoad = (strcmp(villeD,villeDep.c_str()) == 0 && strcmp(villeA,villeArr.c_str()) == 0);
			if(categorie == '0')
			{
				fichierLoad >> moyTransport;
				if(checkLoad)
				{
					TrajetSimple *nouveauTrajet = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyTransport.c_str());
					catal.Add(nouveauTrajet);
				}
			}
			else if(categorie == '1')
			{
				fichierLoad >> nbTrajet;
				if(checkLoad)
				{
					TrajetCompose *nouveauTrajet = new TrajetCompose();
					fichierLoad.seekg(nouveauTrajet->loadTrajetCompose(fichierLoad, fichierLoad.tellg(), nbTrajet));
					catal.Add(nouveauTrajet);
				}
				else
				{
					for(int i = 0; i < nbTrajet; i++) //On skip les n trajets appartenant au trajet composé
					{
						fichierLoad >> useless >> useless >> useless >> useless; 
					}
				}
			}
		}
	}
}//--------Fin de Chargement

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

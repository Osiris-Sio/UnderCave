UnderCave
Auteurs :
	Osiris Sio (Louis AMEDRO)
	Lirei
licence CC BY SA

Fonctionnalités : 
	-> combats (affronter/fuir)
	-> inventaire à potions
	-> caractéristiques du personnage
	-> Plusieurs difficultés selon le personnage choisi
	-> 3 ennemis différents
	-> Histoire complète
	-> Fins alternatives


- Comment jouer ? -

Rien de plus simple ! Utiliser uniquement les chiffres et la touche Entrée de votre clavier pour sélectionner et confirmer une action.
(À l'exception de la question où on vous demande de donner un nom à votre personnage. Vous pourrez utiliser n'importe quelle touche)



- Comment lancer UnderCave sur les différents systèmes (Windows/Linux) ? -


! Remarques ! :
	- Ne déplacez pas les fichiers du dossier du jeu en dehors. Veuillez à ne pas toucher l'intérieur du dossier.
	- Si vous n'avez pas de compilateur/débugger C sur votre machine, effectuez la première méthode qui est la plus simple (selon votre système). 
		Sinon, on vous redirige vers ces deux vidéos YouTube selon toujours votre système :
			- Windows : https://www.youtube.com/watch?v=pTtF6TKJpo8
			- Linux (Ubuntu/Debian) : https://www.youtube.com/watch?v=5rSb1dYl_4I


Windows (2 Méthodes) :

	- Lancez directement le jeu en ouvrant le dossier, puis en exécutant/ouvrant le fichier nommé "UnderCave.exe"
	
	OU

	- Récupérez le chemin du dossier source en faisant un clic droit sur le dossier, "Propriétés", puis copiez "Emplacement" 
		(exemple de chemin : C:\Users\OSIRI\Desktop)
	- Ouvrez une Invite de Commande (CMD dans la barre de recherche)
	- Ecrivez "cd" suivi de l'emplacement du dossier suivi également du nom du dossier. Puis appuyez sur la touche Entrer.
		(exemple : cd C:\Users\OSIRI\Desktop\UnderCave)
	- Saisissez la commande suivante :
		gcc main.c -o UnderCave.exe
	- Jouer en entrant cette dernière commande : 
		.\UnderCave.exe


Linux (2 Méthodes) :

	- Ouvrez un Terminal en faisant un clic droit depuis le dossier du jeu. 
	- Puis, lancer le jeu avec la commande :
		./UnderCave
	
	OU

	- Ouvrez un Terminal
	- Dirigez-vous dans le dossier du jeu, où vous l'avez téléchargé, avec les commandes (ou reprendre le premier tiret de la première méthode):
		- cd (pour se déplacer de fichier en fichier) (exemple : cd Bureau)
		- ls (pour voir les fichiers/dossiers où vous êtes) (exemple : ls)
	- Saisissez la commande suivante :
		gcc main.c -o UnderCave
	- Jouer en entrant cette dernière commande : 
		./UnderCave


- Comment lire les textes correctement ? -

Tout d'abord, vous trouvez dans ce dossier, 2 sous-dossiers : 
	-> un contenant les textes en français (fr)
	-> un contenant les textes en anglais (en)

Pour les textes les plus compliqués, exemple : "chapter1.txt", vous retrouverez :
	-> une partie sans espace entre chaque ligne (utiliser dans le code du jeu)
	-> une partie aérée, pour une lecture simple (pour nous humains)

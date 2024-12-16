
logique de creation:
1- lors de la première execution du programme: on crée une base de données master qui contient les infos sur l'admin (hint + le master_password)
2- on a le choix entre ouvrir une db existante ou crée une autre en s'authentifiant(necessaire dans les 2 cas)
3- après l'authentification on peut effectuer les opérations sur les données(creation, suppression, modification ...)
4-lors de la deconnexion crée un fichier json ou ... pour sauvegarder la session (le dernier fichier de données utiliser pour le restaurer lors d'une nouvelle connexion)
# Safe_Password_Manager
Projet de fin de semestre C 2ESGI

📖 Description
PassVault est un gestionnaire de mots de passe open-source conçu dans le cadre d'un projet de fin semestre 2ESGI pour offrir une solution simple, sécurisée et locale pour la gestion de mots de passe. Ce projet utilise GTK pour l'interface graphique, SQLite pour le stockage en base de données, et Libsodium pour le chiffrement, garantissant la protection des données sensibles de l'utilisateur.

### 🛠️ Fonctionnalités
Authentification sécurisée par mot de passe principal
Stockage des mots de passe chiffré avec Libsodium
Gestion simplifiée des entrées (ajout, modification, suppression)
Recherche rapide dans les mots de passe
Fonction de copie sécurisée des mots de passe au presse-papiers
Intégration d'API optionnelle pour vérifier si un mot de passe a été compromis (ex: Have I Been Pwned)
### 🖼️ Interface Utilisateur
L'interface utilisateur est conçue pour être intuitive et minimaliste :

Écran de connexion pour le mot de passe principal
Tableau de bord principal affichant la liste des mots de passe
Fenêtre d'ajout de mot de passe avec génération sécurisée
Paramètres de sécurité pour modifier le mot de passe principal ou activer des vérifications supplémentaires
### 📐 Architecture du Projet
Voici une vue d'ensemble de la structure du code :

src/
main.c : Point d'entrée de l'application
database.c : Gestion de la base de données SQLite (ajout, récupération, suppression de mots de passe)
encryption.c : Fonctions de chiffrement et hachage avec Libsodium
ui.c : Composants de l'interface utilisateur avec GTK
api.c : Connexion API pour vérifier les mots de passe compromis (facultatif)
### ⚙️ Installation
Prérequis
GTK pour l'interface graphique
SQLite pour la base de données
Libsodium pour le chiffrement

``` 


```

```


### 📂 Guide d'Utilisation
Connexion : Lance l'application et entre le mot de passe principal.
Ajouter un mot de passe : Clique sur “Ajouter” pour enregistrer un nouveau mot de passe avec un site associé et génère un mot de passe sécurisé.
Rechercher et copier : Utilise la barre de recherche pour trouver rapidement une entrée, puis clique sur “Copier” pour copier le mot de passe au presse-papiers.
Paramètres : Accède aux paramètres pour modifier le mot de passe principal ou configurer des vérifications avancées.
### 🔒 Sécurité
Chiffrement des mots de passe : Libsodium est utilisé pour protéger les données avant stockage en base de données.
Hachage sécurisé : Le mot de passe principal est haché avant comparaison pour éviter les fuites directes en mémoire.
Option de vérification des mots de passe compromis via une API externe pour sécuriser davantage les comptes.

📝 Licence
Ce projet est sous licence MIT - voir le fichier LICENSE pour plus de détails.

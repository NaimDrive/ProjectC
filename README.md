# Projet - La Guerre des Cultures 

## Auteurs
BENOIT Baptiste

SEDDAR Naïm

## Lancement du jeu
Afin de générer l'exécutable, taper la commande suivante dans le terminal.
```
make
```

Pour lancer le jeu, utiliser la commande suivante. Il est possible de fournir en paramètre un ou plusieurs fichiers de stratégie. Cependant tous les fichiers doivent avoir comme extension **.strat**.
```
./game [fichier1.strat] [fichier2.strat] [...]
```

## Règles du jeu

L'objectif du jeu est de déterminer qui entre l'empire des légumes et l'empire des fruits, domine le **Domaine Cultivé**.

Pour cela, vous allez réaliser une suite de duel opposant un légume et un fruit en combat singulier.<br/>
Au début de chaque duel, les deux camps ont la possibilité d'acheter une arme, une protection et un soin. Mais attention en temps de guerre les prix des équipements sont élevés !

A l'issue de chaque combat, le combattant toujours vivant se verra verser une prime de victoire.<br/>
Le premier camp n'ayant plus d'argent sera déclaré perdant.

Bonne chance et à bientôt dans le **Domaine Cultivé** !

## Guide débutant

Lorsque vous lancer le jeux vous pouvez executer les commandes ci-dessous.

- ***fight v [s] versus f [t]*** : démarre un combat opposant le Légume v au Fruit f. Il est possible d'utiliser une stratégie préalablement en remplaçant s et/ou t par le numéro de la strategie.
- ***show vegetables*** : affiche la liste numérotée des Légumes, où chacun des Légumes est représenté par son nom.
- ***show vegetable*** : i affiche les caractéristiques du Légume ayant l’identifiant i.
- ***show fruits*** : affiche la liste numérotée des Fruits, où chacun des Fruits est représenté par son nom.
- ***show fruit i*** : affiche les caractéristiques du Fruit ayant l’identifiant i.
- ***show weapons*** : affiche la liste numérotée des armes, où chacune des armes est représentée par son nom.
- ***show weapon i*** : affiche les caractéristiques de l’arme ayant l’identifiant i.
- ***show protections*** : affiche la liste numérotée des protections, où chacune des protections est représentée par son nom.
- ***show protection i*** : affiche les caractéristiques de la protection ayant l’identifiant i.
- ***show cares*** : affiche la liste numérotée des soins, où chacun des soins est représenté par son nom.
- ***show care*** : i affiche les caractéristiques du soin ayant l’identifiant i.
- ***help*** : Affiche la liste des commandes disponibles.
- ***exit*** : permet de quitter le jeu, après en avoir demandé la confirmation.


Pendant un combat, vous avez accès à d'autres commandes.

- ***show*** : affiche les détails de l’équipement du champion dont le tour est actuellement joué.
- ***move forward n*** : fait avancer le concurrent en direction de son adversaire de n pas. Si le n n’est pas précisé, alors le concurrent avance de un seul pas.
- ***move backward n*** : fait reculer le concurrent de n pas. Si le n n’est pas précisé, alors le concurrent recule de un seul pas. 
- ***use weapon n*** : permet d’utiliser n fois l’arme sur l’adversaire. Si le n n’est pas précisé, alors elle n’est utilisée qu’une seule fois. 
- ***use protection*** : fait revêtir au champion sa protection, qui reste active pendant le tour suivant de l’adversaire.
- ***use care n*** : permet d’utiliser n fois le soin sur le champion. Si le n n’est pas précisé, alors il n’est utilisée qu’une seule fois. 
- ***help*** : Affiche la liste des commandes disponibles.
- ***end*** : termine le tour du concurrent.

## Problèmes
Malgré de très longues heures de débuggage. Certaines fonctionnalités ne sont pas au point.

Ci-dessous, la liste des fonctionnalités non implémenté :

- La prise en compte des "if" dans les fichiers .strat n'est pas assuré. La prise en compte des "else" n'a pu aboutir, même après plus d'une semaine de débuggage. Toutefois, les commandes sont exécutées en ignorant les "if".

- Lorsque les deux joueurs utilisent la même strategie durant le même affrontement, il s'avère de que le camps des fruits écrase le tour des légumes (il n'y a que les fruits qui jouent). Malgré la séparation des stratégie utilisées (via des copies), le problème persiste.

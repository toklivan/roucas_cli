# roucas_cli - SPEC (v1)

## Pitch 

Un outil en ligne de commande pour gerer un stock de produits (ajout, vente, reassort), sauvegarde dans un fichier CSV, avec affichage lisible dans le terminal.

## Public cible

Petits commerces / usage perso / projet portfolio C

## Commandes v1

- add       : ajouter un produit
- list      : afficher tous les produits
- sell      : enregistrer une vente (decrementer le stock)
- restock   : reassortir un produit
- low       : afficher les produits sous le seuil d'alerte

## Donnees d'un produit

- id (string, unique)
- name (string)
- category (string)
- buy_price (float)
- sell_price (float)
- stock (int)
- low_threshold (int)

## Stockage

- CSV (un fichier unique)

## Regles

- L'identifiant d'un produit est unique.
- Le stock ne peut jamais devenir negatif.
- Toute erreur affiche un message clair et retourneun code different de 0.
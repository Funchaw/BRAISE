# Premier prototype UE5 — définition de portée

> Rappel : ce document définit *quoi* prototyper, pas *comment coder*.
> Aucune implémentation ne démarre avant validation de ce périmètre.
> Priorité absolue : **GAMEPLAY > GRAPHISMES**.

## Objectif du prototype

Valider en jouable, avec des formes simples (cubes/capsules/plans), que le
noyau de sensations de *BRAISE* fonctionne : maîtrise aérienne précise,
risque/récompense de la jauge de chaleur, satisfaction du tir/destruction,
premier mini-boss lisible.

Le prototype ne doit **pas** chercher à prouver la direction artistique,
le scénario, ou le contenu — seulement le gameplay.

## Contenu du prototype (périmètre fermé)

1. **Joueur**
   - déplacement libre 2D (plan XY ou XZ selon l'axe de scroll retenu),
     avec inertie légère (accélération/décélération, pas de "collé au stick") ;
   - vitesse joueur nettement supérieure à la vitesse de défilement.
2. **Tir**
   - tir principal automatique à cadence fixe, projectile à vitesse modérée ;
   - jauge de chaleur qui monte en tirant, tir plus puissant à jauge haute,
     "surchauffe" temporaire au-delà d'un seuil (fenêtre de vulnérabilité).
3. **Ennemis (2 archétypes suffisent)**
   - un ennemi à trajectoire simple (ligne/sinusoïde) sans tir ;
   - un ennemi qui tire, avec un "tell" visuel avant l'attaque (fiche
     mécanique 3).
4. **Projectiles & collisions**
   - projectiles joueur et ennemi, détection de collision, dégâts appliqués.
5. **Destruction**
   - mort d'ennemi = petit effet (placeholder Niagara basique), pas besoin
     de particules définitives.
6. **Score**
   - compteur simple à l'écran, points par ennemi détruit.
7. **Premier power-up**
   - un seul, ramassable, qui modifie un paramètre existant (ex : cadence
     de tir ou seuil de surchauffe) — pas de deuxième noyau complet à ce
     stade.
8. **Premier mini-boss**
   - une forme simple (grande capsule/cube) avec 2 phases minimum :
     - phase 1 : pattern d'attaque simple + point faible visible ;
     - phase 2 (déclenchée à un seuil de vie) : pattern légèrement modifié,
       pour valider la mécanique "corruption visible" de la fiche 5 (même
       en placeholder : changement de couleur suffit à ce stade).

## Explicitement hors périmètre du prototype

- systèmes de noyaux/formes multiples (fiche 1 complète) ;
- narration, dialogues, cinématiques ;
- musique/son définitifs (un placeholder minimal suffit) ;
- menus, options, sauvegarde ;
- plusieurs niveaux — un seul segment de test (2-3 minutes de jeu) suffit ;
- direction artistique finale.

## Critères de validation du prototype

Le prototype sera jugé réussi si, en jouant :

- le déplacement est immédiatement agréable sans réglage fin (feel de
  base correct avant tuning) ;
- la jauge de chaleur crée un vrai dilemme perceptible ("est-ce que je
  pousse le tir ou je me protège ?") ;
- détruire un ennemi est satisfaisant même avec des formes simples ;
- le mini-boss est lisible : on comprend son pattern et son point faible
  sans explication textuelle.

Si un de ces points échoue, on itère sur le prototype avant d'aller plus
loin — pas de passage à la production tant que ces 4 critères ne sont pas
validés en test.

## Ce que ce document ne couvre pas encore

- structure exacte des classes/Blueprints (viendra avec le lancement du
  développement, section "Architecture UE5" du plan global) ;
- choix Blueprint vs C++ par système (décidé système par système, au
  moment de l'implémenter) ;
- configuration technique cible (FPS, résolution, config mini/recommandée).

# Analyse du jeu de référence (shoot'em up Amiga, style *Agony*)

> **Statut des sources** : aucun fichier Amiga n'a été fourni dans ce dépôt.
> Cette analyse s'appuie sur la structure générale du genre "horizontal
> shoot'em up atmosphérique" de l'ère Amiga (1990-1993) et sur les
> caractéristiques publiquement connues de ce type de jeu (défilement
> horizontal, créature volante transformable, univers biomécanique/onirique,
> bande-son atmosphérique forte). Aucune donnée propriétaire (sprite, code,
> texte, musique) n'est reproduite ici — uniquement des principes de design.
> Si vous déposez des fichiers dans `reference/`, je peux affiner ces
> observations avec plus de précision.

## 1. Gameplay — inventaire des systèmes

| Système | Observation générale (genre + référence) |
|---|---|
| **Déplacement** | Vol libre 8 directions sur un plan 2D, défilement horizontal forcé. Inertie légère à modérée : le personnage n'est pas "collé" au stick, il y a un délai d'accélération/décélération qui donne du poids sans nuire à la précision. |
| **Vitesse** | Vitesse de déplacement du joueur nettement supérieure à la vitesse de défilement du décor → sensation de contrôle total sur le positionnement, contrairement aux shmups verticaux très rapides. |
| **Tir principal** | Tir automatique ou semi-automatique à cadence moyenne, portée courte à moyenne, projectile lent-moyen. La lenteur du projectile oblige à anticiper la position de l'ennemi plutôt qu'à "spammer". |
| **Transformation / formes** | Mécanique signature : le personnage change de forme via power-ups, chaque forme ayant un pattern de tir et une silhouette de collision différents. Ce n'est pas un simple "level up" d'arme — c'est un changement d'identité de jeu. |
| **Ennemis** | Patterns de déplacement sinusoïdaux/organiques plutôt que rigides ; vagues scriptées liées au scroll, avec des points d'apparition cachés (hors écran) qui récompensent la mémorisation. |
| **Boss** | Grands sprites multi-parties, souvent avec un point faible identifiable visuellement (pas de barre de vie explicite dans beaucoup de jeux de l'époque — le feedback vient de l'animation/couleur). |
| **Power-ups** | Drops d'ennemis ou de décor destructible ; effet immédiat et lisible (nouvelle forme, nouvelle arme, bouclier). Peu ou pas de gestion d'inventaire — tout est instantané. |
| **Collisions** | Hitbox du joueur plus petite que le sprite visible (convention arcade), hitbox ennemi souvent généreuse pour favoriser la sensation d'impact du tir. |
| **Dégâts / vies** | Système de vies + jauge d'énergie/points de vie sur le vaisseau/la créature ; mort = perte de position au dernier checkpoint, pas de mort en un coup généralisée (contrairement aux shmups "bullet hell" japonais). |
| **Checkpoints** | Peu nombreux, positionnés avant les boss — la sanction d'un échec est significative (on rejoue une portion de niveau), ce qui crée de la tension. |
| **Scoring** | Score au kill + bonus de destruction totale/combo de zone, mais secondaire au "survivre et avancer" — le scoring de l'époque sert surtout la rejouabilité et le high-score, pas la stratégie moment-à-moment. |
| **Difficulté** | Courbe en dents de scie : montée progressive intra-niveau, pic sur le boss, redescente légère en début de niveau suivant pour souffler. |
| **Progression** | Linéaire, niveau par niveau, sans retour en arrière — la progression du joueur est portée par l'habileté acquise, pas par un système méta. |
| **Rythme** | Alternance de phases de "traversée" (exploration/tension, peu d'ennemis, ambiance sonore) et de phases de "confrontation" (vagues denses, action pure). C'est cette respiration qui distingue un bon shmup atmosphérique d'un simple tir continu. |

## 2. Game feel — pourquoi c'était amusant

- **Sensation de vitesse** : relative, pas brute. Le joueur va vite *par rapport à l'écran*, pas par rapport au décor qui défile à vitesse constante et modérée — ça laisse le temps de lire les patterns tout en donnant une impression de maîtrise aérienne.
- **Sensation de puissance** : vient moins de la cadence de tir que de la **transformation**. Chaque nouvelle forme est un power fantasy différent, pas juste "plus de dégâts". C'est un levier émotionnel plus fort qu'un simple upgrade numérique.
- **Tension** : générée par l'ambiance sonore/visuelle (ton sombre, biomécanique, presque horrifique) plus que par la difficulté brute — le jeu fait peur/inquiète avant de faire mourir.
- **Anticipation** : les ennemis ont des tells (animation d'avant-tir, apparition annoncée par le son/le décor) qui récompensent l'attention plutôt que le réflexe pur.
- **Récompense** : la destruction d'un ennemi ou d'un élément de décor est immédiatement gratifiante visuellement (explosion, débris, drop) — feedback court et net.
- **Feedback visuel/sonore** : hit-flash, secousse légère, son de tir "qui claque" — le jeu vend l'impact du tir indépendamment de la difficulté du niveau.
- **Satisfaction de la destruction** : renforcée par le fait que le décor lui-même est souvent partiellement destructible ou réactif, ce qui donne l'impression que le monde entier répond au joueur, pas seulement les ennemis désignés.

**Pourquoi c'était amusant, en une phrase** : le jeu combine une maniabilité précise et "pardonnante" (vitesse joueur > vitesse scroll, inertie légère) avec une identité visuelle et sonore forte qui transforme un shoot'em up classique en expérience presque cauchemardesque/hypnotique — le gameplay est simple, l'ambiance fait le reste.

## 3. Ce qui a vieilli

| Élément | Pourquoi ça date | Impact aujourd'hui |
|---|---|---|
| Vies + game over sec, peu de checkpoints | Conçu pour l'ère arcade / cartouche (rejouer = normal) | Frustrant pour un public moderne habitué à des courbes d'apprentissage plus douces |
| Pas de lisibilité de barre de vie boss | Contrainte technique (mémoire, résolution) | Le joueur moderne attend un feedback de progression clair |
| Scoring peu intégré au moment-à-moment | Le score était un objectif "méta" (arcade high-score), pas un outil de decision-making | Aujourd'hui le scoring doit motiver des choix de risque en temps réel |
| Progression strictement linéaire sans méta-progression | Norme de l'époque (pas de sauvegarde entre sessions dans beaucoup de cas) | Le marché indé moderne attend au moins un peu de progression entre les runs (déblocages, upgrades permanents ou run-based) |
| Difficulté binaire (on survit ou on meurt, peu d'options d'accessibilité) | Pas de concept d'accessibilité à l'époque | Standard actuel = plusieurs niveaux de difficulté, remapping, assistances |
| Un seul type de contrôle pensé (joystick 1 bouton) | Matériel de l'époque | Aujourd'hui : clavier/souris, manette, Steam Input, avec des inputs plus riches (dash, arme secondaire, etc.) |

## 4. Modernisations proposées (vue d'ensemble)

Le détail mécanique par mécanique est dans
[`02-fiches-mecaniques.md`](./02-fiches-mecaniques.md). Les grands axes :

1. **Checkpoints plus généreux + difficultés sélectionnables**, sans supprimer la tension (on garde des runs "arcade" en option pour les puristes).
2. **Scoring transformé en outil de risque/récompense actif** (multiplicateurs liés à la prise de risque, pas seulement au kill count).
3. **La transformation devient le pilier du kit d'innovations** du nouveau jeu plutôt qu'un simple power-up temporaire (voir concepts, section suivante).
4. **Lisibilité moderne des boss** (phases claires, tells lisibles, feedback de dégâts) sans perdre le mystère visuel qui faisait leur force.
5. **Rythme traversée/confrontation** conservé tel quel — c'est une des forces intemporelles du genre, elle n'a pas besoin d'être modernisée, juste bien exécutée en UE5 (éclairage, son spatialisé, Niagara).

➡️ Suite : [`02-fiches-mecaniques.md`](./02-fiches-mecaniques.md)

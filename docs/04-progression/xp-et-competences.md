# Système XP & Compétences

Système d'amélioration aléatoire façon survivors-like, adapté à l'identité
de Braise (aucune valeur/texte repris d'un jeu existant — structure
générique du genre, contenu original).

## Boucle

1. Détruire un Cendreux → il lâche un ou plusieurs **Éclats de Braise**
   (XP), attirés vers le joueur dans un rayon (magnétisme progressif,
   pas de ramassage manuel précis requis — garde le focus sur le combat).
2. Un seuil d'XP atteint → **montée de niveau** → le jeu propose
   **3 compétences aléatoires** parmi le pool disponible (pondéré par
   rareté et par ce que le joueur possède déjà, voir règles de tirage).
3. Le joueur choisit une compétence (rythme non bloquant : le temps peut
   continuer ou se figer selon le mode de difficulté — voir
   `docs/02-prototype/` pour le prototype, décision finale en vertical
   slice).

## Catégories de compétences

| Catégorie | Effet type | Exemple (à affiner en vertical slice) |
|---|---|---|
| **Feu** (puissance de tir) | Augmente dégâts, cadence, nombre de projectiles | "Braise Jumelle" — tir principal envoie un second projectile décalé |
| **Chaleur** (interaction avec la jauge signature) | Modifie le comportement de la jauge de chaleur | "Combustion Lente" — la jauge descend plus lentement mais monte aussi plus lentement (profil "discret") |
| **Mobilité** | Vitesse, esquive, dash | "Pas de Cendre" — courte esquive invulnérable à cooldown |
| **Défense** | Réduction de dégâts, régénération | "Écorce Ignée" — régénère un point de vie après X secondes sans dégâts |
| **Utilitaire** | Portée, magnétisme XP, interaction biome | "Attraction" — augmente le rayon de collecte des Éclats de Braise |

## Rareté (tirage pondéré)

| Rareté | Poids relatif | Ton visuel | Nom de palier |
|---|---|---|---|
| Commune | 60% | Orange terne | Tison |
| Rare | 30% | Orange vif | Flamme |
| Légendaire | 10% | Blanc incandescent | **Braise** (clin d'œil au titre) |

Une compétence déjà maximisée (si elle a des rangs) sort du pool de
tirage pour laisser de la place aux autres — évite la frustration de
propositions inutiles en fin de run.

## Synergie avec la jauge de chaleur (différenciateur, voir GDD v2)

Certaines compétences "Chaleur" créent des builds radicalement différents :

- **Profil "Discret"** : compétences qui réduisent l'émission de lumière
  à jauge égale → progression plus lente mais vagues moins dures.
- **Profil "Brasier"** : compétences qui amplifient l'effet de la jauge
  haute (dégâts, zone d'effet) au prix d'une visibilité accrue → risque
  maximal, croissance rapide.

Le pool de compétences doit toujours contenir au moins une option de
chaque profil disponible en montée de niveau, pour que le choix de build
reste réel du début à la fin d'un run.

## Règles de conception pour toute nouvelle compétence

- Effet lisible en une phrase (pas de texte de règle à rallonge en jeu).
- Impact visible immédiatement en jeu (changement de VFX/pattern de tir,
  pas seulement un nombre qui change en interne).
- Jamais une compétence qui *retire* du fun sans compensation claire
  (ex : pas de malus pur) — même les compromis "Discret vs Brasier" sont
  des choix de style, pas des punitions.

## Ce qui reste à trancher en vertical slice (pas en prototype)

- Nombre exact de compétences au lancement (viser 15-20 pour le vertical
  slice, pas plus au prototype).
- Système de rangs par compétence (I/II/III) ou compétences à effet unique.
- Interaction exacte avec le Codex/la progression méta (une compétence
  débloquée en méta-progression rejoint-elle le pool de base ?).

➡️ Retour au sommaire : [`../../README.md`](../../README.md)

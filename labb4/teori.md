#1. Lösning till ja-instans.

```
#Roll -> Skådespelare
1
3
1
2
4
4

# Scen -> Roll
1 2 6
2 3 5
2 4 6
2 3 6
1 6
```

#2. Visa att det är NP.

Det är NP om och endast om det finns en algoritm som på polynomisk tid
kan verifiera om lösningen är korrekt eller ej.

Algoritm för att verifiera att lösningen är korrekt:

```
1. För varje scen skapa ett träd T med scenen som rot.
2. Besök alla löv och spara antal förekomster av varje skådespelare i en lista L. (O (e log e))
3. Verifiera att ingen skådespelare finns två eller fler gånger i T. (O(v))
4. Besök alla löv igen. Ifall p1 finnes i T så svara med "inkorrekt lösning" om p2 sedan finnes. (O(e log e))
    Analogt, om p2 först finnes svara med "inkorrekt lösning" om p1 sedan finnes.
5. Svara med "korrekt lösning".
```

#3. Transformera nej-instans

2 till skådespelare behövs.

```
3
5
4
2
1

1 2
1 2
1 3 4
3 5
2 3 5
```

#4. Vilken är den minsta möjliga produktion som löser kriterierna?

```
1
2
3

1 3
2 3
```

#5. Roller i två grupper

3 skådespelare behövs minst.

Se uppgift 4 för minsta produktion. I detta fall är roll 1 och roll 2 i samma grupp
och roll 3 i den andra gruppen.

Om vi ignorerar kriteriet att inga monologer får förekomma så behövs då minst 2 skådespelare istället.

#6. Jämför film a och film b

I film a så kan rollerna 4, 7 och 12 inte finnas i spelas av samma
skådespelare. Detta är detsamma som att 4 och 7 inte kan spelas av samma
skådespelare, 7 och 12 inte kan spelas av samma skådespelare och 4 och 12 inte
kan spelas av samma skådespelare.

I film b så kan roll 4 och 7 inte spelas av samma skådespelare eftersom scen 1 finns.
7 och 12 kan heller inte spelas av samma skådespelare eftersom scen 2 finns.
4 och 12 inte kan spelas av samma skådespelare eftersom scen 3 finns.

Analogt kan sägas om p1 och p2, alltså har dessa två filmer identiskt resultat.

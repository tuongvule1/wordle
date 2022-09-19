# Wordle
We try to find some good starter words for the game [Wordle](https://www.nytimes.com/games/wordle/index.html). Using the list of allowed guesses and possible answers, we find the words with highest expected value of it scores (assuming the answer is chosen randomly among the list of possible answers), where the score is calculated as follow: each yellow gives 2 score and each green gives 3.  
Lowest scoring words, which are useful for [Antiwordle](https://www.antiwordle.com/), are also printed.  
Other useful informations are printed: letters ranked by number of words they appear in.  
For each position, print out the letters ranked by their appearance in that position.  
For each letter, print out the 5 positions ranked by its appearance in that position.

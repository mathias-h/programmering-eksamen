module Main where

safeTail [] = Nothing
safeTail xs = Just $ tail xs

main :: IO()
main = do
    {- 
    jeg har brugt en type constraint for at specificere en type der er a kinden Show, så print kan vise den.
    hvis man ikke gør dette ville print få en array af typen [a] hvor "a" ikke er af kinden Show, som print funktionen påkræver.
    -}
    print $ safeTail ([]::([Int]))
    print $ safeTail [1,2,3]

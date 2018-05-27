module Main where

import Data.List

numberToDanish :: Int -> String
numberToDanish n =
    let names = ["Nul","Et","To","Tre","Fire","Fem","Seks","Syv","Otte","Ni"]
    in intercalate "-" $ map (((!!) names) . \c -> (read [c] :: Int)) (show n)

main :: IO()
main =
    print $ numberToDanish 12039
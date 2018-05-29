module Main where

import Data.Maybe

data Completed = Comp Bool String deriving(Eq, Ord, Show)
data DatabaseItem = DbString String | DbNumber Integer | DbCompleted Completed deriving (Eq, Ord, Show)

theDatabase :: [DatabaseItem]
theDatabase = [
    DbCompleted (Comp True "Hearthstone"),
    DbNumber 9001,
    DbString "Hello, world!",
    DbCompleted (Comp False "Fortnite"),
    DbNumber 42 ]

getValues :: (a -> Maybe b) -> [a] -> [b]
getValues f = map fromJust . filter isJust . map f

getDbString :: DatabaseItem -> Maybe String
getDbString (DbString s) = Just s
getDbString _ = Nothing
filterDbStrings :: [DatabaseItem] -> [String]
filterDbStrings = getValues getDbString

getDbNumber :: DatabaseItem -> Maybe Integer
getDbNumber (DbNumber n) = Just n
getDbNumber _ = Nothing
sumDbNumbers :: [DatabaseItem] -> Integer
sumDbNumbers = sum . getValues getDbNumber

getCompleted :: DatabaseItem -> Maybe String
getCompleted (DbCompleted (Comp f s)) =
    if f == True then Just s
    else Nothing
getCompleted _ = Nothing
dbCompleted :: [DatabaseItem] -> [String]
dbCompleted = getValues getCompleted

main :: IO()
main = do
    print $ (filterDbStrings theDatabase)
    print $ sumDbNumbers theDatabase
    print $ dbCompleted theDatabase
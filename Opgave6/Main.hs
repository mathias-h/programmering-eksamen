module Main where

data Completed = Comp Bool String deriving(Eq, Ord, Show)
data DatabaseItem = DbString String
    | DbNumber Integer
    | DbCompleted Completed
    deriving (Eq, Ord, Show)
theDatabase :: [DatabaseItem]
theDatabase =
    [ DbCompleted (Comp True "Hearthstone")
    , DbNumber 9001
    , DbString "Hello, world!"
    , DbCompleted (Comp False "Fortnite")
    , DbNumber 42
    ]

isDbString :: DatabaseItem -> Bool
isDbString (DbString _) = True
isDbString _ = False
filterDbStrings :: [DatabaseItem] -> [String]
filterDbStrings = map (\(DbString s) -> s) . filter isDbString

isDbNumber :: DatabaseItem -> Bool
isDbNumber (DbNumber _) = True
isDbNumber _ = False
sumDbNumbers :: [DatabaseItem] -> Integer
sumDbNumbers = sum . map (\(DbNumber n) -> n) . filter isDbNumber


isDbCompleted :: DatabaseItem -> Bool
isDbCompleted (DbCompleted (Comp c _)) = c
isDbCompleted _ = False
dbCompleted :: [DatabaseItem] -> [String]
dbCompleted = map (\(DbCompleted (Comp _ s)) -> s) . filter isDbCompleted

main :: IO()
main = do
    print $ (filterDbStrings theDatabase)
    print $ sumDbNumbers theDatabase
    print $ dbCompleted theDatabase
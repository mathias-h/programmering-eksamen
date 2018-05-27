module Main where

data Or a b = First a | Second b deriving (Eq, Show)

instance Functor (Or b) where
    fmap f (Second a) = Second (f a)
    fmap _ (First a) = First a

main :: IO()
main = do
    print $ fmap (+1) (First 1)
    print $ fmap (+1) (Second 1 :: Or Int Int)
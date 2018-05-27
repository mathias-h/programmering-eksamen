module Main where

data Expr = Lit Integer | Add Expr Expr deriving (Show)

e = Add (Add (Lit 1) (Add (Lit 2) (Lit 3))) (Lit 4)

eval :: Expr -> Integer
eval (Lit n) = n
eval (Add a b) = (eval a) + (eval b)

main :: IO()
main = do
    print e
    print $ eval e
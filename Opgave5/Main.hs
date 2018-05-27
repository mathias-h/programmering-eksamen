module Main where

data Price = Price Int deriving (Show)
data Manufacturer = Tesla | Ferrari | Renault | Airbus deriving (Show)
data Vehicle = Car Manufacturer Price | Plane Manufacturer deriving (Show)

isCar :: Vehicle -> Bool
isCar (Car _ _) = True
isCar _ = False

isPlane :: Vehicle -> Bool
isPlane (Plane _) = True
isPlane _ = False

areCars :: [Vehicle] -> [Bool]
areCars = map isCar

getManu :: Vehicle -> Manufacturer
getManu (Car m _) = m
getManu (Plane m) = m

main :: IO()
main =
    let electric = Car Tesla (Price 700000)
        sport = Car Ferrari (Price 2000000)
        family = Car Renault (Price 230000)
        sas = Plane Airbus
    in do 
        print electric
        print sport
        print family
        print sas
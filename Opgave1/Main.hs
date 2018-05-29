module Main where
    
main :: IO ()
main = do
    let mySqr = [x^2 | x <- [1..5]]
    let myCube = [y^3 | y <- [1..5]]
    print $ zip mySqr myCube
    print $ zip (filter (< 50) mySqr) (filter (< 50) myCube)

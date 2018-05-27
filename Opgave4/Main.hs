eft :: (Eq a, Enum a) => a -> a -> [a]
eft a b
    | a == b = []
    | otherwise = a : eft (succ a) b

eftOrd :: Ordering -> Ordering -> [Ordering]
eftOrd = eft
eftInt :: Int -> Int -> [Int]
eftInt = eft
eftChar :: Char -> Char -> [Char]
eftChar = eft
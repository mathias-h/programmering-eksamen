module Main where

import Data.Maybe

data BinaryTree a = Node a (Maybe (BinaryTree a)) (Maybe (BinaryTree a)) | Leaf a

instance (Show a) => Show (BinaryTree a) where
    show (Leaf v) = "Leaf(" ++ (show v) ++ ")"
    show (Node v l r) = 
        let left = if isJust l then show $ fromJust l else "Nothing"
            right = if isJust r then show $ fromJust r else "Nothing"
        in "Node(" ++ show v ++ "," ++ left ++ "," ++ right ++ ")"

insert :: (Ord a) => BinaryTree a -> a -> BinaryTree a
insert (Leaf i) v =
    if v < i
        then Node i (Just $ Leaf v) Nothing
        else Node i Nothing (Just $ Leaf v)
insert (Node v l r) nv =
    if nv < v
        then Node v (insertValue l nv) r
        else Node v l (insertValue r nv)
    where
        insertValue :: (Ord a) => Maybe (BinaryTree a) -> a -> Maybe (BinaryTree a)
        insertValue (Just s) v = Just $ insert s v
        insertValue (Nothing) v = Just $ Leaf v

fromList :: (Ord a) => [a] -> (BinaryTree a)
fromList (x:xs) = _fromList xs (Leaf x)
fromList [] = error "you cannot make a binary tree from an empty list"
_fromList :: (Ord a) => [a] -> (BinaryTree a) -> (BinaryTree a)
_fromList (x:xs) t = _fromList xs (insert t x)
_fromList [] t = t
-- TODO fix

toList :: (BinaryTree a) -> [a]
toList (Node v (Just l) (Just r)) = (toList l) ++ [v] ++ (toList r)
toList (Node v (Nothing) (Just r)) = v : (toList r)
toList (Node v (Just l) (Nothing)) = (toList l) ++ [v]
toList (Node v Nothing Nothing) = [v]
toList (Leaf v) = [v]

tree = Node 4 (Just $ Node 2 (Just $ Leaf 1) (Just $ Leaf 3)) (Just $ Node 6 Nothing (Just $ Leaf 8))
charTree = Node 'd' (Just $ Node 'b' (Just $ Leaf 'a') (Just $ Leaf 'c')) (Just $ Node 'f' Nothing (Just $ Leaf 'g'))

main :: IO()
main = do
    print tree
    print $ insert tree 5
    print $ insert (insert tree 5) 7
    print $ fromList [3,6,2,4,1,8]
    print $ toList tree
    print $ charTree
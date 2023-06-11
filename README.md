# Magical Iterators

This project include:
1. User-defined container class named "MagicalContainer" that can store integers representing mystical elements. There are methods for adding elements, removing elements, and retrieving the size of the container. 

2. Three custom iterator classes named "AscendingIterator", "SideCrossIterator", and "PrimeIterator" - allow traversal of elements in the MagicalContainer class in ascending order, cross order, and prime numbers only, respectively. 

### Each iterator supports the following operations:
 
• Default constructor

• Copy constructor

• Destructor

• Assignment operator

• Equality comparison (operator==)

• Inequality comparison (operator!=)

• GT, LT comparison (operator>, operatorn<) all comparison operators only valid for iterators of the same type of order and should compair the location of the iterator in the container and not the element inside. Example bellow. Using operators on iterators of differant type or differant containers should throw an examtion.

• Dereference operator (operator*)

• Pre-increment operator (operator++)

• begin(type): Returns the appropriate iterator (ascending, cross, or prime) pointing to the first element of the container based on the specified type.

• end(type): Returns the appropriate iterator (ascending, cross, or prime) pointing one position past the last element of the container based on the specified type.

#### For example:
#### say our container contains the numbers 1,2,4,5,14 the iterators will return the elements in the following order:

• Ascending: 1,2,4,5,14 - operator> should return true on 5>2, 14>1

• prime: 2,5 - operator> should return true on 5>2 

• cross: 1,14,2,5,4 (one from the start then one from the end) - operator> should return true on 5>14, 2>1, 4>14

### All iterators work in O(1) in both memory and time complexity. 

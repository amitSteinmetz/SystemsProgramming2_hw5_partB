#include "MagicalContainer.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

// Help func
bool isPrime(const int element)
{
    /* Check if the element is divisible by any number from 2 up to its square root */

    bool is_prime = true;

    if (element < 2) is_prime = false;

    for (int i = 2; i * i <= element; i++)
    {
        if (element % i == 0)
        {
            is_prime = false;
            break;
        }
    }
    
    return is_prime;
}

/* Ctors */

MagicalContainer::MagicalContainer() // No need to init the vector, it is initialized automatcily to default value
{}

MagicalContainer::AscendingIterator::AscendingIterator()
{}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) 
: pContainer(&container), pRunner(container.vec.data())
{}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
: pContainer(other.pContainer), pRunner(other.pRunner)
{}

MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator&& other) noexcept
: pContainer(other.pContainer), pRunner(other.pRunner)
{}

MagicalContainer::SideCrossIterator::SideCrossIterator()
{}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) 
: pContainer(&container), pRunner(container.vec.data()), index(0), low(1), high(container.size() - 1)
{}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
: pContainer(other.pContainer), pRunner(other.pRunner), index(other.index), low(other.low), high(other.high)
{}

MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator&& other) noexcept
: pContainer(other.pContainer), pRunner(other.pRunner), index(other.index), low(other.low), high(other.high)
{}

MagicalContainer::PrimeIterator::PrimeIterator()
{}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) 
: pContainer(&container), prime_it(container.prime_vec.begin()) 
{}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
: pContainer(other.pContainer), prime_it(other.prime_it)   
{}

MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator&& other) noexcept
: pContainer(other.pContainer), prime_it(other.prime_it)  
{}

/* Dtors */

MagicalContainer::AscendingIterator::~AscendingIterator()
{}

MagicalContainer::SideCrossIterator::~SideCrossIterator()
{}

MagicalContainer::PrimeIterator::~PrimeIterator()
{}

// ------------------------------------------------------------- //

/* Methods */

/* MagicalContainer class */ 

void MagicalContainer::addElement(const int element)
{
    // Push the element to the vector
    vec.push_back(element);

    // Sort the vector in ascending order
    std::sort(vec.begin(), vec.end());

    // Delete from prime's vector all the pointers - because the original vector allocated new addresses to it's elements
    prime_vec.clear();
    
    // Check all the prime's in the original vector and add them to prime's vector
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        if (isPrime(*it)) prime_vec.push_back(&(*it));
    }

    // Sort prime's vector
    std::sort(prime_vec.begin(), prime_vec.end());
}

void MagicalContainer::removeElement(int element)
{
    // If container is empty
    if (vec.size() == 0) throw "Container is empty!";

    /* Find the position of the element (assuming element occurs only once in the vector) */ 

    bool erased = false;

    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        if (*it == element)
        {
            vec.erase(it);
            erased = true;

            // Delete all the pointers in prime's vector - because the original vector allocated new addresses to it's elements
            prime_vec.clear();

             // Check all the prime's in the original vector and add them to prime's vector
            for (auto it = vec.begin(); it != vec.end(); it++)
            {
                if (isPrime(*it)) prime_vec.push_back(&(*it));
            }

            break;
        }
    }   

    if (!erased) throw runtime_error("Removing non-exist element!");
}

int MagicalContainer::size()
{
    return vec.size();
}

/* AscendingIterator inner class */ 

// Access
int& MagicalContainer::AscendingIterator::operator*() const
{
    return *pRunner;
}

// prefix
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++()
{
    // If iterator is null
    if (pRunner == nullptr) throw runtime_error("can't increase nullptr!");

    // If the iterator got to the last element
    else if (pRunner == (&pContainer->vec[0] + pContainer->size() - 1)) pRunner = nullptr;

    // Promote pRunner to the next element (the container is already in ascending order)
    else ++pRunner;
    
    return *this;
}

// Comparison
bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const
{
    return (pRunner == other.pRunner);
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const
{
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const
{
    if (!pRunner || !other.pRunner) return false;

    return *pRunner < *other.pRunner;
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const
{
    if (!pRunner || !other.pRunner) return false;

    return *pRunner > *other.pRunner;
}

// Assignment 
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other)
{
    // If iterators are pointing at different containers
    if (pContainer != other.pContainer) throw runtime_error("Iterators are pointing at different containers!");

    /* Copy "other" iterator fields to "this" object */ 
    pRunner = other.pRunner;

    return *this;
}

// Move assignment 
MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(AscendingIterator&& other) noexcept
{
    /* Transfer */

    if (this != &other)
    { 
        pContainer = other.pContainer;
        pRunner = other.pRunner;
    }

    return *this;
}

// Begin, end
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const
{
    /* Begin main idea is to set pRunner to first element of the container */

    AscendingIterator it;

    it.pRunner = &pContainer->vec[0];  
    it.pContainer = pContainer;

    return it;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    /* "End" main idea is to set pRunner to one position after last element (null) */

    AscendingIterator it;

    it.pRunner = nullptr;
    it.pContainer = pContainer;

    return it;
}

/* SideCrossIterator inner class */ 

// Access
int& MagicalContainer::SideCrossIterator::operator*() const
{
    return *pRunner;
}

// prefix
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
{
    // If iterator is null
    if (pRunner == nullptr) throw runtime_error("can't increase nullptr!");

    // if pRunner point to the middle of the container - this is the last element to iterate
    if (pRunner == (&pContainer->vec[0] + pContainer->size()/2)) pRunner = nullptr;

    /* 
    The idea:
        "index" represnt the current position that pRunner point on the container
        "low" represent the left side of the container
        "high" represent the right side of the container

        If the index is even - pRunner should point to left side (low)
        and if index is odd - pRunner should point to right side (high)
    */

    else 
    {
        ++index;
        
        if (index % 2 == 0)
        {
            pRunner = &pContainer->vec[static_cast<std::vector<int>::size_type>(low)];
            low++; 
        }  
        else
        {
            pRunner = &pContainer->vec[static_cast<std::vector<int>::size_type>(high)];
            high--; 
        }
    }
    
    return *this;
}

// Comparison
bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const
{
    return (pRunner == other.pRunner);
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const
{
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const
{
    // Checking which iterator has higher pRunner position (represented by index)
    return index < other.index;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const
{
    // Checking which iterator has higher pRunner position (represented by index)
    return index > other.index;
}

// Assignment 
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
{
    // If iterators are pointing at different containers
    if (pContainer != other.pContainer) throw runtime_error("Iterators are pointing at different containers!");

    /* Copy "other" fields to "this" object */ 

    pRunner = other.pRunner;
    index = other.index;
    low = other.low;
    high = other.high;

    return *this;
}

// Move assignment 
MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(SideCrossIterator&& other) noexcept
{
    /* Transfer */
    
    if (this != &other)
    { 
        pContainer = other.pContainer;
        pRunner = other.pRunner;
        index = other.index;
        low = other.low;
        high = other.high;
    }

    return *this;
}

// Begin, end
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const
{
    /* Begin main idea is to set pRunner to first element of the container */

    SideCrossIterator it;

    it.pRunner = &pContainer->vec[0];  
    it.pContainer = pContainer;
    it.high = pContainer->size() - 1;
    it.low = 1;
    it.index = 0;

    return it;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    /* "End" main idea is to set pRunner to one position after last element (null) */

    SideCrossIterator it;

    it.pRunner = nullptr;
    it.pContainer = pContainer;

    return it;
}

/* PrimeIterator inner class */ 

// Access
int& MagicalContainer::PrimeIterator::operator*() const
{
    return **prime_it;
}

// prefix
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++()
{
    // If there's no prime vector
    if (pContainer->prime_vec.size() == 0) throw runtime_error("there's no primes!");

    // If iterator is null
    if (*prime_it == nullptr) throw runtime_error("can't increase null!");

    // If the iterator got to the last element
    if (*prime_it == pContainer->prime_vec.back()) prime_it = pContainer->prime_vec.end();

    else ++prime_it;

    return *this;
}

// Comparison
bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const
{
    return (prime_it == other.prime_it);
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const
{
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const
{
    if (pContainer->prime_vec.size() == 0) return false;
    
    // If iterator is at the end of container and the other isn't
    if (!*prime_it && *other.prime_it) return false;
    else if (*prime_it && !*other.prime_it) return true;

    // If both iterators at the end of container
    if (!*prime_it && !*other.prime_it) return false;

    return **prime_it < **other.prime_it;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const
{
    if (pContainer->prime_vec.size() == 0) return false;

    // If iterator is at the end of container and the other isn't
    if (!*prime_it && *other.prime_it) return true;
    else if (*prime_it && !*other.prime_it) return false;

    // If both iterators at the end of container
    if (!*prime_it && !*other.prime_it) return false;

    return **prime_it > **other.prime_it;
}

// Assignment 
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other)
{
    // If iterators are pointing at different containers
    if (pContainer != other.pContainer) throw runtime_error("Iterators are pointing at different containers!");

    /* Copy "other" fields to "this" object */
    prime_it = other.prime_it;

    return *this;
}

// Move assignment 
MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(PrimeIterator&& other) noexcept
{
    /* Transfer */
    
    if (this != &other)
    { 
        pContainer = other.pContainer;
        prime_it = other.prime_it;
    }

    return *this;
}

// Begin, end
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const
{
    /* Begin main idea is to set pRunner to first element of the container */

    PrimeIterator it;

    it.prime_it = pContainer->prime_vec.begin();  
    it.pContainer = pContainer;

    return it;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    /* "End" main idea is to set pRunner to one position after last element (null) */

    PrimeIterator it;

    it.prime_it = pContainer->prime_vec.end();
    it.pContainer = pContainer;

    return it;
}

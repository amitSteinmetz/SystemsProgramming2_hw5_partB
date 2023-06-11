#pragma once
namespace ariel{};
#include <vector>
#include <memory>

class MagicalContainer
{
    /* Attributes */ 
    std::vector<int> vec;
    std::vector<int*> prime_vec;

    public:

    /* Ctor */
    MagicalContainer();
    
    /* Methods */
    void addElement(int element);
    void removeElement(int element);
    int size();

    /* Inner classes: */ 

    class AscendingIterator
    {
        /* Attributes */
        MagicalContainer* pContainer;
        int* pRunner;
        
        public: 

        /* Ctors */
        AscendingIterator(); // default
        AscendingIterator(MagicalContainer& container); // parameterized
        AscendingIterator(const AscendingIterator& other); // copy
        AscendingIterator(AscendingIterator&& other) noexcept; // move

        /* Dtor */
        ~AscendingIterator();
        
        /* Methods */

        int& operator*() const; // Access
		AscendingIterator& operator++(); // prefix
        AscendingIterator& operator=(const AscendingIterator& other); // Assignment  
        AscendingIterator& operator=(AscendingIterator&& other) noexcept; // Move assignment    
        AscendingIterator begin() const; // Begin
        AscendingIterator end(); // End

        // Comparison
		bool operator==(const AscendingIterator& other) const;
		bool operator!=(const AscendingIterator& other) const;
        bool operator<(const AscendingIterator& other) const;
        bool operator>(const AscendingIterator& other) const;
    };

    class SideCrossIterator
    {
        /* Attributes */
        MagicalContainer* pContainer;
        int* pRunner;
        int index, low, high;
        
        public: 

        /* Ctors */
        SideCrossIterator(); // default
        SideCrossIterator(MagicalContainer& container); // parameterized
        SideCrossIterator(const SideCrossIterator& other); // copy
        SideCrossIterator(SideCrossIterator&& other) noexcept; // move

         /* Dtor */
        ~SideCrossIterator();
        
        /* Methods */

        int& operator*() const; // Access
		SideCrossIterator& operator++(); // prefix
        SideCrossIterator& operator=(const SideCrossIterator& other); // Assignment   
        SideCrossIterator& operator=(SideCrossIterator&& other) noexcept; // Move assignment      
        SideCrossIterator begin() const; // Begin
        SideCrossIterator end(); // End

        // Comparison
		bool operator==(const SideCrossIterator& other) const;
		bool operator!=(const SideCrossIterator& other) const;
        bool operator<(const SideCrossIterator& other) const;
        bool operator>(const SideCrossIterator& other) const;
    };

    class PrimeIterator
    {
        /* Attributes */
        MagicalContainer* pContainer;
        std::vector<int *>::iterator prime_it;

        public: 

        /* Ctors */
        PrimeIterator(); // default
        PrimeIterator(MagicalContainer& container); // parameterized
        PrimeIterator(const PrimeIterator& other); // copy
        PrimeIterator(PrimeIterator&& other) noexcept; // move

        /* Dtor */
        ~PrimeIterator();
        
        /* Methods */

        int& operator*() const; // Access
		PrimeIterator& operator++(); // prefix
        PrimeIterator& operator=(const PrimeIterator& other); // Assignment       
        PrimeIterator& operator=(PrimeIterator&& other) noexcept; // Move assignment  
        PrimeIterator begin() const; // Begin
        PrimeIterator end(); // End

        // Comparison
		bool operator==(const PrimeIterator& other) const;
		bool operator!=(const PrimeIterator& other) const;
        bool operator<(const PrimeIterator& other) const;
        bool operator>(const PrimeIterator& other) const;
    };
};

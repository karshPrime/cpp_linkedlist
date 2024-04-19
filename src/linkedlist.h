// linked.h

#include <cstddef> // size_t
#include <cstdlib>
#include <istream> // overload >>
#include <ostream> // overload <<
#include <cassert>

#include "node.h"

template<typename T>
class LinkedList {
    private:
        size_t fSize;
        Node<T>* fHead;
        Node<T>* fTail;

    public:
        LinkedList(T aValue) noexcept 
        {
            fSize = 1;
            Node<T>* mNewElement = new Node<T>(aValue);

            // start with one element which is both head and tail
            fHead = mNewElement;
            fTail = mNewElement;
        }

        size_t Size() const noexcept { return fSize; }

        void Insert(T aValue) noexcept
        {
            fSize++;
            Node<T>* lNewElement = new Node<T>(aValue);

            lNewElement->UpdatePrev(fTail);
            lNewElement->UpdateNext(fHead);

            fHead->UpdatePrev(lNewElement);
            fTail->UpdateNext(lNewElement);

            fTail = lNewElement;
        }

        void Remove(size_t aIndex) noexcept
        {
            assert(aIndex < fSize);
            fSize--;
            Node<T>* lDelMe = fHead;

            for (size_t i = 0; i < aIndex; i++)
            {
                lDelMe = lDelMe->Next();
            }

            Node<T>* lBeforeDel = lDelMe->Prev();
            Node<T>* lAfterDel  = lDelMe->Next();

            lBeforeDel->UpdateNext(lAfterDel);
            lAfterDel->UpdatePrev(lBeforeDel);

            free(lDelMe);
        }

        T* Traversal(T(*Action)(Node<T>)) noexcept
        {
            T Result[fSize];

            Node<T>* lElements = fHead;

            for (size_t i = 0; i < fSize; i++)
            {
                Result[i] = Action(lElements);
                lElements = lElements->Next();
            }

            return Result;
        }

        template<class U>
        friend std::ostream& operator<<(std::ostream& aOStream, LinkedList<U>& aList);
};

template<typename T>
std::ostream& operator<<(std::ostream& aOStream, LinkedList<T>& aList)
{
    Node<T>* lElements = aList.fHead;

    aOStream << "[ ";

    for (size_t i = 0; i < aList.fSize; i++)
    {
        aOStream << *lElements << " ";
        lElements = lElements->Next();
    }

    return aOStream << "]";
}


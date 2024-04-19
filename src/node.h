// node.h

#include <ostream>
template<typename T>
class Node {
    private:
        T fValue;
        Node<T>* fNext;
        Node<T>* fPrev;

    public:
        Node(T aValue) noexcept : fValue(aValue)
        {
            fNext = this;
            fPrev = this;
        }

        T Value() const noexcept { return fValue; }
        Node<T>* Next() const noexcept { return fNext; }
        Node<T>* Prev() const noexcept { return fPrev; }

        void UpdateValue(T aValue) noexcept { fValue = aValue; }
        void UpdateNext(Node<T>* aNext) noexcept { fNext = aNext; }
        void UpdatePrev(Node<T>* aPrev) noexcept { fPrev = aPrev; }

        template<class U>
        friend std::ostream& operator<<(std::ostream& aOStream, Node<U>& aNode);
};

template<typename T>
std::ostream& operator<<(std::ostream& aOStream, Node<T>& aNode) 
{
    return aOStream << aNode.fValue;

}


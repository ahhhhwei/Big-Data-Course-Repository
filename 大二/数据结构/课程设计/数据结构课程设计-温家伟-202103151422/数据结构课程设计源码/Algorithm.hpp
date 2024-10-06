#pragma once
template <class BidirectionalIterator>
void Reverse(BidirectionalIterator first, BidirectionalIterator last)
{
    while ((first != last) && (first != --last))
    {
        std::iter_swap(first, last);
        ++first;
    }
}
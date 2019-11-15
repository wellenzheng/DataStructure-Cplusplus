#ifndef DICTIONARY_H
#define DICTIONARY_H

template <typename Key, typename E>
class Dictionary
{
private:
    Key key;
    E element;
    int size;

public:
    Dictionary(/* args */);
    ~Dictionary();
    void clear();
    void insert(const Key &k, const E &e);
    E remove(const Key &k);
    E find(const Key &k);
    E removeAny();
    int size();
};

#endif
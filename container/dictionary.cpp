
namespace lasd {

/* ************************************************************************** */

// DictionaryContainer

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> & travCont) {
    bool all = true;
    travCont.Traverse(
        [this, &all](const Data & value){
            all &= Insert(value);
        } 
    );
    return all;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> && mapCont) {
    bool all = true;
    mapCont.Map(
        [this, &all](Data & value){
            all &= Insert(std::move(value));
        }
    );
    return all;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> & travCont) {
    bool all = true;
    travCont.Traverse(
        [this, &all](const Data & value){
            all &= Remove(value);
        }
    );
    return all;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> & travCont) {
    bool some = false;
    travCont.Traverse(
        [this, &some](const Data & value){
            some |= Insert(value);
        }
    );
    return some;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> && mapCont) {
    bool some = false;
    mapCont.Map(
        [this, &some](Data & value){
            some |= Insert(std::move(value));
        }
    );
    return some;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> & travCont) {
    bool some = false;
    travCont.Traverse(
        [this, &some](const Data & value){
            some |= Remove(value);
        }
    );
    return some;
}

/* ************************************************************************** */

}

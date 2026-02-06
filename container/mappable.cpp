
namespace lasd {

/* ************************************************************************** */

// PreOrderMappableContainer

template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
}

/* ************************************************************************** */

// PostOrderMappableContainer

template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFun fun) {
    PostOrderMap(fun);
}

}
